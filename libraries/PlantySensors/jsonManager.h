#ifndef JsonManager_h
#define JsonManager_h

#include "Arduino.h"
#include <ArduinoJson.h> 

class JsonManager {
public:
  JsonManager();

 
  String createSensorDataJson(String uuid, int sensorh, float sensort, int sensorl, String code_id);

  
};

#endif