#ifndef CONTROL_H
  #define CONTROL_H
#include "Motors.h"
#include "Sensors.h"
#include "lib.h"

#define CellWidth 18
#define CenterToSensing  5
#define StartToCenter 2

void MoveStraight();

void TurnRight();

void TurnLeft();

void AdjustAlignment();

void MoveToCenter();

void MoveCellForward();
#endif