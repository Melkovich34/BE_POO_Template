#ifndef VIBRATION_MOTOR_H
#define VIBRATION_MOTOR_H

#include <Arduino.h>

class VibrationMotor {
public:
/**
 * @brief  Constructeur VibrationMotor
 *
 * @details
 * - Initialisation motorPin = pin, speed = 0;
 * 
 * @param pin : branchement de l'actionneur sur ESP8266
 */
    VibrationMotor(uint8_t pin);
/**
 * @brief  Initialisation de l'actionneur VibrationMotor
 *
 * @details
 *  - pin associé à actionneur définis en OUTPUT
 *  - contrôle de vibration via commande analog, initialisé à 0 = pas de vibration
 */
    void begin();
/**
 * @brief  Sélection de vitesse pour agiter l'actionneur
 *
 * @details
 *  - Associé et controlé par jauge de vitesse sur site Web
 *
 * @param value : 0 < value < 200 => choix de vitesse
 */
    void setSpeed(uint8_t value);

private:
    uint8_t motorPin;
    uint8_t speed;
};

#endif
