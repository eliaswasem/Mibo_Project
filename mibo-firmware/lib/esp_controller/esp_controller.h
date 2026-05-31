//
// Created by elias on 19.05.26.
//

#pragma once

#include <Arduino.h>

class ESPController {
public:
    static void begin();
    static void write(const uint8_t *data, size_t size);

    static void update();
};
