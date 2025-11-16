#ifndef IRRIGATION_DEVICE_H
#define IRRIGATION_DEVICE_H

#include "ModestIoT.h"
#include "DhtSensor.h"
#include "SoilSalinitySensor.h"

/// @brief Device that manages irrigation based on environmental sensor data
class IrrigationDevice : public Device {
public:
    /// @brief Constructor with sensor references
    /// @param dhtSensor Reference to the DHT sensor
    /// @param soil Reference to the soil salinity sensor
    IrrigationDevice(DhtSensor& dhtSensor, SoilSalinitySensor& soil);

    /// @brief Initializes sensors and WiFi
    void setup() override;

    /// @brief Main logic loop: reads sensors, sends data, controls irrigation
    void loop() override;

private:
    DhtSensor& dht;                 // Temperature and humidity sensor
    SoilSalinitySensor& soil;      // Soil salinity sensor

    /// @brief Connects the device to WiFi
    void connectWiFi();

    /// @brief Sends sensor data to the backend as a JSON payload
    void sendData(const String& jsonPayload);
};

#endif
