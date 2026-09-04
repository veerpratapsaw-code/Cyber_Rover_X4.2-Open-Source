/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 05: ESP32-CAM SENSOR & TELEMETRY HUB (WI-FI)
 * FILE      : BarometerSensor.h
 * PURPOSE   : BMP280 Barometric Atmospheric Pressure & Altitude I2C Driver
 * MCU       : ESP32-CAM (AI-Thinker module)
 * ============================================================================
 */

#ifndef CAM_BAROMETER_SENSOR_H
#define CAM_BAROMETER_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include "Config.h"

struct BarometerData {
  float pressureHpa;
  float altitudeMeters;
  float temperatureC;
  bool  valid;
  uint8_t i2cAddress;
};

class BarometerSensor {
private:
  BarometerData data;
  uint8_t address;

  // Calibration coefficients from BMP280 NVM
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;
  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;
  int32_t  t_fine;

  uint8_t read8(uint8_t reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    if (Wire.endTransmission(true) != 0) return 0;
    if (Wire.requestFrom((int)address, 1) != 1) return 0;
    return Wire.available() ? Wire.read() : 0;
  }

  uint16_t read16LE(uint8_t reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    if (Wire.endTransmission(true) != 0) return 0;
    if (Wire.requestFrom((int)address, 2) != 2) return 0;
    if (Wire.available() >= 2) {
      uint8_t lsb = Wire.read();
      uint8_t msb = Wire.read();
      return (uint16_t)((msb << 8) | lsb);
    }
    return 0;
  }

  int16_t readS16LE(uint8_t reg) {
    return (int16_t)read16LE(reg);
  }

  void write8(uint8_t reg, uint8_t val) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
  }

  bool loadCalibration() {
    dig_T1 = read16LE(0x88);
    dig_T2 = readS16LE(0x8A);
    dig_T3 = readS16LE(0x8C);
    dig_P1 = read16LE(0x8E);
    dig_P2 = readS16LE(0x90);
    dig_P3 = readS16LE(0x92);
    dig_P4 = readS16LE(0x94);
    dig_P5 = readS16LE(0x96);
    dig_P6 = readS16LE(0x98);
    dig_P7 = readS16LE(0x9A);
    dig_P8 = readS16LE(0x9C);
    dig_P9 = readS16LE(0x9E);

    // If dig_T1 is 0 or 0xFFFF, communication failed
    return (dig_T1 != 0 && dig_T1 != 0xFFFF);
  }

  int32_t compensateTemp(int32_t adc_T) {
    int32_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    int32_t var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    t_fine = var1 + var2;
    return (t_fine * 5 + 128) >> 8;
  }

  uint32_t compensatePressure(int32_t adc_P) {
    int64_t var1 = ((int64_t)t_fine) - 128000;
    int64_t var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

    if (var1 == 0) return 0; // Avoid division by zero

    int64_t p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (uint32_t)p;
  }

public:
  BarometerSensor()
    : address(0x76), t_fine(0) {
    data.pressureHpa = 1013.25f;
    data.altitudeMeters = 0.0f;
    data.temperatureC = 25.0f;
    data.valid = false;
    data.i2cAddress = 0x76;
  }

  void begin() {
    Wire.begin(BMP_SDA_PIN, BMP_SCL_PIN);
    Wire.setTimeOut(25); // 25ms timeout so it never hangs if no sensor is plugged in
    delay(20);

    // Auto-detect standard BMP280 addresses: 0x76 then 0x77
    address = 0x76;
    uint8_t chipId = read8(0xD0);
    if (chipId != 0x58 && chipId != 0x56 && chipId != 0x57 && chipId != 0x60) {
      address = 0x77;
      chipId = read8(0xD0);
    }

    if (chipId == 0x58 || chipId == 0x56 || chipId == 0x57 || chipId == 0x60) {
      if (loadCalibration()) {
        // Normal Mode: Temp x1 oversampling, Pressure x4 oversampling, Filter 4
        write8(0xF4, 0x27); // ctrl_meas: osrs_t(001), osrs_p(010), mode(11 = normal)
        write8(0xF5, 0x0C); // config: t_sb(000 = 0.5ms), filter(011 = filter 4)
        data.valid = true;
        data.i2cAddress = address;
        Serial.printf("[BMP280] Sensor detected at 0x%02X (ID: 0x%02X)\n", address, chipId);
        update();
        return;
      }
    }

    data.valid = false;
    Serial.println(F("[BMP280] Sensor not found on I2C (standing by until connected)"));
  }

  void update() {
    if (!data.valid) {
      // Periodic retry if sensor wasn't plugged in at boot
      static unsigned long lastRetryMs = 0;
      if (millis() - lastRetryMs > 5000) {
        lastRetryMs = millis();
        begin();
      }
      return;
    }

    Wire.beginTransmission(address);
    Wire.write(0xF7); // Burst read 0xF7..0xFC (6 bytes: press_msb, press_lsb, press_xlsb, temp_msb, temp_lsb, temp_xlsb)
    Wire.endTransmission(false);
    Wire.requestFrom((int)address, 6);

    if (Wire.available() >= 6) {
      uint32_t p_msb  = Wire.read();
      uint32_t p_lsb  = Wire.read();
      uint32_t p_xlsb = Wire.read();
      uint32_t t_msb  = Wire.read();
      uint32_t t_lsb  = Wire.read();
      uint32_t t_xlsb = Wire.read();

      int32_t adc_P = (int32_t)((p_msb << 12) | (p_lsb << 4) | (p_xlsb >> 4));
      int32_t adc_T = (int32_t)((t_msb << 12) | (t_lsb << 4) | (t_xlsb >> 4));

      int32_t tempComp = compensateTemp(adc_T);
      data.temperatureC = (float)tempComp / 100.0f;

      uint32_t pressComp = compensatePressure(adc_P);
      if (pressComp > 0) {
        data.pressureHpa = (float)pressComp / 25600.0f;

        // International Barometric Formula for Altitude:
        // Altitude = 44330 * (1.0 - pow(P / P0, 0.1903))
        data.altitudeMeters = 44330.0f * (1.0f - pow(data.pressureHpa / SEALEVELPRESSURE_HPA, 0.190295f));
      }
    }
  }

  float getPressureHpa() const { return data.pressureHpa; }
  float getAltitudeMeters() const { return data.altitudeMeters; }
  float getTemperatureC() const { return data.temperatureC; }
  bool isValid() const { return data.valid; }
  const BarometerData& getData() const { return data; }
};

#endif // CAM_BAROMETER_SENSOR_H
