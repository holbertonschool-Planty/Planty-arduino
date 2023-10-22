#include "PlantySensors.h"

BluetoothSerial SerialBT;
int sensor_offset = 50;

PlantySensors plantySensors(SerialBT, sensor_offset);

void setup() {
  Serial.begin(9600);
  plantySensors.setupSensors();
}

void loop() {
  plantySensors.readSensors();
}
