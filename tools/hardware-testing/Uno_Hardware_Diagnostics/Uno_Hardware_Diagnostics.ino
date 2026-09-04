/*
============================================================================
PROJECT   : CYBERROVER X — HARDWARE DIAGNOSTIC SUITE
MODULE    : ARDUINO UNO HARDWARE & SENSOR BENCHMARK TEST
MCU       : Arduino Uno (ATmega328P / 5V / 16MHz)
BAUD RATE : 115200 Baud in Serial Monitor (Newline or Both NL & CR)
============================================================================

PURPOSE:
----------------------------------------------------------------------------
Test and verify all physical components connected to the Arduino Uno:
1. Buzzer (Pin D8)
2. 3x HC-SR04 Ultrasonic Sensors (Left: A5/A4, Center: A3/A2, Right: A1/A0)
3. Dual BTS7960 43A Motor Drivers (Left: D5/D6, Right: D9/D10)

HOW TO USE:
----------------------------------------------------------------------------
1. Upload this sketch to Arduino Uno.
2. Open Serial Monitor (Tools -> Serial Monitor).
3. Set Baud Rate to 115200 Baud.
4. Set Line Ending to "Newline" or "Both NL & CR".
5. Wave your hand in front of each sensor to see distance readings change.
6. Type commands into Serial Monitor to test motors and buzzer!

COMMANDS:
----------------------------------------------------------------------------
  w  -> Test Forward Drive (1.5 seconds)
  s  -> Test Reverse Drive (1.5 seconds)
  a  -> Test Spin Left (1.0 second)
  d  -> Test Spin Right (1.0 second)
  x  -> Emergency Stop Motors
  b  -> Test Buzzer Sounds (Beeps & Siren)
  t  -> Run Full Automated Self-Test (Tests all hardware in sequence)
  r  -> Toggle Continuous Radar Streaming On/Off
  h  -> Show this Help Menu
============================================================================
*/

#include <Arduino.h>

// ============================================================================
// HARDWARE PIN DEFINITIONS
// ============================================================================

// Buzzer / Siren
const int PIN_BUZZER     = 8;

// Left BTS7960 Motor Driver
const int PIN_LEFT_RPWM  = 5;
const int PIN_LEFT_LPWM  = 6;

// Right BTS7960 Motor Driver
const int PIN_RIGHT_RPWM = 9;
const int PIN_RIGHT_LPWM = 10;

// HC-SR04 Ultrasonic Sensors
const int PIN_US_LEFT_TRIG   = A5;
const int PIN_US_LEFT_ECHO   = A4;

const int PIN_US_CENTER_TRIG = A3;
const int PIN_US_CENTER_ECHO = A2;

const int PIN_US_RIGHT_TRIG  = A1;
const int PIN_US_RIGHT_ECHO  = A0;

// Test Motor Speed (0 to 255)
const int TEST_SPEED = 160;

// Streaming state
bool g_radarStreaming = true;
unsigned long g_lastRadarPrintMs = 0;

// ============================================================================
// HELPER: ULTRASONIC SENSOR PING WITH AUTO-HEALING
// ============================================================================

