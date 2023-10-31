#include "PlantySensors.h"


const int MIN_LDR_VALUE = 0;
const int MAX_LDR_VALUE = 1023;
DynamicJsonDocument planty(1024);
const char* id = "";


PlantySensors::PlantySensors(BluetoothSerial &bt, int offset)
    : SerialBT(bt), sensor_offset(offset)
{
//cositas
}

void PlantySensors::setupSensors()
{
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
}

void PlantySensors::readSensors()
{
  int sensorh = analogRead(1) / 10;
  String code_id = String(ESP.getEfuseMac(), HEX).substring(0, 8);
  int sensor_lectura = analogRead(2) / 10;
  int ldr_value = analogRead(4);

  int sensorl = map(ldr_value, MIN_LDR_VALUE, MAX_LDR_VALUE, 0, 100);

  float sensort = (5.0 * sensor_lectura / 1024) * 100 - sensor_offset;
  // crear control de usuarios aca
  planty["actual_temperature"] = sensort;
  planty["actual_light"] = sensorl;
  planty["actual_watering"] = sensorh;
  planty["serie"] = code_id;

}

void PlantySensors::sendSensorDataToAPI()
{

  // Configura la solicitud HTTP
  HTTPClient http;
  http.begin("http://api.plantyit.tech/api/planty"); // Reemplaza 'tu_servidor' con la URL de tu servidor

  // Configura la cabecera de la solicitud
  http.addHeader("Content-Type", "application/json");

  // Realiza la solicitud POST
  String body;
  serializeJson(planty, body);
  int httpResponseCode = http.POST(body);
  if (httpResponseCode == 201 || httpResponseCode == 409)
  {
    //request backend uuid
    DynamicJsonDocument response(1024);
    if (deserializeJson(response, http.getString()) == DeserializationError::Ok) {
      id = response["id"];
      SerialBT.println(id);
    }
    else {
       SerialBT.println("Error al deserializar JSON");
    }
  }
  else
  {
    SerialBT.println("Error al realizar la solicitud. Código de respuesta: ");
    SerialBT.println(httpResponseCode);
  }

  http.end();
}

bool PlantySensors::isUUID(const char* str) {
  // Verificar la longitud de la cadena
  if (strlen(str) != 36) {
    return false;
  }

  // Definir un patrón de UUID
  const char* uuidPattern = "0123456789abcdefABCDEF-";

  // Recorrer la cadena y verificar si cada carácter está en el patrón
  for (int i = 0; i < 36; i++) {
    char c = str[i];

    // Comprobar si el carácter está en el patrón
    if (strchr(uuidPattern, c) == nullptr) {
      return false;  // El carácter no está en el patrón
    }
  }

  // Si todas las comprobaciones pasan, la cadena es un UUID válido
  return true;
}