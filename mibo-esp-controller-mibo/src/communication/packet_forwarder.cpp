//
// Created by elias on 20.05.26.
//

#include "packet_forwarder.h"
#include "protocol.h"
#include "teensy_controller.h"
#include "esp_now_controller.h"

void PacketForwarder::forwardToTeensy(const uint8_t* buffer) {
    if (buffer != nullptr && buffer[0] == PROTOCOL_START) {
        const auto cmd = static_cast<Packet>(buffer[1]);

        if (const int16_t payloadSize = getPayloadSize(cmd); payloadSize >= 0) {
            const size_t totalSize = 1 + 1 + static_cast<size_t>(payloadSize) + 1;
            TeensyController::write(buffer, totalSize);
        }
    }
}

void PacketForwarder::forwardToEsp(const uint8_t* buffer) {
    if (buffer != nullptr && buffer[0] == PROTOCOL_START) {
        const auto cmd = static_cast<Packet>(buffer[1]);

        if (const int16_t payloadSize = getPayloadSize(cmd); payloadSize >= 0) {
            const size_t totalSize = 1 + 1 + static_cast<size_t>(payloadSize) + 1;
            ESPNowController::send(buffer, totalSize);
        }
    }
}
