//
// Created by elias on 18.05.26.
//
#pragma once

#include <cstdint>

struct UltrasonicSensor {
    int trigPin;
    int echoPin;
};

enum UltrasonicSensorID {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    SENSOR_COUNT
};

class Ultrasonic {
    static constexpr uint8_t PIN_US_TRIG_FRONT = 1;
    static constexpr uint8_t PIN_US_ECHO_FRONT = 2;
    static constexpr uint8_t PIN_US_TRIG_BACK = 3;
    static constexpr uint8_t PIN_US_ECHO_BACK = 4;
    static constexpr uint8_t PIN_US_TRIG_LEFT = 5;
    static constexpr uint8_t PIN_US_ECHO_LEFT = 6;
    static constexpr uint8_t PIN_US_TRIG_RIGHT = 7;
    static constexpr uint8_t PIN_US_ECHO_RIGHT = 8;
public:
    static constexpr UltrasonicSensor sensors[SENSOR_COUNT] = {
        {PIN_US_TRIG_FRONT, PIN_US_ECHO_FRONT},
        {PIN_US_TRIG_LEFT,  PIN_US_ECHO_LEFT},
        {PIN_US_TRIG_RIGHT, PIN_US_ECHO_RIGHT},
        {PIN_US_TRIG_BACK,  PIN_US_ECHO_BACK},
    };

    static void init();
    static float getDistance(UltrasonicSensorID id);
};