int ENA = 5, ENB = 10;
int IN4 = 9, IN3 = 8, IN2 = 7, IN1 = 6;

#define RightEncoder 3
#define LeftEncoder 2
#define MAXSPEED 255
#define INITIALSPEED 0

#define UPLEFT IN2
#define UPRIGHT IN4
#define DOWNLEFT IN1
#define DOWNRIGHT IN3
bool LastRState = 0;
bool LastLState = 0;
int LastTime = 0;

volatile int RightCount = 0, LeftCount = 0; 
int RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;
float LastDistanceError = 0, LastAngleError = 0;

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
  analogWrite(ENA, 150);
  analogWrite(ENB, 255);

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
  analogWrite(ENB, abs(RightSpeed));
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
  analogWrite(ENA, abs(LeftSpeed));
}

void ReadEncoders(){
  bool State = digitalRead(RightEncoder);
  RightCount +=  (RightSpeed > 0 ? 1 : -1) * State^LastRState;
  LastRState = State;

  State = digitalRead(LeftEncoder);
  LeftCount += (LeftSpeed > 0 ? 1 : -1) * State^LastLState;
  LastLState = State;
}



void setup() 
{
  Serial.begin(115200);
  pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);
  while(Serial.read() != 's');
  LastTime = millis();


//  stop();
}

void loop() 
{
  ReadEncoders();


  // Serial.println((double)LeftCount/RightCount);
  float KpDist = 5.100000, KdDist = 100.00000;
  float DesiredDistance = 100.00;
  float DistanceError = DesiredDistance - ((RightCount+LeftCount)/2.00) * 21.50/40.00;
  float DistanceOutput = KpDist * DistanceError + KdDist * (DistanceError - LastDistanceError); // negative
  LastDistanceError = DistanceError;

  //pid On angle -- pcontroller
  float kpAng = 1, kdAng = 1, C = 40;
  float DesiredAngle = 0;
  float AngleError = DesiredAngle * 38.00 - (LeftCount - RightCount);
  float AngleOutput = (kpAng * AngleError + kdAng * (AngleError - LastAngleError)) * DistanceOutput / 255.00 ; // negative
  LastAngleError = AngleError;

  //right += Output2
  //left += Output2
  int Time = millis();
  if(Time - LastTime > 100){
    Serial.print(LeftCount);
    Serial.print(" ");
    Serial.print(RightCount);
    Serial.print(" ");
    Serial.print(DistanceError);
    Serial.print(" ");
    Serial.print(AngleError);
    Serial.print(" ");
    Serial.print(LeftSpeed);
    Serial.print(" ");
    Serial.print(RightSpeed);
    Serial.print(" ");
    Serial.print(DistanceOutput);
    Serial.print(" ");
    Serial.print(AngleOutput);
    Serial.println(" ");
  }



  //right -= Output
  AddToRightSpeed(DistanceOutput - AngleOutput);
  //left += Output
  AddToLeftSpeed(DistanceOutput + AngleOutput);

}


void RightPulse(){
  RightCount++;
}
void LeftPulse(){
  LeftCount++;
}