float readUltrasonicCm(uint8_t trigPin, uint8_t echoPin) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Send 10µs Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure Echo pulse (Timeout 25ms ~ 400cm max)
  unsigned long duration = pulseIn(echoPin, HIGH, 25000UL);

  // Auto-Healing: Check if Trig and Echo were accidentally swapped
  if (duration == 0) {
    pinMode(echoPin, OUTPUT);
    pinMode(trigPin, INPUT);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(4);
    digitalWrite(echoPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(echoPin, LOW);

    duration = pulseIn(trigPin, HIGH, 25000UL);

    // Restore original pin modes
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  if (duration == 0) return -1.0f; // Sensor not responding or out of range

  float distanceCm = (float)duration * 0.01715f;
  if (distanceCm < 2.0f || distanceCm > 400.0f) return -1.0f;
  return distanceCm;
}

// ============================================================================
// HELPER: MOTOR CONTROL
// ============================================================================

void stopMotors() {
  analogWrite(PIN_LEFT_RPWM, 0);
  analogWrite(PIN_LEFT_LPWM, 0);
  analogWrite(PIN_RIGHT_RPWM, 0);
  analogWrite(PIN_RIGHT_LPWM, 0);
}

void driveForward(int pwm, int durationMs = 1500) {
  Serial.print(F("[MOTORS] Driving FORWARD @ PWM "));
  Serial.print(pwm);
  Serial.print(F(" for "));
  Serial.print(durationMs);
  Serial.println(F(" ms..."));

  analogWrite(PIN_LEFT_RPWM, 0);
  analogWrite(PIN_LEFT_LPWM, pwm);
  analogWrite(PIN_RIGHT_RPWM, 0);
  analogWrite(PIN_RIGHT_LPWM, pwm);

  delay(durationMs);
  stopMotors();
  Serial.println(F("[MOTORS] Stopped."));
}

void driveReverse(int pwm, int durationMs = 1500) {
  Serial.print(F("[MOTORS] Driving REVERSE @ PWM "));
  Serial.print(pwm);
  Serial.print(F(" for "));
  Serial.print(durationMs);
  Serial.println(F(" ms..."));

  analogWrite(PIN_LEFT_RPWM, pwm);
  analogWrite(PIN_LEFT_LPWM, 0);
  analogWrite(PIN_RIGHT_RPWM, pwm);
  analogWrite(PIN_RIGHT_LPWM, 0);

  delay(durationMs);
  stopMotors();
  Serial.println(F("[MOTORS] Stopped."));
}

void spinLeft(int pwm, int durationMs = 1000) {
  Serial.print(F("[MOTORS] Spinning LEFT for "));
  Serial.print(durationMs);
  Serial.println(F(" ms..."));

  analogWrite(PIN_LEFT_RPWM, pwm);
  analogWrite(PIN_LEFT_LPWM, 0);
  analogWrite(PIN_RIGHT_RPWM, 0);
  analogWrite(PIN_RIGHT_LPWM, pwm);

  delay(durationMs);
  stopMotors();
  Serial.println(F("[MOTORS] Stopped."));
}

void spinRight(int pwm, int durationMs = 1000) {
  Serial.print(F("[MOTORS] Spinning RIGHT for "));
  Serial.print(durationMs);
  Serial.println(F(" ms..."));

  analogWrite(PIN_LEFT_RPWM, 0);
  analogWrite(PIN_LEFT_LPWM, pwm);
  analogWrite(PIN_RIGHT_RPWM, pwm);
  analogWrite(PIN_RIGHT_LPWM, 0);

  delay(durationMs);
  stopMotors();
  Serial.println(F("[MOTORS] Stopped."));
}

// ============================================================================
// HELPER: BUZZER AUDIO TEST
// ============================================================================

void testBuzzer() {
  Serial.println(F("[BUZZER] Playing Confirmation Chirps..."));

  // 3 Startup Chirps
  for (int freq = 1200; freq <= 2800; freq += 400) {
    tone(PIN_BUZZER, freq, 60);
    delay(80);
  }
  noTone(PIN_BUZZER);
  delay(200);

  // Short Police Siren sweep
  Serial.println(F("[BUZZER] Playing Police Siren Sweep..."));
  for (int i = 0; i < 2; i++) {
    for (int f = 800; f < 1800; f += 40) {
      tone(PIN_BUZZER, f);
      delay(8);
    }
    for (int f = 1800; f > 800; f -= 40) {
      tone(PIN_BUZZER, f);
      delay(8);
    }
  }
  noTone(PIN_BUZZER);
  Serial.println(F("[BUZZER] Buzzer test complete!"));
}

// ============================================================================
// HELPER: PRINT RADAR STATUS
// ============================================================================

void printRadarSnapshot() {
  float leftCm   = readUltrasonicCm(PIN_US_LEFT_TRIG, PIN_US_LEFT_ECHO);
  float centerCm = readUltrasonicCm(PIN_US_CENTER_TRIG, PIN_US_CENTER_ECHO);
  float rightCm  = readUltrasonicCm(PIN_US_RIGHT_TRIG, PIN_US_RIGHT_ECHO);

  Serial.print(F("RADAR >> [LEFT: "));
  if (leftCm > 0) {
    Serial.print(leftCm, 1);
    Serial.print(F(" cm"));
  } else {
    Serial.print(F("NO ECHO"));
  }

  Serial.print(F("]  [CENTER: "));
  if (centerCm > 0) {
    Serial.print(centerCm, 1);
    Serial.print(F(" cm"));
  } else {
    Serial.print(F("NO ECHO"));
  }

  Serial.print(F("]  [RIGHT: "));
  if (rightCm > 0) {
    Serial.print(rightCm, 1);
    Serial.print(F(" cm"));
  } else {
    Serial.print(F("NO ECHO"));
  }
  Serial.println(F("]"));
}

// ============================================================================
// FULL AUTOMATED HARDWARE SELF-TEST
// ============================================================================

void runFullSelfTest() {
  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(">>> STARTING FULL AUTOMATED HARDWARE SELF-TEST <<<"));
  Serial.println(F("===================================================="));

  // 1. Test Buzzer
  Serial.println(F("[STEP 1/4] Testing Buzzer on Pin D8..."));
  tone(PIN_BUZZER, 2000, 200);
  delay(300);
  tone(PIN_BUZZER, 2500, 200);
  delay(400);
  noTone(PIN_BUZZER);
  Serial.println(F("  -> Buzzer audio pulse sent. Did you hear 2 beeps?"));

  // 2. Test 3x Ultrasonic Sensors
  Serial.println(F("\n[STEP 2/4] Testing 3x Ultrasonic Radar Sensors..."));
  for (int i = 1; i <= 3; i++) {
    Serial.print(F("  Sample "));
    Serial.print(i);
    Serial.print(F(": "));
    printRadarSnapshot();
    delay(200);
  }

  // 3. Test Left Motor
  Serial.println(F("\n[STEP 3/4] Testing LEFT Motor (D5/D6)..."));
  analogWrite(PIN_LEFT_RPWM, 0);
  analogWrite(PIN_LEFT_LPWM, TEST_SPEED);
  delay(1000);
  stopMotors();
  delay(300);

  // 4. Test Right Motor
  Serial.println(F("\n[STEP 4/4] Testing RIGHT Motor (D9/D10)..."));
  analogWrite(PIN_RIGHT_RPWM, 0);
  analogWrite(PIN_RIGHT_LPWM, TEST_SPEED);
  delay(1000);
  stopMotors();

  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(">>> HARDWARE SELF-TEST FINISHED SUCCESSFULLY! <<<"));
  Serial.println(F("===================================================="));
  Serial.println();
}

