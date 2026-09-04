# ⚠️ Sensor & Subsystem Limitations Analysis

To maintain technical honesty and academic rigor, this document outlines the fundamental physical, electrical, and environmental limitations of the sensors and subsystems deployed on the **CyberRover X4.2** prototype.

---

## 1. MQ-Series Gas Sensors (MQ-4, MQ-7, MQ-135)
- **Non-Calibrated Relative ADC Readings**: Raw readings represent semiconductor surface resistance changes ($R_s/R_0$), not calibrated parts-per-million (PPM) concentrations.
- **Cross-Sensitivity**: MQ sensors are cross-sensitive to multiple atmospheric gases and volatile organic compounds (VOCs). For instance, MQ-135 responds to both ammonia and smoke, and MQ-7 reacts to hydrogen as well as carbon monoxide.
- **Preheating Dependency**: Sensors require sustained heating coil power. Accurate resistance stabilization requires up to 24–48 hours of burn-in and several minutes of warmup before readings stabilize.
- **Ambient Temperature & Humidity Drift**: Changes in relative humidity and ambient temperature shift baseline resistance, causing baseline drift unless dynamic compensation curves are applied.

---

## 2. DHT11 Climate Sensor
- **Slow Response Latency**: The physical sampling cycle requires at least 1 to 2 seconds between consecutive reads.
- **Coarse Resolution**:
  - Temperature accuracy is ±2.0°C with 1°C resolution.
  - Humidity accuracy is ±5% RH within a limited 20%–90% range.
- **Condensation Vulnerability**: Prolonged exposure to 100% condensing humidity can saturate the capacitive humidity polymer.

---

## 3. BMP280 Barometer & Altimeter
- **Weather Sensitivity**: The barometric calculation assumes a standard sea-level pressure ($1013.25\text{ hPa}$). Local barometric weather fronts cause calculated altitude to drift over hours unless recalibrated against local QNH values.
- **Acoustic / Airflow Noise**: Fast motor motion or fan airflow directly over the sensor vent hole can induce local Bernoulli pressure drops, causing brief altitude estimation spikes.

---

## 4. HC-SR04 Ultrasonic Obstacle Radar
- **Surface Material Absorption**: Soft, fibrous, or angled materials (e.g. curtains, cloth, angled smooth surfaces) absorb or specularly reflect 40 kHz sound waves away from the receiver, causing false-open readings.
- **Beam Angle & Field of View**: Each sensor has an effective cone of ~15° to 30°. Small wire hazards, low-lying floor lips (< 2 cm), and drop-offs (cliffs, stairs) cannot be detected.
- **Speed of Sound Temperature Dependency**: Speed of sound varies with temperature ($c \approx 331.3 + 0.606 \times T$). Extreme cold or heat introduces minor distance calculation errors (~±2–5%).

---

## 5. Wireless Communication & Video Streaming
- **2.4 GHz RF Attenuation**: Both ESP-NOW and Wi-Fi operate in the crowded 2.4 GHz ISM band. Signal strength degrades significantly through reinforced concrete walls, dense soil, and metal bulkheads.
- **Bandwidth Bottlenecks**: High Wi-Fi camera framerates consume network bandwidth, which can cause frame latency spikes or dropped TCP packets on standard smartphone hotspots.
- **Line-of-Sight Limitations**: Standard omnidirectional PCB antennas restrict reliable range to ~30–50 meters line-of-sight outdoors, and ~15–25 meters through residential partition walls.

---

## 6. Chassis, Terrain & Mobility
- **Skid-Steer Friction**: 4WD tank steering requires tire slip against the driving surface. Turning on high-friction surfaces (e.g. thick carpet, coarse rubber mats) draws high stall current.
- **Obstacle Clearance**: The low ground clearance (~2.5–3.5 cm) limits traversing capability to indoor surfaces, compact dirt, and shallow gravel. The rover cannot climb stairs or traverse deep mud or water puddles.
- **Open MDF Chassis**: The chassis is not water-sealed (IP00 rating). Exposure to rain, water submersion, or conductive metal dust will damage electronics.

---

## 7. Battery & Power Architecture
- **Voltage Sag Under Load**: High motor acceleration causes momentary battery pack voltage sag. While the logic buck converter filters this out for microcontrollers, severely depleted batteries (< 10.2V) risk brownouts.
- **No Active Battery Thermal Balancing**: Prototype uses standard 3S Li-ion pack protection; active temperature sensing across individual battery cells is not implemented.
