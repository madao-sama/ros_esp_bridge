#include "ros_esp_bridge.h"
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "encoder.h"
#include "motor.h"
#include "udp.h"
#include "eeprom.h"

void setup() {
  Serial.begin(115200);
  // while(1){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        delay(200);
    }
    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        Serial.println("WiFi Connected");
        // break;
    }
  // }
  delay(10);
  Serial.println("UDP Initializing");
  if(udp.listenMulticast(IPAddress(239,1,2,3), 8080)) {
      Serial.print("UDP Listening on IP: ");
      Serial.println(WiFi.localIP());
      udp.onPacket([](AsyncUDPPacket packet) {
          
          char *tmp = reinterpret_cast <char *>(packet.data());
          // Serial.print("tmp: ");
          // Serial.println(tmp);
          // Serial.print("outside length: ");
          // Serial.println(strlen(tmp));
          if(UDPDataOperations(tmp)){
            runCommand();
          }
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
    // Serial.print("reset reason:  ");
    // Serial.println(ESP.getFreeHeap());
    // Serial.print("block size: ");
    // Serial.println(ESP.getMaxFreeBlockSize());
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
