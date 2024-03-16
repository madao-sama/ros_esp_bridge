#include "ros_esp_bridge.h"
#include "encoder.h"
#include "motor.h"
#include "udp.h"
#include "eeprom.h"

char argv1[100];
int arg = 0;
int tx_index = 0;
const char *delim = " ";

void resetCommand() {
  memset(argv1, 0, sizeof(argv1));
  arg = 0;
  tx_index = 0;
}

void runCommand(char cmd) {
  Serial.println("runcommand içi");
    // char *p_argv1 = argv1;
    // char *token;
    // int i = 1;

  switch(cmd) {
    case READ_ENCODERS:
      Serial.print(motor1PID.Encoder);
      Serial.print(" ");
      Serial.print(motor2PID.Encoder);
      Serial.print(" ");
      Serial.print(motor3PID.Encoder);
      Serial.print(" ");
      Serial.println(motor4PID.Encoder);
      break;

    case GET_PID_VALUES:
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
      Serial.println("OK");
      break;

    case STOP_MOTORS:
      stopMotors();
      resetPID();
      moving = 0;
      Serial.println("OK");
      break;

    case MOTOR_SPEEDS:
      Serial.println("motor speed");
      // Serial.println(argv1);
      // token = strtok(p_argv1, delim);
      // arg_list[0] = (atof(token))/100.0;
      // while (token != NULL && i<4) {
      //   token = strtok(NULL, delim);
      //   arg_list[i] = atoi(token)/100.0;
      //   i++;
      // }

      lastMotorCommand = millis();
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
        Serial.println("OK"); 
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
      
      Serial.println("Update PID");

      Kp = arg_list[0];
      Kd = arg_list[1];
      Ki = arg_list[2];
      Ko = arg_list[3];

      Serial.print(Kp);
      Serial.print(Kd);
      Serial.print(Ki);
      Serial.println(Ko);

      writeToEEPROM(arg_list[0], arg_list[1], arg_list[2], arg_list[3]);
      Serial.println("OK");
      break;
  }
  resetCommand();
  Serial.println("run command sonu");
}

hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer(){
  updatePID();
}

void attachInterruptTask(void *pvParameters) {
  My_timer = timerBegin(0, 8, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000000, true);
  timerAlarmEnable(My_timer); //Just Enable
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  retryConnectionPoint:
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("WiFi Failed");
      delay(200);
      goto retryConnectionPoint;
  }
  if(udp.listenMulticast(IPAddress(239,1,2,3), 8080)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {

          Serial.print("Default datas: ");
          Serial.print(packet.length());
          Serial.println();
          //reply to the client
          char *tmp = reinterpret_cast <char *>(packet.data());
          Serial.print("tmp: ");
          Serial.println(tmp);
          runCommand(UDPDataOperations(tmp));
          // Serial.print(cmd);
          // Serial.print(arg_list[0]);
          // Serial.print(arg_list[1]);
          // Serial.print(arg_list[2]);
          // Serial.println(arg_list[3]);          
      });
  }

  readFromEEPROM();
  attachInterrupt(digitalPinToInterrupt(encoder1_c1), shaft_moved_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder2_c1), shaft_moved_2, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder3_c1), shaft_moved_3, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoder4_c1), shaft_moved_4, FALLING);
  pinMode(encoder1_c2,INPUT);
  pinMode(encoder2_c2,INPUT);
  pinMode(encoder3_c2,INPUT);
  pinMode(encoder4_c2,INPUT);
  pinMode(2, OUTPUT);
  stopMotors();
  delay(100);
  xTaskCreatePinnedToCore(attachInterruptTask, "Attach Interrupt Task", 2000, NULL, 6, NULL, 0);
}

void loop() {
  // print_encoder_values();
  while(WiFi.status() == WL_CONNECTED){
    sprintf(udp_message, "%d %d %d %d", motor1PID.Encoder, motor2PID.Encoder, motor3PID.Encoder, motor4PID.Encoder);
    udp.broadcastTo(udp_message, 8080);
    delay(50);
  }
  Serial.println("connection lost");
  
  // while (Serial.available()) {
  //   // Read the next character
  //   char chr = Serial.read();
  //   // Terminate a command with a CR
  //   if (chr == '>') {
  //     if (arg == 1){
  //       argv1[tx_index] = NULL;
  //     }
  //     Serial.println("runCommand");
  //     runCommand();
  //     resetCommand();
  //   }
  //   // Use spaces to delimit parts of the command
  //   else if (chr == '-') {
  //     // Step through the arguments
  //     if (arg == 0){
  //       arg = 1;
  //     }
  //     else if (arg == 1)  {
  //       argv1[tx_index] = NULL;
  //       tx_index = 0;
  //     }
  //     continue;
  //   }
  //   else {
  //     if (arg == 0) {
  //       // The first arg is the single-letter command
  //       cmd = chr;
  //     }
  //     else if (arg == 1) {
  //       // Subsequent arguments can be more than one character
  //       argv1[tx_index] = chr;
  //       tx_index++;
  //     }
  //   }
  // }
}
