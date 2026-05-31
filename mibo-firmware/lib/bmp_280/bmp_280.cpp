//
// Created by catgod on 19.05.26.
//

#include "bmp_280.h"
#include <Adafruit_BMP280.h>

static Adafruit_BMP280 bmp;

bool BMP280::init() {
    // Teensy 4.1 standard use Pin 19 (SCL)and Pin 18 (SDA)
    // 0x77 is Standard-I2C-Adresse (some boards use 0x76)
    if (!bmp.begin(0x77)) {
        return false;
    }

    // Sensor-Settings
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Use Mode */
                    Adafruit_BMP280::SAMPLING_X2,     /* TemperatureOversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure-Oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filter */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby-Time */
    return true;
}

float BMP280::getTemperature() {
    return bmp.readTemperature();
}

float BMP280::getPressure() {
    return bmp.readPressure();
}
