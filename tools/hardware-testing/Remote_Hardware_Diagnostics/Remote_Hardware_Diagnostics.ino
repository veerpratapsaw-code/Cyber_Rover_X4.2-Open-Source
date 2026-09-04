/*
============================================================================
PROJECT   : CYBERROVER X — HARDWARE DIAGNOSTIC SUITE
MODULE    : ESP32 REMOTE CONTROLLER COMPLETE HARDWARE BENCHMARK & PIN TEST
MCU       : ESP32 DevKit V1 (38-Pin / ESP32 D0WD V3)
BAUD RATE : 115200 Baud in Serial Monitor (Newline or Both NL & CR)
============================================================================

HARDWARE UNDER TEST:
----------------------------------------------------------------------------
1. Left Joystick     : LX (GPIO 35), LY (GPIO 34), JL Click (GPIO 25)
2. Right Joystick    : RX (GPIO 33), RY (GPIO 32), JR Click (GPIO 26)
3. Push Buttons      : P1 (GPIO 12), P2 (GPIO 13)
4. Toggle Switches   : Toggle 1 (GPIO 27), Toggle 2 (GPIO 14)
5. Battery Monitor   : 1S Li-ion ADC1_CH0 (GPIO 36 / VP) with 5:1 divider
6. Tactical Buzzer   : Active/Passive Piezo Buzzer (GPIO 4)
7. I2C Bus / OLED    : SDA (GPIO 21), SCL (GPIO 22) - Bus Address Scanner
8. WiFi / ESP-NOW    : Factory Station MAC Address display for pairing

HOW TO USE:
----------------------------------------------------------------------------
1. Connect your ESP32 Remote Controller via USB cable to PC.
2. In Arduino IDE, select Board: "DOIT ESP32 DEVKIT V1" or "ESP32 Dev Module".
3. Select the correct COM Port and click Upload.
4. Open Serial Monitor (Ctrl + Shift + M).
5. Set Baud Rate to 115200.
6. Set Line Ending to "Newline" or "Both NL & CR".
7. By default, live continuous telemetry streams every 250ms!
8. Type commands into Serial Monitor to test individual modules!

COMMANDS:
----------------------------------------------------------------------------
  s  -> Toggle Live Telemetry Stream On/Off
  b  -> Test Buzzer Audio (Chirp, Scale & Alarm)
  i  -> Scan I2C Bus for SSD1306 OLED (GPIO 21/22)
  t  -> Deep Diagnostic for Toggle 2 (GPIO 14 Electrical Analysis)
  p  -> Interactive Digital Buttons & Switches Test
  c  -> Joystick Range & Center Calibration Test
  v  -> Battery Voltage & Resistor Divider Inspection
  w  -> Display WiFi STA MAC Address for ESP-NOW Pairing
  a  -> Run Full Automated Self-Test
  h  -> Show this Help Menu
============================================================================
*/

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>

// ============================================================================
// HARDWARE PIN DEFINITIONS (Matched to Config.h)
// ============================================================================

// Joysticks (ADC1 Analog Channels & Switches)
const int PIN_JOY_L_X  = 35; // ADC1_CH7
const int PIN_JOY_L_Y  = 34; // ADC1_CH6
const int PIN_JOY_L_SW = 25; // Left Stick Click Switch

const int PIN_JOY_R_X  = 33; // ADC1_CH5 (Swapped to GPIO33 for X-Axis)
const int PIN_JOY_R_Y  = 32; // ADC1_CH4 (Swapped to GPIO32 for Y-Axis)
const int PIN_JOY_R_SW = 26; // Right Stick Click Switch

// Digital Push Buttons & Toggle Switches
const int PIN_PUSH_1   = 12; // Push Button 1
const int PIN_PUSH_2   = 13; // Push Button 2
const int PIN_TOGGLE_1 = 27; // Toggle Switch 1 (Park)
const int PIN_TOGGLE_2 = 14; // Toggle Switch 2 (Mute / Aux)

// Battery ADC
const int PIN_BATTERY_ADC = 36; // ADC1_CH0 (VP / 1S Li-ion Monitor)

