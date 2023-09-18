#ifndef SENSORS_H
  #define SENSORS_H

  //-----------  A5 - SCL ;  A4 - SDA; interupt 2;

  #include "lib.h"

  #define getbit(x,i) (1 & (x >> i))
  #define setbit(x,i) (x |= (1 << i))
  #define clrbit(x,i) (x &= ~(1 << i))



  //Encoders variables
  #define Encoder 3

  //IR Sensors variables
  #define FrontSensor 12
  #define RightFatalSensor 4 
  #define LeftFatalSensor 11
  #define RightSensor 0
  #define LeftSensor 1 

  //UltraSonic variables
  //UltraSonic
  #define MAX_MEASURED_DISTANCE 288
  #define TRIGGER A0
  #define ECHO A1
  #define MAX_ALLOWED_DISTANCE 5

  void GyroScopeInit();

  //ALL SENSORS READINGS
  void ReadGyro();

  void ReadEncoder();

  void ReadIR();

  bool wallFront();

  bool wallRight();

  bool wallLeft();

  float GetDistance();

#endif

