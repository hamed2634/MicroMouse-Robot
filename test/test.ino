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

volatile int RightCount = 0, LeftCount = 0; 
int RightSpeed = INITIALSPEED, LeftSpeed = INITIALSPEED;
float LastLeftDistanceError = 0, LastRightDistanceError = 0;
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
  RightCount +=  State^LastRState;
  LastRState = State;

  State = digitalRead(LeftEncoder);
  LeftCount +=  State^LastLState;
  LastLState = State;
}



void setup() 
{
  Serial.begin(38400);
  pinMode(RightEncoder, INPUT);
  pinMode(LeftEncoder, INPUT);
  //attachInterrupt(digitalPinToInterrupt(LeftEncoder),LeftPulse,RISING);
  //attachInterrupt(digitalPinToInterrupt(RightEncoder),RightPulse,RISING);


//  stop();
}

void loop() 
{
  ReadEncoders();


  // Serial.println((double)LeftCount/RightCount);




  float RightKp = 0.5, LeftKp = 0.5, RightKd = 50, LeftKd = 50;
  float DesiredDistance = 100.00;
  float RightDistanceError = DesiredDistance - RightCount * 21.50/40.00;
  float LeftDistanceError = DesiredDistance - LeftCount * 21.50/40.00;
  float RightOutput = RightKp * RightDistanceError + RightKd * (RightDistanceError - LastRightDistanceError);
  float LeftOutput = LeftKp * LeftDistanceError + LeftKd * (LeftDistanceError - LastLeftDistanceError);

  LastRightDistanceError = RightDistanceError;
  LastLeftDistanceError = LeftDistanceError; 

  //right += Output2
  //left += Output2
  
  Serial.print(LeftCount);
  Serial.print(" ");
  Serial.print(RightCount);
  Serial.print(" ");
  Serial.print(LeftDistanceError);
  Serial.print(" ");
  Serial.print(LeftSpeed);
  Serial.print(" ");
  Serial.print(LeftOutput);
  Serial.print(" ");
  Serial.print(RightDistanceError);
  Serial.print(" ");
  Serial.print(RightSpeed);
  Serial.print(" ");
  Serial.print(RightOutput);
  Serial.println(" ");

  //right -= Output
  if(RightDistanceError > 0) AddToRightSpeed(RightOutput);
  if(LeftDistanceError > 0)  AddToLeftSpeed(LeftOutput);

}


void RightPulse(){
  RightCount++;
}
void LeftPulse(){
  LeftCount++;
}


