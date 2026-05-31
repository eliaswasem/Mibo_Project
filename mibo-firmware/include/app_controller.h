// Created by elias on 20.05.26.
#pragma once
#include "../lib/protocol/protocol.h"

class AppController {
public:
    static void init();
    static void onPacketReceived(const RxPacket& packet);
};
