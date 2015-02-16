


void setup(){
  Serial.begin(57600); //9600);
  Serial.setTimeout(100);
}

void loop(){
  char buffer[5];
//  int i = Serial.parseInt();
  int r = Serial.readBytesUntil(0xFF, buffer, 5);
  if(r>=2){
    int i = ((int)buffer[r-2]<<8) + buffer[r-1];
    int out = i>>10;
    int val = i&0x03FF;
    Serial.println(out);
    Serial.println(val);
    Serial.println();
    delay(1);
  }
  //TODO write to dac
}
