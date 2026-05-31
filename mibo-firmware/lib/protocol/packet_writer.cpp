// Created by elias on 20.05.26.
#include "packet_writer.h"

#include <esp_controller.h>
#include "protocol.h"

void PacketWriter::write_packet(const uint8_t* buffer) {
    // Fixed: check the underlying value of the pointer index [0]
    if (buffer != nullptr && buffer[0] == PROTOCOL_START) {

        // Fixed: read the command out of the buffer index [1]
        Packet cmd = static_cast<Packet>(buffer[1]);

        int16_t payloadSize = getPayloadSize(cmd);
        if (payloadSize < 0) return;

        size_t total_size = 1 + 1 + static_cast<size_t>(payloadSize) + 1;

        ESPController::write(buffer, total_size);
    }
}
