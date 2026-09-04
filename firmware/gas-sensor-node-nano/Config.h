/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 04: GAS SENSOR NODE (ARDUINO NANO)
 * FILE      : Config.h
 * PURPOSE   : Hardware pinout mapping, test thresholds & timing parameters
 * MCU       : Arduino Nano (ATmega328P / 5V / 16MHz)
 * ============================================================================
 */

#ifndef NANO_CONFIG_H
#define NANO_CONFIG_H

#include <Arduino.h>

// ============================================================================
// HARDWARE PIN DEFINITIONS
// ============================================================================

const int PIN_MQ4   = A0;  // MQ-4 Methane / CNG sensor analog output
const int PIN_MQ7   = A1;  // MQ-7 Carbon Monoxide analog output
const int PIN_MQ135 = A2;  // MQ-135 Air Quality / Multi-gas analog output

// I2C 16x2 LCD Backpack (PCF8574)
#define LCD_I2C_ADDR             0x27
#define LCD_COLS                 16
#define LCD_ROWS                 2

// ============================================================================
// TEST DANGER THRESHOLDS (RAW 10-BIT ADC: 0..1023)
// ============================================================================

const int MQ4_DANGER_THRESHOLD   = 700;
const int MQ7_DANGER_THRESHOLD   = 850;
const int MQ135_DANGER_THRESHOLD = 700;

// ============================================================================
// TIMING CONSTANTS (NON-BLOCKING)
// ============================================================================

const unsigned long UART_SEND_INTERVAL_MS = 500;   // 2 Hz UART telemetry streaming
const unsigned long LCD_PAGE_INTERVAL_MS  = 3000;  // Rotate normal pages every 3 sec
const unsigned long LCD_REFRESH_RATE_MS   = 250;   // LCD redraw rate
const unsigned long LCD_WATCHDOG_HEAL_MS  = 6000;  // Auto-heal LCD every 6 sec

#endif // NANO_CONFIG_H
