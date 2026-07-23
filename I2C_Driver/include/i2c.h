#pragma once

#include <Arduino.h>
#include <stdint.h>

void i2c_init(); // initialize i2c = same as gpio_driver_init() -> just for visibility
void i2c_start(); // start condition

void i2c_write_bit(bool bit); // MASTER writing on SDA line 
bool i2c_read_bit(); // Master reading on SDA line

bool i2c_get_ack(); // Get ACK from slave

bool i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(bool ack);

void i2c_send_ack(); // Send ACK to Slave (Write 0 on SDA Line)
void i2c_send_nack(); // Send NACK to Slave (Write 1 on SDA Line)

void i2c_stop();

// High level helpers
bool i2c_write_register(uint8_t slave_addr, uint8_t reg, uint8_t data);
bool i2c_read_register(uint8_t slave_addr, uint8_t reg, uint8_t *data);
bool i2c_write_registers(uint8_t slave_addr, uint8_t reg, const uint8_t *buffer, uint8_t len); // constant because we are only reading from pointer
bool i2c_read_registers(uint8_t slave_addr, uint8_t reg, uint8_t *buffer, uint8_t len); // no constant because we are modifying memoery
