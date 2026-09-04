/**
 * ============================================================================
 * PROJECT   : CYBERROVER X — NODE 03: MOTOR CONTROLLER & SOUND BRAIN
 * FILE      : AutoNavigator.h
 * PURPOSE   : Manual, Semi-Auto (Collision Assist) & Full Autonomous Navigation
 * MCU       : Arduino Uno (ATmega328P)
 * ============================================================================
 */

#ifndef UNO_AUTO_NAVIGATOR_H
#define UNO_AUTO_NAVIGATOR_H

#include <Arduino.h>
#include "Config.h"
#include "MotorDriver.h"
#include "RadarSensors.h"

enum AutoState {
  STATE_FORWARD,
  STATE_STEER_LEFT,
  STATE_STEER_RIGHT,
  STATE_TURN_LEFT,
  STATE_TURN_RIGHT,
  STATE_ESCAPE_REVERSE,
  STATE_ESCAPE_SPIN
};

class AutoNavigator {
private:
  AutoState     autoState;
  unsigned long stateStartMs;
  unsigned long actionDurationMs;
  uint8_t       consecutiveTurns;
  unsigned long lastTurnMs;
  bool          lastTurnWasLeft;

// Direction configuration: Set to (+1) for normal forward, (-1) if mechanically reversed
#define AUTO_DRIVE_DIR (+1)

  void autoDriveMotors(MotorDriver &motors, int leftPwm, int rightPwm) {
    motors.setTargets(constrain(leftPwm, -MAX_PWM, MAX_PWM),
                      constrain(rightPwm, -MAX_PWM, MAX_PWM));
  }

  void autoCruiseForward(MotorDriver &motors, int speed = AUTO_CRUISE_PWM) {
    autoDriveMotors(motors, AUTO_DRIVE_DIR * speed, AUTO_DRIVE_DIR * speed); // Forward cruise
  }

  void autoCruiseReverse(MotorDriver &motors, int speed = AUTO_REVERSE_PWM) {
    autoDriveMotors(motors, -AUTO_DRIVE_DIR * speed, -AUTO_DRIVE_DIR * speed); // Reverse escape
  }

  void autoPivotLeft(MotorDriver &motors, int speed = AUTO_TURN_PWM) {
    autoDriveMotors(motors, -AUTO_DRIVE_DIR * speed, AUTO_DRIVE_DIR * speed); // Left reverse, Right forward
  }

  void autoPivotRight(MotorDriver &motors, int speed = AUTO_TURN_PWM) {
    autoDriveMotors(motors, AUTO_DRIVE_DIR * speed, -AUTO_DRIVE_DIR * speed); // Left forward, Right reverse
  }

  void autoSteerForwardLeft(MotorDriver &motors, int highSpeed = CORRIDOR_HIGH_PWM, int lowSpeed = CORRIDOR_LOW_PWM) {
    autoDriveMotors(motors, AUTO_DRIVE_DIR * lowSpeed, AUTO_DRIVE_DIR * highSpeed);
  }

  void autoSteerForwardRight(MotorDriver &motors, int highSpeed = CORRIDOR_HIGH_PWM, int lowSpeed = CORRIDOR_LOW_PWM) {
    autoDriveMotors(motors, AUTO_DRIVE_DIR * highSpeed, AUTO_DRIVE_DIR * lowSpeed);
  }

public:
  AutoNavigator()
    : autoState(STATE_FORWARD), stateStartMs(0), actionDurationMs(0),
      consecutiveTurns(0), lastTurnMs(0), lastTurnWasLeft(false) {}

  void resetAutoState() {
    autoState = STATE_FORWARD;
    stateStartMs = millis();
    consecutiveTurns = 0;
    lastTurnMs = millis();
  }

  void calculateManual(MotorDriver &motors, int8_t throttle, int8_t steering) {
    if (abs(throttle) < JOY_DEADZONE && abs(steering) < JOY_DEADZONE) {
      motors.setTargets(0, 0);
      return;
    }

    // Pure tank pivot in place
    if (abs(throttle) < JOY_DEADZONE && abs(steering) >= JOY_DEADZONE) {
      int turnPwm = map(abs(steering), JOY_DEADZONE, 100, MIN_TURN_PWM, MAX_PWM);
      if (steering > 0) { // Turn Right
        motors.setTargets(turnPwm, -turnPwm);
      } else { // Turn Left
        motors.setTargets(-turnPwm, turnPwm);
      }
      return;
    }

    // Smooth forward/reverse arcade drive
    int basePwm = 0;
    if (throttle > 0) {
      basePwm = map(throttle, JOY_DEADZONE, 100, MIN_DRIVE_PWM, MAX_PWM);
    } else {
      basePwm = -map(-throttle, JOY_DEADZONE, 100, MIN_DRIVE_PWM, MAX_PWM);
    }

    float turnRatio = (float)steering / 100.0f;
    int leftPwm = basePwm;
    int rightPwm = basePwm;

    if (steering > 0) { // Steer Right
      rightPwm = (int)((float)basePwm * (1.0f - (turnRatio * 1.6f)));
    } else if (steering < 0) { // Steer Left
      leftPwm = (int)((float)basePwm * (1.0f - (-turnRatio * 1.6f)));
    }

    motors.setTargets(constrain(leftPwm, -MAX_PWM, MAX_PWM),
                      constrain(rightPwm, -MAX_PWM, MAX_PWM));
  }

