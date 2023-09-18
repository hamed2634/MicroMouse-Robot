#include "Motors.h"

float RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;

//Control Functions
void stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  LeftSpeed = 0;
  RightSpeed = 0;
}

void forward()
{
  //Right
  analogWrite(ENA, INITIALSPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Left
  analogWrite(ENB, INITIALSPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  LeftSpeed = INITIALSPEED;
  RightSpeed = INITIALSPEED;
}

void StopSlowly()
{
  //Right
  analogWrite(ENA, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Left
  analogWrite(ENB, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  LeftSpeed = 100;
  RightSpeed = 100;
}

void backward()
{
  //Right
  analogWrite(ENA, abs(INITIALSPEED));
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //Left
  analogWrite(ENB, abs(INITIALSPEED));
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  LeftSpeed = -100;
  RightSpeed = -100;
}

void AddToRightSpeed(float OUT, int maxspeed){
  //speed
  int LastSpeed = RightSpeed;
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, maxspeed);
  RightSpeed = max(RightSpeed, -maxspeed);
  if(RightSpeed * LastSpeed <= 0){
      if(RightSpeed < 0){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  analogWrite(ENA, (int)fabs(RightSpeed));
}

void AddToLeftSpeed(float OUT, int maxspeed){
  int LastSpeed = LeftSpeed;
  LeftSpeed += OUT;
  LeftSpeed = min(LeftSpeed, maxspeed);
  LeftSpeed = max(LeftSpeed, -maxspeed);
  if(LeftSpeed * LastSpeed <= 0) {
    if(LeftSpeed < 0){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else{
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
  }
  analogWrite(ENB, (int)fabs(LeftSpeed));
}