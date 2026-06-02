//
// Created by elias on 23.03.26.
//
#pragma once

#include <cmath>
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

    static constexpr uint8_t SPEED_1M_MS = 1; // Time in milliseconds for 1 metre
    static constexpr uint8_t SPEED_1D_MS = 1; // Time in milliseconds for 1 degree

    static uint8_t motorSpeed;
    static uint8_t innerSpeed;

public:
    static uint32_t targetTime;

    static bool isMoving;

    static void init();

    static void update();

    static void drive_forward(float_t metres);
    static void turn_right(uint16_t degrees);

    static void curve_right(float_t metres);

    static void drive_right(float_t metres);
    static void drive_backwards(float_t metres);
    static void turn_left(uint16_t degrees);

    static void curve_left(float_t metres);

    static void drive_left(float_t metres);
    static void stop();
    static void set_motor_speed(uint8_t speed);
};
