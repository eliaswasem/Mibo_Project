//
// Created by catgod on 19.05.26.
//

#pragma once

class BMP280 {
public:

    static bool init();

    static float getTemperature();

    static float getPressure();
};