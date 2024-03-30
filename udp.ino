#include "udp.h"

char UDPDataOperations(char *UDPData){
  char *token;

  // Serial.print("udp data: ");
  // Serial.println(UDPData);

  int i = 0;
  // Serial.print("length: ");
  // Serial.println(strlen(UDPData));
  if(UDPData[1] == '>'){
    command = strtok(UDPData, ">");
    if(command == nullptr){
      return 0;
    }
    return 1;
  }
  if(UDPData[1] == '-'){
    command = strtok(UDPData, "-");
    while (token != NULL && i<4) {
      token = strtok(NULL, " ");
      arg_list[i] = atoi(token)/100.0;
      i++;
    }
    
    // Serial.println("parsed");
    // Serial.print(command);
    // Serial.print(" ");
    // Serial.print(arg_list[0]);
    // Serial.print(" ");
    // Serial.print(arg_list[1]);
    // Serial.print(" ");
    // Serial.print(arg_list[2]);
    // Serial.print(" ");
    // Serial.println(arg_list[3]);  
    if(command == nullptr){
      return 0;
    }
    return 1;
  }
   
  
  // Serial.print("parsed: ");
  // Serial.print(command);
  // Serial.print("  core:  ");
  // Serial.println( xPortGetCoreID());

  return 0;  
}