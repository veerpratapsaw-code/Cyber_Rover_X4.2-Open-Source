# 🦇 Obstacle Sensing & Reactive Radar Array

This document details the forward-facing ultrasonic radar array and obstacle-avoidance logic implemented on the **CyberRover X4.2**.

---

## 📐 Radar Array Geometry

The rover utilizes three **HC-SR04** ultrasonic distance transceivers mounted in a curved array on the front MDF bumper:

```
                  FRONT OF ROVER
                      ▲
                      │ (Forward Path)
               ┌──────────────┐
               │    CENTER    │  (0° Dead Ahead)
               │   HC-SR04    │  Trig: A3 | Echo: A2
               └──────┬───────┘
                      │
        ┌─────────────┴─────────────┐
        │                           │
  ┌─────▼────────┐            ┌─────▼────────┐
  │     LEFT     │            │    RIGHT     │
  │   HC-SR04    │            │   HC-SR04    │
  │ (-45° Left)  │            │ (+45° Right) │
  │ Trig: A5     │            │ Trig: A1     │
  │ Echo: A4     │            │ Echo: A0     │
  └──────────────┘            └──────────────┘
```

---

## ⚡ Technical Specifications & Measurement Loop

- **Operating Principle**: 40 kHz ultrasonic acoustic burst emission with echo return pulse measurement:
  $$\text{Distance (cm)} = \frac{\text{Echo Pulse Duration (\mu s)}}{58.2}$$
- **Measuring Range**: ~2 cm to 400 cm (effective obstacle threshold tuned to ~15–35 cm in firmware).
- **Scanning Technique**: Non-blocking interleaved round-robin pinging handled by `RadarSensors.h` on the Arduino Uno, preventing acoustic cross-talk and echo confusion between adjacent sensors.

---

## 🤖 Reactive Avoidance Algorithm (`AutoNavigator.h`)

The rover supports two drive modes selected via Remote Button `P2`:

### 1. Manual Drive Mode (`MODE_MANUAL`)
- Full operator control from joysticks.
- Obstacle distances are monitored and audio warnings (beeps) are emitted if obstacles are dangerously close, but motion commands are not overridden.

### 2. Auto Assist / Obstacle Avoidance Mode (`MODE_AUTO`)
- Forward throttle commands are vetted by the safety layer:
  - **Center Obstacle Detected (< 25 cm)**: Rover halts forward motion, reverses briefly, and turns toward the side with greater clear distance.
  - **Left Obstacle Detected (< 20 cm)**: Automatically steers right while maintaining forward progression.
  - **Right Obstacle Detected (< 20 cm)**: Automatically steers left while maintaining forward progression.
  - **Dead End / Boxed In (< 15 cm all directions)**: Reverses immediately and triggers the acoustic alarm siren until path opens.
