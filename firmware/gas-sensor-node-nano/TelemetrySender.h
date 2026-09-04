/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 04: GAS SENSOR NODE (ARDUINO NANO)
 * FILE      : TelemetrySender.h
 * PURPOSE   : High-Speed UART CSV Telemetry Streamer (@ 115200 Baud)
 * MCU       : Arduino Nano (ATmega328P)
 * ============================================================================
 */

#ifndef NANO_TELEMETRY_SENDER_H
#define NANO_TELEMETRY_SENDER_H

#include <Arduino.h>
#include "Config.h"
#include "GasSensors.h"

class TelemetrySender {
private:
  unsigned long lastSendMs;

public:
  TelemetrySender() : lastSendMs(0) {}

  void begin() {
    Serial.begin(115200);
  }

  void update(const GasSensors &sensors) {
    unsigned long now = millis();
    if (now - lastSendMs < UART_SEND_INTERVAL_MS) return;
    lastSendMs = now;

    // Structured CSV packet format: "MQ4,<val>,MQ7,<val>,MQ135,<val>\r\n"
    Serial.print(F("MQ4,"));
    Serial.print(sensors.getMQ4());
    Serial.print(F(",MQ7,"));
    Serial.print(sensors.getMQ7());
    Serial.print(F(",MQ135,"));
    Serial.println(sensors.getMQ135());
  }
};

#endif // NANO_TELEMETRY_SENDER_H
