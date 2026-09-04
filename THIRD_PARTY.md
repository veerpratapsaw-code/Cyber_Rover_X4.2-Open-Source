# 🧩 Third-Party Notices & Dependency Attribution

The **CyberRover X4.2** project relies upon and integrates open-source third-party software, libraries, and firmware modules. This document attributes upstream authors, projects, and their respective licensing terms.

---

## 🛠️ Microcontroller Libraries (Arduino Ecosystem)

The following libraries are utilized across the firmware nodes and are archived in [`firmware/libraries/`](firmware/libraries/) for offline build reproducibility:

| Library | Upstream Author / Maintainer | Purpose | License |
| :--- | :--- | :--- | :--- |
| **Adafruit SSD1306** | Adafruit Industries | Monochrome OLED graphics driver for 128x64 display | BSD 3-Clause |
| **Adafruit GFX Library** | Adafruit Industries | Core graphics primitives (lines, circles, text, bitmaps) | BSD 3-Clause |
| **Adafruit BusIO** | Adafruit Industries | I2C and SPI bus wrapper | MIT License |
| **Adafruit Unified Sensor** | Adafruit Industries | Unified sensor driver abstraction | Apache License 2.0 |
| **LiquidCrystal_I2C** | Frank de Brabander / Marco Schwartz | 16x2 HD44780 character LCD control over PCF8574 I2C backpack | GNU LGPL v2.1+ |
| **DHT Sensor Library** | Adafruit Industries | One-wire protocol decoding for DHT11/DHT22 climate sensors | MIT License |
| **AM2302-Sensor** | Martin H. | High-precision climate sensor wrapper | MIT License |
| **ESP32Servo** | Kevin Harrington | Hardware timer PWM servo control for ESP32 | GNU LGPL v2.1+ |
| **RF24** | TMRh20 / Avamander | Driver for nRF24L01+ 2.4GHz transceivers | GNU GPL v2 |
| **ESP_Mail_Client** | K. Suwatchai (Mobizt) | Embedded SMTP/IMAP client library | MIT License |
| **Servo** | Michael Margolis / Arduino LLC | Standard AVR Arduino servo library | GNU LGPL v2.1 |

---

## 🌐 Web Application Dependencies (`website/package.json`)

The presentation web application utilizes the following npm packages:

| Package | Version | Purpose | License |
| :--- | :---: | :--- | :--- |
| **react** | `^19.2.8` | Declarative UI framework | MIT License |
| **react-dom** | `^19.2.8` | React DOM renderer | MIT License |
| **vite** | `^8.2.0` | Frontend build tool and development server | MIT License |
| **@vitejs/plugin-react**| `^6.0.4` | Vite plugin for React Fast Refresh | MIT License |
| **gsap** | `^3.15.0` | High-performance animation engine | Standard GreenSock License |
| **lenis** | `^1.3.26` | Smooth momentum scrolling engine | MIT License |
| **lucide-react** | `^1.31.0` | Open-source SVG icon system | ISC License |
| **oxlint** | `^1.75.0` | High-performance JavaScript/TypeScript linter | MIT License |

---

## 🛡️ Intellectual Property Disclaimer

- All product names, logos, and brands (e.g., Arduino, Espressif, Adafruit, OmniVision, Bosch Sensortec, Infineon) are property of their respective owners.
- Their inclusion in this repository is purely descriptive of hardware compatibility and does not imply endorsement, affiliation, or commercial sponsorship.
- Original project firmware and software do not relicense any upstream open-source code under incompatible terms.
