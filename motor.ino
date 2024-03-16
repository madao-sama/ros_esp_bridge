#include "motor.h"

void resetPID(){
   motor1PID.TargetRPM = 0.0;
   motor1PID.PrevEnc = motor1PID.Encoder;
   motor1PID.output = 0;
   motor1PID.PrevRPM = 0;
   motor1PID.RealRPM = 0;
   motor1PID.ITerm = 0;
   motor1PID.PrevMicros = 0;
   
   motor2PID.TargetRPM = 0.0;
   motor2PID.PrevEnc = motor2PID.Encoder;
   motor2PID.output = 0;
   motor2PID.PrevRPM = 0;
   motor2PID.RealRPM = 0;
   motor2PID.ITerm = 0;
   motor2PID.PrevMicros = 0;
   
   motor3PID.TargetRPM = 0.0;
   motor3PID.PrevEnc = motor3PID.Encoder;
   motor3PID.output = 0;
   motor3PID.PrevRPM = 0;
   motor3PID.RealRPM = 0;
   motor3PID.ITerm = 0;
   motor3PID.PrevMicros = 0;
   
   motor4PID.TargetRPM = 0.0;
   motor4PID.PrevEnc = motor4PID.Encoder;
   motor4PID.output = 0;
   motor4PID.PrevRPM = 0;
   motor4PID.RealRPM = 0;
   motor4PID.ITerm = 0;
   motor4PID.PrevMicros = 0;
}

void doPID(ts_motor_encoder_info * p) {
  long Perror;
  long output;
  p->RealRPM = (60000000.0/(micros() - p->PrevMicros))*(p->Encoder - p->PrevEnc)/EncoderPerCount;
  p->PrevMicros = micros();
  p->PrevEnc = p->Encoder;

  Perror = p->TargetRPM - p->RealRPM;

  output = (Kp * Perror - Kd * (p->RealRPM - p->PrevRPM) + p->ITerm) / Ko;

  output += p->output;
  if (output >= MAX_PWM)
    output = MAX_PWM;
  else if (output <= -MAX_PWM)
    output = -MAX_PWM;
  else
  
  p->ITerm += Ki * Perror;
  p->output = output;
  p->PrevRPM = p->RealRPM;
}

void updatePID() {  
  static unsigned long long int last_time = millis();
  if(last_time >= time_interval){
    stopMotors();
    return;
  }
  if (!moving){
    resetPID();
    stopMotors();
    return;
  }
  
  doPID(&motor1PID);
  doPID(&motor2PID);
  doPID(&motor3PID);
  doPID(&motor4PID);
  setMotorSpeed();
  // digitalWrite(2, !digitalRead(2));

}

void setMotorSpeed() {
  
  int reverse = 0;
  if (motor1PID.output < 0)
  {
    motor1PID.output = -motor1PID.output;
    reverse = 1;
  }
  if (motor1PID.output > 255){
    motor1PID.output = 255;
  }

  if      (reverse == 0) { analogWrite(motor1_in1, motor1PID.output); analogWrite(motor1_in2, 0); }
  else if (reverse == 1) { analogWrite(motor1_in2, motor1PID.output); analogWrite(motor1_in1, 0); }
  
  reverse = 0;
  if (motor2PID.output < 0)
  {
    motor2PID.output = -motor2PID.output;
    reverse = 1;
  }
  if (motor2PID.output > 255){
    motor2PID.output = 255;
  }

  if      (reverse == 0) { analogWrite(motor2_in1, motor2PID.output); analogWrite(motor2_in2, 0); }
  else if (reverse == 1) { analogWrite(motor2_in2, motor2PID.output); analogWrite(motor2_in1, 0); }
  
  reverse = 0;
  if (motor3PID.output < 0)
  {
    motor3PID.output = -motor3PID.output;
    reverse = 1;
  }
  if (motor3PID.output > 255){
    motor3PID.output = 255;
  }

  if      (reverse == 0) { analogWrite(motor3_in1, motor3PID.output); analogWrite(motor3_in2, 0); }
  else if (reverse == 1) { analogWrite(motor3_in2, motor3PID.output); analogWrite(motor3_in1, 0); }
  
  reverse = 0;
  if (motor4PID.output < 0)
  {
    motor4PID.output = -motor4PID.output;
    reverse = 1;
  }
  if (motor4PID.output > 255){
    motor4PID.output = 255;
  }

  if      (reverse == 0) { analogWrite(motor4_in1, motor4PID.output); analogWrite(motor4_in2, 0); }
  else if (reverse == 1) { analogWrite(motor4_in2, motor4PID.output); analogWrite(motor4_in1, 0); }
}

void stopMotors(){
  analogWrite(motor1_in1, 0);
  analogWrite(motor1_in2, 0);
  analogWrite(motor2_in1, 0);
  analogWrite(motor2_in2, 0);
  analogWrite(motor3_in1, 0);
  analogWrite(motor3_in2, 0);
  analogWrite(motor4_in1, 0);
  analogWrite(motor4_in2, 0);
}

void print_motor_data(){
  
  Serial.print(motor1PID.Encoder);
  Serial.print(" ");
  Serial.print(motor2PID.Encoder);
  Serial.print(" ");
  Serial.print(motor3PID.Encoder);
  Serial.print(" ");
  Serial.print(motor4PID.Encoder);
  Serial.print("\t\t output: ");

  Serial.print(motor1PID.output);
  Serial.print(" ");
  Serial.print(motor2PID.output);
  Serial.print(" ");
  Serial.print(motor3PID.output);
  Serial.print(" ");
  Serial.print(motor4PID.output);
  Serial.print("\t\t target: ");

  Serial.print(motor1PID.TargetRPM);
  Serial.print(" ");
  Serial.print(motor2PID.TargetRPM);
  Serial.print(" ");
  Serial.print(motor3PID.TargetRPM);
  Serial.print(" ");
  Serial.print(motor4PID.TargetRPM);
  Serial.print("\t\t real: ");

  Serial.print(motor1PID.RealRPM);
  Serial.print(" ");
  Serial.print(motor2PID.RealRPM);
  Serial.print(" ");
  Serial.print(motor3PID.RealRPM);
  Serial.print(" ");
  Serial.print(motor4PID.RealRPM);

  Serial.println("\t\t");

}
