#include "DFPlayerMini.h"

DFPlayerMini::DFPlayerMini(HardwareSerial &serial)
    : _serial(serial)
{}

void DFPlayerMini::send(uint8_t cmd, uint16_t param) {
    uint8_t trame[10];
    uint16_t checksum;

    trame[0] = 0x7E;        // Start
    trame[1] = 0xFF;        // Version
    trame[2] = 0x06;        // Length
    trame[3] = cmd;         // Commande
    trame[4] = 0x00;        // Feedback (0 = pas de retour)
    trame[5] = (param >> 8) & 0xFF; // Param high
    trame[6] = param & 0xFF;        // Param low

    checksum = 0 - (trame[1] + trame[2] + trame[3] + trame[4] + trame[5] + trame[6]);
    trame[7] = (checksum >> 8) & 0xFF; // Checksum high
    trame[8] = checksum & 0xFF;        // Checksum low
    trame[9] = 0xEF;        // End

    // Envoi UART
    for (int i = 0; i < 10; i++) {
        _serial.write(trame[i]);
    }
}

void DFPlayerMini::play(uint16_t track) {
    send(0x03, track); // Commande 0x03 = Play track par index
}

void DFPlayerMini::stop() {
    send(0x16, 0); // Commande 0x16 = Stop
}

void DFPlayerMini::setVolume(uint8_t volume) {
    if(volume > 30) volume = 30; // Limite max
    send(0x06, volume); // Commande 0x06 = Set volume
}

void DFPlayerMini::reset() {
    send(0x0C, 0); // Commande 0x0C = Reset
}
