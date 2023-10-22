#include "PlantySensors.h"

const int MIN_LDR_VALUE = 0;
const int MAX_LDR_VALUE = 1023; 

PlantySensors::PlantySensors(BluetoothSerial& bt, int offset)
  : SerialBT(bt), sensor_offset(offset) {
    if (!SerialBT.begin("Planty_Arduino")) {
      // If Bluetooth is not available, add an error field to the JSON
      jsonManager.addError("Device Bluetooth not found");
    }
  }

void PlantySensors::setupSensors() {
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
}

void PlantySensors::readSensors() {
  int sensorh = analogRead(1) / 10;
  String code_id = String(ESP.getEfuseMac(), HEX).substring(0, 8);
  int sensor_lectura = analogRead(2) / 10;
  int ldr_value = analogRead(4);

  int sensorl = customMap(ldr_value, MIN_LDR_VALUE, MAX_LDR_VALUE, 0, 100);

  float sensort = (5.0 * sensor_lectura / 1024) * 100 - sensor_offset;

  jsonManager.setHumidity(sensorh);
  jsonManager.setTemperature(sensort);
  jsonManager.setMappedLDRValue(sensorl);
  jsonManager.setCodeId(code_id);

  String jsonString = jsonManager.getJSON();

  SerialBT.println(jsonString);

}