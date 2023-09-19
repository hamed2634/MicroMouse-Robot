#include <NewPing.h>

NewPing Ultra = NewPing(A7, , 400);
void setup(){
  Serial.begin(115200);
}
void loop(){
  Serial.println(Ultra.ping_cm());
  delay(30);
}