// ============================================================================
// PRINT HELP MENU
// ============================================================================

void printHelpMenu() {
  Serial.println();
  Serial.println(F("===================================================="));
  Serial.println(F(" CYBERROVER X — ARDUINO UNO HARDWARE DIAGNOSTICS   "));
  Serial.println(F("===================================================="));
  Serial.println(F("AVAILABLE COMMANDS (Type in Serial Monitor & Enter):"));
  Serial.println(F("  w  : Drive Forward (1.5s @ PWM 160)"));
  Serial.println(F("  s  : Drive Reverse (1.5s @ PWM 160)"));
  Serial.println(F("  a  : Spin Turn Left (1.0s)"));
  Serial.println(F("  d  : Spin Turn Right (1.0s)"));
  Serial.println(F("  x  : Emergency Stop"));
  Serial.println(F("  b  : Play Buzzer Siren & Chirps (Pin D8)"));
  Serial.println(F("  r  : Toggle Continuous Radar Stream On/Off"));
  Serial.println(F("  t  : Run Full Automated Self-Test"));
  Serial.println(F("  h  : Show this Menu"));
  Serial.println(F("===================================================="));
  Serial.println();
}

// ============================================================================
// SETUP
// ============================================================================

void setup() {
  Serial.begin(115200);
  delay(400);

  // Pin Configurations
  pinMode(PIN_BUZZER, OUTPUT);
  digitalWrite(PIN_BUZZER, LOW);

  pinMode(PIN_LEFT_RPWM, OUTPUT);
  pinMode(PIN_LEFT_LPWM, OUTPUT);
  pinMode(PIN_RIGHT_RPWM, OUTPUT);
  pinMode(PIN_RIGHT_LPWM, OUTPUT);
  stopMotors();

  // 2 Startup Confirmation Beeps
  tone(PIN_BUZZER, 1800, 100);
  delay(150);
  tone(PIN_BUZZER, 2400, 120);
  delay(200);
  noTone(PIN_BUZZER);

  printHelpMenu();
  Serial.println(F("[STATUS] Hardware ready. Continuous radar stream active..."));
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
  unsigned long now = millis();

  // 1. Process User Commands from Serial Monitor
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == '\r' || cmd == '\n' || cmd == ' ') return;

    Serial.print(F("[COMMAND RECEIVED]: '"));
    Serial.print(cmd);
    Serial.println(F("'"));

    switch (cmd) {
      case 'w':
      case 'W':
        driveForward(TEST_SPEED, 1500);
        break;

      case 's':
      case 'S':
        driveReverse(TEST_SPEED, 1500);
        break;

      case 'a':
      case 'A':
        spinLeft(TEST_SPEED, 1000);
        break;

      case 'd':
      case 'D':
        spinRight(TEST_SPEED, 1000);
        break;

      case 'x':
      case 'X':
        stopMotors();
        Serial.println(F("[STOP] Motors halted."));
        break;

      case 'b':
      case 'B':
        testBuzzer();
        break;

      case 'r':
      case 'R':
        g_radarStreaming = !g_radarStreaming;
        Serial.print(F("[STREAM] Radar stream "));
        Serial.println(g_radarStreaming ? F("ENABLED (Streaming every 400ms)") : F("PAUSED"));
        break;

      case 't':
      case 'T':
        runFullSelfTest();
        break;

      case 'h':
      case 'H':
      case '?':
        printHelpMenu();
        break;

      default:
        Serial.println(F("[?] Unknown command. Type 'h' for help."));
        break;
    }
  }

  // 2. Stream Ultrasonic Distance Readings (every 400 ms)
  if (g_radarStreaming && (now - g_lastRadarPrintMs >= 400)) {
    g_lastRadarPrintMs = now;
    printRadarSnapshot();
  }
}
