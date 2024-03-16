#include "eeprom.h"

void readFromEEPROM(){
  preferences.begin("PIDValues", true); 
  Kp = preferences.getFloat("Kp", 20.0);
  Kd = preferences.getFloat("Kd", 12.0);
  Ki = preferences.getFloat("Ki", 0.0);
  Ko = preferences.getFloat("Ko", 50.0);
  preferences.end();
}

void writeToEEPROM(float KpVal, float KdVal, float KiVal, float KoVal){
  preferences.begin("PIDValues", false); 
  preferences.putFloat("Kp", KpVal);
  preferences.putFloat("Kd", KdVal);
  preferences.putFloat("Ki", KiVal);
  preferences.putFloat("Ko", KoVal);
  preferences.end();
}