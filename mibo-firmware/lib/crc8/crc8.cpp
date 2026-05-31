// Created by elias on 20.05.26.
#include "crc8.h"

uint8_t CRC8::calculate(const uint8_t* data, size_t len) {
    uint8_t crc = 0x00;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) crc = (crc << 1) ^ 0x31;
            else            crc <<= 1;
        }
    }
    return crc;
}

void CRC8::update(uint8_t& crc, uint8_t byte) {
    crc ^= byte;
    for (uint8_t j = 0; j < 8; j++) {
        if (crc & 0x80) crc = (crc << 1) ^ 0x31;
        else            crc <<= 1;
    }
}
