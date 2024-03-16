#include "udp.h"

char UDPDataOperations(char *UDPData){
  char *command, *token;
  Serial.print("udp data: ");
  Serial.println(UDPData);

  int i = 0;
  if(UDPData[1] == '>'){
    command = strtok(UDPData, ">");
    Serial.println("parsed");
    Serial.println(command);
    return *command;
  } 
  command = strtok(UDPData, "-");
  while (token != NULL && i<4) {
    token = strtok(NULL, " ");
    arg_list[i] = atoi(token)/100.0;
    i++;
  }

  Serial.println("parsed");
  Serial.print(command);
  Serial.print(" ");
  Serial.print(arg_list[0]);
  Serial.print(" ");
  Serial.print(arg_list[1]);
  Serial.print(" ");
  Serial.print(arg_list[2]);
  Serial.print(" ");
  Serial.println(arg_list[3]);   
  return *command;  

}