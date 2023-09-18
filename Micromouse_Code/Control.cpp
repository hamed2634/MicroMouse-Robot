#include "Control.h"

float GyroRatio = 352.3333/360;

extern float AngleZ, ZError; // declare Z, ZError to assign Angle of yaw and error of it..
float LastAngleError = 0, DesiredAngle = 0;
extern volatile int Count; 
extern float RightSpeed , LeftSpeed;


void MoveStraight() {

    /*              FeedForward             */
    int DesiredSpeed = 255;
    float KpSpeed = 0.01;
    float SpeedError = DesiredSpeed - (LeftSpeed + RightSpeed)/2.0;

    int SpeedOutput = KpSpeed * SpeedError;

    /*        PID On Angle -- PD Controller         */
    float kpAng = 0.1, kdAng = 12, AngleOutput = 0, AngleError = DesiredAngle - AngleZ;
    AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ;

    AddToRightSpeed(SpeedOutput + AngleOutput,MAXSPEED);
    AddToLeftSpeed(SpeedOutput + -1 * AngleOutput, MAXSPEED);

    LastAngleError = AngleError;
    // Debug5(z, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);
}


void TurnRight() {
    StopSlowly();

    DesiredAngle -= 90 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;

    while(fabs(AngleError) > 1){
        ReadGyro();
        //pid On angle -- pcontroller
        //float kpAng = 0.2, kdAng = 10;
        //float kpAng = 0.05, kdAng = 5;
        float kpAng = 0.15, kdAng = 15;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
        AddToRightSpeed(AngleOutput,MAXTURNSPEED);
        //left += Output
        AddToLeftSpeed(-1 * AngleOutput,MAXTURNSPEED);
        LastAngleError = AngleError;
        //Debug5(z, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);
    }
    forward();
}

void TurnLeft(){
    stop();
    DesiredAngle += 90 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;
    while(fabs(AngleError) > 1){
        ReadGyro();
        //pid On angle -- pcontroller
        float kpAng = 0.05  , kdAng = 5;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
        AddToRightSpeed(AngleOutput, MAXTURNSPEED);
        //left += Output
        AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
        LastAngleError = AngleError;
        //Debug5(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
    }
    forward();
}

void TurnAround(){
    stop();
    DesiredAngle += 180 * GyroRatio;
    float AngleError = DesiredAngle - AngleZ;
    while(fabs(AngleError) > 1){
        ReadGyro();
        //pid On angle -- pcontroller
        float kpAng = 0.1  , kdAng = 0;
        AngleError = DesiredAngle - AngleZ;
        float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
        AddToRightSpeed(AngleOutput, MAXTURNSPEED);
        //left += Output
        AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
        LastAngleError = AngleError;
        //Debug5(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
    }
    forward();
}

void MoveCellForward(){
    Count = 0;
    bool Sensed = 0;
    while(GetDistance() > CellWidth){
        ReadGyro();
        ReadEncoder();
        MoveStraight();
        if(!Sensed && GetDistance() > CenterToSensing) {
            ReadIR();
            ReadUltra();
            Sensed = 1;
        }
    }
    return;
}

void MoveToCenter(){
    Count = 0;
    while(GetDistance() > StartToCenter){
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