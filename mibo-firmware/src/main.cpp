#include <Arduino.h>
#include <Wire.h>

#include <motors.h>
#include <gps.h>
#include "../lib/esp_controller/esp_controller.h"
#include "../lib/ultrasonic/ultrasonic.h"

void setup() {
    Wire.begin(); //SDA 18 SCL 19
    Motors::init();
    GPS::begin();
    Ultrasonic::init();
    ESPController::begin();
}

void loop() {
    GPS::update();
    ESPController::update();
}
