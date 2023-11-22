#include "PlantySensors.h"

BluetoothSerial SerialBT;
int sensor_offset = 100;
extern const char* id;
String status;
const int addressForSSID = 0;
const int addressForPassword = sizeof(char) * 32;
const int addressForUUID = sizeof(char) * 32 + sizeof(char) * 32;
char ssid[64] = "default_ssid";
char password[64] = "default_password";
extern bool wifiConfigured;


PlantySensors plantySensors(SerialBT, sensor_offset);

void setup() {
  Serial.begin(9600);
  EEPROM.begin(768);
   String btCode_id = String(ESP.getEfuseMac(), HEX).substring(0, 4);
  String plantyBtName = "Planty-" + btCode_id;
  if (!SerialBT.begin(plantyBtName)) {
    Serial.println("Error: Bluetooth no está disponible.");
  }
  EEPROM.get(addressForSSID, ssid);
  EEPROM.get(addressForPassword, password);
}
void loop(){
  String bluetoothData;
  Serial.println("SSID: " + String(ssid));
  Serial.println("Password: " + String(password));
  plantySensors.connectToWiFi();
if (SerialBT.available()) {
  bluetoothData = SerialBT.readString();
} else {
  
  bluetoothData = "";
}
  DynamicJsonDocument dataJson(200);
  try
  {
    if (bluetoothData != ""){
    deserializeJson(dataJson, bluetoothData);
      SerialBT.println("{status_code:4}");
    }
  }
  catch (const std::exception &e)
  {
    SerialBT.println("catch");
    dataJson["status_code"] = 0;
  }
  
  switch (dataJson["status_code"].as<int>())
  {
  case 1:
  if (dataJson["data"] && dataJson["data"]["ssid"] && dataJson["data"]["password"]) {
    
    int attempts = 0;
    strcpy(ssid, dataJson["data"]["ssid"]);
    strcpy(password, dataJson["data"]["password"]);
    wifiConfigured = true;
    plantySensors.connectToWiFi();
    if (wifiConfigured) {
      SerialBT.println("{status_code:5}");
      
      EEPROM.put(addressForSSID, ssid);
      EEPROM.put(addressForPassword, password);
      EEPROM.commit();
      delay(1000);
      EEPROM.get(addressForSSID, ssid);
      EEPROM.get(addressForPassword, password);

    } else {
      SerialBT.println("{status_code:6}");
      Serial.println("Error: No se pudo conectar a la red Wi-Fi.");
    }
  }
    break;
  case 2:
    delay(1000);
    if (id && plantySensors.isUUID(id)) {
          SerialBT.println(id);
    } else {
      plantySensors.readSensors();
      plantySensors.sendSensorDataToAPI();
    }
    break;
  default:
    delay(5000);
    break;
  }

}
