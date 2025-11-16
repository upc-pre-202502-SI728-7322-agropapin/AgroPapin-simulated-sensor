#ifndef SOIL_SALINITY_SENSOR_H
#define SOIL_SALINITY_SENSOR_H

#include <Arduino.h>

/// @brief Handles analog readings and salinity percentage calculation from a soil salinity sensor
class SoilSalinitySensor {
public:
    /// @brief Constructor
    /// @param analogPin Analog input pin connected to the sensor
    /// @param minValue Raw analog value for 100% salinity (too much conductivity)
    /// @param maxValue Raw analog value for 0% salinity (no conductivity)
    SoilSalinitySensor(uint8_t analogPin, float minValue = 0.0, float maxValue = 10.0);

    /// @brief Initializes the sensor (if needed)
    void begin();

    /// @brief Reads the analog value and updates the percentage
    void update();

    /// @brief Returns the latest soil salinity percentage (0–100%)
    float getPercentage() const;

private:
    uint8_t pin;       // Analog input pin
    float minRaw;        // Minimum expected raw value (wet soil)
    float maxRaw;        // Maximum expected raw value (dry soil)
    float percentage;  // Calculated soil salinity percentage
};

#endif