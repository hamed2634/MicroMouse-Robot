#include "Micromouse_Code.h"
extern int Count;
bool turned = 0;
bool turn2 = 0;
bool Sensed = 0;
extern NewPing LeftUltra,RightUltra,FrontUltra;
extern float AngleZ;
int ping = 20;

void loop() {
  MoveFromCenterToSensing();
  ReadWallsUltra();
  if(wallRight() && wallFront() && wallLeft()) {
    TurnLeft();
    TurnLeft();
    BrakeFromSensingToCenter();
  }
  else if(wallRight() && wallFront()){
    BrakeFromSensingToCenter();
    TurnLeft();
  }
  else if(wallRight()){
    BrakeFromSensingToCenter();
  }
  else {
    BrakeFromSensingToCenter();
    TurnRight();
  }



  // MoveFromCenterToSensing();
  // ReadWallsUltra();
  // BrakeFromSensingToCenter();
  // TurnRight();
  // MoveFromCenterToSensing();
  // ReadWallsUltra();
  // BrakeFromSensingToCenter();
  // TurnLeft();
  // MoveFromCenterToSensing();
  // ReadWallsUltra();
  // BrakeFromSensingToCenter();
  // stop();
  // delay(500000000);


  // forward();
  //  MoveFromSensingToCenter();
  // BrakeFromSensingToCenter();

  // //Take UltraSonic Reads


  // //if moveforward with out turns
  // //else 
  // Serial.println(GetDistance());
  // Serial.println(GetDistance());
  // for(int i = 1 ; i < 1000 ;i++){
  //   ReadEncoder();
  //   delay(1);
  // }
  // Serial.println(GetDistance());



  //timer++;
  //doIt();
  // ReadGyro();
  // ReadEncoder();
  // if(timer > 50) {
  //   ReadWallsUltra();
  //   Serial.print(wallLeft());
  //   Serial.print(" ");
  //   Serial.print(wallFront());
  //   Serial.print(" ");
  //   Serial.print(wallRight());
  //   Serial.println();
  //   timer = 0;
  // }
  //Serial.println(AngleZ);
  //Serial.print(" ");
   //Serial.println(GetDistance());
  // Serial.print(LeftUltra.ping_cm());
  // Serial.print(" ");
  // Serial.print(FrontUltra.ping_cm());
  // Serial.print(" ");
  // Serial.print(RightUltra.ping_cm());
  // Serial.println();
  //MoveStraightUltra();

  // if(GetDistance() > CellWidth) {
  //   Count = 0;
  //   Sensed = 0; 
  //   //TakeDecision of Rotating
  // }

  // if(!Sensed && GetDistance() > StartToCenter) {
  //   //ReadWallsUltra();
  //   Sensed = 1;
  //   // Serial.print(LeftUltra.ping_cm());
  //   // Serial.print(" ");
  //   // Serial.print(FrontUltra.ping_cm());
  //   // Serial.print(" ");
  //   // Serial.println(RightUltra.ping_cm());
  // } 


  // if(GetDistance() > 53 && !turned) {
  //   TurnLeft();
  //   MoveCellForward();
  //   TurnRight();
  //   turned = 1;
  //   Count = 0;
  // }
  //188
  // if(GetDistance() > 170 && !turn2){
  //   TurnRight();
  //   TurnRight();
  //   turn2 = 1;
  // }
  // if(wallRight() && wallFront() && wallLeft()) {
  //   TurnLeft();
  //   TurnLeft();
  //   timer = 100;
  // }
  // else if(wallRight() && wallFront()){
  //   TurnLeft();
  //       timer = 100;

  // }
  // else if(wallRight()){
  //   MoveStraight();
  // }
  // else {
  //   TurnRight();
  //       timer = 100;
  // }



  // ReadGyro();
  // MoveStraight();
  // ReadWallsUltra();
  // if(wallRight()) {
  //   if(wallFront()) { 
  //     TurnLeft();
  //     MoveCellForward();
  //   }
  //   else {
  //     MoveStraight();
  //   }
  // }
  // else {
  //   TurnRight();
  //   MoveCellForward();
  // }








  // ReadEncoder();
  // if(GetDistance() > 70) {
  //   stop();
  //   delay(5000000);
  // }

//  MoveStraight();
    // ReadEncoder();
    // Serial.print(Count);
    // Serial.print(" ");
    // Serial.println(GetDistance());
    // if(Serial.available()){
    //   Serial.read();
    //   Count = 0;
    // }



  
  


}
