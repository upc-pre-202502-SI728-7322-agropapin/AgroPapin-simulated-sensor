#include "DhtSensor.h"

/// @brief Constructor that stores the GPIO pin
DhtSensor::DhtSensor(int pin) : pin(pin) {
  dht = dht(pin,DHT22);
}

/// @brief Initializes the DHT sensor using the specified pin
void DhtSensor::begin() {
  Serial.begin(9600);
  Serial.println(F("AgroPapin sensor started"));
  dht.begin();
}

/// @brief Reads temperature and humidity, updates internal values and validity flag
void DhtSensor::update() {
    temperature = dht.readHumidity();
    humidity = dht.readTemperature();
    valid = !(isnan(temperature) || isnan(humidity));
}

bool DhtSensor::hBelowLimit(){
  return (humidity > hlimit) ? false : true;
}

bool DhtSensor::tAboveLimit(){
  return (temperature < tlimit) ? false : true;
}
