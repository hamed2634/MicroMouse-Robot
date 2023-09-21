#include "Control.h"

float GyroRatio = 352.3333/360;

extern float AngleZ, ZError; // declare Z, ZError to assign Angle of yaw and error of it..
float LastAngleError = 0, DesiredAngle = 0;
extern volatile int Count; 
extern float RightSpeed , LeftSpeed;
int FatalSensorTimer = 0;

void MoveStraight() {

    // /*              FeedForward             */
    int DesiredSpeed = 125;
    float KpSpeed = 0.05;
    float SpeedError = DesiredSpeed - (LeftSpeed + RightSpeed)/2.0;

    int SpeedOutput = KpSpeed * SpeedError;

    /*        PID On Angle -- PD Controller         */
    float kpAng = 0.03, kdAng = 5, AngleOutput = 0, AngleError = DesiredAngle - AngleZ;
    AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ;

    AddToRightSpeed(SpeedOutput + AngleOutput,MAXSPEED);
    AddToLeftSpeed(SpeedOutput + -1 * AngleOutput, MAXSPEED);

    LastAngleError = AngleError;
    //Debug5(AngleZ, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);
}


void TurnRight() {

    StopSlowly(); // decrease speed to turn smooth

    DesiredAngle -= 90 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;

    while(fabs(AngleError) > 10) {
        ReadGyro();
        /*          pid On angle -- pcontroller            */
        // float kpAng = 0.2, kdAng = 10;
        float kpAng = 0.05, kdAng = 5; // best const..
        //float kpAng = 0.03, kdAng = 5; 
        // float kpAng = 0.15, kdAng = 15;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ;
        AddToRightSpeed(AngleOutput,MAXTURNSPEED);
        AddToLeftSpeed(-1 * AngleOutput,MAXTURNSPEED);
        LastAngleError = AngleError;
        // Debug5(z, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);
    }

    forward();
}

void TurnLeft() {

  StopSlowly(); // decrease speed to turn smooth

    DesiredAngle += 90 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;
    
    while(fabs(AngleError) > 1) {
        ReadGyro();
        /*          pid On angle -- pcontroller            */
        float kpAng = 0.05  , kdAng = 5;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
        AddToRightSpeed(AngleOutput, MAXTURNSPEED);
        AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
        LastAngleError = AngleError;
        //Debug5(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
    }

    forward();
}

void TurnAround(){
    StopSlowly();

    DesiredAngle += 180 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;

    while(fabs(AngleError) > 1){
        ReadGyro();
        /*          pid On angle -- pcontroller            */
        float kpAng = 0.01  , kdAng = 0.1;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ;
        AddToRightSpeed(AngleOutput, MAXTURNSPEED);
        AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
        LastAngleError = AngleError;
        //Debug5(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
    }
    forward();
}


void MoveCellForward(){
    int Timer = 0;
    while(Timer < 1500){
        MoveStraight();
        Timer++;
    }
    return;
}

void MoveFromStartToCenter(){
    Count = 0;
    while(GetDistance() < StartToCenter){
        ReadGyro();
        ReadEncoder();
        MoveStraight();
    }
    return;
}

void AdjustAlignment() {
    backward();
    AngleZ = DesiredAngle;
    delay(200);
    MoveToCenter();
    return;
}

void MoveFromCenterToSensing(){
  Count = 0;
  while(GetDistance() < CenterToSensing){
    ReadGyro();
    ReadEncoder();
    MoveStraight();
  }
}

void MoveFromSensingToCenter(){
  Count = 0;
  while(GetDistance() < SensingToCenter){
    ReadGyro();
    ReadEncoder();
    MoveStraight();
  }
}

void BrakeFromSensingToCenter(){
  Count = 0;
  while(GetDistance() < AccDistance(SensingToCenter)){
    ReadGyro();
    ReadEncoder();
    MoveStraight();
  }
  stop();
  Count = 0;
  // while(GetDistance() < SensingToCenter){
  //   ReadGyro();
  //   ReadEncoder();
  //   static float LastDistanceError = 0;
  //   float Kp = 0, Kd = 93.75;
  //   float DistanceError = SensingToCenter - GetDistance();
  //   float DistanceOutput = Kp * DistanceError + Kd * (DistanceError - LastDistanceError); 
  //   LastDistanceError = DistanceError;
  //   AddToLeftSpeed(DistanceOutput,MAXSPEED);
  //   AddToRightSpeed(DistanceOutput,MAXSPEED);
  // }
}

void ControlFatalsensors() {
  FatalSensorTimer++;
  if(FatalSensorTimer > 100){
      ReadIR();
    if(GetLeftFatal() && !GetRightFatal()) {
      DesiredAngle -= 5 * GyroRatio;
    }
    if(GetRightFatal() && !GetLeftFatal()) {
      DesiredAngle += 5 * GyroRatio;
    }
    FatalSensorTimer = 0;
  }
  //Debug2(GetLeftFatal(), GetRightFatal());
}