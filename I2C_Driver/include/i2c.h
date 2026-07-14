#pragma once

void i2c_init();
void i2c_start();
void i2c_write_bit(bool bit);
bool i2c_read_bit();
void i2c_stop();