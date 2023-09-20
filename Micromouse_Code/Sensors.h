#ifndef SENSORS_H
#define SENSORS_H

#include "lib.h"

// Macro to functions (bitset)
#define getbit(x,i) (1 & (x >> i))
#define setbit(x,i) (x |= (1 << i))
#define clrbit(x,i) (x &= ~(1 << i))

// Encoders variables
#define Encoder 12

// IR Sensors variables
#define RightFatalSensor 4 
#define LeftFatalSensor 1

// UltraSonic variables
#define MAX_MEASURED_DISTANCE 288
#define LeftTrigger A2
#define LeftEcho A3
#define FrontTrigger 11
#define FrontEcho 3
#define RightTrigger A0
#define RightEcho A1
#define MAX_ALLOWED_Vert_DISTANCE 5
#define MAX_ALLOWED_Horiz_DISTANCE 16


void GyroScopeInit();

void ReadGyro();

void ReadEncoder();

void ReadIR();

void ReadUltra();

bool wallFront();

bool wallRight();

bool wallLeft();

float GetDistance();

void ReadWallsUltra();

#endif