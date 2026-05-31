//
// Created by elias on 19.05.26.
//
#include "teensy_controller.h"
#include <Arduino.h>

void TeensyController::begin() {
    Serial1.begin(115200);
}

void TeensyController::write(const std::uint8_t* data, size_t size) {
    if (data != nullptr && size > 0) {
        Serial1.write(data, size);
    }
}