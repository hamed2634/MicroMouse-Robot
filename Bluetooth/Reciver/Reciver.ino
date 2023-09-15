void setup(){
  Serial.begin(115200);
  while(Serial.read() != 's');
}

void loop(){
  while(1){
    for(int i = 0; i < 100;i++){
      Serial.println(i);
      delay(100);
    }
  }

}