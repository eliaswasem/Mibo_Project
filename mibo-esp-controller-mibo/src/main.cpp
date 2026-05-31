//
// Created by elias on 20.05.26.
//

#include "esp_now_controller.h"
#include "packet_forwarder.h"
#include "teensy_controller.h"

void setup() {
    TeensyController::begin();
    ESPNowController::init();
}

void loop() {
    PacketForwarder::update();
}