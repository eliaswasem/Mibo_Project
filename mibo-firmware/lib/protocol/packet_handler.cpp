// Created by elias on 20.05.26.
#include "packet_handler.h"
#include <crc8.h>

uint8_t PacketHandler::m_payloadBuffer[32] = {0};
PacketHandler::RxState PacketHandler::m_rxState = PacketHandler::RxState::WAIT_START;
uint8_t PacketHandler::m_bytesToRead = 0;
uint8_t PacketHandler::m_bytesRead = 0;
Packet PacketHandler::m_currentCmd = static_cast<Packet>(0);
uint8_t PacketHandler::m_calculatedCrc = 0;

void (*PacketHandler::m_onPacketReceivedCallback)(const RxPacket&) = nullptr;

void PacketHandler::setOnPacketReceived(void (*callback)(const RxPacket&)) {
    m_onPacketReceivedCallback = callback;
}

void PacketHandler::parseByte(uint8_t byte) {
    switch (m_rxState) {

        case RxState::WAIT_START:
            if (byte == PROTOCOL_START) m_rxState = RxState::READ_CMD;
            break;

        case RxState::READ_CMD: {
            m_currentCmd = static_cast<Packet>(byte);

            int16_t payloadSize = getPayloadSize(m_currentCmd);
            if (payloadSize < 0) {
                m_rxState = RxState::WAIT_START;
                break;
            }

            m_bytesToRead = static_cast<uint8_t>(payloadSize);
            m_bytesRead = 0;
            m_calculatedCrc = 0x00;
            CRC8::update(m_calculatedCrc, byte);

            if (m_bytesToRead == 0) m_rxState = RxState::READ_CRC;
            else                    m_rxState = RxState::READ_PAYLOAD;
            break;
        }

        case RxState::READ_PAYLOAD:
            m_payloadBuffer[m_bytesRead++] = byte;
            CRC8::update(m_calculatedCrc, byte);

            if (m_bytesRead == m_bytesToRead) m_rxState = RxState::READ_CRC;
            break;

        case RxState::READ_CRC:
            if (byte == m_calculatedCrc) {
                RxPacket packet{m_currentCmd, m_payloadBuffer, m_bytesToRead};
                if (m_onPacketReceivedCallback != nullptr) {
                    m_onPacketReceivedCallback(packet);
                }
            }
            m_rxState = RxState::WAIT_START;
            break;
    }
}
