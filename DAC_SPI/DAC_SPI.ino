
// SPI Library
#include <SPI.h>

#define Dac1_CS 10 // Will control CS pin on DAC1 to clock in/out values
#define Dac2_CS 2 // Will control CS pin on DAC2 to clock in/out values
#define Dac3_CS  3 // Will control CS pin on DAC3 to clock in/out values
#define Dac4_CS 4 // Will control CS pin on DAC4 to clock in/out values
#define Dac5_CS 5 // Will control CS pin on DAC5 to clock in/out values
#define Dac6_CS 6 // Will control CS pin on DAC6 to clock in/out values

#define DEBUG 1

int dacPins[] = {
  Dac1_CS,
  Dac2_CS,
  Dac3_CS,
  Dac4_CS,
  Dac5_CS,
  Dac6_CS
};
const unsigned short SetupWord = 12288; // Setup word where 4 MSB are "0011" to indicate Unbuffered Vref, 1x gain, and Active Mode
void setup() {
  //Controlling Analog Writes with CS Pin
  pinMode(Dac1_CS, OUTPUT); //CS Dac1
  pinMode(Dac2_CS, OUTPUT); //CS Dac2
  pinMode(Dac3_CS, OUTPUT); //CS Dac3
  pinMode(Dac4_CS, OUTPUT); //CS Dac4
  pinMode(Dac5_CS, OUTPUT); //CS Dac5
  pinMode(Dac6_CS, OUTPUT); //CS Dac6
  
  SPI.begin();
  Serial.begin(9600); //57600
  Serial.setTimeout(10);
}

void loop() {
  
  if(Serial.available()){
    dacwrite(1, Serial.read());
  }
  
//  if(Serial.available()){
//    int i = Serial.parseInt();
//  //  if(!Serial.available()){ return; }
//  //  int i = Serial.read();
//    if(i>0){
//  //    Serial.read();
//      int dacnum = i>>10;
//      int data = i % 1024;
//      dacwrite(dacnum, data);
//  //    dacwrite(1, i);
//      delay(1);
//    }  
//  }
  
  
  
  
  
//  while(Serial.available()){
//    Serial.write(Serial.read()); 
//  }
  
//  char buffer[5];
////  int i = Serial.parseInt();
//  int r = Serial.readBytesUntil(0xFF, buffer, 5);
//  if(r>=2){
////    int i = ((int)buffer[r-2]<<8) + buffer[r-1];
////    int dacnum = i>>10;
////    int data = i&0x03FF;
//    int dacnum =
//    dacwrite(dacnum, data);
////    Serial.println(dacnum);
////    Serial.println(data); 
//  
//    delay(1);
//  }
  
  
//  int i;
//  if(Serial.available()){
//    dacwrite(1, Serial.read());
//  }

//  dacwrite(1, random(0,1023));
//  delay(100);
//    while(i = Serial.read() == 0xFF){
//      Serial.print("tossed: ");
//      Serial.print(i);
//    }
    
////    int i = Serial.read();
////    if(i<0){return;}
//    unsigned int i = Serial.parseInt();
//    if(i==0){
////      Serial.print("!");
//      return;
//    }
////    i = i<<8;
////    int b = Serial.read();
////    if(b<0){return;}  
////    i+=b;
////    if(Serial.read()!=0){return;}
//    int dacnum = i>>10;
//    if(dacnum<1 || dacnum>6){return;}
////    int data = i & 0x03FF;
//    int data = i - (dacnum<<10);
////    Serial.print("dac:");
////    Serial.println(dacnum);
////    Serial.print("data:");
////    Serial.println(data);
//    //int dacnum = 1;
//    //int data = 512;
//    dacwrite(dacnum, data);
//    //Serial.println(out);
//    //Serial.println(val);
//    //Serial.println();
//    //TODO write to dac
////    }
//    delay(1);
}



void dacwrite(int dacnum, unsigned int data){
   if(dacnum<1 || dacnum>6){ return; }
   if(DEBUG){
     Serial.print(dacnum);
     Serial.print("-");
     Serial.println(data);
   }
   data = data<<2; // bit shifts this to the left twice to account for first two unused bits of control word
   data = data | SetupWord; // bitwise OR with setup word that has buffer, gain, and shutdown settings
   digitalWrite(dacPins[dacnum-1], LOW); // Drive CS low to clock in data
   SPI.transfer(data>>8); // send word + data
   SPI.transfer(data % 256);
   digitalWrite(dacPins[dacnum-1], HIGH); // drive high until next value is taken
}
