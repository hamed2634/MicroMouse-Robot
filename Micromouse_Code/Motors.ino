#include "Motors.h"

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
}

void backward()
{
  //Right
  analogWrite(ENA, INITIALSPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //Left
  analogWrite(ENB, INITIALSPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void AddToRightSpeed(float OUT, int maxspeed){
  //speed
  int LastSpeed = RightSpeed;
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, maxspeed);
  RightSpeed = max(RightSpeed, -maxspeed);


  //need optimize
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