#include "VibrationMotor.h"

VibrationMotor::VibrationMotor(uint8_t pin)
    : motorPin(pin), speed(0) {}

void VibrationMotor::begin() {
    pinMode(motorPin, OUTPUT);
    analogWrite(motorPin, 0);
}

void VibrationMotor::setSpeed(uint8_t value) {
    if (value <= 0)
      speed = 0;
    else if (value >= 200)
      speed = 200;
    else
      speed = value;
    analogWrite(motorPin, speed);
}

void VibrationMotor::stop() {
    speed = 0;
    analogWrite(motorPin, 0); // Arrêt physique du moteur
}