#ifndef PlantySensors_h
#define PlantySensors_h

#include "Arduino.h"
#include "jsonManager.h"
#include <BluetoothSerial.h>

class PlantySensors {
public:
  PlantySensors(BluetoothSerial& bt, int offset);
  void setupSensors();
  void readSensors();

private:
  BluetoothSerial& SerialBT;
  int sensor_offset;
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
