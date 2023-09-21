#ifndef CONTROL_H
#define CONTROL_H

#include "Debug.h"
#include "Motors.h"
#include "Sensors.h"
#include "lib.h"

#define CenterToCenter 14
#define CenterToSensing  11.7
#define SensingToCenter 7
#define StartToCenter 2

void MoveStraight();

void TurnRight();

void TurnLeft();

void TurnAround();

void MoveToCenter();

void MoveCellForward();

void AdjustAlignment();

void MoveFromCenterToSensing();

void MoveFromStartToCenter();

void BrakeFromSensingToCenter();

void MoveFromSensingToCenter();

void ControlFatalsensors();

#endif