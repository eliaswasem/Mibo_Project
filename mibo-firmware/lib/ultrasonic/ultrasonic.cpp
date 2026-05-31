//
// Created by elias on 18.05.26.
//

#include "ultrasonic.h"

#include <Arduino.h>

void Ultrasonic::init() {
    pinMode(PIN_US_TRIG_FRONT, OUTPUT);
    pinMode(PIN_US_ECHO_FRONT, INPUT);

    pinMode(PIN_US_TRIG_BACK, OUTPUT);
    pinMode(PIN_US_ECHO_BACK, INPUT);

    pinMode(PIN_US_TRIG_RIGHT, OUTPUT);
    pinMode(PIN_US_ECHO_RIGHT, INPUT);

    pinMode(PIN_US_TRIG_LEFT, OUTPUT);
    pinMode(PIN_US_ECHO_LEFT, INPUT);
}


float Ultrasonic::getDistance(const UltrasonicSensorID id) {
    const auto&[trigPin, echoPin] = sensors[id];

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    u_long duration = pulseInLong(echoPin, HIGH, 30000); // 30ms timeout

    if (duration == 0) {
        return 400.0f; // 400 means no obstacle
    }
    return static_cast<float>(duration) * 0.0343f / 2.0f;
}
