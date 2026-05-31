//
// Created by elias on 20.05.26.
//

#include "esp_now_controller.h"
#include "packet_forwarder.h"
#include <esp_now.h>
#include <esp_wifi.h>
#include <Arduino.h>
#include <nvs_flash.h>

void ESPNowController::init() {
    // 1. Configure and switch RF hardware to the external antenna
    pinMode(WIFI_ENABLE, OUTPUT);
    digitalWrite(WIFI_ENABLE, LOW);     // Enable RF switch power control

    pinMode(WIFI_ANT_CONFIG, OUTPUT);
    digitalWrite(WIFI_ANT_CONFIG, HIGH);

    // 2. Initialize Non-Volatile Storage (NVS) to prevent Wi-Fi crashes
    if (const esp_err_t ret = nvs_flash_init(); ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }

    // Initialize the Wi-Fi in Station (STA) mode.
    const wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_wifi_set_storage(WIFI_STORAGE_RAM); // Protects flash memory from wear
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();

    // Set Channel to WIFI_CHANNEL
    esp_wifi_set_channel(WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);

    // Set tx power to 80 (equals +20 dBm (100mW)).
    esp_wifi_set_max_tx_power(80);

    // Initialize the ESP-NOW protocol layer
    if (esp_now_init() != ESP_OK) {
        return;
    }

    // Register the packet reception callback
    esp_now_register_recv_cb(onDataReceive);

    // Configure and register the remote peer link on Channel 1
    esp_now_peer_info_t peerInfo = {};
    for (std::size_t i = 0; i < 6; ++i) {
        peerInfo.peer_addr[i] = ESP_MAC_ADDRESS[i];
    }
    peerInfo.channel = WIFI_CHANNEL; //Set ESP_NOW channel
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    // Tune for long distance
    wifi_tx_rate_config_t rateConfig = {};
    rateConfig.phymode = WIFI_PHY_MODE_11B;  // Long-range legacy 802.11b mode
    rateConfig.rate    = WIFI_PHY_RATE_1M_L; // Force 1 Mbps rate for maximum receiver sensitivity
    rateConfig.ersu    = true;               // Enable Extended Range Single User mode for ESP32-C6
    rateConfig.dcm     = false;

    esp_now_set_peer_rate_config(ESP_MAC_ADDRESS, &rateConfig);
}

void ESPNowController::send(const uint8_t *data, const std::size_t len) {
    if (data != nullptr) {
        esp_now_send(ESP_MAC_ADDRESS, data, len);
    }
}

void ESPNowController::onDataReceive(const esp_now_recv_info_t *recvInfo, const uint8_t *data, const int len) {
    if (data != nullptr && len > 0 && recvInfo != nullptr && recvInfo->rx_ctrl != nullptr) {


        // ------------------------- DEBUG -----------------------------
        // Extract Received Signal Strength Indicator (RSSI) in dBm
        const int rssi = recvInfo->rx_ctrl->rssi;

        // Log diagnostics for antenna alignment and field testing
        Serial.print("Packet received on Ch1! RSSI: ");
        Serial.print(rssi);
        Serial.println(" dBm");

        // Forward the buffer to the Teensy
        PacketForwarder::forwardToTeensy(data);
    }
}
