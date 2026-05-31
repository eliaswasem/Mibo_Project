//
// Created by elias on 19.05.26.
//
#include "esp_controller.h"

#include "packet_handler.h"

void ESPController::begin() {
    Serial8.begin(115200);
}

void ESPController::write(const uint8_t* data, size_t size) {
    if (data != nullptr && size > 0) {
        Serial8.write(data, size);
    }
}

void ESPController::update() {
    if (Serial8.available()) {
        PacketHandler::parseByte(Serial8.read());
    }
}