#ifndef CONTROL_H
  #define CONTROL_H
#include "Motors.h"
#include "Sensors.h"

//ERRORS
float LastAngleError = 0;
float DesiredAngle = 0;

void MoveStraight();

void TurnRight();

void TurnLeft();
#endif