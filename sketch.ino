#include "ModestIoT.h"
#include "DhtSensor.h"
#include "SoilSalinitySensor.h"
#include "IrrigationDevice.h"

// Create sensor instances with their respective GPIO pins
DhtSensor dht(2);          // DHT22 connected to GPIO 15
SoilSalinitySensor soil(3); // Soil salinity sensor connected to GPIO 34

// Create the irrigation device with sensor references
IrrigationDevice device(dht, soil);

/// @brief Arduino setup function. Initializes sensors and network.
void setup() {
  device.setup();
}

/// @brief Arduino loop function. Reads sensors and sends data.
void loop() {
  device.loop();
}