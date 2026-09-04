/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
 * FILE      : ClimateSensor.h
 * PURPOSE   : DHT11 Climate Sensor Reader & Dew Point Calculation Engine
 * MCU       : ESP32-CAM
 * ============================================================================
 */

#ifndef CAM_CLIMATE_SENSOR_H
#define CAM_CLIMATE_SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include "Config.h"

struct ClimateData {
  float tempC;
  float tempF;
  float humidity;
  float dewPointC;
  bool valid;
  unsigned long lastReadMs;
};

class ClimateSensor {
private:
  DHT         dht;
  ClimateData data;

  float calculateDewPoint(float temp, float hum) {
    if (hum <= 0.0f) return 0.0f;
    float a = 17.271f, b = 237.7f;
    float tempFactor = (a * temp) / (b + temp);
    float gamma = tempFactor + log(hum / 100.0f);
    return (b * gamma) / (a - gamma);
  }

public:
  ClimateSensor()
    : dht(DHTPIN, DHTTYPE) {
    data.tempC = 27.0f;
    data.tempF = 80.6f;
    data.humidity = 55.0f;
    data.dewPointC = 17.0f;
    data.valid = false;
    data.lastReadMs = 0;
  }

  void begin() {
    pinMode(DHTPIN, INPUT_PULLUP);
    dht.begin();
    update();
  }

  void update() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      delay(50);
      h = dht.readHumidity();
      t = dht.readTemperature();
    }

    if (!isnan(h) && !isnan(t) && h > 0.0f && t > -40.0f) {
      data.tempC = t;
      data.tempF = (t * 1.8f) + 32.0f;
      data.humidity = h;
      data.dewPointC = calculateDewPoint(t, h);
      data.valid = true;
    } else {
      data.valid = false;
    }
    data.lastReadMs = millis();
  }

  const ClimateData& getData() const { return data; }
  float getTempC() const { return data.tempC; }
  float getTempF() const { return data.tempF; }
  float getHumidity() const { return data.humidity; }
  float getDewPointC() const { return data.dewPointC; }
  bool isValid() const { return data.valid; }
};

#endif // CAM_CLIMATE_SENSOR_H
