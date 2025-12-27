#ifndef VIBRATION_MOTOR_H
#define VIBRATION_MOTOR_H

#include <Arduino.h>

class VibrationMotor {
public:
    VibrationMotor(uint8_t pin);

    void begin();
    void setSpeed(uint8_t value);

private:
    uint8_t motorPin;
    uint8_t speed;
};

#endif
