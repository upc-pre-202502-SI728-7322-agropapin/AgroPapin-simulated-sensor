#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Structure to hold chip state
typedef struct {
  pin_t pin;    // Analog output pin    
  uint32_t voltage_attr;      // salinity's parts per thousand attribute value (simulated)
} chip_data_t;

/// @brief Timer callback that updates analog output based on salinity sensor's ppt
void chip_timer_callback(void *data) 
{
  chip_data_t *chip_data = (chip_data_t*)data;
  
  // Read the current salinity attribute value
  float salinity = attr_read(chip_data->voltage_attr);

  // Convert the salinity value (0.0-10.0) to voltage (0-5V)
  float volts = 5 * (salinity / 10.0);
  // Write the voltage to the analog output pin
  pin_dac_write(chip_data->pin, volts);
  
}

/// @brief Initializes the chip: sets up attributes, pin, and timer
void chip_init() 
{
  // Allocate memory for chip state
  chip_data_t *chip_data = (chip_data_t*)malloc(sizeof(chip_data_t));

  // Initialize analog output pin
  chip_data->pin = pin_init("A0", ANALOG);
  chip_data->voltage_attr = attr_init_float("salinity", 1.0);

  // Set up a repeating timer to periodically update the analog output
  const timer_config_t config = 
  {
    .callback = chip_timer_callback,
    .user_data = chip_data,
  };

  timer_t timer_id = timer_init(&config);
  timer_start(timer_id, 1000, true); // Run every 1000ms
}
