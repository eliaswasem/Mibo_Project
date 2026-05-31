// Created by elias on 20.05.26.
#pragma once
#include <cstdint>
#include <cstddef>

class CRC8 {
public:
    static uint8_t calculate(const uint8_t* data, size_t len);
    static void update(uint8_t& crc, uint8_t byte);
};
