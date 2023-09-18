#ifndef MOTORS_H
#define MOTORS_H

#include "lib.h"

//Motors Variables
#define ENA 6
#define ENB 5
#define IN4 10
#define IN3 9
#define IN2 8
#define IN1 7

//Motors Speeds
#define MAXSPEED 255
#define MAXTURNSPEED 150
#define INITIALSPEED 255

void forward();

void backward();

void stop();

void AddToRightSpeed(float, int);

void AddToLeftSpeed(float, int);

#endif
