#include "Sensors.h"

//gyroscope variables
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
float AngleZ = 0, ZError = 0;


//Integration varibles
float LastTime = 0, Time, dt, Area;

//Encoder Variables
bool LastEncoderState = 0;
volatile int Count = 0; 

//UltraSonic
NewPing Ultra = NewPing(TRIGGER, ECHO, MAX_MEASURED_DISTANCE); // Each sensor's trigger pin, echo pin, and max distance to ping.


char Wall_Readings; // L - L45 - F - R45 - R

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
  if(fabs(Area) > 0.01) AngleZ += Area;
  LastTime = Time;
}

void ReadEncoder(){
  bool State = digitalRead(Encoder);
  Count += State^LastEncoderState;
  LastEncoderState = State;
}

void ReadIR(){
  if(!digitalRead(LeftFatalSensor)) setbit(Wall_Readings,0);
  else clrbit(Wall_Readings,0);

  // if(!digitalRead(LeftSensor)) setbit(Wall_Readings,1);
  // else clrbit(Wall_Readings,1);

  // if(!digitalRead(RightSensor)) setbit(Wall_Readings,3);
  // else clrbit(Wall_Readings,3);

  if(!digitalRead(RightFatalSensor)) setbit(Wall_Readings,4);
  else clrbit(Wall_Readings,4);
}

void ReadUltra(){
  if(Ultra.ping_cm() < MAX_ALLOWED_DISTANCE) setbit(Wall_Readings,2);
  else clrbit(Wall_Readings,2);
}

bool wallFront(){
  return getbit(Wall_Readings,2);
}

bool wallRight(){
  return getbit(Wall_Readings,1);
}

bool wallLeft(){
  return getbit(Wall_Readings,3);
}

float GetDistance(){
  return Count/40.0 * 3.65*PI;
}


