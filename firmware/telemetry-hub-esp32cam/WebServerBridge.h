/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
 * FILE      : WebServerBridge.h
 * PURPOSE   : REST API WebServer with CORS & Flashlight Torch Control
 * MCU       : ESP32-CAM
 * ============================================================================
 */

#ifndef CAM_WEB_SERVER_BRIDGE_H
#define CAM_WEB_SERVER_BRIDGE_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "Config.h"
#include "GasReceiver.h"
#include "ClimateSensor.h"
#include "BarometerSensor.h"

class WebServerBridge {
private:
  WebServer        server;
  bool             flashLightOn;
  GasReceiver*     gasNode;
  ClimateSensor*   climateNode;
  BarometerSensor* barometerNode;

  static WebServerBridge* instance;

  static void handleApiSensorsStatic() {
    if (instance) instance->handleApiSensors();
  }

  static void handleApiTorchStatic() {
    if (instance) instance->handleApiTorch();
  }

  void handleApiSensors() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

    bool isSta = (WiFi.status() == WL_CONNECTED);
    String ipStr = isSta ? WiFi.localIP().toString() : WiFi.softAPIP().toString();

    String json = "{";
    if (gasNode) {
      json += "\"connected\":" + String(gasNode->isConnected() ? "true" : "false") + ",";
      json += "\"mq4\":" + String(gasNode->isConnected() ? gasNode->getMQ4() : 0) + ",";
      json += "\"mq7\":" + String(gasNode->isConnected() ? gasNode->getMQ7() : 0) + ",";
      json += "\"mq135\":" + String(gasNode->isConnected() ? gasNode->getMQ135() : 0) + ",";
      json += "\"packets\":" + String(gasNode->getPacketCount()) + ",";
      json += "\"age_ms\":" + String(gasNode->getAgeMs()) + ",";
    }
    if (climateNode) {
      json += "\"dht_valid\":" + String(climateNode->isValid() ? "true" : "false") + ",";
      json += "\"temp_c\":" + String(climateNode->getTempC(), 1) + ",";
      json += "\"temp_f\":" + String(climateNode->getTempF(), 1) + ",";
      json += "\"humidity\":" + String(climateNode->getHumidity(), 1) + ",";
      json += "\"dew_point_c\":" + String(climateNode->getDewPointC(), 1) + ",";
    }
    if (barometerNode) {
      json += "\"bmp_valid\":" + String(barometerNode->isValid() ? "true" : "false") + ",";
      json += "\"pressure_hpa\":" + String(barometerNode->getPressureHpa(), 2) + ",";
      json += "\"altitude_m\":" + String(barometerNode->getAltitudeMeters(), 1) + ",";
      json += "\"bmp_temp_c\":" + String(barometerNode->getTemperatureC(), 1) + ",";
    }
    json += "\"torch\":" + String(flashLightOn ? "true" : "false") + ",";
    json += "\"ip\":\"" + ipStr + "\"";
    json += "}";

    server.send(200, "application/json", json);
  }

  void handleApiTorch() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    if (server.hasArg("toggle")) {
      flashLightOn = !flashLightOn;
    } else if (server.hasArg("state")) {
      flashLightOn = (server.arg("state") == "1" || server.arg("state") == "true");
    }
    digitalWrite(FLASH_LED_PIN, flashLightOn ? HIGH : LOW);

    server.send(200, "application/json", "{\"torch\":" + String(flashLightOn ? "true" : "false") + "}");
  }

public:
  WebServerBridge()
    : server(80), flashLightOn(false),
      gasNode(nullptr), climateNode(nullptr), barometerNode(nullptr) {
    instance = this;
  }

  void begin(GasReceiver &gas, ClimateSensor &climate, BarometerSensor &barometer) {
    gasNode = &gas;
    climateNode = &climate;
    barometerNode = &barometer;

    pinMode(FLASH_LED_PIN, OUTPUT);
    digitalWrite(FLASH_LED_PIN, LOW); // Torch Off

    // Connect to Hotspot
    WiFi.mode(WIFI_STA);
    WiFi.begin(STA_SSID, STA_PASS);

    Serial.print(F("[WIFI] Connecting to Phone Hotspot '"));
    Serial.print(STA_SSID);
    Serial.print(F("'..."));

    unsigned long startMs = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startMs < 8000) {
      delay(200);
      Serial.print(F("."));
    }

    if (WiFi.status() == WL_CONNECTED) {
      WiFi.setSleep(false); // Disable Wi-Fi sleep for lowest latency
      Serial.println();
      Serial.print(F("[OK] Connected to Hotspot! IP: http://"));
      Serial.println(WiFi.localIP());
    } else {
      Serial.println();
      Serial.println(F("[INFO] Hotspot search timed out. Hosting SoftAP fallback."));
      WiFi.mode(WIFI_AP);
      WiFi.softAP(AP_SSID, AP_PASS);
      Serial.print(F("[OK] SoftAP Active at: http://"));
      Serial.println(WiFi.softAPIP());
    }

    // Start mDNS Responder
    if (MDNS.begin("cybergas")) {
      Serial.println(F("[OK] mDNS Active: http://cybergas.local/"));
    }

    // Register Routes
    server.on("/api/sensors", HTTP_GET, handleApiSensorsStatic);
    server.on("/api/torch", HTTP_GET, handleApiTorchStatic);
    server.begin();

    Serial.println(F("[OK] REST API Server Started on Port 80 (/api/sensors)"));
  }

  void update() {
    server.handleClient();
  }
};

#endif // CAM_WEB_SERVER_BRIDGE_H
