//
// Created by catgod on 20.5.2026
//

#pragma once
#include <Arduino.h>
#include <Adafruit_QMC5883P.h>
#include <cstdint>

class Compass {
private:
    static Adafruit_QMC5883P qmc; // Hardware driver instance for the QMC5883P sensor
    static bool isInitialized;    // Status flag tracking if the sensor started successfully

public:
    // Fixed I2C address for the QMC5883P hardware sensor
    static constexpr uint8_t COMPASS_ADDRESS = 0x76;

    // Public 3D calibration offsets manually set in the header
    static inline float offsetX = 0.0f;
    static inline float offsetY = 0.0f;
    static inline float offsetZ = 0.0f;

    /**
     * Initializes the I2C connection using the COMPASS_ADDRESS.
     * @return true if the sensor is detected and ready, false on failure.
     */
    static bool begin();

    /**
     * Calculates the tilt-compensated 3D heading relative to magnetic North.
     * @return Heading angle in degrees (0.0 to 360.0), or -1.0f on error.
     */
    static float getHeading();

    /**
     * Calculates the standard uncompensated 2D yaw angle.
     * @return Yaw angle in degrees (0.0 to 360.0), or -1.0f on error.
     */
    static float getYaw();

    /**
     * Calculates the tilt pitch angle relative to the magnetic horizon.
     * @return Pitch angle in degrees (-90.0 to 90.0), or -999.0f on error.
     */
    static float getPitch();
};
