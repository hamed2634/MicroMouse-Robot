//-----------  A5 - SCL ;  A4 - SDA; interupt 2;
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

float LastTime = 0, Time, dt, Sum;
float z = 0;
float ZError = 0;
float DesiredAngle = 0;

int ENA = 6, ENB = 11;
int IN4 = 9, IN3 = 10, IN2 = 7, IN1 = 8;

#define RightEncoder 4
#define LeftEncoder 3
#define MAXSPEED 255
#define INITIALSPEED 255

#define UPLEFT IN2
#define UPRIGHT IN4
#define DOWNLEFT IN1
#define DOWNRIGHT IN3
bool LastRState = 0;
bool LastLState = 0;

volatile int RightCount = 0, LeftCount = 0; 
float RightSpeed = 0, LeftSpeed = 0;
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
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
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


void ReadGyro(){
  mpu.getEvent(&a, &g, &temp);
  Time = millis();
  dt = Time - LastTime;

  Sum = (g.gyro.z - ZError);
  if(fabs(Sum) > 0.007) z += Sum * dt/1000.0 * 180/M_PI;
  LastTime = Time;
  //Serial.println(z);
}


void TurnRight(){
  DesiredAngle += 90;
  float AngleError = DesiredAngle - z;
  AddToRightSpeed(-600);
  AddToLeftSpeed(600);  
  float time = millis();
  while(fabs(AngleError) > 33){
    ReadGyro();
    AngleError = DesiredAngle - z;
  }
  Serial.println(millis() - time);
  stop();
  delay(1000000); 
}


void ReadEncoders(){
  bool State = digitalRead(RightEncoder);
  RightCount +=   State^LastRState;
  LastRState = State;

  State = digitalRead(LeftEncoder);
  LeftCount += State^LastLState;
  LastLState = State;
}


float first;
void setup() 
{
  Serial.begin(115200);
  pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  //while(!Serial);


  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
    // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(100);
      Serial.println("Failed to find MPU6050 chip");
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  //calibration
  for(int i = 0; i < 200; i++){
    mpu.getEvent(&a, &g, &temp);
    ZError += g.gyro.z;
  }
  ZError/=200.0;
  first = millis();
  LastTime = millis();

}
char turned = 0;
void loop() 
{
  ReadEncoders();
  ReadGyro();

  //pid On angle -- pcontroller
  float kpAng = 0.07, kdAng = 7;
  float AngleError = DesiredAngle - z;
  if(fabs(AngleError) < 1){
    AddToRightSpeed(30);
    AddToLeftSpeed(30);
  }else{
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    AddToRightSpeed(-AngleOutput);
    //left += Output
    AddToLeftSpeed(AngleOutput);
  }
  LastAngleError = AngleError;



  // Serial.print(LeftCount);
  // Serial.print(" ");
  // Serial.print(RightCount);
  // Serial.print(" ");
  //Serial.print(" HAMEd ");


  // Serial.print(" ");
  // Serial.print(LeftSpeed);
  // Serial.print(" ");
  // Serial.print(RightSpeed);
  // Serial.print(" ");
  // Serial.print(AngleOutput);
  // Serial.println("");



  // if(Time > 5000){
  //   TurnRight();
  // }
  // right -= Output


// //  delay(30);

//   // 1 = 3.3*PI
//   // 1 -- > 40
   float dist = LeftCount/40.0 * 3.65*PI;
  

  if(dist > 50){
    TurnRight();
    stop();
    delay(100000);
  }
 
}


void RightPulse(){
  RightCount++;
}
void LeftPulse(){
  LeftCount++;
}
