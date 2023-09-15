#include "Setup.h"

//pins initialize
void PinsInitialize(){
  pinMode(LeftEncoder, INPUT);
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


 // pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);
  // pinMode(RightSensor, INPUT);
  // pinMode(LeftSensor, INPUT);
  pinMode(FrontSensor, INPUT);
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
