/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
 * FILE      : GasReceiver.h
 * PURPOSE   : Hardware UART2 Receiver & CSV Parser for Arduino Nano Gas Node
 * MCU       : ESP32-CAM
 * ============================================================================
 */

#ifndef CAM_GAS_RECEIVER_H
#define CAM_GAS_RECEIVER_H

#include <Arduino.h>
#include "Config.h"

struct GasData {
  int mq4Raw;
  int mq7Raw;
  int mq135Raw;
  unsigned long lastUpdate;
  bool connected;
  uint32_t packetCount;
  uint32_t parseErrorCount;
};

class GasReceiver {
private:
  HardwareSerial sensorSerial;
  GasData        data;
  char           buffer[80];
  size_t         bufIdx;

  void parsePacket(const char *packet) {
    if (strncmp(packet, "MQ4,", 4) != 0) {
      data.parseErrorCount++;
      return;
    }

    int mq4 = -1, mq7 = -1, mq135 = -1;
    int parsed = sscanf(packet, "MQ4,%d,MQ7,%d,MQ135,%d", &mq4, &mq7, &mq135);

    if (parsed == 3 &&
        mq4 >= 0 && mq4 <= 1023 &&
        mq7 >= 0 && mq7 <= 1023 &&
        mq135 >= 0 && mq135 <= 1023) {

      data.mq4Raw = mq4;
      data.mq7Raw = mq7;
      data.mq135Raw = mq135;
      data.lastUpdate = millis();
      data.connected = true;
      data.packetCount++;

      // Pulse status LED briefly on valid packet reception
      digitalWrite(STATUS_LED_PIN, LOW); // ON (Active LOW)
      delayMicroseconds(500);
      digitalWrite(STATUS_LED_PIN, HIGH); // OFF
    } else {
      data.parseErrorCount++;
    }
  }

public:
  GasReceiver()
    : sensorSerial(2), bufIdx(0) {
    data.mq4Raw = 0;
    data.mq7Raw = 0;
    data.mq135Raw = 0;
    data.lastUpdate = 0;
    data.connected = false;
    data.packetCount = 0;
    data.parseErrorCount = 0;
  }

  void begin() {
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, HIGH); // OFF (Active LOW)

    sensorSerial.begin(SENSOR_BAUD, SERIAL_8N1, SENSOR_RX_PIN, SENSOR_TX_PIN);
  }

  void update() {
    while (sensorSerial.available() > 0) {
      char c = (char)sensorSerial.read();
      if (c == '\r') continue;

      if (c == '\n') {
        buffer[bufIdx] = '\0';
        if (bufIdx > 0) parsePacket(buffer);
        bufIdx = 0;
      } else {
        if (bufIdx < sizeof(buffer) - 1) buffer[bufIdx++] = c;
        else bufIdx = 0;
      }
    }

    // Check Timeout
    if (data.connected && (millis() - data.lastUpdate > SENSOR_TIMEOUT_MS)) {
      data.connected = false;
    }
  }

  const GasData& getData() const { return data; }
  bool isConnected() const { return data.connected; }
  int getMQ4() const { return data.mq4Raw; }
  int getMQ7() const { return data.mq7Raw; }
  int getMQ135() const { return data.mq135Raw; }
  uint32_t getPacketCount() const { return data.packetCount; }
  unsigned long getAgeMs() const {
    return (data.lastUpdate > 0) ? (millis() - data.lastUpdate) : 99999;
  }
};

#endif // CAM_GAS_RECEIVER_H
