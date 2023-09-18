#include "Setup.h"
extern float LastTime;
//pins initialize

void PinsInitialize(){
  pinMode(Encoder, INPUT);

  pinMode(RightFatalSensor, INPUT);
  pinMode(LeftFatalSensor, INPUT);
  //pinMode(RightSensor, INPUT);
  //pinMode(LeftSensor, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}


void setup() 
{
  Serial.begin(115200);
  PinsInitialize();
  GyroScopeInit();

  // while(1){
  //   forward();
  //   delay(2000);
  //   // backward();
  //   // delay(2000);
  // }


  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
  LastTime = millis();
}
