#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>
#include <Servo.h>

Servo pitchServo;
Servo rollServo;

float q0;
float q1;
float q2;
float q3;

float rollTarget=0;
float rollActual;
float rollError;
float rollServoVal=90;

float pitchTarget=0;
float pitchActual;
float pitchError;
float pitchServoVal=90;

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 myIMU = Adafruit_BNO055();

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
myIMU.begin();
delay(1000);
int8_t temp=myIMU.getTemp();
myIMU.setExtCrystalUse(true);
rollServo.attach(2);
pitchServo.attach(3);

rollServo.write(rollServoVal);
delay(20);
pitchServo.write(pitchServoVal);
delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t system, gyro, accel, mg = 0;
myIMU.getCalibration(&system, &gyro, &accel, &mg);

imu::Quaternion quat=myIMU.getQuat();

q0=quat.w();
q1=quat.x();
q2=quat.y();
q3=quat.z();

rollActual=atan2(2*(q0*q1+q2*q3),1-2*(q1*q1+q2*q2));
pitchActual=asin(2*(q0*q2-q3*q1));

rollActual=rollActual/(2*3.141592654)*360;
pitchActual=pitchActual/(2*3.141592654)*360;

rollError=rollTarget-rollActual;
pitchError=pitchTarget-pitchActual;

if (abs(pitchError)>1.5){
  pitchServoVal=pitchServoVal+pitchError/2;
  pitchServo.write(pitchServoVal);
  delay(20);
}


if (abs(rollError)>1.5){
  rollServoVal=rollServoVal+rollError/2;
  rollServo.write(rollServoVal);
  delay(20);
}

Serial.print(rollTarget);
Serial.print(",");
Serial.print(rollActual);
Serial.print(",");
Serial.print(pitchTarget);
Serial.print(",");
Serial.print(pitchActual);
Serial.print(",");
Serial.print(accel);
Serial.print(",");
Serial.print(gyro);
Serial.print(",");
Serial.print(mg);
Serial.print(",");
Serial.println(system);

delay(BNO055_SAMPLERATE_DELAY_MS);
}