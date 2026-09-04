/*
============================================================================
PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
MCU       : ESP32-CAM (AI-Thinker module / Standard ESP32)
FRAMEWORK : Arduino / C++17
PURPOSE   : Dedicated Wi-Fi Gateway for Laptop Master Dashboard

SYSTEM MODULES:
----------------------------------------------------------------------------
1. Config.h          : Wi-Fi credentials, hardware pinouts & timing limits
2. ClimateSensor.h   : DHT11 climate reader & dew point calculation engine
3. GasReceiver.h     : Hardware UART2 CSV parser for Nano gas telemetry
4. WebServerBridge.h : REST API WebServer (/api/sensors) with CORS & Torch
============================================================================
*/

#include <Arduino.h>
#include "Config.h"
#include "ClimateSensor.h"
#include "BarometerSensor.h"
#include "GasReceiver.h"
#include "WebServerBridge.h"

// Define static instance pointer for WebServer C-callbacks
WebServerBridge* WebServerBridge::instance = nullptr;

//==================================================
// GLOBAL SUBSYSTEM INSTANCES
//==================================================

ClimateSensor   climate;
BarometerSensor barometer;
GasReceiver     gasReceiver;
WebServerBridge webBridge;

unsigned long g_lastDhtUpdateMs = 0;
unsigned long g_lastBmpUpdateMs = 0;

//==================================================
// SETUP
//==================================================

void setup() {
  Serial.begin(115200);
  delay(400);

  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(" CYBERROVER X — ESP32-CAM TELEMETRY & SENSOR HUB    "));
  Serial.println(F(" Status: Booting Subsystems...                      "));
  Serial.println(F("===================================================="));

  // 1. Initialize Hardware Subsystems
  climate.begin();
  Serial.println(F("[OK] Climate Sensor (DHT11) initialized on GPIO 14"));

  barometer.begin();

  gasReceiver.begin();
  Serial.println(F("[OK] Gas Telemetry UART Receiver initialized on GPIO 13"));

  webBridge.begin(gasReceiver, climate, barometer);

  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(" SYSTEM READY — STREAMING TELEMETRY TO DASHBOARD     "));
  Serial.println(F("===================================================="));
}

//==================================================
// MAIN REAL-TIME LOOP
//==================================================

void loop() {
  unsigned long now = millis();

  // 1. Handle Incoming HTTP REST API Requests
  webBridge.update();

  // 2. Read and Parse Incoming UART Telemetry from Arduino Nano
  gasReceiver.update();

  // 3. Update DHT11 Climate Telemetry (every 2000 ms)
  if (now - g_lastDhtUpdateMs >= DHT_UPDATE_MS) {
    g_lastDhtUpdateMs = now;
    climate.update();
  }

  // 4. Update BMP280 Barometric Pressure & Altitude (every 1000 ms)
  if (now - g_lastBmpUpdateMs >= BMP_UPDATE_MS) {
    g_lastBmpUpdateMs = now;
    barometer.update();
  }
}
