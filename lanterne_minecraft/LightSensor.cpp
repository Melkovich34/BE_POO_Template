#include "LightSensor.h"


LightSensor::LightSensor(uint8_t pin, matriceRGB& matrix, int seuil)
    : _pin(pin), _matrix(matrix), _seuil(seuil), _animationState(false){}

void LightSensor::begin() {
    pinMode(_pin, INPUT);
}

void LightSensor::start(uint32_t interval_ms) {
    _timer.attach_ms(interval_ms, +[] (LightSensor* self) {
        self->controlMatrix();
    }, this);
}

void LightSensor::stop() {
    _timer.detach();
}

int LightSensor::readSensor() {
    return analogRead(_pin);
}

void LightSensor::setSeuil(uint8_t value) {
  if (value <= 0)
    _seuil = 0;
  else if (value >= 1024)
    _seuil = 1024;
  else
    _seuil = value;
}

void LightSensor::controlMatrix(){
  int valeur = readSensor();
  if ((valeur <= _seuil) && (!_animationState)) {
      _matrix.start(2000);
      _animationState = true;
  } else if ((valeur >= _seuil) && (_animationState)){
      _matrix.stop();
      _animationState = false;
  }
  //Serial.printf("valeur : %d | animation : %d\n", valeur, _animationState);
}