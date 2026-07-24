#include <Arduino.h>
#include "mpu6050.h"


void setup()
{
    Serial.begin(115200);

    if(!mpu6050_init())
    {
        Serial.println("MPU6050 initialization failed");
        while(1);
    }

    Serial.println("MPU6050 initialized");
}


void loop()
{
    MPU6050_Data data;


    if(mpu6050_read_all(&data))
    {
        Serial.print("Acceleration X Axis: ");
        Serial.println(data.accel_x);

        Serial.print("Acceleration Y Axis: ");
        Serial.println(data.accel_y);

        Serial.print("Acceleration Z Axis: ");
        Serial.println(data.accel_z);

        Serial.print("Gyro X Axis: ");
        Serial.println(data.gyro_x);

        Serial.print("Gyro Y Axis: ");
        Serial.println(data.gyro_y);

        Serial.print("Gyro Z Axis: ");
        Serial.println(data.gyro_z);
    }
    else
    {
        Serial.println("Sensor not working");
    }


    delay(1000);
}