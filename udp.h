#ifndef UDP_H
#define UDP_H

#include "WiFi.h"
#include "AsyncUDP.h"

#define ssid       "telefon"
#define pass       "telefonunsifresi"

AsyncUDP udp;
float arg_list[4];
char *command;

char UDPDataOperations(char *UDPData);

#endif
