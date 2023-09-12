//-----------  A5 - SCL ;  A4 - SDA; interupt 2;
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define getbit(x,i) (1 & (x >> i))
#define setbit(x,i) (x |= (1 << i))
#define clrbit(x,i) (x &= ~(1 << i))

//Motors Variables
#define ENA 6
#define ENB 10
#define IN4 9
#define IN3 11
#define IN2 7
#define IN1 8
#define MAXSPEED 100
#define INITIALSPEED 100
float RightSpeed = 0, LeftSpeed = 0;

//gyroscope variables
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
float z = 0;
float ZError = 0;
float DesiredAngle = 0;

//Encoders variables
#define RightEncoder 
#define LeftEncoder 3
bool LastRState = 0;
bool LastLState = 0;
volatile int RightCount = 0, LeftCount = 0; 

//IR Sensors variables
#define FrontSensor 12
#define RightDiagonalSensor 4 
#define LeftDiagonalSensor 5 
#define RightSensor 0
#define LeftSensor 1 
 
char IR_Readings; // L - L45 - F - R45 - R
float DistanceWhenRead;

//Integration varibles
float LastTime = 0, Time, dt, Sum;

//ERRORS
float LastAngleError = 0;

//pins initialize
void PinsInitialize(){
 // pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);
  // pinMode(RightSensor, INPUT);
  // pinMode(LeftSensor, INPUT);
  pinMode(FrontSensor, INPUT);
}

//GYROSCOPE INITIALIZE
void GyroScopeInit(){

  // Try to initialize!
  mpu.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  //calibration
  for(int i = 0; i < 200; ++i){
    mpu.getEvent(&a, &g, &temp);
    ZError += g.gyro.z;
  }
  ZError /= 200.0;
}

//ALL SENSORS READINGS
void ReadGyro(){
  mpu.getEvent(&a, &g, &temp);
  Time = millis();
  dt = Time - LastTime;
  Sum = (g.gyro.z - ZError);
  if(fabs(Sum) > 0.08) z += Sum * dt/1000.0 * 180/M_PI;
  LastTime = Time;
}

void ReadEncoders(){
  // bool State = digitalRead(RightEncoder);
  // RightCount +=   State^LastRState;
  // LastRState = State;

  bool State = digitalRead(LeftEncoder);
  LeftCount += State^LastLState;
  LastLState = State;
}

void ReadIR(){
  // if(digitalRead(RightSensor)) setbit(IR_Readings,0);
  // else clrbit(IR_Readings,0);

  if(!digitalRead(RightDiagonalSensor)) setbit(IR_Readings,1);
  else clrbit(IR_Readings,1);

  if(!digitalRead(FrontSensor)) setbit(IR_Readings,2);
  else clrbit(IR_Readings,2);

  if(!digitalRead(LeftDiagonalSensor)) setbit(IR_Readings,3);
  else clrbit(IR_Readings,3);

  // if(digitalRead(LeftSensor)) setbit(IR_Readings,4);
  // else clrbit(IR_Readings,4);
}

bool wallFront(){
  return !getbit(IR_Readings,2);
}

bool wallRight(){
  return !getbit(IR_Readings,1);
}

bool wallLeft(){
  return !getbit(IR_Readings,3);
}

float GetDistance(){
  return LeftCount/40.0 * 3.65*PI;
}


//Control Functions
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
  //Right
  analogWrite(ENA, INITIALSPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Left
  analogWrite(ENB, INITIALSPEED);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward()
{
  //Right
  analogWrite(ENA, INITIALSPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //Left
  analogWrite(ENB, INITIALSPEED);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void AddToRightSpeed(float OUT){
  //speed
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, MAXSPEED);
  RightSpeed = max(RightSpeed, -MAXSPEED);

  //need optimize
  if(RightSpeed < 0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  analogWrite(ENA, (int)fabs(RightSpeed));
}

void AddToLeftSpeed(float OUT){
  LeftSpeed += OUT;
  LeftSpeed = min(LeftSpeed, MAXSPEED);
  LeftSpeed = max(LeftSpeed, -MAXSPEED);
  if(LeftSpeed < 0){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  analogWrite(ENB, (int)fabs(LeftSpeed));
}

void MoveStraight(){
  //pid On angle -- pdcontroller
  float kpAng = 0.07, kdAng = 7;
  float AngleError = DesiredAngle - z;
  if(fabs(AngleError) < 1){
    AddToRightSpeed(30);
    AddToLeftSpeed(30);
  }
  else{
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput);
    //left += Output
    AddToLeftSpeed(-AngleOutput);
  }
  LastAngleError = AngleError;
}


void TurnRight(){
  stop();
  DesiredAngle += 90;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.07, kdAng = 7;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput);
    //left += Output
    AddToLeftSpeed(-AngleOutput);
    LastAngleError = AngleError;
  } 
}

void TurnLeft(){
  stop();
  DesiredAngle -= 90;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.08, kdAng = 7;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput);
    //left += Output
    AddToLeftSpeed(-AngleOutput);
    LastAngleError = AngleError;
  } 
}


void PrintIR(){
  for(int i = 4; i >= 0; i--){
    Serial.print(getbit(IR_Readings,i));
    Serial.print(" ");
  }
  Serial.println();
}

void setup() 
{
  Serial.begin(115200);
  PinsInitialize();
  GyroScopeInit();


  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
  LastTime = millis();
}
bool turned = 0;
void loop() 
{
  ReadEncoders();
  ReadGyro();
  MoveStraight();
  //ReadIR();
  //PrintIR();
  //Serial.println(z);

  // if(GetDistance() > 100){
  //   stop();
  //   delay(200000);
  // }

  // if(!turned && GetDistance() > 100){
  //   TurnLeft();
  //   turned = 1;
  // }
  // else if(GetDistance() > 200){
  //   stop();
  //   delay(200000);
  // }



  // ReadIR();
  // if(!wallFront()){
  //   MoveStraight();
  // }
  // else if(!wallRight()){
  //   TurnRight();
  // }
  // else if(!wallLeft()){
  //   TurnLeft();
  // }


  // if(GetDistance() - DistanceWhenRead > 18){
  //   if(!wallFront()){
  //     MoveStraight();
  //   }
  //   else if(!wallRight()){
  //     TurnRight();
  //   }
  //   else if(!wallLeft()){
  //     TurnLeft();
  //   }
  //   ReadIR();
  //   DistanceWhenRead = GetDistance();
  // }
  // else {
  //   MoveStraight();
  // }

  //MoveStraight();
  // Serial.print(wallLeft());
  // Serial.print(" ");
  // Serial.print(wallFront());
  // Serial.print(" ");
  // Serial.println(wallRight());

  
  // Serial.print(digitalRead(LeftSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(LeftDiagonalSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(FrontSensor));
  // Serial.print(" ");
  // Serial.print(digitalRead(RightDiagonalSensor));
  // Serial.print(" ");
  // Serial.println(digitalRead(RightSensor));
  
  // Serial.print(LeftCount);
  // Serial.print(" ");
  // Serial.print(RightCount);
  // Serial.print(" ");
  // Serial.print(LeftSpeed);
  // Serial.print(" ");
  // Serial.print(RightSpeed);
  // Serial.print(" ");
  // Serial.print(AngleOutput);
  // Serial.println("");

}
