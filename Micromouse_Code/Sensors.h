#ifndef SENSORS_H
  #define SENSORS_H

  //-----------  A5 - SCL ;  A4 - SDA; interupt 2;
  #include <Adafruit_MPU6050.h>
  #include <Adafruit_Sensor.h>
  #include <Wire.h>

  #define getbit(x,i) (1 & (x >> i))
  #define setbit(x,i) (x |= (1 << i))
  #define clrbit(x,i) (x &= ~(1 << i))



  //gyroscope variables
  //Adafruit_MPU6050 mpu;
  sensors_event_t a, g, temp;
  float z = 0;
  float ZError = 0;


  //Integration varibles
  float LastTime = 0, Time, dt, Area;



  //Encoders variables
  #define RightEncoder 
  #define LeftEncoder 3
  bool LastRState = 0;
  bool LastLState = 0;
  volatile int RightCount = 0, LeftCount = 0; 

  //IR Sensors variables
  #define FrontSensor 12
  #define RightDiagonalSensor 4 
  #define LeftDiagonalSensor 11
  #define RightSensor 0
  #define LeftSensor 1 

  void GyroScopeInit();

  //ALL SENSORS READINGS
  void ReadGyro();

  char IR_Readings; // L - L45 - F - R45 - R
  float DistanceWhenRead;

  void ReadEncoders();

  void ReadIR();

  bool wallFront();

  bool wallRight();

  bool wallLeft();

  float GetDistance();
#endif

