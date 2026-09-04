# 🧪 ESP32 REMOTE CONTROLLER HARDWARE DIAGNOSTICS & BENCHMARK SUITE

Use this sketch to test and verify every physical input and peripheral on the **CYBERROVER X Remote Controller** using only the **Arduino Serial Monitor** (no OLED screen or car needed!).

---

## 📋 What This Code Tests:

1. **Left Analog Joystick (GPIO 35 X, GPIO 34 Y)**:
   - 12-bit ADC readings (0..4095) with live ASCII direction indicator bar.
   - Normalized -100 to +100 range with automatic center calibration.
2. **Right Analog Joystick (GPIO 33 X, GPIO 32 Y)**:
   - Live readings and directional bar.
3. **Joystick Click Switches**:
   - **JL (Left Click - GPIO 25)**: Instant `[CLICK!]` detection.
   - **JR (Right Click - GPIO 26)**: Instant `[CLICK!]` detection.
4. **Push Buttons**:
   - **P1 (GPIO 12)**: Shows raw pin logic and debounced `[PRESSED]` state.
   - **P2 (GPIO 13)**: Shows raw pin logic and debounced `[PRESSED]` state.
5. **Toggle Switches**:
   - **Toggle 1 (GPIO 27)**: Shows `[ ON ]` / `[OFF]`.
   - **Toggle 2 (GPIO 14)**: Shows `[ ON ]` / `[OFF]` PLUS raw physical pin voltage / electrical state (`LOW/0` or `HIGH/1`) to immediately diagnose wiring issues!
6. **1S Li-ion Battery ADC (GPIO 36 / VP)**:
   - 16x oversampled ADC read via 5:1 resistor divider.
   - Computes battery voltage (e.g. 3.85V) and remaining charge percentage (0-100%).
7. **Buzzer (GPIO 4)**:
   - Tests tones, confirmation chirps, and alert scales.
8. **I2C Bus Scanner (SDA=21, SCL=22)**:
   - Pings addresses on the I2C bus to verify SSD1306 OLED is responding at `0x3C`.
9. **WiFi Station MAC Address**:
   - Prints the ESP32's unique factory MAC address for ESP-NOW pairing with the rover.

---

## 🚀 How to Run:

1. Connect your **ESP32 Remote Controller** to your computer via USB.
2. In Arduino IDE:
   - Open [`Remote_Hardware_Diagnostics.ino`](Remote_Hardware_Diagnostics.ino).
   - Select Board: **DOIT ESP32 DEVKIT V1** (or **ESP32 Dev Module**).
   - Select the correct **COM Port** and click **Upload**.
3. Open **Serial Monitor** (`Ctrl + Shift + M`).
4. Set Baud Rate to **115200**.
5. Set Line Ending to **Newline** or **Both NL & CR**.
6. Live diagnostic telemetry will immediately begin streaming at 4 Hz!

---

## ⌨️ Available Serial Monitor Commands:

| Command | Action | Expected Output |
| :---: | :--- | :--- |
| **`s`** | **Pause / Resume Stream** | Stops or resumes the continuous 4 Hz telemetry line |
| **`b`** | **Test Buzzer** | Plays 4 audible test tones on GPIO 4 |
| **`i`** | **Scan I2C Bus** | Scans for OLED display at `0x3C` on SDA 21 / SCL 22 |
| **`t`** | **Deep Diagnostic: Toggle 2** | Performs a 6-second live electrical probe of GPIO 14 to see if the switch changes voltage when flipped |
| **`p`** | **Interactive Buttons Test** | Opens a 10-second window to click and verify all 6 buttons and switches |
| **`c`** | **Calibrate Joysticks** | Samples neutral center values when sticks are released |
| **`v`** | **Inspect Battery Voltage** | Shows raw ADC, divider calculations, voltage, and health status |
| **`w`** | **Show WiFi MAC Address** | Prints factory MAC address for ESP-NOW pairing |
| **`a`** | **Full Automated Self-Test** | Runs I2C scan $\rightarrow$ Buzzer $\rightarrow$ Battery $\rightarrow$ Joysticks $\rightarrow$ WiFi |
| **`h`** | **Help Menu** | Re-prints the command menu |

---

## 🔍 How to Diagnose Toggle 2 (GPIO 14):

1. Type **`t`** in the Serial Monitor and press Enter.
2. Flip **Toggle Switch 2** back and forth while the test runs.
3. Observe the output:
   * If `Digital: LOW (GND)` when flipped one way, and `Digital: HIGH (3.3V)` when flipped the other way $\rightarrow$ **The hardware is 100% working!**
   * If it stays `HIGH (3.3V)` constantly $\rightarrow$ The switch is not grounded or wire is loose.
   * If it stays `LOW (GND)` constantly $\rightarrow$ The switch is shorted to ground.
