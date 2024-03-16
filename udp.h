#ifndef UDP_H
#define UDP_H

#include "WiFi.h"
#include "AsyncUDP.h"

const char* ssid = "telefon";
const char* pass = "telefonunsifresi";

AsyncUDP udp;
float arg_list[4];

char UDPDataOperations(char *UDPData);

#endif