// Buzzer
const int PIN_BUZZER   = 4;  // Active / Passive Buzzer Pin

// I2C Pins for SSD1306 OLED
const int PIN_I2C_SDA  = 21;
const int PIN_I2C_SCL  = 22;

// Inversion Configuration (From Config.h)
const bool INVERT_PUSH_BUTTONS     = true;
const bool INVERT_TOGGLE_SWITCHES  = false;

// ============================================================================
// GLOBAL STATE & TIMING
// ============================================================================
bool g_streamingActive = true;
unsigned long g_lastStreamMs = 0;
const unsigned long STREAM_INTERVAL_MS = 250; // 4 Hz Live Refresh

// Joystick Center Calibration Offsets
int g_calibLx = 2048;
int g_calibLy = 2048;
int g_calibRx = 2048;
int g_calibRy = 2048;

// ============================================================================
// HELPER FUNCTIONS: HARDWARE READINGS
// ============================================================================

// Read oversampled ADC to suppress electrical noise
int readOversampledAdc(int pin, int samples = 8) {
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(pin);
    delayMicroseconds(30);
  }
  return (int)(sum / samples);
}

// Convert 0..4095 ADC reading to -100 .. +100 relative to calibrated center
int mapJoystickAxis(int raw, int center) {
  int delta = raw - center;
  if (abs(delta) < 120) return 0; // Neutral deadzone

  if (delta > 0) {
    long span = 4095 - center - 120;
    if (span <= 0) span = 1;
    return constrain((int)(((long)(delta - 120) * 100) / span), 0, 100);
  } else {
    long span = center - 120;
    if (span <= 0) span = 1;
    return constrain((int)(((long)(delta + 120) * 100) / span), -100, 0);
  }
}

// Measure battery voltage using 5:1 divider
float readBatteryVolts() {
  int raw = readOversampledAdc(PIN_BATTERY_ADC, 16);
  // ESP32 12-bit ADC (3.3V reference) with 5:1 divider & factory calibration
  float pinVolts = ((float)raw / 4095.0f) * 3.3f;
  float batVolts = pinVolts * 5.0f * 1.0398f;
  return batVolts;
}

int calculateBatteryPercent(float volts) {
  if (volts <= 1.0f) return 0; // Disconnected
  if (volts >= 4.20f) return 100;
  if (volts <= 3.40f) return 0;
  return constrain((int)((volts - 3.40f) / (4.20f - 3.40f) * 100.0f), 0, 100);
}

// Generate simple ASCII directional mini-bar
void printMiniBar(int val) {
  // val is -100 .. +100
  char bar[11] = "     |    ";
  int pos = map(val, -100, 100, 0, 9);
  pos = constrain(pos, 0, 9);
  bar[pos] = (val == 0) ? '|' : (val > 0 ? '>' : '<');
  Serial.print(bar);
}

// ============================================================================
// DIAGNOSTIC ROUTINES
// ============================================================================

void printHelpMenu() {
  Serial.println();
  Serial.println(F("============================================================"));
  Serial.println(F(" CYBERROVER X — ESP32 REMOTE CONTROLLER HARDWARE DIAGNOSTIC "));
  Serial.println(F("============================================================"));
  Serial.println(F(" COMMANDS:"));
  Serial.println(F("   s  -> Toggle Live Telemetry Streaming (Pause / Resume)"));
  Serial.println(F("   b  -> Test Piezo Buzzer (Chirps, 2.4kHz tone & Alarm)"));
  Serial.println(F("   i  -> Scan I2C Bus for SSD1306 OLED (0x3C on GPIO 21/22)"));
  Serial.println(F("   t  -> DEEP DIAGNOSTIC: Toggle 2 (GPIO 14 Electrical State)"));
  Serial.println(F("   p  -> Interactive Buttons Test (P1, P2, T1, T2, JL, JR)"));
  Serial.println(F("   c  -> Auto-Calibrate Joysticks (Measure Center Deadband)"));
  Serial.println(F("   v  -> Battery Voltage & Resistor Divider Inspection"));
  Serial.println(F("   w  -> View ESP32 WiFi STA MAC Address (ESP-NOW Link)"));
  Serial.println(F("   a  -> Run Full Automated Diagnostic Self-Test"));
  Serial.println(F("   h  -> Re-display this Help Menu"));
  Serial.println(F("============================================================"));
  Serial.println();
}

