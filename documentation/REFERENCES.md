# 📚 Project References & Technical Documentation

This document compiles the authentic technical specifications, datasheets, communication protocols, and official manufacturer documentation utilized in the design and development of the **CyberRover X4.2**.

---

## 💻 Microcontrollers & Compute Platforms

1. **Espressif ESP32-S3 (Rover Master)**
   - Technical Reference Manual: [Espressif ESP32-S3 TRM](https://www.espressif.com/en/products/socs/esp32-s3)
   - ESP-NOW Protocol Documentation: [Espressif ESP-NOW User Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/api-reference/network/esp_now.html)
2. **Espressif ESP32 DevKit V1 (Remote Controller)**
   - Datasheet & Hardware Reference: [ESP32 Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
3. **AI-Thinker ESP32-CAM (Telemetry Hub)**
   - Module Specification & Schematic: [AI-Thinker ESP32-CAM Hardware Overview](https://docs.ai-thinker.com/esp32-cam)
   - OmniVision OV2640 CMOS Sensor Datasheet: [OmniVision OV2640 Specification](https://www.uctronics.com/download/cam_module/OV2640DS.pdf)
4. **Arduino Uno R3 (Motor & Radar Brain)**
   - Hardware Documentation: [Arduino Uno R3 Official Docs](https://docs.arduino.cc/hardware/uno-rev3/)
   - Microchip ATmega328P Complete Datasheet: [Microchip ATmega328P](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
5. **Arduino Nano V3 (Gas Sensor Node)**
   - Hardware Reference: [Arduino Nano Official Docs](https://docs.arduino.cc/hardware/nano/)

---

## ⚡ Motor Control & Actuation

1. **BTS7960 High-Current H-Bridge Motor Driver**
   - Infineon BTS7960 High Current PN Half Bridge Datasheet: [Infineon BTS7960 Datasheet](https://www.infineon.com/dgdl/bts7960_ds_11.pdf?fileId=db3a30431f848401011fcbf5b4957e8a)
   - 43A Peak Current rating, PWM control up to 25 kHz with internal logic-level protection.
2. **Geared DC Motors (4WD Skid-Steering)**
   - Permanent magnet DC gearmotors with high-torque gearboxes.

---

## 🔬 Environmental & Spatial Sensors

1. **Zhengzhou Winsen MQ-4 Methane Gas Sensor**
   - Technical Manual & Sensitivity Characteristics: [Winsen MQ-4 Datasheet](https://www.winsen-sensor.com/d/files/semiconductor/mq-4.pdf)
2. **Zhengzhou Winsen MQ-7 Carbon Monoxide Sensor**
   - Technical Manual & Micro-Heating Cycles: [Winsen MQ-7 Datasheet](https://www.winsen-sensor.com/d/files/semiconductor/mq-7.pdf)
3. **Zhengzhou Winsen MQ-135 Air Quality Sensor**
   - Technical Manual & Resistive Characteristics: [Winsen MQ-135 Datasheet](https://www.winsen-sensor.com/d/files/semiconductor/mq-135.pdf)
4. **Aosong DHT11 Humidity & Temperature Sensor**
   - Digital Output Single-Bus Specification: [Aosong DHT11 Datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Revised-2022-3453300.pdf)
5. **Bosch Sensortec BMP280 Digital Barometric Pressure Sensor**
   - Engineering Datasheet & I2C Registers: [Bosch Sensortec BMP280 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)
6. **ElecFreaks / SparkFun HC-SR04 Ultrasonic Ranging Module**
   - Acoustic Echo Protocol & Timing Guide: [HC-SR04 User Manual](https://www.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf)

---

## 🖥️ Displays & Audio

1. **Solomon Systech SSD1306 OLED Driver**
   - 128x64 Dot Matrix OLED / PLED Segment Driver: [Solomon Systech SSD1306 Datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)
2. **Hitachi HD44780 LCD Controller + NXP PCF8574 I2C Expander**
   - Dot Matrix Liquid Crystal Display Controller: [Hitachi HD44780U](https://www.sparkfun.com/datasheets/LCD/HD44780.pdf)
   - PCF8574 Remote 8-Bit I/O Expander for I2C Bus: [NXP PCF8574 Datasheet](https://www.nxp.com/docs/en/data-sheet/PCF8574_PCF8574A.pdf)

---

## 📦 Software & Libraries

1. **Adafruit SSD1306 & GFX Libraries**: [Adafruit SSD1306 GitHub](https://github.com/adafruit/Adafruit_SSD1306)
2. **LiquidCrystal_I2C Library**: [Frank de Brabander / Marco Schwartz LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
3. **ESP32Servo Library**: [Kevin Harrington ESP32Servo](https://github.com/madhephaestus/ESP32Servo)
4. **React & Vite**: [React Documentation](https://react.dev/), [Vite Documentation](https://vite.dev/)
5. **GSAP (GreenSock Animation Platform)**: [GSAP Docs](https://gsap.com/)
