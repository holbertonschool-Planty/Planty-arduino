#ifndef PlantySensors_h
#define PlantySensors_h

#include "Arduino.h"
#include "BluetoothSerial.h"
#include "WiFi.h"
#include "ArduinoJson.h"
#include "HTTPClient.h"
#include "WiFiClientSecure.h"
#include "EEPROM.h"



extern DynamicJsonDocument planty;
extern const char* id;
extern int sensorl;
extern const int addressForSSID;
extern const int addressForPassword;
extern char ssid[64];
extern char password[64];

class PlantySensors {
public:
  void retrieveStoredCredentials();
  PlantySensors(BluetoothSerial& bt, int offset);
  void connectToWiFi();
  bool isCredentialsValid();
  void readSensors();
  void sendSensorDataToAPI();
  /*void putSensorData(const char* apiEndpoint);*/
  bool isUUID(const char* str);
  
 
  

private:
  BluetoothSerial& SerialBT;
  int sensor_offset;
  DynamicJsonDocument dataJson;
};

class SensorData {
public:
  SensorData(int sensorh, float sensort, int sensorl, String code_id) {
    this->sensorh = sensorh;
    this->sensort = sensort;
    this->sensorl = sensorl;
    this->code_id = code_id;
  }

  int getSensorh() {
    return sensorh;
  }

  float getSensort() {
    return sensort;
  }

  int getSensorl() {
    return sensorl;
  }

  String getCodeId() {
    return code_id;
  }

private:
  int sensorh;
  float sensort;
  int sensorl;
  String code_id;
};

#endif
