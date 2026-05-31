// Created by elias on 20.05.26.
#include "app_controller.h"
#include <cstring>
#include <packet_handler.h>

void AppController::init() {
    PacketHandler::setOnPacketReceived(AppController::onPacketReceived);
}

void AppController::onPacketReceived(const RxPacket& packet) {
    switch (packet.cmd) {

        case Packet::SPEED: {
            if (packet.dataLen == sizeof(SpeedPayload)) {
                SpeedPayload payload;
                std::memcpy(&payload, packet.data, sizeof(SpeedPayload));
            }
            break;
        }

        case Packet::STOP: {
            break;
        }

        case Packet::GOTO: {
            if (packet.dataLen == sizeof(GotoPayload)) {
                GotoPayload payload;
                // Copies bytes to a aligned memory structure to prevent architecture alignment faults
                std::memcpy(&payload, packet.data, sizeof(GotoPayload));
            }
            break;
        }

        default:
            break;
    }
}
