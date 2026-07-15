#include "gpio.h"
#include "config.h"
#include <Arduino.h>

void gpio_driver_init() {

 pinMode(sda_pin, OUTPUT_OPEN_DRAIN);
 pinMode(scl_pin, OUTPUT_OPEN_DRAIN);

 digitalWrite(sda_pin, HIGH);
 digitalWrite(scl_pin, HIGH);

}

void gpio_release(uint8_t pin) {

    digitalWrite(pin, HIGH);

}

void gpio_pull_low(uint8_t pin) {

    digitalWrite(pin, LOW);

}

bool gpio_read(uint8_t pin) {
    return digitalRead(pin);
}