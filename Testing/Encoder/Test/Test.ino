void setup(){
  Serial.begin(115200);
  pinMode(1,INPUT);
}
void loop(){
  Serial.println(digitalRead(1));
}