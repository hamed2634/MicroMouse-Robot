#define Encoder 13
#define IN1 4
#define IN2 5
#define EN 3
#define SPEED 255
long Count = 0, LastCount = 0;
int State = 0, LastState = 0;
float LastTime = 0;
void forward()
{
  analogWrite(EN, SPEED);

  //LEFT
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

}

void ReadEncoders(){
  bool State = digitalRead(Encoder);
  Count += State^LastState;
  LastState = State;
}



void setup() 
{
  Serial.begin(115200);
  pinMode(Encoder, INPUT);
  forward();
  delay(30);
  LastTime = millis();

//  stop();
}
void loop(){
  LastCount = Count;
  bool State = digitalRead(Encoder);
  if(State != LastState){
    float Time = millis();
    float speed = 1/ (Time - LastTime) * 1000 * 60/40.0;
    LastState = State;
    Serial.println(speed);
    LastTime = millis();
  }

  //Serial.print(" ");

  //Serial.println(Count);

}
