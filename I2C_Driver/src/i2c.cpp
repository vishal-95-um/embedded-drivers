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
    // STOP condition = SDA = LOW to HIGH while SCL is HIGH
    
    gpio_pull_low(sda_pin);
    delayMicroseconds(i2c_delay_us);
    
    gpio_release(scl_pin);
    delayMicroseconds(i2c_delay_us);

    gpio_release(sda_pin);
    delayMicroseconds(i2c_delay_us);

}

