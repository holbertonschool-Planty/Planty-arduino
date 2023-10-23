# Planty Arduino
`Version: 1.0.0`
### **Planty Arduino** is a project that utilizes an Arduino board to collect sensor data, convert it to JSON format, serialize the data, and transmit it through a Bluetooth connection. Follow these steps to set up and use the project:  

## Table of Contents
- [Requirements](##requirements)
- [Installation](##installation)
- [Usage](##usage)
- [Folder Structure](##folder-structure)

## Requirements
### Before you begin with this project, ensure that you meet the following requirements:

- `Compatible Arduino Board:`: You will need a compatible Arduino board, such as Arduino Uno, to run this project.

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
sensort: Displays temperature with an offset shift.
```
```
sensorl: Indicates light level on a scale of 0 to 100.
```

`Data Monitoring`: You can use a Bluetooth-compatible application to receive and monitor the data transmitted by the device.


## Folder Structure
The project consists of the following files and folders:

- `Plantyrduino.ino`: The main file containing the project's code.
- `PlantySensors`:
  -  `PlantySensors.h`: Header for the `PlantySensors` class, which manages sensor configuration and Bluetooth communication.
  -  `PlantySensors.cpp`: Implementation of the `PlantySensors` class and sensor configuration.
  -  `jsonManager.h`: Header for the `JsonManager` class, responsible for creating data in JSON format.
  -  `jsonManager.cpp`:Implementation of the `JsonManager` class, responsible for creating data in JSON format.


### La estructura de carpetas es la siguiente:
```
Planty-arduino/
│
├── libraries/
│   ├── ArduinoJson/
│   ├── BluetoothSerial/
│   ├── EspSoftwareSerial/
│   ├── PantySensors/
│       ├── jsonManager.h
│       ├── PlantySensors.h
│       ├── PlantySensors.cpp
│       ├── jsonManager.h
│
├── Plantyrduino.ino
```
