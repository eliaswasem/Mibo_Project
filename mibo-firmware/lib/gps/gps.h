#pragma once

#include <TinyGPS++.h>
#include <Arduino.h>

class GPS {
    static TinyGPSPlus gps;
public:
    static void begin();
    static void update();

    static bool hasFix();
    static uint32_t satellites();
    static double getLat();
    static double getLng();

    static double distanceTo(double destLat, double destLng);
    static double courseTo(double destLat, double destLng);
};
