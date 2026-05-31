// Created by elias on 20.05.26.
#pragma once
#include "protocol.h"

class PacketHandler {
public:
    enum class RxState : uint8_t {
        WAIT_START,
        READ_CMD,
        READ_PAYLOAD,
        READ_CRC
    };

    static void parseByte(uint8_t byte);
    
    static void setOnPacketReceived(void (*callback)(const RxPacket&));

private:

    static void (*m_onPacketReceivedCallback)(const RxPacket&);

    static uint8_t m_payloadBuffer[32];
    static RxState m_rxState;
    static uint8_t m_bytesToRead;
    static uint8_t m_bytesRead;
    static Packet m_currentCmd;
    static uint8_t m_calculatedCrc;
};
