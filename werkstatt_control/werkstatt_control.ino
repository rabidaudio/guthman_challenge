


//String com = "0 13 128 1023 512 19 ";

void setup(){
  Serial.begin(9600);
}

void loop(){
//  Serial.println( parseCommand(com) );
//parseCommand(com);
  if(Serial.available()){
    String com = Serial.readString();  //"";
    //read in the line
//    while(Serial.available()){
//      delay(3);
//      if (Serial.available() >0) {
//        char c = Serial.read();  //gets one byte from serial buffer
//        if(c == 10) break;
//        com += c; //makes the string readString
//      }
//    }
    int numbers[6];
    parseCommand(numbers, com);
    for(int i=0; i<6; i++){
      Serial.println(numbers[i]);
      //TODO write to DAC
    }
  }
// delay(100);
}

// 6 ints, each separated by a space
void parseCommand(int *numbers, String com){
  int last = 0;
//  int numbers[6];
//  Serial.println(com);
  for(int i=0; i<6; i++){//for each space
    int nextSpace = com.indexOf(" ", last);
    
    numbers[i] = com.substring(last, nextSpace).toInt();
//    Serial.print("last:");
//    Serial.print(last);
//    Serial.print(" nextSpace:");
//    Serial.println(nextSpace);
//    Serial.println(numbers[i]);
//    Serial.println("");
    last = nextSpace+1;
  }
//  return numbers;
}
