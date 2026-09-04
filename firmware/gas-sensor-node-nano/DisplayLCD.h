/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 04: GAS SENSOR NODE (ARDUINO NANO)
 * FILE      : DisplayLCD.h
 * PURPOSE   : 16x2 I2C LCD UI Controller with Auto-Healing Noise Watchdog
 * MCU       : Arduino Nano (ATmega328P)
 * ============================================================================
 */

#ifndef NANO_DISPLAY_LCD_H
#define NANO_DISPLAY_LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"
#include "GasSensors.h"

class DisplayLCD {
private:
  LiquidCrystal_I2C lcd;
  uint8_t           currentPage;
  unsigned long     lastPageChangeMs;
  unsigned long     lastRefreshMs;
  unsigned long     lastHealMs;

public:
  DisplayLCD()
    : lcd(LCD_I2C_ADDR, LCD_COLS, LCD_ROWS),
      currentPage(0), lastPageChangeMs(0),
      lastRefreshMs(0), lastHealMs(0) {}

  void begin() {
    lcd.init();
    lcd.backlight();
    lcd.clear();

    // Splash Screen
    lcd.setCursor(0, 0);
    lcd.print(F(" CYBERROVER X4 "));
    lcd.setCursor(0, 1);
    lcd.print(F(" SENSOR NODE L3"));
    delay(1800);
    lcd.clear();
  }

  void update(const GasSensors &sensors) {
    unsigned long now = millis();

    // 1. Cycle LCD Display Page every 3000 ms
    if (now - lastPageChangeMs >= LCD_PAGE_INTERVAL_MS) {
      lastPageChangeMs = now;
      currentPage = (currentPage + 1) % 3;
    }

    // 2. Self-Healing LCD Watchdog (Recovers from Motor Back-EMF / I2C noise)
    if (now - lastHealMs >= LCD_WATCHDOG_HEAL_MS) {
      lastHealMs = now;
      lcd.init();
      lcd.backlight();
    }

    // 3. Redraw LCD at non-blocking refresh rate (250 ms)
    if (now - lastRefreshMs >= LCD_REFRESH_RATE_MS) {
      lastRefreshMs = now;
      render(sensors);
    }
  }

  void render(const GasSensors &sensors) {
    if (sensors.isDanger()) {
      // Danger Alert Screen Override
      lcd.setCursor(0, 0);
      lcd.print(F("!!! DANGER !!!  "));

      lcd.setCursor(0, 1);
      if (sensors.isDangerMQ7()) {
        lcd.print(F("MQ7:"));
        lcd.print(sensors.getMQ7());
        lcd.print(F(" (CO)     "));
      } else if (sensors.isDangerMQ4()) {
        lcd.print(F("MQ4:"));
        lcd.print(sensors.getMQ4());
        lcd.print(F(" (GAS)    "));
      } else if (sensors.isDangerMQ135()) {
        lcd.print(F("MQ135:"));
        lcd.print(sensors.getMQ135());
        lcd.print(F(" (AQI)  "));
      }
      return;
    }

    // Normal 3-Page Rotating Display
    switch (currentPage) {
      case 0:
        lcd.setCursor(0, 0);
        lcd.print(F("MQ4: "));
        lcd.print(sensors.getMQ4());
        lcd.print(F("         "));

        lcd.setCursor(0, 1);
        lcd.print(F("MQ7: "));
        lcd.print(sensors.getMQ7());
        lcd.print(F("         "));
        break;

      case 1:
        lcd.setCursor(0, 0);
        lcd.print(F("MQ135: "));
        lcd.print(sensors.getMQ135());
        lcd.print(F("       "));

        lcd.setCursor(0, 1);
        lcd.print(F("RAW DATA (10BIT)"));
        break;

      case 2:
        lcd.setCursor(0, 0);
        lcd.print(F("MQ4:"));
        lcd.print(sensors.getMQ4());
        lcd.setCursor(9, 0);
        lcd.print(F("MQ7:"));
        lcd.print(sensors.getMQ7());
        lcd.print(F("   "));

        lcd.setCursor(0, 1);
        lcd.print(F("MQ135:"));
        lcd.print(sensors.getMQ135());
        lcd.print(F("       "));
        break;
    }
  }
};

#endif // NANO_DISPLAY_LCD_H
