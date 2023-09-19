
//Motors Variables
#define ENA 5
#define ENB 6
#define IN4 7
#define IN3 8
#define IN2 9
#define IN1 10


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
  analogWrite(ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // //Left
  // analogWrite(ENB, 255);
  // digitalWrite(IN3, LOW);
  // digitalWrite(IN4, HIGH);
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


void setup() 
{
  Serial.begin(115200);
  //forward();
  delay(30);
}

void loop() {}


