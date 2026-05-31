//
// Created by elias on 23.03.26.
//

#include "motors.h"
#include <Arduino.h>

uint8_t Motors::motorSpeed = SPEED_DEFAULT;
uint8_t Motors::innerSpeed = (SPEED_DEFAULT * 30) / 100;

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

void Motors::drive_forward() {
    analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
    analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);
}

void Motors::turn_right() {
        analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
        digitalWrite(PIN_MOTOR_FR_1, LOW); analogWrite(PIN_MOTOR_FR_2, motorSpeed);
        analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
        digitalWrite(PIN_MOTOR_BR_1, LOW); analogWrite(PIN_MOTOR_BR_2, motorSpeed);
}

void Motors::drive_right() {
        analogWrite(PIN_MOTOR_FL_1, motorSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
        analogWrite(PIN_MOTOR_FR_1, innerSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
        analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
        analogWrite(PIN_MOTOR_BR_1, innerSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);
}

void Motors::drive_backwards() {
        digitalWrite(PIN_MOTOR_FL_1, LOW); analogWrite(PIN_MOTOR_FL_2, motorSpeed);
        digitalWrite(PIN_MOTOR_FR_1, LOW); analogWrite(PIN_MOTOR_FR_2, motorSpeed);
        digitalWrite(PIN_MOTOR_BL_1, LOW); analogWrite(PIN_MOTOR_BL_2, motorSpeed);
        digitalWrite(PIN_MOTOR_BR_1, LOW); analogWrite(PIN_MOTOR_BR_2, motorSpeed);
}

void Motors::turn_left() {
    digitalWrite(PIN_MOTOR_FL_1, LOW); analogWrite(PIN_MOTOR_FL_2, motorSpeed);
    analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
    analogWrite(PIN_MOTOR_BL_1, motorSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
    analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);
}

void Motors::drive_left() {
        analogWrite(PIN_MOTOR_FL_1, innerSpeed); digitalWrite(PIN_MOTOR_FL_2, LOW);
        analogWrite(PIN_MOTOR_FR_1, motorSpeed); digitalWrite(PIN_MOTOR_FR_2, LOW);
        analogWrite(PIN_MOTOR_BL_1, innerSpeed); digitalWrite(PIN_MOTOR_BL_2, LOW);
        analogWrite(PIN_MOTOR_BR_1, motorSpeed); digitalWrite(PIN_MOTOR_BR_2, LOW);
}

void Motors::stop() {
    digitalWrite(PIN_MOTOR_FL_1, LOW); digitalWrite(PIN_MOTOR_FL_2, LOW);
    digitalWrite(PIN_MOTOR_FR_1, LOW); digitalWrite(PIN_MOTOR_FR_2, LOW);
    digitalWrite(PIN_MOTOR_BL_1, LOW); digitalWrite(PIN_MOTOR_BL_2, LOW);
    digitalWrite(PIN_MOTOR_BR_1, LOW); digitalWrite(PIN_MOTOR_BR_2, LOW);
}

void Motors::set_motor_speed(int speed) {
        motorSpeed = constrain(speed, SPEED_MIN, SPEED_MAX);
        innerSpeed = (motorSpeed * 30) / 100;
    }