void testBuzzer() {
  Serial.println(F("\n--- [BUZZER TEST: PIN GPIO 4] ---"));
  Serial.println(F("1. Testing Short Beep (2000 Hz)..."));
  tone(PIN_BUZZER, 2000, 100);
  delay(200);

  Serial.println(F("2. Testing High Confirmation Chirp (2800 Hz)..."));
  tone(PIN_BUZZER, 2800, 150);
  delay(250);

  Serial.println(F("3. Testing Multi-Tone Scale (1047 Hz -> 2093 Hz)..."));
  int notes[] = {1047, 1318, 1568, 2093};
  for (int n = 0; n < 4; n++) {
    tone(PIN_BUZZER, notes[n], 80);
    delay(100);
  }
  noTone(PIN_BUZZER);
  digitalWrite(PIN_BUZZER, LOW);
  Serial.println(F("[PASS] Buzzer test complete! Did you hear all 4 tones?"));
}

void scanI2CBus() {
  Serial.println(F("\n--- [I2C BUS SCANNER: SDA=21, SCL=22] ---"));
  byte error, address;
  int nDevices = 0;

  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
  Wire.setClock(400000L);

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print(F(" -> I2C device found at address 0x"));
      if (address < 16) Serial.print(F("0"));
      Serial.print(address, HEX);

      if (address == 0x3C) {
        Serial.println(F(" [FOUND: SSD1306 OLED Display 128x64]"));
      } else if (address == 0x3D) {
        Serial.println(F(" [FOUND: SSD1306 OLED Alternate Address]"));
      } else {
        Serial.println(F(" [Unknown I2C Peripheral]"));
      }
      nDevices++;
    } else if (error == 4) {
      Serial.print(F(" -> Unknown error at address 0x"));
      if (address < 16) Serial.print(F("0"));
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println(F("[FAIL] No I2C devices found! Check OLED wiring (VCC, GND, SDA=21, SCL=22)."));
  } else {
    Serial.printf("[PASS] %d I2C device(s) successfully detected!\n", nDevices);
  }
}

void testToggle2DeepDiagnostic() {
  Serial.println(F("\n============================================================"));
  Serial.println(F(" DEEP DIAGNOSTIC: TOGGLE SWITCH 2 (GPIO 14) ELECTRICAL TEST "));
  Serial.println(F("============================================================"));
  Serial.println(F("This test analyzes the physical wire & voltage state on GPIO 14."));
  Serial.println(F("Flip Toggle 2 back and forth over the next 6 seconds...\n"));

  for (int i = 0; i < 20; i++) {
    // Test with standard INPUT_PULLUP
    pinMode(PIN_TOGGLE_2, INPUT_PULLUP);
    delay(10);
    int readPullup = digitalRead(PIN_TOGGLE_2);

    // Test with raw analog read to see actual voltage on the pin
    int rawAdc = analogRead(PIN_TOGGLE_2);
    float pinVolts = ((float)rawAdc / 4095.0f) * 3.3f;

    Serial.printf(
      "[%02d/20] Pin 14 (INPUT_PULLUP) Digital: %s | Raw Voltage: %.2fV (ADC: %4d) -> State: %s\n",
      i + 1,
      readPullup == LOW ? "LOW (GND)" : "HIGH (3.3V)",
      pinVolts,
      rawAdc,
      readPullup == LOW ? "[SWITCH ON / CLOSED TO GND]" : "[SWITCH OFF / OPEN]"
    );
    delay(300);
  }

  Serial.println(F("\nDIAGNOSTIC SUMMARY FOR TOGGLE 2:"));
  Serial.println(F("- If digital read NEVER changed from HIGH: Toggle 2 is disconnected or not pulling to GND."));
  Serial.println(F("- If digital read was ALWAYS LOW: Toggle 2 is shorted to GND or switch is stuck ON."));
  Serial.println(F("- If digital read flipped between LOW and HIGH as you toggled: Hardware is 100% OK!"));
  Serial.println(F("============================================================\n"));
}

