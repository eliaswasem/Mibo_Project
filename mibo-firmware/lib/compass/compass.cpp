//
// Created by catgod on 20.5.2026
//

#include "compass.h"
#include <cmath>

Adafruit_QMC5883P Compass::qmc;
bool Compass::isInitialized = false;

bool Compass::begin() {
    if (!qmc.begin(COMPASS_ADDRESS, &Wire)) {
        isInitialized = false;
        return false;
    }

    qmc.setRange(QMC5883P_RANGE_8G);
    qmc.setODR(QMC5883P_ODR_100HZ);

    isInitialized = true;
    return true;
}

float Compass::getYaw() {
    if (!isInitialized) {
        return -1.0f;
    }

    float rawX = 0.0f, rawY = 0.0f, rawZ = 0.0f;
    if (!qmc.getGaussField(&rawX, &rawY, &rawZ)) {
        return -1.0f;
    }

    // Apply manual horizontal offsets
    float x = rawX - offsetX;
    float y = rawY - offsetY;

    if (std::abs(x) < 0.001f && std::abs(y) < 0.001f) {
        return -1.0f;
    }

    // Standard 2D angle calculation
    float yaw = std::atan2(y, x);
    float yawDegrees = yaw * 180.0f / static_cast<float>(M_PI);

    if (yawDegrees < 0) {
        yawDegrees += 360.0f;
    }

    return yawDegrees;
}

float Compass::getPitch() {
    if (!isInitialized) {
        return -999.0f;
    }

    float rawX = 0.0f, rawY = 0.0f, rawZ = 0.0f;
    if (!qmc.getGaussField(&rawX, &rawY, &rawZ)) {
        return -999.0f;
    }

    // Apply manual 3D offsets
    float x = rawX - offsetX;
    float y = rawY - offsetY;
    float z = rawZ - offsetZ;

    // Calculate vertical pitch relative to the total horizontal field strength
    float pitch = std::atan2(-x, std::sqrt(y * y + z * z));

    return pitch * 180.0f / static_cast<float>(M_PI);
}

float Compass::getHeading() {
    if (!isInitialized) {
        return -1.0f;
    }

    float rawX = 0.0f, rawY = 0.0f, rawZ = 0.0f;
    if (!qmc.getGaussField(&rawX, &rawY, &rawZ)) {
        return -1.0f;
    }

    // Apply all three manual calibration offsets
    float x = rawX - offsetX;
    float y = rawY - offsetY;
    float z = rawZ - offsetZ;

    // Generate pitch and roll transformation matrices in radians
    float pitchRad = std::atan2(-x, std::sqrt(y * y + z * z));
    float rollRad  = std::atan2(y, z);

    // Guard against vertical gimbal lock limits
    if (std::abs(pitchRad) >= (M_PI / 2.0)) {
        return -1.0f;
    }

    // Flatten vectors using tilt-compensation matrix mapping
    float compX = x * std::cos(pitchRad) + z * std::sin(pitchRad);
    float compY = x * std::sin(rollRad) * std::sin(pitchRad) + y * std::cos(rollRad) - z * std::sin(rollRad) * std::cos(pitchRad);

    if (std::abs(compX) < 0.001f && std::abs(compY) < 0.001f) {
        return -1.0f;
    }

    // Compute final tilt-corrected magnetic course
    float heading = std::atan2(compY, compX);
    float headingDegrees = heading * 180.0f / static_cast<float>(M_PI);

    if (headingDegrees < 0) {
        headingDegrees += 360.0f;
    }

    return headingDegrees;
}
