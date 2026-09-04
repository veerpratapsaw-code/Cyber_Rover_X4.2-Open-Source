/*
============================================================================
PROJECT   : CYBERROVER X — NODE 04: GAS SENSOR NODE (ARDUINO NANO)
MCU       : Arduino Nano (ATmega328P / 5V / 16MHz)
FRAMEWORK : Arduino AVR
OUTPUT    : UART @ 115200 Baud -> Level Shifter -> ESP32-CAM Telemetry Hub

SYSTEM MODULES:
----------------------------------------------------------------------------
1. Config.h          : Pin mapping, danger thresholds & timing constants
2. GasSensors.h      : 10-bit ADC sampling & danger evaluation (MQ-4, MQ-7, MQ-135)
3. DisplayLCD.h      : 16x2 I2C LCD driver with auto-healing watchdog
4. TelemetrySender.h : UART CSV telemetry streaming engine (@ 115200 baud)
============================================================================
*/

#include <Arduino.h>
#include "Config.h"
#include "GasSensors.h"
#include "DisplayLCD.h"
#include "TelemetrySender.h"

//==================================================
// GLOBAL SUBSYSTEM INSTANCES
//==================================================

GasSensors      sensors;
DisplayLCD      lcdDisplay;
TelemetrySender telemetry;

//==================================================
// SETUP
//==================================================

void setup() {
  // 1. Initialize Hardware Subsystems
  telemetry.begin();
  sensors.begin();
  lcdDisplay.begin();

  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(" CYBERROVER X — NODE 04: GAS SENSOR NODE (NANO)     "));
  Serial.println(F(" Status: MQ-4, MQ-7, MQ-135 Active | UART @ 115200  "));
  Serial.println(F("===================================================="));
}

//==================================================
// MAIN LOOP (NON-BLOCKING)
//==================================================

void loop() {
  // 1. Continuous Analog Sensor Acquisition
  sensors.update();

  // 2. Transmit UART Telemetry Packet at 500 ms interval (2 Hz)
  telemetry.update(sensors);

  // 3. Update 16x2 I2C LCD Display (Rotating pages & danger alerts)
  lcdDisplay.update(sensors);
}