  void calculateSemiAuto(MotorDriver &motors, const RadarSensors &radar, int8_t throttle, int8_t steering) {
    // If moving forward and obstacle is within critical stop distance -> Override brake
    if (throttle > 0 && radar.getDistCenter() < DIST_CRITICAL_STOP) {
      motors.setTargets(0, 0);
      return;
    }
    calculateManual(motors, throttle, steering);
  }

  void updateAuto(MotorDriver &motors, const RadarSensors &radar) {
    unsigned long now = millis();
    unsigned long stateElapsed = now - stateStartMs;

    float distL = radar.getDistLeft();
    float distC = radar.getDistCenter();
    float distR = radar.getDistRight();

    switch (autoState) {
      // 1. FORWARD CRUISE
      case STATE_FORWARD:
        autoCruiseForward(motors, AUTO_CRUISE_PWM);

        // A. Emergency Critical Stop & Reverse (< 20 cm)
        if (distC < DIST_CRITICAL_STOP) {
          autoState = STATE_ESCAPE_REVERSE;
          stateStartMs = now;
          actionDurationMs = 450;
          consecutiveTurns++;
          lastTurnMs = now;
          break;
        }

        // B. Obstacle Ahead (< 45 cm) -> Choose Best Turn Direction
        if (distC < DIST_OBSTACLE_WARN) {
          if (distL >= distR) {
            autoState = STATE_TURN_LEFT;
            lastTurnWasLeft = true;
          } else {
            autoState = STATE_TURN_RIGHT;
            lastTurnWasLeft = false;
          }
          stateStartMs = now;
          actionDurationMs = 400;
          consecutiveTurns++;
          lastTurnMs = now;
          break;
        }

        // C. Side Wall Corridor Tracking
        if (distL < DIST_SIDE_WALL && distR >= DIST_SIDE_WALL) {
          autoState = STATE_STEER_RIGHT;
          stateStartMs = now;
          actionDurationMs = 220;
          break;
        } else if (distR < DIST_SIDE_WALL && distL >= DIST_SIDE_WALL) {
          autoState = STATE_STEER_LEFT;
          stateStartMs = now;
          actionDurationMs = 220;
          break;
        }

        // Reset trapped counter after 3s of clear driving
        if (now - lastTurnMs > 3000) {
          consecutiveTurns = 0;
        }
        break;

      // 2. CORRIDOR STEERING
      case STATE_STEER_LEFT:
        autoSteerForwardLeft(motors, CORRIDOR_HIGH_PWM, CORRIDOR_LOW_PWM);
        if (stateElapsed >= actionDurationMs || distC < DIST_OBSTACLE_WARN) {
          autoState = STATE_FORWARD;
          stateStartMs = now;
        }
        break;

      case STATE_STEER_RIGHT:
        autoSteerForwardRight(motors, CORRIDOR_HIGH_PWM, CORRIDOR_LOW_PWM);
        if (stateElapsed >= actionDurationMs || distC < DIST_OBSTACLE_WARN) {
          autoState = STATE_FORWARD;
          stateStartMs = now;
        }
        break;

      // 3. TANK PIVOT TURNS
      case STATE_TURN_LEFT:
        autoPivotLeft(motors, AUTO_TURN_PWM);
        if (stateElapsed >= actionDurationMs) {
          if (distC >= DIST_OBSTACLE_WARN || stateElapsed >= 800) {
            autoState = STATE_FORWARD;
            stateStartMs = now;
          }
        }
        break;

      case STATE_TURN_RIGHT:
        autoPivotRight(motors, AUTO_TURN_PWM);
        if (stateElapsed >= actionDurationMs) {
          if (distC >= DIST_OBSTACLE_WARN || stateElapsed >= 800) {
            autoState = STATE_FORWARD;
            stateStartMs = now;
          }
        }
        break;

      // 4. CRITICAL REVERSE ESCAPE
      case STATE_ESCAPE_REVERSE:
        autoCruiseReverse(motors, AUTO_REVERSE_PWM);
        if (stateElapsed >= actionDurationMs) {
          if (consecutiveTurns >= 4) {
            autoState = STATE_ESCAPE_SPIN;
            actionDurationMs = 750;
          } else {
            autoState = (distL >= distR) ? STATE_TURN_LEFT : STATE_TURN_RIGHT;
            actionDurationMs = 450;
          }
          stateStartMs = now;
        }
        break;

      // 5. 180-DEGREE TRAP ESCAPE SPIN
      case STATE_ESCAPE_SPIN:
        autoPivotLeft(motors, AUTO_TURN_PWM);
        if (stateElapsed >= actionDurationMs) {
          consecutiveTurns = 0;
          autoState = STATE_FORWARD;
          stateStartMs = now;
        }
        break;

      default:
        autoState = STATE_FORWARD;
        stateStartMs = now;
        break;
    }
  }

  AutoState getAutoState() const { return autoState; }
};

#endif // UNO_AUTO_NAVIGATOR_H
