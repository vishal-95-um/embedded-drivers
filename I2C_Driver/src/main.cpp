#include <Arduino.h>
#include "mpu6050.h"


void setup() {
  
}

void loop() {
  int16_t ax, ay, az;

  if(mpu6050_read_raw_accelration(&ax, &ay, &az)) {
    printf("AX = %d\n", ax);
    printf("AY = %d\n", ay);
    printf("AZ = %d\n", az);
  }
}