void testButtonsInteractive() {
  Serial.println(F("\n--- [INTERACTIVE BUTTONS & SWITCHES BENCHMARK (10 SECONDS)] ---"));
  Serial.println(F("Press and toggle all buttons now (P1, P2, T1, T2, JL, JR)..."));
  
  unsigned long start = millis();
  while (millis() - start < 10000) {
    int p1Raw  = digitalRead(PIN_PUSH_1);
    int p2Raw  = digitalRead(PIN_PUSH_2);
    int t1Raw  = digitalRead(PIN_TOGGLE_1);
    int t2Raw  = digitalRead(PIN_TOGGLE_2);
    int jlRaw  = digitalRead(PIN_JOY_L_SW);
    int jrRaw  = digitalRead(PIN_JOY_R_SW);

    // Evaluate logical states
    bool p1Pressed = INVERT_PUSH_BUTTONS ? (p1Raw == HIGH) : (p1Raw == LOW);
    bool p2Pressed = INVERT_PUSH_BUTTONS ? (p2Raw == HIGH) : (p2Raw == LOW);
    bool t1Active  = INVERT_TOGGLE_SWITCHES ? (t1Raw == HIGH) : (t1Raw == LOW);
    bool t2Active  = INVERT_TOGGLE_SWITCHES ? (t2Raw == HIGH) : (t2Raw == LOW);
    bool jlPressed = (jlRaw == LOW);
    bool jrPressed = (jrRaw == LOW);

    Serial.printf(
      "P1(D12):%s | P2(D13):%s | T1(D27):%s | T2(D14):%s | JL(D25):%s | JR(D26):%s\n",
      p1Pressed ? "[PRESSED]" : "  --   ",
      p2Pressed ? "[PRESSED]" : "  --   ",
      t1Active  ? " [ ON ] " : " [OFF] ",
      t2Active  ? " [ ON ] " : " [OFF] ",
      jlPressed ? "[CLICK!]" : "  --   ",
      jrPressed ? "[CLICK!]" : "  --   "
    );
    delay(250);
  }
  Serial.println(F("--- Interactive test window ended. Type 'p' to run again. ---\n"));
}

void calibrateJoysticks() {
  Serial.println(F("\n--- [JOYSTICK AUTO-CALIBRATION] ---"));
  Serial.println(F("DO NOT TOUCH the joysticks! Sampling neutral centers..."));

  long sumLx = 0, sumLy = 0, sumRx = 0, sumRy = 0;
  const int SAMPLES = 100;

  for (int i = 0; i < SAMPLES; i++) {
    sumLx += analogRead(PIN_JOY_L_X);
    sumLy += analogRead(PIN_JOY_L_Y);
    sumRx += analogRead(PIN_JOY_R_X);
    sumRy += analogRead(PIN_JOY_R_Y);
    delay(5);
  }

  g_calibLx = (int)(sumLx / SAMPLES);
  g_calibLy = (int)(sumLy / SAMPLES);
  g_calibRx = (int)(sumRx / SAMPLES);
  g_calibRy = (int)(sumRy / SAMPLES);

  Serial.println(F("Calibrated Neutral Center Offsets:"));
  Serial.printf("  Left  Stick -> X: %4d | Y: %4d (Ideal: ~2048)\n", g_calibLx, g_calibLy);
  Serial.printf("  Right Stick -> X: %4d | Y: %4d (Ideal: ~2048)\n", g_calibRx, g_calibRy);
  
  tone(PIN_BUZZER, 2400, 100);
  Serial.println(F("[PASS] Calibration complete and stored in RAM."));
}

