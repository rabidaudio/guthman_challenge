// ATMEL ATTINY45 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2)  Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

#include <SoftwareSerial.h>

#define PEAK 1023 //675 if 5V

#define pinX A1 //7
#define pinY A2 //3
#define pinZ A3 //2

#define pinTX 5 //6
#define pinRX 1 //1

#define LED 0 //5

#define DELAYTIME 1

//#define NAME "KittenBall 1"

SoftwareSerial bluetooth(pinTX, pinRX);

int last_speed = 0;

void setup(){
  pinMode(LED, OUTPUT);
//  digitalWrite(LED, LOW);

  bluetooth.begin(9600);
  
  
//  bluetooth.println("hello");
//  delay(1000);
  
//  ref = fast_distance_formula(a
//  sendAndBlockForResponse("AT");
}


void loop(){
  int x = analogRead(pinX);
  int y = analogRead(pinY);
  int z = analogRead(pinZ);
//  float fx= mapf(x, 0, PEAK, -3, 3); // 3.3/5 * 1023 =~ 675
//  float fy= mapf(y, 0, PEAK, -3, 3);
//  float fz= mapf(z, 0, PEAK, -3, 3);
  
//  bluetooth.print(fx);
//  bluetooth.print(" ");
//  bluetooth.print(fy);
//  bluetooth.print(" ");
//  bluetooth.println(fz);

  bluetooth.print(four_digit(x));
  bluetooth.print(" ");
  bluetooth.print(four_digit(y));
  bluetooth.print(" ");  
  bluetooth.println(four_digit(z));
  
  //fast aproximation of euclidian distance
  x=(x-512);
  y=(y-512);
  z=(z-512);
//  int current_speed = x*x+y*y+z*z;
  int q = fast_distance_formula(x,y,z);
  if(q>last_speed){
    last_speed = q;
  }
  if(last_speed<0){
    last_speed = 0;
  }
  analogWrite(LED, last_speed);
  last_speed -= 10;
//  bluetooth.println(q);
  
  delay(DELAYTIME);
}


int fast_distance_formula(long x, long y, long z){
  int m = (x+y+z-170);//round(sqrt(x*x+y*y+z*z)-100);
  return m<20 ? 0 : (m>1023 ? 1023 : m);
//  return (x*x+y*y+z*z)/((abs(x)+abs(y)+abs(z))/3)/2;
//  return min((x*x+y*y+z*z)/((abs(x)+abs(y)+abs(z))/3), 1023);
// return (x*x+y*y+z*z);
}

//float mapf(long x, long in_min, long in_max, long out_min, long out_max){
//  return (float)((x - in_min) * (out_max - out_min)) / (float)((in_max - in_min)) + out_min;
//}

String four_digit(int number){
  String result = "";
  if(number<10){
    result+="0";
  }
  if(number<100){
    result+="0";
  }
  if(number<1000){
    result+="0";
  }
  result+=number;
  return result;
}
