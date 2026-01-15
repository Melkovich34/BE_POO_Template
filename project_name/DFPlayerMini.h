#ifndef DFPLAYERMINI_H
#define DFPLAYERMINI_H

#include <Arduino.h>

class DFPlayerMini
{
public:

    /**
     * @brief  Constructeur de DFPlayerMini
     *
     * @details
     * -
     *
     * @param param1 serial : Association d'un port série
     */
    DFPlayerMini(HardwareSerial &serial);

    /**
    * @brief  Lancement d'un son stocké sur carte SD
    *
    * @details
    * - Envoie commande lecture son + n° de la track à jouer
    */
    void play(uint16_t track);

    /**
    * @brief  Coupe la track en cours d'éxécution
    *
    * @details
    * - Envoie commande arret du son
    */
    void stop();

    /**
    * @brief  Régler son de haut-parleur
    *
    * @details
    * - Envoie commande réglage son + limitation du volume max à 30
    */
    void setVolume(uint8_t volume);

        /**
    * @brief  Reset du DFPlayerMini
    *
    * @details
    * - Envoie commande reset
    */
    void reset();

private:
    HardwareSerial &_serial;

    /**
    * @brief  Envoie trame de commande à DFPlayerMini sur liaison UART
    */
    void send(uint8_t cmd, uint16_t param);
};

#endif
