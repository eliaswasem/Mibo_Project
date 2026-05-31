// Created by elias on 20.05.26.
#pragma once
#include <cstdint>
#include <cstddef>

inline constexpr uint8_t PROTOCOL_START = 0xAA;

enum class Packet : uint8_t {
    SPEED = 0x01,
    STOP  = 0x02,
    GOTO  = 0x10
};

// Enforces 1-byte boundary alignment for exact cross-platform structure layout
#pragma pack(push, 1)
struct SpeedPayload { uint8_t speed; };
struct GotoPayload  { int32_t lat; int32_t lon; };
#pragma pack(pop)

struct RxPacket {
    Packet cmd;
    const uint8_t* data;
    uint8_t dataLen;
};

// Maps command type to payload size and checks command validity
inline constexpr int16_t getPayloadSize(Packet cmd) {
    switch (cmd) {
        case Packet::SPEED: return sizeof(SpeedPayload);
        case Packet::STOP:  return 0;
        case Packet::GOTO:  return sizeof(GotoPayload);
        default:            return -1;
    }
}
