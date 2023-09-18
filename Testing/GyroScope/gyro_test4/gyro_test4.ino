 /*the closed-loop feedback control can be achieved with MPU6050 
-----------  A5 - SCL ;  A4 - SDA; interupt 2;
*/

#include <Wire.h>
#include <I2Cdev.h> 
#define MPU6050_ADDR 0x68  // Alternatively set AD0 to HIGH  --> Address = 0x69

//define DRIVE module IO Pin
  #define STBY 3  // STBY  <  ENR || ENL 
  #define IN1 8   //Left
  #define ENL 6   //PWML

  #define IN3 7   //Right
  #define ENR 5   //PWMR
 
  int highspeed=255;
  int lowspeed=10;
  int mySpeed = 200;   // speed
  
  int corrSpeedL;       //Left Motor
  int corrSpeedR;       //Right Motor
  unsigned long t1 = 0;
  unsigned long t2 = 0;

  //***** MPU6050 **********
  //A5 - SCL ;  A4 - SDA; interupt 2;
  #define MPU6050_RA_GYRO_ZOUT_H      0x47
  //uint8_t buffer[14];
  float gyroZ; // Raw register values  gyroscope
  
  unsigned long lastTime = 0;
  float dt;      //Differential time
  long gyroZ0 = 0;  //Gyro offset = mean value
  float yaw;
  float yawOld = 0;
  float gyroAngleZ = 0; //Angle variable

  

//before execute loop() function, 
void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // wake up!
  Wire.endTransmission(true);
  
  delay(2000);
  Serial.print("   ***  straight_line_4 ****");
  
  // Call this function if you need to get the IMU error values for your module
  calibration();

}

void loop() {
    
    calcYaw();
    Serial.print("Yaw : ");
    Serial.println(yaw);
}

   
  
  int16_t getRotationZ()
  {
    uint8_t buffer[14];
  I2Cdev::readBytes(MPU6050_ADDR, MPU6050_RA_GYRO_ZOUT_H, 2, buffer);
  return (((int16_t)buffer[0]) << 8) | buffer[1];
  }
    
  void calibration()
 {
  //Here we do 100 readings for gyro sensitiv Z-axis output -gyroZ, we sum them and divide them by 100.
  // gyrZ0 mean value of gyroZ raw register values in 100 ms
  
  unsigned short times = 100; //Sampling times
  for (int i = 0; i < times; i++)
  {
    gyroZ = getRotationZ();     // gyroZ - Raw register values gyroscope Z axis
    gyroZ0 += gyroZ; //sum all measured values gyroZ
  }
  gyroZ0 /= times; 
  }

 void calcYaw(){
 
  unsigned long currentTime = millis();   //current time(ms)
  //get the current timestamp in Milliseconds since epoch time which is
  dt = (currentTime - lastTime) / 1000.0; //Differential time(s)
  lastTime = currentTime;                 //Last sampling time(ms)

  gyroZ = getRotationZ();
  
  float angularZ = (gyroZ - gyroZ0) / 131.0 * dt; //angular z: =t
  if (fabs(angularZ) < 0.05) //
  {
    angularZ = 0.00;
  }
  gyroAngleZ += angularZ; //returns the absolute value of the z-axis rotazion integral 
  yaw = - gyroAngleZ;
//  Serial.print(" | GyZo = "); Serial.print(gyroZ0);
//  Serial.println();
//  Serial.print(" | GyroAngle = "); Serial.print (gyroAngleZ);
//  Serial.println();
  
 }
   
 
 
  
  