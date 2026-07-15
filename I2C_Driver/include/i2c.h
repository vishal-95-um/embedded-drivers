#pragma once

#include <stdint.h>

void i2c_init(); // initialize i2c = same as gpio_driver_init() -> just for visibility
void i2c_start(); // start condition

void i2c_write_bit(bool bit); // MASTER writing on SDA line 
bool i2c_read_bit(); // Master reading on SDA line

bool i2c_get_ack(); // Get ACK from slave

bool i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(bool ack);

void i2c_send_ack();
void i2c_send_nack();

void i2c_stop();