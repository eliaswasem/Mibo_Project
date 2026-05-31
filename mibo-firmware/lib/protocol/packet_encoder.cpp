// Created by elias on 20.05.26.
#include "packet_encoder.h"
#include "crc8.h"
#include <cstring>

thread_local uint8_t PacketEncoder::m_sendBuffer[PacketEncoder::BUFFER_SIZE] = {0};

const uint8_t* PacketEncoder::encode(Packet cmd, const void* payloadData, size_t payloadSize) {
    int16_t expectedSize = getPayloadSize(cmd);
    if (expectedSize < 0) return nullptr;

    m_sendBuffer[0] = PROTOCOL_START;
    m_sendBuffer[1] = static_cast<uint8_t>(cmd);

    if (payloadData != nullptr && expectedSize > 0) {
        std::memcpy(&m_sendBuffer[HEADER_SIZE], payloadData, expectedSize);
    }

    size_t crcDataLen = 1 + expectedSize;
    uint8_t crc = CRC8::calculate(&m_sendBuffer[1], crcDataLen);

    m_sendBuffer[HEADER_SIZE + expectedSize] = crc;
    return m_sendBuffer;
}
