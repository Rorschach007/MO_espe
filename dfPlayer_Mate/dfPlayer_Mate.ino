#include <Servo.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
int btn1 = 8;
int btn2 = 7;
int btn3 = 6;
int btnw4 = 2;
int btnw5 = 4;
int btnw6 = 3;
int servo_1 = 53;
int servo_2 = 52;
//int servo_3 = 50;
int ojos =13;
int pos = 105;
Servo servo;
int pin_analogico = A1; 
int pin_digital = A0;
int var=0;
int lect1;
int lect2;
int lect3;
int lect4;
int lect5;
int lect6;
int lect7;
int lect8;
//int lect9;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
//SoftwareSerial nodeMCU(3,2);
DFRobotDFPlayerMini teamMO;
void printDetail(uint8_t type, int value);
void setup(){
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);       //serial de comunicacion
  pinMode(btn1,INPUT);
  pinMode(btn2,INPUT);
  pinMode(btn3,INPUT);
  pinMode(servo_1, INPUT_PULLUP);
  pinMode(servo_2, INPUT_PULLUP);
//  pinMode(servo_3, INPUT_PULLUP);
  pinMode(ojos, OUTPUT);
  servo.attach(9);
  pinMode(btnw4,INPUT_PULLUP);
  pinMode(btnw5,INPUT_PULLUP);
  pinMode(btnw6,INPUT_PULLUP);
  pinMode(btn3,INPUT);
  pinMode(pin_analogico,INPUT_PULLUP);
  pinMode(pin_digital,INPUT);
  Serial.println("Testing ...");
  if(!teamMO.begin(mySoftwareSerial)){  //|
    while(true){delay(0);               //|   MP3Player
    }                                   //|
   }                                    //|
  teamMO.volume(30);
  teamMO.play(7);
 }
  void loop(){
    for (pos = 70; pos <= 140; pos += 1){
      servo.write(pos);              
      delay(20);             
   }
  lect1 = digitalRead(btn1);
  lect2 = digitalRead(btn2);
  lect3 = digitalRead(btn3);  
  lect4 = digitalRead(btnw4);  
  lect5 = digitalRead(btnw5);  
  lect6 = digitalRead(btnw6);  
  lect7 = digitalRead(servo_1);  
  lect8 = digitalRead(servo_2);  
//  lect9 = digitalRead(servo_3);  
  Serial.print("lect1 = ");
  Serial.println(lect1);
  Serial.print("lect2 = ");
  Serial.println(lect2);
  Serial.print("lect3 = ");
  Serial.println(lect3);
  Serial.print("lect4 = ");
  Serial.println(lect4);
  Serial.print("lect5 = ");
  Serial.println(lect5);
  Serial.print("lect6 = ");
  Serial.println(lect6);
  Serial.print("lect7 = ");
  Serial.println(lect7);
  Serial.print("lect8 = ");
  Serial.println(lect8);

  digitalWrite(ojos, LOW);
  if (digitalRead(pin_digital) == HIGH){ //fotosensor
  Serial.println("no hay luz");
  digitalWrite(ojos, LOW);
  }
  else{
   Serial.println("hay luz"); //fotosensor
   digitalWrite(ojos, HIGH);
  }
  delay(0);
  if(lect1==1){
    var = 1;
  }
  if(lect2 == 1){
    var = 2;
  }
  if(lect3 ==1){
    var = 3;
  }
  if(lect4 == 1){
    var = 4;
  }
  if(lect5 == 1){
    var = 5;
  }
  if(lect6 == 1){
    var = 6;
  }
  if(lect7 == 1){
    var = 7;
  }
  if(lect8 == 1){
    var = 8;
  }
//  if(lect9 == 1){
//    var = 0;
//  }
  Serial.print("var = ");
  Serial.println(var);
  switch(var){
    case 1:
    teamMO.play(1);
    delay(2500);
    var =0;
    break;
    case 2:
    teamMO.play(2);
    delay(2500);
    var =0;
    break;
    case 3:
    teamMO.play(3);
    delay(2500);
    var =0;
    break;
    case 4:
    teamMO.play(4);
    servo.write(70);//derecha
    delay(2500);
    var =0;
    break;
    case 5:
    teamMO.play(5);
    servo.write(105);//centro
    delay(2500);
    var =0;
    break;
    case 6:
    teamMO.play(6);
    servo.write(140);//izquierda
    delay(2500);
    var =0;
    break;
    case 7:
    servo.write(70);//derecha
    delay(110);
    var =0;
    break;
    case 8:
    servo.write(105);//centro
    delay(110);
    var =0;
    break;
    case 9:
    servo.write(140);//izquierda
    delay(110);
    var =0;
    break;
  }
     for (pos = 140; pos >= 70; pos -= 1) {
      servo.write(pos);              
      delay(20);                       
   }
}
void printDetail(uint8_t type, int value){
}
