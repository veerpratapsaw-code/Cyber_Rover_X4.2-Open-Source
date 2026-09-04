/*
============================================================================
PROJECT   : CYBERROVER X — NODE 03: MOTOR CONTROLLER & SOUND BRAIN
MCU       : Arduino Uno (ATmega328P / 5V / 16MHz)
FRAMEWORK : Arduino AVR
BAUD      : USB Serial = 115200, SoftwareSerial (S3 Link) = 38400

SYSTEM MODULES:
----------------------------------------------------------------------------
1. Config.h        : Hardware pinout mapping and speed/distance thresholds
2. SoundEngine.h   : Non-blocking tactical sirens, horns & time bomb engine
3. MotorDriver.h   : BTS7960 Dual H-Bridge motor control with smooth ramping
4. RadarSensors.h  : 3x HC-SR04 ultrasonic obstacle sensors with auto-healing
5. AutoNavigator.h : Manual, Semi-Auto (Collision Assist) & Full Auto states
6. CommsGateway.h  : Serial frame parser (0xAA 0x55 + CyberPacket) & telemetry
============================================================================
*/

#include <Arduino.h>
#include "Config.h"
#include "SoundEngine.h"
#include "MotorDriver.h"
#include "RadarSensors.h"
#include "AutoNavigator.h"
#include "CommsGateway.h"

//==================================================
// GLOBAL SUBSYSTEM INSTANCES
//==================================================

SoundEngine   sound;
MotorDriver   motors;
RadarSensors  radar;
AutoNavigator nav;
CommsGateway  comms;

unsigned long g_lastMotorUpdateMs = 0;
unsigned long g_lastDebugPrintMs  = 0;
uint8_t       g_previousMode      = MODE_MANUAL;

//==================================================
// SERIAL MONITOR DEBUG TELEMETRY OUTPUT (4 Hz)
//==================================================

void printSerialDebug() {
  Serial.print(F("[MODE: "));
  uint8_t mode = comms.getMode();

  switch (mode) {
    case MODE_MANUAL:    Serial.print(F("MANUAL")); break;
    case MODE_SEMI_AUTO: Serial.print(F("SEMI_AUTO")); break;
    case MODE_AUTO:      
      Serial.print(F("AUTO -> ")); 
      switch (nav.getAutoState()) {
        case STATE_FORWARD:        Serial.print(F("FORWARD")); break;
        case STATE_STEER_LEFT:     Serial.print(F("STEER_LEFT")); break;
        case STATE_STEER_RIGHT:    Serial.print(F("STEER_RIGHT")); break;
        case STATE_TURN_LEFT:      Serial.print(F("TURN_LEFT")); break;
        case STATE_TURN_RIGHT:     Serial.print(F("TURN_RIGHT")); break;
        case STATE_ESCAPE_REVERSE: Serial.print(F("REVERSE_ESCAPE")); break;
        case STATE_ESCAPE_SPIN:    Serial.print(F("SPIN_ESCAPE")); break;
        default:                   Serial.print(F("UNKNOWN")); break;
      }
      break;
    case MODE_PARK:      Serial.print(F("PARK")); break;
    default:             Serial.print(F("UNKNOWN")); break;
  }

  Serial.print(F("] | US RADAR [L: "));
  Serial.print(radar.getDistLeft(), 1);
  Serial.print(F(" cm | C: "));
  Serial.print(radar.getDistCenter(), 1);
  Serial.print(F(" cm | R: "));
  Serial.print(radar.getDistRight(), 1);
  Serial.print(F(" cm] | MOTORS [L: "));
  Serial.print(motors.getCurrentLeft());
  Serial.print(F(" | R: "));
  Serial.print(motors.getCurrentRight());
  Serial.println(F("]"));
}

//==================================================
// SETUP
//==================================================

void setup() {
  // 1. Initialize Hardware Subsystems
  motors.begin();
  sound.begin();
  radar.begin();
  comms.begin();

  // 2. Start PC USB Diagnostic Serial
  Serial.begin(115200);

  // 3. Play Startup Confirmation Chirp
  sound.triggerSound(FX_SCIFI_CHIRP);

  Serial.println();
  Serial.println(F("=================================================="));
  Serial.println(F(" CYBERROVER X — UNO MOTOR & SOUND CONTROLLER      "));
  Serial.println(F(" Status: BTS7960 Ready | Radar Active | 38400 S3  "));
  Serial.println(F("=================================================="));
}

//==================================================
// MAIN REAL-TIME LOOP
//==================================================

void loop() {
  unsigned long now = millis();

  // 1. Process Non-Blocking Tactical Sound Engine
  sound.update();

  // 2. Read and Parse Incoming Frames from ESP32-S3
  bool newPacket = comms.update(sound);
  uint8_t currentMode = comms.getMode();

  // Reset auto navigator if mode just switched into AUTO
  if (currentMode != g_previousMode) {
    g_previousMode = currentMode;
    if (currentMode == MODE_AUTO) {
      nav.resetAutoState();
    }
  }

  // 3. Update Ultrasonic Radar Sensors (50 Hz Round-Robin)
  radar.update();

  // 4. Safety Failsafe & Mode Dispatcher
  if (comms.isTimedOut() && currentMode != MODE_AUTO) {
    // Radio link lost > 400ms: Emergency safety halt
    motors.stopImmediate();
  } else if (comms.isEmergencyStop()) {
    // Remote emergency brake flag active
    motors.stopImmediate();
  } else {
    // Normal Mode Execution
    const CyberPacket &pkt = comms.getPacket();

    switch (currentMode) {
      case MODE_MANUAL:
        nav.calculateManual(motors, pkt.leftY, pkt.rightX);
        break;

      case MODE_SEMI_AUTO:
        nav.calculateSemiAuto(motors, radar, pkt.leftY, pkt.rightX);
        break;

      case MODE_AUTO:
        nav.updateAuto(motors, radar);
        break;

      case MODE_PARK:
        motors.setTargets(0, 0);
        break;
    }
  }

  // 5. Smooth Acceleration & Deceleration Motor Ramping (50 Hz)
  if (now - g_lastMotorUpdateMs >= 20) {
    g_lastMotorUpdateMs = now;
    motors.update();
  }

  // 6. Live Debug Telemetry to PC Serial Monitor (4 Hz)
  if (now - g_lastDebugPrintMs >= 250) {
    g_lastDebugPrintMs = now;
    printSerialDebug();
  }
}