#pragma once

#include <stdint.h>
#include <stdbool.h>

#define MPU6050_ADDRESS 0x68

// MPU6050 Registers
#define MPU6050_WHO_AM_I 0x75 // return the address of device
#define MPU6050_PWR_MGMT1 0x6B
#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1A
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

bool mpu6050_init();

uint8_t mpu6050_read_register(uint8_t reg);

bool mpu6050_write_register(uint8_t reg, uint8_t data);

// Data Registers
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C

#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E

#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

#define MPU6050_TEMP_OUT_H   0x41
#define MPU6050_TEMP_OUT_L   0x42

#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_GYRO_XOUT_L  0x44

#define MPU6050_GYRO_YOUT_H  0x45
#define MPU6050_GYRO_YOUT_L  0x46

#define MPU6050_GYRO_ZOUT_H  0x47
#define MPU6050_GYRO_ZOUT_L  0x48

typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;

    int16_t temperature;

    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
} mpu6050_raw_data_t;


bool mpu6050_read_bytes(uint8_t start_register, uint8_t *buffer, uint8_t no_of_bytes);
bool mpu6050_read_raw_data(mpu6050_raw_data_t *data);


