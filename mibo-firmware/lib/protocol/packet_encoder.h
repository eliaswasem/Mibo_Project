// Created by elias on 20.05.26.
#pragma once
#include "protocol.h"

class PacketEncoder {
public:
    static constexpr size_t BUFFER_SIZE = 64;
    static constexpr size_t MAX_PAYLOAD_SIZE = 32;
    static constexpr size_t HEADER_SIZE = 2;

    static const uint8_t* encode(Packet cmd, const void* payloadData, size_t payloadSize);

private:
    thread_local static uint8_t m_sendBuffer[BUFFER_SIZE];
};
