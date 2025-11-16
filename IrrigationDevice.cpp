#include "IrrigationDevice.h"
#include <WiFi.h>
#include <HttpClient.h>
#include <Arduino.h>

/// @brief Constructor that assigns references to the DHT and soil sensors
IrrigationDevice::IrrigationDevice(DhtSensor& dhtSensor, SoilSalinitySensor& soil)
    : dht(dhtSensor), soil(soil) {}

/// @brief Initializes serial communication, sensors, and WiFi connection
void IrrigationDevice::setup() {
    Serial.begin(115200);
    dht.begin();
    soil.begin();
    connectWiFi();
}

/// @brief Main loop that reads sensor data, sends JSON, and handles logic
void IrrigationDevice::loop() {
  dht.update();
  soil.update();

  if (!dht.valid) {
      Serial.println("Failed to read DHT sensor.");
      delay(2000);
      return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(dht.humidity);
  if (dht.hBelowLimit()){
    Serial.print("% LOW HUMIDITY LEVELS!\n");
  }
  else {
    Serial.print("% ");
  }
  Serial.print(F("Temperature: "));
  Serial.print(dht.temperature);
  Serial.print(F("°C"));
  if (dht.tAboveLimit()){
    Serial.print(" HIGH TEMPERATURE LEVELS!\n");
  }
  else {
    Serial.print("\n");
  }

  float soilSalinity = soil.getPercentage();

  if (!soilSalinity) {
      Serial.println("Failed to read soil salinity sensor.");
      delay(2000);
      return;
  }

  Serial.print(f"Soil Salinity: %.1f %%\n", soilSalinity);

  // Generate JSON payload
  String jsonPayload = "{";
          jsonPayload += "\"device_id\":\"agro-tech-001\",";
          jsonPayload += "\"soil_moisture\":" + String(soilSalinity, 1) + ",";
          jsonPayload += "\"temperature\":" + String(dht.temperature, 1) + ",";
          jsonPayload += "\"temperatureLimit\":" + String(dht.tAboveLimit, 1) + ",";
          jsonPayload += "\"humidity\":" + String(dht.humidity, 1) + ",";
          jsonPayload += "\"humidityLimit\":" + String(dht.hBelowLimit, 1) + ",";
          jsonPayload += "\"zone\":\"C\"";
          jsonPayload += "}";

  Serial.println("Generated JSON:");
  Serial.println(jsonPayload);

  sendData(jsonPayload);

  delay(10000);
}

/// @brief Connects to the specified WiFi network
void IrrigationDevice::connectWiFi() {
  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
}

/// @brief Sends the JSON payload to the backend API
/// @param jsonPayload The formatted JSON string to send
void IrrigationDevice::sendData(const String& jsonPayload) {
    if (WiFi.status() == WL_CONNECTED) {
        HttpClient http;

        // URL must point to the private gateway IP when using Wokwi
        http.begin("http://192.168.100.7:5000/api/v1/monitoring/device-metrics"); 

        http.addHeader("Content-Type", "application/json");
        http.addHeader("x-api-key", "test-api-key-123");

        int httpResponseCode = http.POST(jsonPayload);

        if (httpResponseCode > 0) {
            Serial.print(f"POST sent. HTTP response code: %d\n", httpResponseCode);
            String response = http.getString();
            Serial.println("Server response:");
            Serial.println(response);
        } else {
            Serial.print(f"POST failed: %s\n", http.errorToString(httpResponseCode).c_str());
        }

        http.end();
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}
