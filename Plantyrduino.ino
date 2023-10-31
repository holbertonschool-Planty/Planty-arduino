#include "PlantySensors.h"

BluetoothSerial SerialBT;
int sensor_offset = 100;
bool wifiConfigured = false;
char ssid[32];
char password[64];
extern const char* id;


PlantySensors plantySensors(SerialBT, sensor_offset);

void setup()
{
  Serial.begin(9600);

   String btCode_id = String(ESP.getEfuseMac(), HEX).substring(0, 4);
  String plantyBtName = "Planty-" + btCode_id;
  if (!SerialBT.begin(plantyBtName)) {
    Serial.println("Error: Bluetooth no está disponible.");
  }
  plantySensors.setupSensors();
  planty["serie"] = String(ESP.getEfuseMac(), HEX).substring(0, 8);
}

void loop()
{
  String bluetoothData;  // Declara una variable de tipo String para almacenar los datos Bluetooth

if (SerialBT.available()) {
  bluetoothData = SerialBT.readString();
} else {
  // Si no hay datos disponibles, asigna una cadena de texto vacía a bluetoothData
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

      Serial.println("Configurando conexión Wi-Fi...");
      WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED && attempts < 20) {
      delay(1000);
      Serial.println("Conectando a la red Wi-Fi...");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      SerialBT.println("{status_code:5}");
    } else {
      SerialBT.println("{status_code:6}");
      Serial.println("Error: No se pudo conectar a la red Wi-Fi.");
    }
  }
    break;
  case 2:
    delay(1000);
    if (!plantySensors.isUUID(id))
    {
      plantySensors.readSensors();
      plantySensors.sendSensorDataToAPI();
    }
    else
    {
      SerialBT.println(id);
    }
    break;
  default:
  
    delay(5000);
    break;
  }
}