#include "PlantySensors.h"

DynamicJsonDocument planty(1024);
const char* id;
const int pinLdr = 32;
const int pinHum = 34;
int sensorl;
float sensorh;
float sensort;
bool useHTTPS = true;
bool wifiConfigured = false;
String body;
HTTPClient http, https;
int httpResponseCode;


PlantySensors::PlantySensors(BluetoothSerial &bt, int offset)
    : SerialBT(bt), sensor_offset(offset), dataJson(1024)
{
    //cositas
}

void PlantySensors::readSensors()
{
    String code_id = String(ESP.getEfuseMac(), HEX).substring(0, 8);
    sensorh = analogRead(pinHum);
    //sensort = bmp.readTemperature(); change the sensor
    sensorl = analogRead(pinLdr);

    sensorl = map(sensorl, 0, 4095, 0, 100);
    sensorh = sensorh / 100;
    sensorh = map(sensorh, 0, 40.95, 0, 100.0);

    planty["actual_temperature"] = sensort;
    planty["actual_light"] = sensorl;
    planty["actual_watering"] = sensorh;
    planty["serie"] = code_id;
}

void PlantySensors::sendSensorDataToAPI() {
  Serial.println("1");
    String url = "http://api.plantyit.tech/api/planty";
  Serial.println("2");
    http.begin(url);
    http.addHeader("Content-Type", "application/json");
    Serial.println("3");

    String body;
    serializeJson(planty, body);
    Serial.println("4");
    int httpResponseCode = http.POST(body);

    // Maneja la respuesta
    Serial.println("5");
    if (httpResponseCode == 201 || httpResponseCode == 409) {
        // Request the UUID to Backend
        Serial.println("6");
        DynamicJsonDocument response(1024);
        Serial.println("7");
        if (deserializeJson(response, http.getString()) == DeserializationError::Ok) {
            id = response["id"];
            Serial.println("8");
            SerialBT.println(id);
        } else {
            SerialBT.println("Error al deserializar JSON");
            Serial.println("9");
        }
    } else {
        SerialBT.print("Error al realizar la solicitud. Código de respuesta: ");
        SerialBT.println(httpResponseCode);
        Serial.println("10");
    }
    Serial.println("11");
    // End of conection
    http.end();
}



bool PlantySensors::isUUID(const char* str) {

 if (strlen(str) != 36) {
        return false;
    }

    // Define a UUID pattern
    const char* uuidPattern = "0123456789abcdefABCDEF-";

    // Traverse the string and check if each character is in the pattern
    for(int i = 0; i < 36; i++) {
        char c = str[i];

        // Check if the character is in the pattern
        if (strchr(uuidPattern, c) == nullptr) {
            return false; // Character is not in the pattern
        }
    }

    // If all checks pass, the string is a valid UUID.
    return true;
}

void PlantySensors::connectToWiFi() {
  if (isCredentialsValid()) {
    Serial.println("Credenciales válidas. Intentando conexión Wi-Fi...");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
      delay(1000);
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conexión Wi-Fi exitosa.");
      wifiConfigured = true;
      EEPROM.put(addressForSSID, ssid);
      EEPROM.put(addressForPassword, password);
      EEPROM.commit();
    } else {
      Serial.println("Error al conectar a la red Wi-Fi.");
    }
  } else {
    Serial.println("No se encontraron credenciales almacenadas o son inválidas.");
  }
}

bool PlantySensors::isCredentialsValid() {
  return (strlen(ssid) > 0 && strlen(password) > 0);
}