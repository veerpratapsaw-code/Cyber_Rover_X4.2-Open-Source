/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 04: GAS SENSOR NODE (ARDUINO NANO)
 * FILE      : GasSensors.h
 * PURPOSE   : 10-Bit ADC Sampling & Hazard Evaluation for MQ-4, MQ-7, MQ-135
 * MCU       : Arduino Nano (ATmega328P)
 * ============================================================================
 */

#ifndef NANO_GAS_SENSORS_H
#define NANO_GAS_SENSORS_H

#include <Arduino.h>
#include "Config.h"

class GasSensors {
private:
  int rawMQ4;
  int rawMQ7;
  int rawMQ135;

public:
  GasSensors() : rawMQ4(0), rawMQ7(0), rawMQ135(0) {}

  void begin() {
    analogReference(DEFAULT); // 5.0V Reference
  }

  void update() {
    rawMQ4   = analogRead(PIN_MQ4);
    rawMQ7   = analogRead(PIN_MQ7);
    rawMQ135 = analogRead(PIN_MQ135);
  }

  int getMQ4() const { return rawMQ4; }
  int getMQ7() const { return rawMQ7; }
  int getMQ135() const { return rawMQ135; }

  bool isDangerMQ4() const { return rawMQ4 >= MQ4_DANGER_THRESHOLD; }
  bool isDangerMQ7() const { return rawMQ7 >= MQ7_DANGER_THRESHOLD; }
  bool isDangerMQ135() const { return rawMQ135 >= MQ135_DANGER_THRESHOLD; }
  bool isDanger() const { return isDangerMQ4() || isDangerMQ7() || isDangerMQ135(); }
};

#endif // NANO_GAS_SENSORS_H
