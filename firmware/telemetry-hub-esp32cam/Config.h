/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
 * FILE      : Config.h
 * PURPOSE   : Wi-Fi credentials, hardware pinouts & timing definitions
 * MCU       : ESP32-CAM (AI-Thinker module / Standard ESP32)
 * ============================================================================
 */

#ifndef CAM_CONFIG_H
#define CAM_CONFIG_H

#include <Arduino.h>

//==================================================
// WI-FI HOTSPOT CREDENTIALS
//==================================================
// Replace with your 2.4 GHz field hotspot or access point credentials
const char* STA_SSID = "YOUR_WIFI_SSID";
const char* STA_PASS = "YOUR_WIFI_PASSWORD";

// Fallback SoftAP in case Hotspot is offline
const char* AP_SSID  = "CyberRover-Sensor-Hub";
const char* AP_PASS  = "cyberrover123";

//==================================================
// HARDWARE PIN DEFINITIONS FOR ESP32-CAM
//==================================================
// Arduino Nano Telemetry Receiver (via 3.3V Divider)
// NOTE: GPIO 16 is tied to PSRAM on AI-Thinker; GPIO 13 is safe & direct.
// SENSOR_TX_PIN must be >= 0 (GPIO 12 dummy pin) to prevent ESP32 HAL -1 crash.
#define SENSOR_RX_PIN        13     // From Nano TX (via 1k/2k voltage divider)
#define SENSOR_TX_PIN        12     // Unused dummy TX (must be valid GPIO >= 0)
#define SENSOR_BAUD          115200 // Matching Arduino Nano Baud Rate

#define DHTPIN               14     // DHT11 Data Pin (GPIO 14)
#define DHTTYPE              DHT11

#define FLASH_LED_PIN        4      // ESP32-CAM High-Power Flashlight LED
#define STATUS_LED_PIN       33     // ESP32-CAM Small Red Status LED (Active LOW)

// BMP280 I2C Barometric Pressure & Altitude Sensor (Arriving later)
#define BMP_SDA_PIN          2      // I2C SDA (GPIO 2 on ESP32-CAM header)
#define BMP_SCL_PIN          15     // I2C SCL (GPIO 15 on ESP32-CAM header)
#define SEALEVELPRESSURE_HPA 1013.25f

//==================================================
// TIMING CONSTANTS
//==================================================
const unsigned long SENSOR_TIMEOUT_MS = 2500;
const unsigned long DHT_UPDATE_MS     = 2000;
const unsigned long BMP_UPDATE_MS     = 1000;

#endif // CAM_CONFIG_H
