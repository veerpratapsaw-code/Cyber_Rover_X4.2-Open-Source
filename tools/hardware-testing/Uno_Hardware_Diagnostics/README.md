# 🧪 ARDUINO UNO HARDWARE DIAGNOSTICS & BENCHMARK SUITE

Use this sketch to test your hardware before full rover assembly!

---

## 📋 What This Code Tests:
1. **Arduino Uno Core & Clock**: Verified by serial boot message at 115200 baud.
2. **Buzzer (Pin D8)**: Plays 2 confirmation beeps at startup, plus full siren/horn tests on command `b`.
3. **3x HC-SR04 Ultrasonic Sensors**:
   - **Left Sensor**: Trig `A5`, Echo `A4`
   - **Center Sensor**: Trig `A3`, Echo `A2`
   - **Right Sensor**: Trig `A1`, Echo `A0`
   - Real-time live distance in cm streamed every 400ms.
4. **Dual BTS7960 Motor Drivers**:
   - **Left Motor**: RPWM `Pin 5`, LPWM `Pin 6`
   - **Right Motor**: RPWM `Pin 9`, LPWM `Pin 10`
   - Forward, Reverse, Spin Left, Spin Right commands with automated 1-second safety stop.

---

## 🚀 How to Run:
1. Open [`Uno_Hardware_Diagnostics.ino`](Uno_Hardware_Diagnostics.ino) in Arduino IDE.
2. Select Board: **Arduino Uno**.
3. Select the correct **COM Port** for your Uno and click **Upload**.
4. Open **Serial Monitor** (`Ctrl + Shift + M`).
5. Set Baud Rate to **115200**.
6. Set Line Ending to **Newline** or **Both NL & CR**.

---

## ⌨️ Available Serial Monitor Commands:

| Command | Action | Expected Hardware Response |
| :---: | :--- | :--- |
| **`t`** | **Full Automated Self-Test** | Tests Buzzer beeps $\rightarrow$ Samples 3x Ultrasonic sensors $\rightarrow$ Spins Left Motor 1s $\rightarrow$ Spins Right Motor 1s |
| **`w`** | **Drive Forward** | Both Left & Right motors spin forward for 1.5 seconds, then stop automatically |
| **`s`** | **Drive Reverse** | Both Left & Right motors spin in reverse for 1.5 seconds, then stop automatically |
| **`a`** | **Spin Left** | Left motor reverses, Right motor forwards for 1.0 second, then stops |
| **`d`** | **Spin Right** | Left motor forwards, Right motor reverses for 1.0 second, then stops |
| **`x`** | **Emergency Stop** | Immediately stops all PWM signals to both motor channels |
| **`b`** | **Test Buzzer** | Plays sci-fi chirps followed by a two-cycle police siren audio sweep on Pin D8 |
| **`r`** | **Toggle Radar Stream** | Pauses or resumes the continuous 400ms distance printout |
| **`h`** | **Help Menu** | Re-prints the full list of test commands |

---

## 🔍 Visual Verification Checklist:
* [ ] **Buzzer**: When powered on or typing `b`, do you hear crisp, loud tones?
* [ ] **Left US Sensor**: Wave your hand in front of the Left sensor $\rightarrow$ does `[LEFT: ... cm]` drop to ~10–15 cm?
* [ ] **Center US Sensor**: Wave your hand in front of the Center sensor $\rightarrow$ does `[CENTER: ... cm]` drop?
* [ ] **Right US Sensor**: Wave your hand in front of the Right sensor $\rightarrow$ does `[RIGHT: ... cm]` drop?
* [ ] **Left Motor**: Type `w` $\rightarrow$ does the left wheel turn smoothly?
* [ ] **Right Motor**: Type `w` $\rightarrow$ does the right wheel turn in the same direction?
