#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  Serial.println("end");
  
  // Your additional MPU6050 setup code here, e.g., setting sensitivity, offsets, etc.
}

void loop() {
  // Your MPU6050 data reading and processing code here
}
