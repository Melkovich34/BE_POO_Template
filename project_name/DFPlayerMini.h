#ifndef DFPLAYERMINI_H
#define DFPLAYERMINI_H

#include <Arduino.h>

class DFPlayerMini
{
public:
    DFPlayerMini(HardwareSerial &serial);


    void play(uint16_t track);
    void stop();
    void setVolume(uint8_t volume);
    void reset();

private:
    HardwareSerial &_serial;

    void send(uint8_t cmd, uint16_t param);
};

#endif
