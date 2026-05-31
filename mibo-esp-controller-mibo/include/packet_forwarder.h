//
// Created by elias on 20.05.26.
//

#pragma once
#include <cstdint>

class PacketForwarder {
public:
    static void forwardToTeensy(const uint8_t* buffer);
    static void forwardToEsp(const uint8_t* buffer);

    static void update();
};
