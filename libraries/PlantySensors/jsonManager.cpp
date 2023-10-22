#include "jsonManager.h"
#include "Arduino.h"

String JsonManager::createSensorDataJson(int sensorh, float sensort, int sensorl, String code_id) {

  DynamicJsonDocument jsonDoc(200);

  jsonDoc["code_id"] = code_id;
  jsonDoc["humidity"] = sensorh;
  jsonDoc["temperature"] = sensort;
  jsonDoc["light"] = sensorl;

  String jsonString;
  serializeJson(jsonDoc, jsonString);

  return jsonString;
}