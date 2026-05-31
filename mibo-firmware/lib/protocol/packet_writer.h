// Created by elias on 20.05.26.
#pragma once
#include <cstdint>

class PacketWriter {
public:
    static void write_packet(const uint8_t* buffer);
};
