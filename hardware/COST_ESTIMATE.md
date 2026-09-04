# 💰 CyberRover X4.2 — Cost Analysis & Build Financials

This document presents the financial breakdown for the **CyberRover X4.2** project, clearly differentiating between **direct prototype build cost** and **research, development, and iteration expenditure**.

---

## 📊 Summary of Prototype Financials

```
┌────────────────────────────────────────────────────────────────────────┐
│                      TOTAL PROJECT FINANCIAL SUMMARY                   │
├──────────────────────────────────────┬─────────────────────────────────┤
│ Functional Vehicle Electronics Cost  │                         ₹7,530  │
│ Handheld Remote Electronics Cost     │                         ₹1,550  │
│ Structural Hardware & Fasteners (est)│                         ₹1,200  │
├──────────────────────────────────────┼─────────────────────────────────┤
│ CURRENT PROTOTYPE REPLICATION COST   │                 ~ ₹10,000 - 11,000 │
├──────────────────────────────────────┼─────────────────────────────────┤
│ R&D / Iteration Component Loss       │                       > ₹5,000  │
├──────────────────────────────────────┼─────────────────────────────────┤
│ TOTAL HISTORICAL PROJECT EXPENDITURE │                 ~ ₹15,500 - 16,500 │
└──────────────────────────────────────┴─────────────────────────────────┘
```

---

## 1. Direct Prototype Replication Cost

This figure reflects the cost to procure the functional components required to build one complete CyberRover X4.2 system (rover + handheld remote).

### A. Core Rover Hardware
| Category | Identified Items | Subtotal (₹) |
| :--- | :--- | :---: |
| **Drive Motors & H-Bridges** | 4x Geared DC Motors (₹1,600) + 2x BTS7960 43A Drivers (₹800) | ₹2,400 |
| **Microcontrollers** | ESP32-S3 (₹1,600) + Uno (₹450) + Nano (₹250) + ESP32-CAM (₹850) | ₹3,150 |
| **Sensors Suite** | 3x MQ Gas (₹600) + DHT11 (₹50) + BMP280 (₹180) + 3x HC-SR04 (₹600) | ₹1,430 |
| **Displays, Sound & Power** | 16x2 LCD (₹300) + Siren (₹50) + 3S Battery (₹350) + Buck (₹140) + Wiring (₹300) | ₹1,140 |
| **Vehicle Electronics Total** | | **₹7,530** |

### B. Handheld Remote Controller Electronics
| Item | Description | Cost (₹) |
| :--- | :--- | :---: |
| **ESP32 Microcontroller** | 30-Pin DevKit V1 | ₹550 |
| **OLED Display** | 0.96" I2C SSD1306 | ₹200 |
| **Joysticks** | 2x Analog 2-Axis Joysticks | ₹400 |
| **Switches & Buttons** | Tactile pushbuttons & toggle switches | ₹200 |
| **Remote Power** | Dedicated Li-ion power pack | ₹200 |
| **Remote Electronics Total** | | **₹1,550** |

### C. Estimated Structural & Hardware Overhead
- Hand-cut MDF chassis plates and internal bracketry
- High-current XT30 power connectors and heavy gauge battery wiring
- Fasteners (M3/M4 machine screws, locknuts, brass standoffs)
- Rubberized traction tires
- **Estimated Mechanical Hardware Total**: **~ ₹1,000 – ₹1,500**

**Net Prototype Build Cost**: **Approximately ₹10,000 to ₹11,000 INR**.

---

## 2. Research, Development & Iteration Expenditure

> [!IMPORTANT]
> **SEPARATION OF R&D LOSSES**: In student and hobbyist robotics projects, component destruction during prototyping is normal. However, accounting standards require that burned components NOT be amortized into the unit BOM.

During the development period starting in September 2025, the project owner incurred **over ₹5,000 in material losses**:
- **High-Current Driver Burnouts**: Early motor tests without proper current limiting and back-EMF protection caused driver MOSFET failure.
- **Logic Level Discrepancies**: Accidental 5V direct connection to 3.3V-only ESP32 and ESP32-CAM pins damaged early development boards before the 1kΩ/2kΩ voltage dividers and isolated buses were finalized.
- **Sensor Element Degradation**: MQ-series sensors require sustained heating coils (consuming ~160mA each). Overvolting during power-rail experimentation burned heating filaments.
- **Chassis Iterations**: Multiple MDF cuts were discarded due to wheel clearance, weight distribution, and bracket alignment redesigns.

**Total R&D and Learning Loss**: **> ₹5,000 INR**.

---

## 3. Cost-Efficiency Analysis & Benchmark Comparison

For an educational, dual-radio, multi-MCU reconnaissance platform with obstacle-avoidance radar, multi-gas detection, climate sensing, barometric altimetry, and an ergonomic handheld remote controller with Cyber OS:
- **Total Prototype Build Cost**: **~ ₹10,500 INR (~ $125 USD)**
- **Commercial Alternative (Industrial Inspection Drones/Rovers)**: Typically exceeds **₹2,00,000 to ₹10,00,000+ INR**, while remaining closed-source and proprietary.
- **Open-Source Advantage**: Utilizes widely available COTS (Commercial Off-The-Shelf) parts accessible to students and makers in emerging regions.
