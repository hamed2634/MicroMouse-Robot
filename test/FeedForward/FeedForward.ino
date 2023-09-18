
//-----------  A5 - SCL ;  A4 - SDA; interupt 2;
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <NewPing.h>

#define getbit(x,i) (1 & (x >> i))
#define setbit(x,i) (x |= (1 << i))
#define clrbit(x,i) (x &= ~(1 << i))

//Motors Variables
#define ENA 5
#define ENB 6
#define IN4 8
#define IN3 7
#define IN2 9
#define IN1 10
#define MAXSPEED 255
#define MAXTURNSPEED 175
#define INITIALSPEED 200
float RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;

//UltraSonic
#define MAX_MEASURED_DISTANCE 288
#define TRIGGER A0
#define ECHO A1
#define MAX_ALLOWED_DISTANCE 5
NewPing Ultra = NewPing(TRIGGER, ECHO, MAX_MEASURED_DISTANCE); // Each sensor's trigger pin, echo pin, and max distance to ping.

//gyroscope variables
Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
float z = 0;
float ZError = 0;
int DesiredAngle = 0;
float GyroRatio = 352.3333/360;

//Encoders variables
#define Encoder 3
bool LastEncoderState = 0;
volatile int Count = 0; 

//IR Sensors variables
#define RightFatalSensor 4 
#define LeftFatalSensor 11
//#define RightSensor 
//#define LeftSensor 
 
char Wall_Readings; // L - L45 - F - R45 - R

//Integration varibles
float LastTime = 0, Time, dt, Area;

//ERRORS
float LastAngleError = 0;

//pins initialize
void PinsInitialize(){
  pinMode(Encoder, INPUT);

  pinMode(RightFatalSensor, INPUT);
  pinMode(LeftFatalSensor, INPUT);
  //pinMode(RightSensor, INPUT);
  //pinMode(LeftSensor, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
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
  Area = (g.gyro.z - ZError) * dt/1000.0 * 180/M_PI;
  if(fabs(Area) > 0.01) z += Area;
  LastTime = Time;
}

void ReadEncoder(){
  bool State = digitalRead(Encoder);
  Count += State^LastEncoderState;
  LastEncoderState = State;
}

void ReadIR(){
  if(!digitalRead(LeftFatalSensor)) setbit(Wall_Readings,0);
  else clrbit(Wall_Readings,0);

  // if(!digitalRead(LeftSensor)) setbit(Wall_Readings,1);
  // else clrbit(Wall_Readings,1);

  // if(!digitalRead(RightSensor)) setbit(Wall_Readings,3);
  // else clrbit(Wall_Readings,3);

  if(!digitalRead(RightFatalSensor)) setbit(Wall_Readings,4);
  else clrbit(Wall_Readings,4);
}

void ReadUltra(){
  if(Ultra.ping_cm() < MAX_ALLOWED_DISTANCE) setbit(Wall_Readings,2);
  else clrbit(Wall_Readings,2); 
}

bool wallFront(){
  return getbit(Wall_Readings,2);
}

bool wallRight(){
  return getbit(Wall_Readings,3);
}

bool wallLeft(){
  return getbit(Wall_Readings,1);
}

float GetDistance(){
  return Count/40.0 * 3.65*PI;
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
  LeftSpeed = 0;
  RightSpeed = 0;
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
  LeftSpeed = INITIALSPEED;
  RightSpeed = INITIALSPEED;
}

