#include "TimerOne.h"
int ENA = 5, ENB = 10;
int IN4 = 9, IN3 = 8, IN2 = 6, IN1 = 7;

#define RightEncoder 3
#define LeftEncoder 2


#define MAXSPEED 255
#define INITIALSPEED 200

bool LastRState = 0;
bool LastLState = 0;

volatile int RightCount = 0, LeftCount = 0; 
double diskslots = 20.00;

void RightPulse(){
  RightCount++;
}
void LeftPulse(){
  LeftCount++;
}
double rotation1, rotation2;
// interrupt serviece routine
void ISR_timerone(){
  Timer1.detachInterrupt();
  Serial.print("Right Motor Speed: ");
  rotation1 = RightCount/diskslots * 60.00;
  Serial.print(rotation1);
  RightCount = 0;
  Serial.print(" - Left Motor Speed: ");
  rotation2 = LeftCount/diskslots * 60.00;
  Serial.println(rotation2);
  LeftCount = 0;
  Timer1.attachInterrupt(ISR_timerone);

}




int RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;
int LastError = 0;
double LastTime = 0;

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

void AddToRightSpeed(double OUT){
  //speed
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, MAXSPEED);
  RightSpeed = max(RightSpeed, 0);
  analogWrite(ENB, RightSpeed);
}

void AddToLeftSpeed(double OUT){
  LeftSpeed += OUT;
  LeftSpeed = min(LeftSpeed, MAXSPEED);
  LeftSpeed = max(LeftSpeed, 0);
  analogWrite(ENA, LeftSpeed);
}




void setup() 
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
  Timer1.attachInterrupt(ISR_timerone);
  forward();
  delay(50);
}

void loop() 
{

  //pid On angle -- pcontroller
  double kp = 0.1, kd = 0;
  double DesiredAngle = 30;
  double AngleError = DesiredAngle - (rotation2 - rotation1);
  double Output = kp * AngleError + kd * (AngleError - LastError); // negative

  //LastTime = time;
  LastError = AngleError;


  // Serial.print(LeftCount);
  // Serial.print(" ");
  // Serial.print(RightCount);
  // Serial.print(" ");
  // Serial.print(AngleError);
  // Serial.print(" ");
  // Serial.print(LeftSpeed);
  // Serial.print(" ");
  // Serial.print(RightSpeed);
  // Serial.print(" ");
  // Serial.println(Output);


  //right -= Output
  AddToRightSpeed(-Output);

  //left += Output
  AddToLeftSpeed(Output);

  //pid on dist

}





