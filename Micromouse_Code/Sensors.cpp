#include "Sensors.h"

//GYROSCOPE INITIALIZE
void GyroScopeInit(){

  // Try to initialize!
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  //calibration
  for(int i = 0; i < 200; ++i){
    mpu.getEvent(&a, &g, &temp);
    ZError += g.gyro.z;
  }
  ZError /= 200.0;
}



//ALL SENSORS READINGS
void ReadGyro(){
  mpu.getEvent(&a, &g, &temp);
  Time = millis();
  dt = Time - LastTime;
  Area = (g.gyro.z - ZError) * dt/1000.0 * 180/M_PI;
  if(fabs(Area) > 0.01) z += Area;
  LastTime = Time;
}

void ReadEncoders(){
  // bool State = digitalRead(RightEncoder);
  // RightCount +=   State^LastRState;
  // LastRState = State;

  bool State = digitalRead(LeftEncoder);
  LeftCount += State^LastLState;
  LastLState = State;
}


void ReadIR(){
  // if(digitalRead(RightSensor)) setbit(IR_Readings,0);
  // else clrbit(IR_Readings,0);

  if(!digitalRead(RightDiagonalSensor)) setbit(IR_Readings,1);
  else clrbit(IR_Readings,1);

  if(!digitalRead(FrontSensor)) setbit(IR_Readings,2);
  else clrbit(IR_Readings,2);

  if(!digitalRead(LeftDiagonalSensor)) setbit(IR_Readings,3);
  else clrbit(IR_Readings,3);

  // if(digitalRead(LeftSensor)) setbit(IR_Readings,4);
  // else clrbit(IR_Readings,4);
}

bool wallFront(){
  return !getbit(IR_Readings,2);
}

bool wallRight(){
  return !getbit(IR_Readings,1);
}

bool wallLeft(){
  return !getbit(IR_Readings,3);
}

float GetDistance(){
  return LeftCount/40.0 * 3.65*PI;
}


