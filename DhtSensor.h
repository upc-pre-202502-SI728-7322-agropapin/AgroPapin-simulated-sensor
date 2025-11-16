#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include "DHT.h"

/// @brief Class that encapsulates interaction with a DHT sensor (e.g., DHT11/DHT22)
class DhtSensor {
public:
    /// @brief Constructor that sets the GPIO pin connected to the DHT sensor
    /// @param pin GPIO pin number where the DHT sensor data line is connected
    DhtSensor(int pin);

    /// @brief Initializes the DHT sensor (should be called in setup)
    void begin();

    /// @brief Updates the temperature and humidity readings from the sensor
    void update();

    bool tAboveLimit();
    bool hBelowLimit();

    /// @brief Latest temperature reading in degrees Celsius
    float temperature = 0;

    /// @brief Latest humidity reading in percentage (%)
    float humidity = 0;

    /// @brief Flag indicating if the last reading was successful
    bool valid = false;

private:
    /// @brief GPIO pin where the sensor is connected
    int pin;

    /// @brief maximum temperature before critical level is reached in degrees Celsius
    float tlimit = 255;

    /// @brief maximum humidity before critical level is reached in percentage (%)
    float hlimit = 255;

    /// @brief Internal DHT object used to interact with the sensor
    DHT dht;
};

#endif