void StopSlowly()
{
  //Right
  analogWrite(ENA, 100);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  //Left
  analogWrite(ENB, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  LeftSpeed = 100;
  RightSpeed = 100;
}

void backward()
{
  //Right
  analogWrite(ENA, abs(INITIALSPEED));
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  //Left
  analogWrite(ENB, abs(INITIALSPEED));
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void AddToRightSpeed(float OUT, int maxspeed){
  //speed
  int LastSpeed = RightSpeed;
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, maxspeed);
  RightSpeed = max(RightSpeed, -1 * maxspeed);


  //need optimize
  if(RightSpeed * LastSpeed <= 0){
      if(RightSpeed < 0){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else{
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
  }
  analogWrite(ENA, (int)fabs(RightSpeed));
}

void AddToLeftSpeed(float OUT, int maxspeed){
  int LastSpeed = LeftSpeed;
  LeftSpeed += OUT;
  LeftSpeed = min(LeftSpeed, maxspeed);
  LeftSpeed = max(LeftSpeed, -1 * maxspeed);
  if(LeftSpeed * LastSpeed <= 0) {
    if(LeftSpeed < 0){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else{
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
  }
  analogWrite(ENB, (int)fabs(LeftSpeed));
}

void Debug(float a, float b, float c,float d,float e){
  Serial.print(a);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.print(c);
  Serial.print(" ");
  Serial.print(d);
  Serial.print(" ");
  Serial.println(e);
}

void MoveStraight(){
  //FeedForward
  int DesiredSpeed = 255;
  float KpSpeed = 0.01;
  float SpeedError = DesiredSpeed - (LeftSpeed + RightSpeed)/2.0;

  int SpeedOutput = KpSpeed * SpeedError;


  
  // int bias = 5;
  // int SpeedOutput = Timer/1000 * bias;

  //PID On Angle -- PD Controller
  float kpAng = 0.1, kdAng = 12, AngleOutput = 0;
  float AngleError = DesiredAngle - z;
  AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative


  AddToRightSpeed(SpeedOutput + AngleOutput,MAXSPEED);
  AddToLeftSpeed(SpeedOutput + -1 * AngleOutput, MAXSPEED);
  LastAngleError = AngleError;
  Debug(z, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);

  // Timer++;
}


void TurnRight(){
  StopSlowly();
  DesiredAngle -= 90 * GyroRatio;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    //float kpAng = 0.2, kdAng = 10;
    //float kpAng = 0.05, kdAng = 5;
    float kpAng = 0.15, kdAng = 15;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput,MAXTURNSPEED);
    //left += Output
    AddToLeftSpeed(-1 * AngleOutput,MAXTURNSPEED);
    LastAngleError = AngleError;
    Debug(z, DesiredAngle, LeftSpeed , RightSpeed , AngleOutput);
  } 
  forward();
}

void TurnLeft(){
  stop();
  DesiredAngle += 90 * GyroRatio;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.05  , kdAng = 5;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput, MAXTURNSPEED);
    //left += Output
    AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
    LastAngleError = AngleError;
    //Debug(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
  } 
  forward();
}

void TurnAround(){
  stop();
  DesiredAngle += 180 * GyroRatio;
  float AngleError = DesiredAngle - z;
  while(fabs(AngleError) > 1){
    ReadGyro();
    //pid On angle -- pcontroller
    float kpAng = 0.1  , kdAng = 0;
    AngleError = DesiredAngle - z;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(AngleOutput, MAXTURNSPEED);
    //left += Output
    AddToLeftSpeed(-1 * AngleOutput, MAXTURNSPEED);
    LastAngleError = AngleError;
    //Debug(z,DesiredAngle,AngleError, LeftSpeed - AngleOutput, RightSpeed + AngleOutput);
  } 
  forward();
}


void PrintIR(){
  for(int i = 4; i >= 0; i--){
    Serial.print(getbit(Wall_Readings,i));
    Serial.print(" ");
  }
  Serial.println();
}

bool turned = 0;
bool MovedToCenter = 0; 
float CellWidth = 18;
float CenterToSensing = 5;
float X_Distance;
float Y_Distance;
float LastVisitedCenter;
bool Sensed;

void setup() 
{
  Serial.begin(115200);
  forward();
  delay(5000000);
  //while(Serial.read() != 's');
  PinsInitialize();
  GyroScopeInit();

  LastTime = millis();
}

int GetDirection(){
  return (DesiredAngle % 360) / 90;
}


void loop() 
{
  ReadGyro();
  ReadEncoder();
  MoveStraight();
  if(GetDistance() > CellWidth){
    Count = 0;
    Sensed = 0; 
    //TakeDecision of Rotating

  }
  if(!Sensed && GetDistance() > CenterToSensing){
    ReadIR();
    ReadUltra();
    Sensed = 1;
  } 

  // if(GetDistance() > 50 && !turned) {
  //   TurnRight();
  //   LeftCount = 0;
  //   turned = 1;
  // }


  // if(GetDistance() - DistanceWhenDecison > 2.00){
  //   if(wallFront()){
  //     Serial.println("Turning Around");
  //     TurnAround();
  //   }
  //   else if(!wallRight()){
  //     Serial.println("Turning Right");
  //     DistanceWhenRead = GetDistance();
  //     while(GetDistance() - DistanceWhenRead < 7.00){
  //       ReadEncoders();
  //       ReadGyro();
  //       MoveStraight();
  //     }
  //     TurnRight();
  //   }
  //   else if(!wallLeft()){
  //     Serial.println("Turning Left");
  //     DistanceWhenRead = GetDistance();
  //     while(GetDistance() - DistanceWhenRead < 7.00){
  //       ReadEncoders();
  //       ReadGyro();
  //       MoveStraight();
  //     }
  //     TurnLeft();
  //   }
  //   DistanceWhenDecison = GetDistance();
  // }



  // if(Serial.available()){
  //   char choice = Serial.read();
  //   if(choice == 's'){
  //     stop();
  //     z = 0;
  //     while(Serial.read() != 's');
  //     forward();
  //   }
  //   else if(choice == 'l'){
  //     TurnLeft();
  //   }
  //   else if(choice == 'r'){
  //     TurnRight();
  //   }
  // }

  //PrintIR();
  //Serial.println(z);

  // if(GetDistance() > 100){
  //   stop();
  //   delay(200000);
  // }







  if(Serial.available()){
    char choice = Serial.read();
    if(choice == 's'){
      stop();
      delay(10000000);
    }
  }

}
