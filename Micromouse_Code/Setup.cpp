#include "Setup.h"
extern float LastTime;
//pins initialize
extern char Wall_Readings;
void PinsInitialize() {
  // Encoder
  pinMode(Encoder, INPUT);

  // //Fatalsensors
  // pinMode(RightFatalSensor, INPUT);
  // pinMode(LeftFatalSensor, INPUT);

  //ControlMotors
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void setup()  {
  Serial.begin(115200);
  //while(Serial.read() != 's');
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
  setbit(Wall_Readings,3);
  forward();
  //MoveFromStartToCenter();
  LastTime = millis();
}
