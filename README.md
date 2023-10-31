# Planty Arduino 
`Version: 2.0.0`
### **Planty Arduino** is a project that utilizes an Arduino board to collect sensor data, convert it to JSON format, serialize the data, and transmit it through a Bluetooth connection. Follow these steps to set up and use the project:  

## Table of Contents 
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Functions](#functions)
- [Wi-Fi Connection](#wi-fi-connection)
- [Status Code Dictionary](#status-code-dictionary)
- [Folder Structure](#folder-structure)


## Requirements
### Before you begin with this project, ensure that you meet the following requirements:

- `Compatible Arduino Board:`: You will need a compatible Arduino board, such as Arduino Uno, to run this project.

- `Configure the Arduino IDE with the specification of esp32`: 

`Step 1`: Open Arduino IDE
```

Open Arduino IDE on your computer.
```
`Step 2`: Access Preferences
```
In the top left of the Arduino IDE window, go to the "File" menu and select "Preferences." A popup window with preference settings will open.
```
`Step 3`: Add URL for ESP32 Wemos D1 Mini
```
Within the preferences window, find the field labeled "Additional Boards Manager URLs." This is where you should add the URL for the ESP32 Wemos D1 Mini. In your case, add the following URL:
```
https://github.com/espressif/arduino-esp32/releases/download/2.0.14/esp32-2.0.14.zip

`Step 4`: Save and Close
```
Once you have added the URL, make sure to click the "OK" or "Apply" button to save the configuration.
```
`Step 5`: Update Boards Manager
```
After saving the URL, go to the "Tools" menu in Arduino IDE, select "Board," and choose "Boards Manager." This will open the Boards Manager.
```
`Step 6`: Install ESP32 Boards
```
Inside the Boards Manager, search for "esp32" or "ESP32 by Espressif Systems" and click the "Install" button. This will download and install the ESP32 boards package from the URL you added in the preferences.
```
- `Sensors`: Connect the sensors to the Arduino board as per the code specifications. The provided code uses three sensors: a humidity sensor (sensorh), a temperature sensor (sensort), and a light sensor (sensorl).

- `Bluetooth Module`: Make sure you have a Bluetooth module that is compatible with the Arduino board. The code uses the `BluetoothSerial` module for communication.

- `Arduino IDE`: Install the Arduino IDE on your computer if you haven't already. You can download it from the [official Arduino website](https://www.arduino.cc/en/Main/Software).

## Installation
- ### Follow these steps to configure and run the project on your Arduino board:
- `Clone or Download the Repository`: Clone this repository to your computer or download the files as a ZIP archive.

- `Connect the Arduino Board`: Connect the Arduino board to your computer using a USB cable.

- `Configure Sensors`: Ensure that the sensors are correctly connected to the specified pins in the code. In the provided code, pins 1, 2, and 4 are used for the sensors.

- `Open the Code`: Open the `Plantyrduino.ino` file in the Arduino IDE.

- `Upload the Code:`: Upload the code to your Arduino board using the "Upload" function in the Arduino IDE.

## Usage
### The Planty-Arduino project is responsible for collecting sensor data and transmitting it via Bluetooth. Follow these steps to use it:

- `Power On the Arduino Board`: Once you have uploaded the code to your Arduino board, power it on.

- `Bluetooth Connection`: Search for and connect to the device named "Planty_Arduino" via Bluetooth.

- `Data Reception`: The project will automatically transmit sensor data through the Bluetooth connection. The data includes humidity (sensorh), temperature (sensort), and light level (sensorl).

```
sensorh: Represents humidity on a scale of 0 to 100.
```
```
sensort: Displays temperature on a scale of 0 to 100.
```
```
sensorl: Indicates light level on a scale of 0 to 100.
```

`Data Monitoring`: You can use a Bluetooth-compatible application to receive and monitor the data transmitted by the device.


## Functions
### The project includes several key functions that perform sensor data collection, transmission, and more. Here is an overview of the functions:

```
PlantySensors::setupSensors()
```
This function sets up the sensors by configuring the pins they are connected to on the Arduino board.
```
PlantySensors::readSensors()
```
It reads data from the connected sensors, including humidity, temperature, and light levels. The data is stored in a JSON document for transmission.
```
PlantySensors::sendSensorDataToAPI()
```
This function sends the sensor data to an API via an HTTP POST request. It serializes the data into JSON format and handles the API communication.
```
PlantySensors::isUUID(const char* str)
```
This function checks if a given string is a valid UUID. It verifies the length and character format of the input string.

## Wi-Fi Connection
The Planty Arduino project includes a Wi-Fi connection feature. Here's how it works:

- When the Arduino board receives a specific data packet via Bluetooth with a "status_code" of 1, it expects to receive Wi-Fi credentials (SSID and password).
- It attempts to connect to the specified Wi-Fi network using the received credentials.
- The Wi-Fi connection status is monitored, and the result is communicated back via Bluetooth with "status_code" 5 for successful connection or "status_code" 6 for connection failure.
- This Wi-Fi connection allows remote configuration of the Arduino board and enables additional control and monitoring capabilities for the Planty Arduino project.

## Status Code Dictionary
The status codes used in the project are as follows:

- `1:` Request to perform Wi-Fi connection.
- `2:` Response to provide the UUID.
- `4:` Request to reset the response history on the frontend.
- `5:` Successful Wi-Fi connection established.
- `6:` Error in Wi-Fi credentials; connection failed.

`These status codes are utilized to convey the state and progress of the Planty Arduino project.`

## Folder Structure
The project consists of the following files and folders:

- `Plantyrduino.ino`: The main file containing the project's code.
- `PlantySensors`:
  -  `PlantySensors.h`: This file serves as the header for the PlantySensors class, which manages sensor configuration and Bluetooth communication in the project.
  -  `PlantySensors.cpp`: This file contains the implementation of the PlantySensors class and sensor configuration. It defines the functions and methods that perform specific tasks related to sensor data collection and Bluetooth communication.


### La estructura de carpetas es la siguiente:
```
Planty-arduino/
│
├── libraries/
│   ├── ArduinoJson/
│   ├── BluetoothSerial/
│   ├── EspSoftwareSerial/
│   ├── PantySensors/
│       ├── PlantySensors.h
│       ├── PlantySensors.cpp
│
├── Plantyrduino.ino
```