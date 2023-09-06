#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

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


void AddToRightSpeed(float OUT){
  //speed
  RightSpeed += OUT;
  RightSpeed = min(RightSpeed, MAXSPEED);
  RightSpeed = max(RightSpeed, -MAXSPEED);
  if(RightSpeed < 0){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  analogWrite(ENB, (int)fabs(RightSpeed));
}

void AddToLeftSpeed(float OUT){
  LeftSpeed += OUT;
  LeftSpeed = min(LeftSpeed, MAXSPEED);
  LeftSpeed = max(LeftSpeed, -MAXSPEED);
  if(LeftSpeed < 0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  analogWrite(ENA, (int)fabs(LeftSpeed));
}

void TurnRight(){
  stop();
  while(1){
    //pid On angle -- pcontroller
    float kpAng = 0.5, kdAng = 10;
    float DesiredAngle = 90;
    float AngleError = DesiredAngle - x;
    float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
    LastAngleError = AngleError;
    //right -= Output
    AddToRightSpeed(AngleOutput);
    //left += Output
    AddToLeftSpeed(-AngleOutput);
    if(fabs(AngleError) < 1) return;
  }
}


void ReadEncoders(){
  bool State = digitalRead(RightEncoder);
  RightCount +=  (RightSpeed > 0 ? 1 : -1) * State^LastRState;
  LastRState = State;

  State = digitalRead(LeftEncoder);
  LeftCount += (LeftSpeed > 0 ? 1 : -1) * State^LastLState;
  LastLState = State;
}

void ReadGyro(){
  mpu.getEvent(&a, &g, &temp);
  Time = millis();
  dt = Time - LastTime;

  Sum = (g.gyro.x - XError);
  if(fabs(Sum) > 0.05) x += Sum * dt/1000.0 * 180/M_PI;
  LastTime = Time;

  Serial.print(dt);
  Serial.print(" ");
  Serial.print(x);
  Serial.print(" ");
}



void setup() 
{
  Serial.begin(115200);
  pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);


  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
  //while(Serial.read() != 's');

    // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
      Serial.println("Failed to find MPU6050 chip");
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");

  //calibration
  for(int i = 0; i < 200; i++){
    mpu.getEvent(&a, &g, &temp);
    XError += g.gyro.x;
  }
  XError/=200.0;
  forward();
  delay(30);
  LastTime = millis();
//  stop();
}

void loop() 
{
  //ReadEncoders();
  ReadGyro();

  //pid On angle -- pcontroller
  float kpAng = 0.8, kdAng = 10;
  float DesiredAngle = 0;
  float AngleError = DesiredAngle - x;
  float AngleOutput = kpAng * AngleError + kdAng * (AngleError - LastAngleError) ; // negative
  LastAngleError = AngleError;

  // Serial.print(LeftCount);
  // Serial.print(" ");
  // Serial.print(RightCount);
  // Serial.print(" ");
  //Serial.print(" HAMEd ");


  Serial.print(AngleError);
  Serial.print(" ");
  Serial.print(LeftSpeed);
  Serial.print(" ");
  Serial.print(RightSpeed);
  Serial.print(" ");
  Serial.print(AngleOutput);
  Serial.println("");



  if(Time > 5000){
    TurnRight();
  }
  // right -= Output
  AddToRightSpeed(AngleOutput);
  //left += Output
  AddToLeftSpeed(-AngleOutput);
  delay(30);

}


void RightPulse(){
  RightCount++;
}
void LeftPulse(){
  LeftCount++;
}


