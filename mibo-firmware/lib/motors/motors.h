//
// Created by elias on 23.03.26.
//
#pragma once

#include <cstdint>

class Motors {
    static constexpr uint8_t PIN_MOTOR_FL_1 = 21;
    static constexpr uint8_t PIN_MOTOR_FL_2 = 47;
    static constexpr uint8_t PIN_MOTOR_FR_1 = 13;
    static constexpr uint8_t PIN_MOTOR_FR_2 = 14;
    static constexpr uint8_t PIN_MOTOR_BL_1 = 15;
    static constexpr uint8_t PIN_MOTOR_BL_2 = 16;
    static constexpr uint8_t PIN_MOTOR_BR_1 = 11;
    static constexpr uint8_t PIN_MOTOR_BR_2 = 12;

    static constexpr uint8_t SPEED_MIN = 0;
    static constexpr uint8_t SPEED_MAX = 255;
    static constexpr uint8_t SPEED_DEFAULT = 150;

    static uint8_t motorSpeed;
    static uint8_t innerSpeed;

public:
    static void init();
    static void drive_forward();
    static void turn_right();
    static void drive_right();
    static void drive_backwards();
    static void turn_left();
    static void drive_left();
    static void stop();
    static void set_motor_speed(int speed);
};