void testBatteryVoltage() {
  Serial.println(F("\n--- [BATTERY ADC INSPECTION: PIN GPIO 36] ---"));
  int raw = readOversampledAdc(PIN_BATTERY_ADC, 32);
  float pinVolts = ((float)raw / 4095.0f) * 3.3f;
  float batVolts = readBatteryVolts();
  int pct = calculateBatteryPercent(batVolts);

  Serial.printf("  Raw ADC1_CH0 Reading : %d / 4095\n", raw);
  Serial.printf("  ESP32 Pin Voltage    : %.3f V\n", pinVolts);
  Serial.printf("  Calculated 1S Battery: %.2f V\n", batVolts);
  Serial.printf("  Remaining Percentage : %d %%\n", pct);

  if (batVolts < 2.0f) {
    Serial.println(F("  Status: [DISCONNECTED] Battery sensor reads < 2.0V (running on USB power alone)."));
  } else if (batVolts < 3.40f) {
    Serial.println(F("  Status: [CRITICAL LOW] Battery < 3.40V! Recharge required."));
  } else if (batVolts < 3.70f) {
    Serial.println(F("  Status: [LOW] Battery nominal ~3.6-3.7V."));
  } else {
    Serial.println(F("  Status: [HEALTHY] Battery voltage is good (3.7V - 4.2V)."));
  }
}

void showWifiMac() {
  Serial.println(F("\n--- [ESP32 WIRELESS NETWORK METADATA] ---"));
  WiFi.mode(WIFI_STA);
  Serial.print(F("  Local Remote Station MAC: "));
  Serial.println(WiFi.macAddress());
  Serial.println(F("  Protocol Target Peer    : 1C:DB:D4:4B:08:40 (ESP32-S3 Rover Master)"));
  Serial.println(F("  Broadcast Address       : FF:FF:FF:FF:FF:FF"));
}

void runAutomatedSelfTest() {
  Serial.println(F("\n============================================================"));
  Serial.println(F(" STARTING AUTOMATED REMOTE HARDWARE SELF-TEST...            "));
  Serial.println(F("============================================================"));

  // 1. I2C Bus Scan
  scanI2CBus();
  delay(400);

  // 2. Buzzer Confirmation
  testBuzzer();
  delay(400);

  // 3. Battery Sensor
  testBatteryVoltage();
  delay(400);

  // 4. Joystick Zero Sampling
  calibrateJoysticks();
  delay(400);

  // 5. WiFi Check
  showWifiMac();
  delay(400);

  Serial.println(F("\n============================================================"));
  Serial.println(F(" [SELF-TEST COMPLETE] Type 's' to resume live telemetry!     "));
  Serial.println(F("============================================================\n"));
}

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  // 1. Start Serial
  Serial.begin(115200);
  while (!Serial && millis() < 300);

  // 2. Initialize Buzzer to Silent state
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);
  noTone(PIN_BUZZER);

  // 3. Configure Input Pins with Internal Pull-ups
  pinMode(PIN_JOY_L_SW, INPUT_PULLUP);
  pinMode(PIN_JOY_R_SW, INPUT_PULLUP);
  pinMode(PIN_PUSH_1,   INPUT_PULLUP);
  pinMode(PIN_PUSH_2,   INPUT_PULLUP);
  pinMode(PIN_TOGGLE_1, INPUT_PULLUP);
  pinMode(PIN_TOGGLE_2, INPUT_PULLUP);

  // 4. Configure ADC Resolution
  analogReadResolution(12);
  analogSetPinAttenuation(PIN_BATTERY_ADC, ADC_11db);
  analogSetPinAttenuation(PIN_JOY_L_X,     ADC_11db);
  analogSetPinAttenuation(PIN_JOY_L_Y,     ADC_11db);
  analogSetPinAttenuation(PIN_JOY_R_X,     ADC_11db);
  analogSetPinAttenuation(PIN_JOY_R_Y,     ADC_11db);

  // 5. Initialize I2C Bus
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

  // 6. Fast Startup Chirp
  tone(PIN_BUZZER, 2000, 80);

  // 7. Initial Calibration
  g_calibLx = analogRead(PIN_JOY_L_X);
  g_calibLy = analogRead(PIN_JOY_L_Y);
  g_calibRx = analogRead(PIN_JOY_R_X);
  g_calibRy = analogRead(PIN_JOY_R_Y);

  printHelpMenu();
  Serial.println(F(">>> Live Telemetry Streaming is ACTIVE. Press 's' to Pause. <<<\n"));
}

