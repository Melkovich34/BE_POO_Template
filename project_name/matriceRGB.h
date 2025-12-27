#ifndef MATRICE_RGB_H
#define MATRICE_RGB_H

#include <Ticker.h>
#include <Wire.h>
#include "grove_two_rgb_led_matrix.h"

#ifdef SEEED_XIAO_M0
    #define SERIAL Serial
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE)
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif

class matriceRGB {
public:
    matriceRGB();
    void begin();
    void start(uint32_t interval_ms);
    void stop();

private:
    GroveTwoRGBLedMatrixClass matrix;
    Ticker timer;

    static constexpr uint8_t cpt_RGB = 6;
    uint8_t index;
    bool ledState;

    void changeColor();
};

#endif
