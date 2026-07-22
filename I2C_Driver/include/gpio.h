#pragma once

#include <Arduino.h>
#include <stdint.h>

void gpio_driver_init(); // Initialie G21 and G22 for I2C ie make both open drain and make both high for idle

void gpio_release(uint8_t pin); 

void gpio_pull_low(uint8_t pin);

bool gpio_read(uint8_t pin);