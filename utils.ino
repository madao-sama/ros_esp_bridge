#include "utils.h"

void resetCommand() {
  memset(argv1, 0, sizeof(argv1));
  arg = 0;
  tx_index = 0;
}

void runCommand() {
  // Serial.println("runcommand içi");
    // char *p_argv1 = argv1;
    // char *token;
    // int i = 1;

  char *msg;
  msg = (char*)malloc(64*sizeof( char));
  switch(*command) {
    case READ_ENCODERS:
      sprintf(msg, "encoder:%d %d %d %d>", motor1PID.Encoder, motor2PID.Encoder, motor3PID.Encoder, motor4PID.Encoder);
      udp.broadcastTo(msg, 8080);
      Serial.print(motor1PID.Encoder);
      Serial.print(" ");
      Serial.print(motor2PID.Encoder);
      Serial.print(" ");
      Serial.print(motor3PID.Encoder);
      Serial.print(" ");
      Serial.println(motor4PID.Encoder);
      free(msg);
      break;

    case GET_PID_VALUES:
      sprintf(msg, "pid:%04f %04f %04f %04f>", Kp, Kd, Ki, Ko);
      udp.broadcastTo(msg, 8080);
      Serial.print("Kp: ");
      Serial.print(Kp);
      Serial.print(" Kd: ");
      Serial.print(Kd);
      Serial.print(" Ki: ");
      Serial.print(Ki);
      Serial.print(" Ko: ");
      Serial.println(Ko);
      break;
      
    case RESET_ENCODERS:
      resetEncoders();
      resetPID();
      udp.broadcastTo("resetencoder>", 8080);
      // Serial.println("OK");
      break;

    case STOP_MOTORS:
      stopMotors();
      resetPID();
      moving = 0;
      // Serial.println("OK");
      break;

    case MOTOR_SPEEDS:  
      last_message_time = millis();
      // Serial.println("motor speed");
      // Serial.println(argv1);
      // token = strtok(p_argv1, delim);
      // arg_list[0] = (atof(token))/100.0;
      // while (token != NULL && i<4) {
      //   token = strtok(NULL, delim);
      //   arg_list[i] = atoi(token)/100.0;
      //   i++;
      // }

      if (arg_list[0] == 0 && arg_list[1] == 0 && arg_list[2] == 0 && arg_list[3] == 0) {
        stopMotors();
        resetPID();
        moving = 0;
        break;
      }
      else {
        moving = 1;
        motor1PID.TargetRPM = arg_list[0];
        motor2PID.TargetRPM = arg_list[1];
        motor3PID.TargetRPM = arg_list[2];
        motor4PID.TargetRPM = arg_list[3];
        // Serial.print(motor1PID.TargetRPM);
        // Serial.print(" ");
        // Serial.print(motor2PID.TargetRPM);
        // Serial.print(" ");
        // Serial.print(motor3PID.TargetRPM);
        // Serial.print(" ");
        // Serial.println(motor4PID.TargetRPM);
        // Serial.println("OK"); 
        break;
      }     

    case UPDATE_PID:
      // Serial.println(argv1);
      // token = strtok(p_argv1, delim);
      // arg_list[0] = (atof(token))/100.0;
      // Serial.print(arg_list[0]);
      // Serial.print( " ");
      // while (token != NULL && i<4) {
      //   token = strtok(NULL, delim);
      //   arg_list[i] = atoi(token)/100.0;
      //   i++;
      // }
      // Serial.print(arg_list[1]);
      // Serial.print( " ");
      // Serial.print(arg_list[2]);
      // Serial.print( " ");
      // Serial.println(arg_list[3]);
      
      // Serial.println("Update PID");

      Kp = arg_list[0];
      Kd = arg_list[1];
      Ki = arg_list[2];
      Ko = arg_list[3];

      // Serial.print(Kp);
      // Serial.print(Kd);
      // Serial.print(Ki);
      // Serial.println(Ko);

      writeToEEPROM(arg_list[0], arg_list[1], arg_list[2], arg_list[3]);
      // Serial.println("OK");
      break;
  }
  resetCommand();
  
  // Serial.println("run command sonu");
}

// void IRAM_ATTR onTimer(){
//   updatePID();
// }

void attachInterruptTask(void *pvParameters) {
  // My_timer = timerBegin(1, 8, true);
  // timerAttachInterrupt(My_timer, &onTimer, true);
  // timerAlarmWrite(My_timer, 1000000, true);
  // timerAlarmEnable(My_timer); //Just Enable
  // vTaskDelete(NULL);
  int last_time = 0;
  while(1){
    if(millis()-last_message_time >= message_time_interval){
      moving = 0;
      stopMotors();
      digitalWrite(2, LOW);
    }
    else {
      while(millis()-last_time >= 50){
        updatePID();
        last_time = millis();
      }
    }
    delay(1);
  }
}
