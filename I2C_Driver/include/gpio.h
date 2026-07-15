#pragma once

#include <stdint.h>

void gpio_driver_init(); 

void gpio_release(uint8_t pin);

void gpio_pull_low(uint8_t pin);

bool gpio_read(uint8_t pin);