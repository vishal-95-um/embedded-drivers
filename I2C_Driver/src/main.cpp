#include <Arduino.h>
#include "mpu6050.h"


void setup() {
  Serial.begin(115200);
}

void loop() {

 MPU6050_Data data;

 if(mpu6050_read_all(&data)) {

  Serial.println("Accelration X Axis:", data->accel_x);
  Serial.println("Accelration Y Axis:", data->accel_y);
  Serial.println("Accelration Z Axis:", data->accel_z);

 } else {
  Serial.println("Sensor not working");
 }

delay(1000);
}

