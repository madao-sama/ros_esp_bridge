#ifndef EEPROM_H
#define EEPROM_H

#include <Preferences.h>

Preferences preferences;

void writeToEEPROM(float KpVal, float KdVal, float KiVal, float KoVal);
void readFromEEPROM();

#endif