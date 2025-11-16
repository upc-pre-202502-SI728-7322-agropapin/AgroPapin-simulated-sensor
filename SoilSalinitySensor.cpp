#include "SoilSalinitySensor.h"

/// @brief Constructor that sets pin and calibration range
SoilSalinitySensor::SoilSalinitySensor(uint8_t analogPin, float minValue, float maxValue)
    : pin(analogPin), minRaw(minValue), maxRaw(maxValue), percentage(0.0f) {}

/// @brief Configures the analog pin as input
void SoilSalinitySensor::begin() {
    pinMode(pin, INPUT);
}

/// @brief Reads analog value and calculates soil salinity percentage
void SoilSalinitySensor::update() {
    int raw = analogRead(pin);
    percentage = 100.0f * (maxRaw - raw) / (maxRaw - minRaw);
    percentage = constrain(percentage, 0.0f, 100.0f);
}

/// @brief Returns the last calculated salinity percentage
float SoilSalinitySensor::getPercentage() const {
    return percentage;
}