// ============================================================================
// MAIN LOOP: REAL-TIME SERIAL STREAMING & COMMAND DISPATCHER
// ============================================================================

void loop() {
  unsigned long now = millis();

  // 1. Process Serial User Commands
  if (Serial.available() > 0) {
    char cmd = tolower(Serial.read());

    // Flush any leftover newline characters
    while (Serial.available() && (Serial.peek() == '\r' || Serial.peek() == '\n')) {
      Serial.read();
    }

    switch (cmd) {
      case 's':
        g_streamingActive = !g_streamingActive;
        Serial.printf("\n>>> Live Telemetry Streaming is now %s <<<\n\n", g_streamingActive ? "ACTIVE" : "PAUSED");
        break;
      case 'b': testBuzzer(); break;
      case 'i': scanI2CBus(); break;
      case 't': testToggle2DeepDiagnostic(); break;
      case 'p': testButtonsInteractive(); break;
      case 'c': calibrateJoysticks(); break;
      case 'v': testBatteryVoltage(); break;
      case 'w': showWifiMac(); break;
      case 'a': runAutomatedSelfTest(); break;
      case 'h': printHelpMenu(); break;
      default:
        break;
    }
  }

  // 2. Periodic Live Telemetry Stream (4 Hz)
  if (g_streamingActive && (now - g_lastStreamMs >= STREAM_INTERVAL_MS)) {
    g_lastStreamMs = now;

    // Read Joysticks
    int rawLx = readOversampledAdc(PIN_JOY_L_X);
    int rawLy = readOversampledAdc(PIN_JOY_L_Y);
    int rawRx = readOversampledAdc(PIN_JOY_R_X);
    int rawRy = readOversampledAdc(PIN_JOY_R_Y);

    int mapLx = mapJoystickAxis(rawLx, g_calibLx);
    int mapLy = mapJoystickAxis(rawLy, g_calibLy);
    int mapRx = mapJoystickAxis(rawRx, g_calibRx);
    int mapRy = mapJoystickAxis(rawRy, g_calibRy);

    // Read Buttons (Raw Pin States)
    int p1Pin = digitalRead(PIN_PUSH_1);
    int p2Pin = digitalRead(PIN_PUSH_2);
    int t1Pin = digitalRead(PIN_TOGGLE_1);
    int t2Pin = digitalRead(PIN_TOGGLE_2);
    int jlPin = digitalRead(PIN_JOY_L_SW);
    int jrPin = digitalRead(PIN_JOY_R_SW);

    // Calculate Logical States
    bool p1State = INVERT_PUSH_BUTTONS ? (p1Pin == HIGH) : (p1Pin == LOW);
    bool p2State = INVERT_PUSH_BUTTONS ? (p2Pin == HIGH) : (p2Pin == LOW);
    bool t1State = INVERT_TOGGLE_SWITCHES ? (t1Pin == HIGH) : (t1Pin == LOW);
    bool t2State = INVERT_TOGGLE_SWITCHES ? (t2Pin == HIGH) : (t2Pin == LOW);
    bool jlState = (jlPin == LOW);
    bool jrState = (jrPin == LOW);

    // Read Battery
    float batV = readBatteryVolts();
    int batPct = calculateBatteryPercent(batV);

    // Formatted Telemetry Line
    Serial.printf(
      "L-STICK[X:%+04d Y:%+04d] ", mapLx, mapLy
    );
    printMiniBar(mapLy);

    Serial.printf(
      " | R-STICK[X:%+04d Y:%+04d] ", mapRx, mapRy
    );
    printMiniBar(mapRx);

    Serial.printf(
      " | BTNS[P1:%d P2:%d T1:%d T2:%d JL:%d JR:%d (T2_PIN14:%s)] | BAT:%.2fV(%02d%%)\n",
      p1State ? 1 : 0,
      p2State ? 1 : 0,
      t1State ? 1 : 0,
      t2State ? 1 : 0,
      jlState ? 1 : 0,
      jrState ? 1 : 0,
      t2Pin == LOW ? "LOW/0" : "HIGH/1",
      batV,
      batPct
    );
  }
}
