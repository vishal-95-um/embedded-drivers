#pragma once

#include <stdint.h>

void i2c_init();
void i2c_start();

void i2c_write_bit(bool bit);
bool i2c_read_bit();

bool i2c_get_ack();

bool i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(bool ack);

void i2c_send_ack();
void i2c_send_nack();

void i2c_stop();