#include "Micromouse_Code.h" 
extern int Count;
void loop() 
{
  ReadEncoder();
  ReadGyro();
  MoveStraight();
  //ReadIR();
  //PrintIR();
  //Serial.println(z);

  // if(GetDistance() > 100){
  //   stop();
  //   delay(200000);
  // }

  if(GetDistance() > 100){
    TurnLeft();
    Count = 0;
  }
  
  // ReadIR();
  // if(!wallFront()){
  //   MoveStraight();
  // }
  // else if(!wallRight()){
  //   TurnRight();
  // }
  // else if(!wallLeft()){
  //   TurnLeft();
  // }


  // if(GetDistance() - DistanceWhenRead > 18){
  //   if(!wallFront()){
  //     MoveStraight();
  //   }
  //   else if(!wallRight()){
  //     TurnRight();
  //   }
  //   else if(!wallLeft()){
  //     TurnLeft();
  //   }
  //   ReadIR();
  //   DistanceWhenRead = GetDistance();
  // }
  // else {
  //   MoveStraight();
  // }

  //MoveStraight();
  // Serial.print(wallLeft());
  // Serial.print(" ");
  // Serial.print(wallFront());
  // Serial.print(" ");
  // Serial.println(wallRight());

  
  // Serial.print(digitalRead(LeftSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(LeftDiagonalSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(FrontSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(RightDiagonalSensor));
  // Serial.print(" ");
  // Serial.println(digitalRead(RightSensor));
  
  // Serial.print(LeftCount);
  // Serial.print(" ");
  // Serial.print(RightCount);
  // Serial.print(" ");
  // Serial.print(LeftSpeed);
  // Serial.print(" ");
  // Serial.print(RightSpeed);
  // Serial.print(" ");
  // Serial.print(AngleOutput);
  // Serial.println("");

}
