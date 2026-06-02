//
// Created by elias on 23.03.26.
//

#include "motors.h"
#include <Arduino.h>

uint8_t Motors::motorSpeed = SPEED_DEFAULT;
uint8_t Motors::innerSpeed = (SPEED_DEFAULT * 30) / 100;
uint32_t Motors::targetTime = 0;
bool Motors::isMoving = false;

void Motors::init() {
    pinMode(PIN_MOTOR_FL_1, OUTPUT);
    pinMode(PIN_MOTOR_FL_2, OUTPUT);
    pinMode(PIN_MOTOR_FR_1, OUTPUT);
    pinMode(PIN_MOTOR_FR_2, OUTPUT);
    pinMode(PIN_MOTOR_BL_1, OUTPUT);
    pinMode(PIN_MOTOR_BL_2, OUTPUT);
    pinMode(PIN_MOTOR_BR_1, OUTPUT);
    pinMode(PIN_MOTOR_BR_2, OUTPUT);
}

void Motors::update() {
    if (isMoving && millis() >= targetTime) {
        stop();
    }
}

void Motors::drive_forward(const float_t metres) {
    analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
    analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);

    targetTime = millis() + static_cast<uint32_t>(metres * static_cast<float_t>(SPEED_1M_MS));
    isMoving = true;
}

void Motors::turn_right(const uint16_t degrees) {
    analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
    digitalWrite(PIN_MOTOR_FR_1, LOW); analogWrite(PIN_MOTOR_FR_2, motorSpeed);
    analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    digitalWrite(PIN_MOTOR_BR_1, LOW); analogWrite(PIN_MOTOR_BR_2, motorSpeed);

    targetTime = millis() + (degrees * SPEED_1D_MS);
    isMoving = true;
}

void Motors::curve_right(const float_t metres) {
    analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
    analogWrite(PIN_MOTOR_FR_1, innerSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    analogWrite(PIN_MOTOR_BR_1, innerSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);

    targetTime = millis() + static_cast<uint32_t>(metres * static_cast<float_t>(SPEED_1M_MS));
    isMoving = true;
}

void Motors::drive_backwards(const float_t metres) {
    digitalWrite(PIN_MOTOR_FL_1, LOW); analogWrite(PIN_MOTOR_FL_2, motorSpeed);
    digitalWrite(PIN_MOTOR_FR_1, LOW); analogWrite(PIN_MOTOR_FR_2, motorSpeed);
    digitalWrite(PIN_MOTOR_BL_1, LOW); analogWrite(PIN_MOTOR_BL_2, motorSpeed);
    digitalWrite(PIN_MOTOR_BR_1, LOW); analogWrite(PIN_MOTOR_BR_2, motorSpeed);

    targetTime = millis() + static_cast<uint32_t>(metres * static_cast<float_t>(SPEED_1M_MS));
    isMoving = true;
}

void Motors::turn_left(const uint16_t degrees) {
    digitalWrite(PIN_MOTOR_FL_1, LOW); analogWrite(PIN_MOTOR_FL_2, motorSpeed);
    analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    digitalWrite(PIN_MOTOR_BL_1, LOW); digitalWrite(PIN_MOTOR_BL_2, motorSpeed);
    analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);

    targetTime = millis() + (degrees * SPEED_1D_MS);
    isMoving = true;
}

void Motors::curve_left(const float_t metres) {
    analogWrite(PIN_MOTOR_FL_1, innerSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
    analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    analogWrite(PIN_MOTOR_BL_1, innerSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);

    targetTime = millis() + static_cast<uint32_t>(metres * static_cast<float_t>(SPEED_1M_MS));
    isMoving = true;
}

void Motors::stop() {
    digitalWrite(PIN_MOTOR_FL_1, LOW); digitalWrite(PIN_MOTOR_FL_2, LOW);
    digitalWrite(PIN_MOTOR_FR_1, LOW); digitalWrite(PIN_MOTOR_FR_2, LOW);
    digitalWrite(PIN_MOTOR_BL_1, LOW); digitalWrite(PIN_MOTOR_BL_2, LOW);
    digitalWrite(PIN_MOTOR_BR_1, LOW); digitalWrite(PIN_MOTOR_BR_2, LOW);

    isMoving = false;
}

void Motors::set_motor_speed(uint8_t speed) {
        motorSpeed = constrain(speed, SPEED_MIN, SPEED_MAX);
        innerSpeed = (motorSpeed * 30) / 100;
    }