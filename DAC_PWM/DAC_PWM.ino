

#define COUNT 6

int controlPins[COUNT] = {
  3,
  5,
  6,
  9,
  10,
  11
};

void setup(){
  int p;
  for(p=0; p<COUNT; p++){
    pinMode(controlPins[p], OUTPUT);
    analogWrite(controlPins[p], 10);
  }
  Serial.begin(9600);
}

void loop(){
//  unsigned int i;
//  for(i=0; i<1024;i++){
//    analogWrite(controlPins[1], i);
//    delay(100);
//  }
  if(Serial.available()){
    int i = Serial.parseInt();
  //  if(!Serial.available()){ return; }
  //  int i = Serial.read();
    if(i>0){
  //    Serial.read();
      int dacnum = i>>10;
      unsigned int data = (i & 0xFF);
      if(dacnum<1 || dacnum>6){ return; }
      Serial.print(controlPins[dacnum-1]);
      Serial.print("-");
      Serial.println(data);
      analogWrite(controlPins[dacnum-1], data);
//      delay(1);
    }  
  }
  
}

