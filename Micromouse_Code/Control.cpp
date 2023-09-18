#include "Control.h"

extern float z, ZError;
//ERRORS
float LastAngleError = 0;
float DesiredAngle = 0;

void MoveStraight(){
  //pid On angle -- pdcontroller
  float kpAng = 0.07, kdAng = 7;
  float AngleError = DesiredAngle - z;
  if(fabs(AngleError) < 1){
    AddToRightSpeed(30, MAXSPEED);
    AddToLeftSpeed(30, MAXSPEED);
  }
  else{
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput,MAXSPEED);
    //left += Output
    AddToLeftSpeed(-AngleOutput, MAXSPEED);
  }
  LastAngleError = AngleError;

}

void TurnRight(){
  DesiredAngle -= 90;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.07, kdAng = 7;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput,MAXTURNSPEED);
    //left += Output
    AddToLeftSpeed(-AngleOutput,MAXTURNSPEED);
    LastAngleError = AngleError;
  } 
}

void TurnLeft(){
  DesiredAngle += 90;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.07  , kdAng = 7;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput, MAXTURNSPEED);
    //left += Output
    AddToLeftSpeed(-AngleOutput, MAXTURNSPEED);
    LastAngleError = AngleError;
  } 
}
