#include "i2c.h"
#include "gpio.h"
#include "config.h"
#include <Arduino.h>

void i2c_init() {

    gpio_driver_init();

}

void i2c_start() {
    
    // make sure bus is idle
    gpio_release(sda_pin);
    gpio_release(scl_pin);
    delayMicroseconds(i2c_delay_us);

    // start condition (SDA = LOW, SCL = HIGH)
    gpio_pull_low(sda_pin);
    delayMicroseconds(i2c_delay_us);
    
    // SCL = LOW so data transfer can happen after this (SDA only allowed to change when SCL is HIGH)
    gpio_pull_low(scl_pin);
    delayMicroseconds(i2c_delay_us);

}

void i2c_write_bit(bool bit) {
    
    // write on sda line
    if(bit) {
        gpio_release(sda_pin);
    } else {
        gpio_pull_low(sda_pin);
    }

    delayMicroseconds(i2c_delay_us);
    
    // SCL = HIGH so slave can read it
    gpio_release(scl_pin);
    delayMicroseconds(i2c_delay_us);

    // reading by slave happens here (when scl is high)
    
    // SCL = LOW so after this data transaction can happen 
    gpio_pull_low(scl_pin);
    delayMicroseconds(i2c_delay_us);

}

bool i2c_read_bit() {
    // let slave control sda
    gpio_release(sda_pin);
    delayMicroseconds(i2c_delay_us);
   
    // raise SCL so master can read
    gpio_release(scl_pin);
    delayMicroseconds(i2c_delay_us);

    bool bit = gpio_read(sda_pin);
    
    // SCL = LOW so after this data transaction can happen 
    gpio_pull_low(scl_pin);
    delayMicroseconds(i2c_delay_us);
    
    return bit;
}

bool i2c_get_ack() {
    return !i2c_read_bit(); // read bit from slave for ACK , NOT so ACK(0) can be converted to True
}


bool i2c_write_byte(uint8_t data) {

    for (int i=7; i>=0; i--) {
        bool bit = (data >> i) & 0x01;
        i2c_write_bit(bit);
    }

    return i2c_get_ack();
}

uint8_t i2c_read_byte(bool ack) {
    uint8_t data = 0;

    for (int i = 7; i>=0; i--) {
        bool bit = i2c_read_bit();

        data |= (bit << i);
    }

    if (ack)
    i2c_send_ack();
    else
    i2c_send_nack();

    return data;
}

void i2c_send_ack() {
    i2c_write_bit(false);
}

void i2c_send_nack() {
    i2c_write_bit(true);
}


void i2c_stop() {
    // STOP condition ==> SDA = LOW to HIGH while SCL is HIGH
    
    gpio_pull_low(sda_pin);
    delayMicroseconds(i2c_delay_us);
    
    gpio_release(scl_pin);
    delayMicroseconds(i2c_delay_us);

    gpio_release(sda_pin);
    delayMicroseconds(i2c_delay_us);

}

bool i2c_write_register(uint8_t slave_addr, uint8_t reg, uint8_t data) {

    i2c_start();
    
    if(!i2c_write_byte((slave_addr << 1) | 0)) {
       goto error;
    }

    if(!i2c_write_byte(reg)) {
        goto error;
    }

    if(!i2c_write_byte(data)) {
        goto error;
    }
    
    i2c_stop();
    return true;
    
error:
    i2c_stop();
    return false;

}

bool i2c_read_register(uint8_t slave_addr, uint8_t reg, uint8_t *data) {
    
    i2c_start();

    if(!i2c_write_byte((slave_addr<<1) | 0)) {
        goto error;
    }

    if(!i2c_write_byte(reg)) {
        goto error;
    }

    i2c_start();

    if(!i2c_write_byte((slave_addr<<1) | 1)) {
        goto error;
    }

    *data = i2c_read_byte(false);

    i2c_stop();

    return true;

error:
    i2c_stop();
    return false;
    
}

bool i2c_write_registers(uint8_t slave_addr, uint8_t reg, const uint8_t *buffer, uint8_t len) {

    if (len == 0)
    return false;

    i2c_start();

    if(!i2c_write_byte((slave_addr << 1) | 0)){
        goto error;
    }

    if(!i2c_write_byte(reg)) {
        goto error;
    }

    for(uint8_t i = 0; i<len; i++) {
        if(!i2c_write_byte(buffer[i])){
            goto error;
        };
    }

    i2c_stop();
    return true;

    error:
      i2c_stop();
      return false;
}

bool i2c_read_registers(uint8_t slave_addr, uint8_t reg, uint8_t *buffer, uint8_t len) {

    if (len == 0)
    return false;

    i2c_start();

    if(!i2c_write_byte((slave_addr << 1) | 0)){
        goto error;
    }

    if(!i2c_write_byte(reg)) {
        goto error;
    }

    i2c_start();

    if(!i2c_write_byte((slave_addr << 1) | 1)){
        goto error;
    }

    for(uint8_t i = 0; i<len; i++) {
        bool ack = i < (len - 1);
        buffer[i] = i2c_read_byte(ack);
    }
    
    i2c_stop();
    return true;

    error:
      i2c_stop();
      return false;

}