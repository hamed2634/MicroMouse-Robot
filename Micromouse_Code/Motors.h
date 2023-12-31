#ifndef MOTORS_H
#define MOTORS_H

#include "lib.h"

//Motors Variables
#define ENA 5
#define ENB 6
#define IN4 7
#define IN3 8
#define IN2 9
#define IN1 10

//Motors Speeds
#define MAXSPEED 125
#define MAXTURNSPEED 150
#define INITIALSPEED 125

void forward();

void backward();

void stop();

void StopSlowly();

void AddToRightSpeed(float, short);

void AddToLeftSpeed(float, short);

#endif
