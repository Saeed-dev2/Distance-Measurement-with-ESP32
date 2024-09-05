# Distance Measurement

This project demonstrates how to Measure the distance and how to interface the HC-SR04 ultrasonic sensor with an ESP32 using the ESP-IDF framework. The implementation includes initialization of GPIO pins, sending trigger pulses, measuring echo pulses, and calculating distances.

## Prerequisites

- ESP32 development board
- HC-SR04 Ultrasonic Sensor
- ESP-IDF environment set up
- Connection wires

## Hardware Connections

- Connect the VCC of the HC-SR04 sensor to the 3.3
V of the ESP32.
- Connect the GND of the HC-SR04 sensor to the GND of the ESP32.
- Connect the TRIG pin of the HC-SR04 sensor to GPIO 4 of the ESP32.
- Connect the ECHO pin of the HC-SR04 sensor to GPIO 5 of the ESP32.

## Project Structure

```plaintext
ultrasonic_sensor
├── main
│   ├── CMakeLists.txt
│   └── ultrasonic_sensor.c
├── CMakeLists.txt
└── sdkconfig

```
## Getting Started
1. Create a New ESP-IDF Project
Create a new directory for your project and navigate to it:

```
idf.py create-project my_project
```
2. Build and Flash the Project
Set the target to ESP32, build the project, and flash it to your ESP32 board:
```
idf.py set-target esp32
idf.py build
idf.py flash
```
3. Monitor the Output
Start the serial monitor to see the output:
```
idf.py monitor
```
To exit the serial monitor, press `Ctrl + ]`
