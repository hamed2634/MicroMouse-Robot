#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Adafruit_MPU6050 mpu;
// sensors_event_t a, g, temp;

float LastTime = 0, Time, dt, Sum;
float x = 0;
float XError = 0;

int ENA = 5, ENB = 10;
int IN4 = 9, IN3 = 8, IN2 = 7, IN1 = 6;

#define RightEncoder 3
#define LeftEncoder 4
#define MAXSPEED 255
#define INITIALSPEED 200

#define UPLEFT IN2
#define UPRIGHT IN4
#define DOWNLEFT IN1
#define DOWNRIGHT IN3
bool LastRState = 0;
bool LastLState = 0;

volatile int RightCount = 0, LeftCount = 0; 
float RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;
float LastAngleError = 0;

void stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}



void forward()
{
  analogWrite(ENA, INITIALSPEED);
  analogWrite(ENB, INITIALSPEED);

  //LEFT
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Right
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward()
{
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void setup() 
{
   Serial.begin(115200);
  // while(Serial.read() != 's');


  forward();
  delay(30);
}

void loop() 
{


}

