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


void PacketForwarder::update() {
    // Keep local parser state across execution ticks without dynamic allocation
    static uint8_t rxBuffer[256];
    static size_t bytesRead = 0;
    static int16_t expectedPayloadSize = -1;

    // Process all bytes currently waiting in the hardware serial FIFO buffer
    while (Serial1.available() > 0) {
        const uint8_t incomingByte = Serial1.read();

        // State 0: Look for the unique protocol start identifier
        if (bytesRead == 0) {
            if (incomingByte == PROTOCOL_START) {
                rxBuffer[bytesRead++] = incomingByte;
            }
            continue;
        }

        // State 1: Grab the command type and fetch its expected data length
        if (bytesRead == 1) {
            rxBuffer[bytesRead++] = incomingByte;
            const auto cmd = static_cast<Packet>(incomingByte);
            expectedPayloadSize = getPayloadSize(cmd);

            // Safety Check: Drop frame if command is invalid OR exceeds buffer capacity
            const size_t totalExpectedSize = 2 + static_cast<size_t>(expectedPayloadSize) + 1;
            if (expectedPayloadSize < 0 || totalExpectedSize > sizeof(rxBuffer)) {
                bytesRead = 0;
                expectedPayloadSize = -1;
            }
            continue;
        }


        // State 2: Accumulate payload data and the closing end byte
        const size_t totalExpectedSize = 2 + static_cast<size_t>(expectedPayloadSize) + 1;

        if (bytesRead < totalExpectedSize) {
            rxBuffer[bytesRead++] = incomingByte;

            // Trigger transmission once the frame is fully assembled
            if (bytesRead == totalExpectedSize) {
                forwardToEsp(rxBuffer);

                // Reset state machine for the next incoming stream packet
                bytesRead = 0;
                expectedPayloadSize = -1;
            }
        }
    }
}