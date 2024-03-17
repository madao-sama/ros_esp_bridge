#include "encoder.h"

/*
* Encoders interrupt funcs
*/

void shaft_moved_1(){
  static int last_run = 0;
  if (millis()-last_run>5){
    if (digitalRead(encoder1_c2)==1){
      motor1PID.Encoder++;
      motor1PID.dir="CW";
      }
    if (digitalRead(encoder1_c2)==0){
      motor1PID.Encoder--; 
      motor1PID.dir="CCW";}
    last_run=millis();
  }
}

void shaft_moved_2(){
  static int last_run = 0;
  if (millis()-last_run>5){
    if (digitalRead(encoder2_c2)==1){
      motor2PID.Encoder++;
      motor2PID.dir = "CW";
      }
    if (digitalRead(encoder2_c2)==0){
      motor2PID.Encoder--; 
      motor2PID.dir="CCW";}
    last_run=millis();
  }
}

void shaft_moved_3(){
  static int last_run = 0;
  if (millis()-last_run>5){
    if (digitalRead(encoder3_c2)==1){
      motor3PID.Encoder++;
      motor3PID.dir="CW";
      }
    if (digitalRead(encoder3_c2)==0){
      motor3PID.Encoder--; 
      motor3PID.dir="CCW";}
    last_run=millis();
  }
}

void shaft_moved_4(){  

  static int last_run = 0;
  if (millis()-last_run>5){
    if (digitalRead(encoder4_c2)==1){
      motor4PID.Encoder++;
      motor1PID.dir="CW";
      }
    if (digitalRead(encoder4_c2)==0){
      motor4PID.Encoder--; 
      motor4PID.dir="CCW";}
    last_run=millis();
  }
}

void resetEncoders(){
  motor1PID.Encoder = 0;
  motor2PID.Encoder = 0;
  motor3PID.Encoder = 0;
  motor4PID.Encoder = 0;
}

void print_encoder_values(){
  Serial.print("counter1 : ");
  Serial.print(motor1PID.Encoder);
  Serial.print(" direction1 : ");
  Serial.print(motor1PID.dir);  

  Serial.print("  counter2 : ");
  Serial.print(motor2PID.Encoder);
  Serial.print(" direction2 : ");
  Serial.print(motor2PID.dir);  

  Serial.print("  counter3 : ");
  Serial.print(motor3PID.Encoder);
  Serial.print(" direction3 : ");
  Serial.print(motor3PID.dir);  

  Serial.print("  counter4 : ");
  Serial.print(motor4PID.Encoder);
  Serial.print(" direction4 : ");
  Serial.println(motor4PID.dir);  
}
