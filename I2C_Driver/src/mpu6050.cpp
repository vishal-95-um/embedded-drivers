#include "mpu6050.h"
#include "i2c.h"

uint8_t mpu6050_read_register(uint8_t reg) {
    
    uint8_t data;

    i2c_start();

    i2c_write_byte((MPU6050_ADDRESS<<1) | 0); // 7 bit address + write bit

    i2c_write_byte(reg);

    i2c_start();

    i2c_write_byte((MPU6050_ADDRESS<<1) | 1); // address again because R/W bit always exist with address

    data = i2c_read_byte(false); // read one byte and then send NACK

    i2c_stop();

    return data;

}

bool mpu6050_write_register(uint8_t reg, uint8_t data) {

    i2c_start();

    i2c_write_byte((MPU6050_ADDRESS)<<1 | 0);

    i2c_write_byte(reg);

    bool ack = i2c_write_byte(data);

    i2c_stop();

    return ack;
}

bool mpu6050_init() {

    // 1. Verify Identity
    uint8_t who_am_i = mpu6050_read_register(MPU6050_WHO_AM_I);
    if(who_am_i != 0x68) {
        return false;
    }

    // 2. Wake up the sensor
    if(!mpu6050_write_register(MPU6050_PWR_MGMT1, 0x01)) {
        return false;
    }

    // 3. Set sample rate = 100hz
    if(!mpu6050_write_register(MPU6050_SMPLRT_DIV, 9)){
        return false;
    }

    // 4. Configure digital low pass filter
    if(!mpu6050_write_register(MPU6050_CONFIG, 0x03)) {
        return false;
    }

    // 5. Accelerometer: ±2g
    if(!mpu6050_write_register(MPU6050_ACCEL_CONFIG, 0x00)) {
        return false;
    }

    // 6. Gyroscope: ±250 °/s
    if(!mpu6050_write_register(MPU6050_GYRO_CONFIG, 0x00)) {
        return false;
    }

    return true;
}

bool mpu6050_read_bytes(uint8_t starting_regiser, uint8_t *buffer, uint8_t no_of_bytes) {

    i2c_start();

    if(!i2c_write_byte(MPU6050_ADDRESS << 1) | 0) {
      i2c_stop();
      return false;
    }

    if(!i2c_write_byte(starting_regiser)) {
      i2c_stop();
      return false;
    }

    i2c_start();

    if(!i2c_write_byte((MPU6050_ADDRESS<<1) | 1)) {
        i2c_stop();
        return false;
    }

    for(uint8_t i = 0; i<no_of_bytes; i++) {

        bool ack = (i < no_of_bytes - 1);

        buffer[i] = i2c_read_byte(ack);
    }
}