#ifndef RELAY_ACTUATOR_H
#define RELAY_ACTUATOR_H

#include "ModestIoT.h"

/// @brief Controls a relay connected to a digital output pin
class RelayActuator : public Actuator {
public:
    /// @brief Constructor with relay pin
    /// @param pin GPIO pin connected to the relay
    RelayActuator(int pin);

    /// @brief Initializes the relay pin as output
    void begin();

    /// @brief Activates or deactivates the relay
    /// @param state True to turn ON, False to turn OFF
    void activate(bool state) override;

    /// @brief Returns the last state of the relay
    bool getState() const;

private:
    int pin;         // GPIO pin connected to the relay
    bool lastState;  // Stores the last activation state
};

#endif
