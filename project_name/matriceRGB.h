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
/**
 * @brief  Constructeur matriceRGB
 *
 * @details initialisation ledState = false et index = 0
 */
    matriceRGB();
/**
 * @brief  Initialisation matriceRGB
 *
 * @details
 * 
 * - Connexion uc->matrice via I2C
 * - Verification que connexion bien établis
 * - LEDs matrice LED mis à 0
 */
    void begin();
/**
 * @brief  Lancement du timer d'interruption pour contrôle animation sur matriceRGB
 *
 * @details
 * 
 * - Déclenchement contrôlé par appuie des boutons sur site Web
 * - Lors déclenchement interruption, lance fonction changeColor()
 *
 * @param interval_ms : temps déclenchement de interruption
 */
    void start(uint32_t interval_ms);
/**
 * @brief  Arrêt du timer d'interruption
 *
 * @details
 * 
 * - Déclenchement contrôlé par appuie bouton sur site Web
 * - Désactive le lancement de fonction changeColor()
 * - Eteint les LEDs de matriceRGB
 */
    void stop();

private:
    GroveTwoRGBLedMatrixClass matrix;
    Ticker timer;

    //Variable utilisé pour créer animation changeColor()
    static constexpr uint8_t cpt_RGB = 6;
    uint8_t index;

    bool ledState;

/**
 * @brief  Changement de couleur sur matriceRGB
 *
 * @details
 * 
 * - Liée à timer lorsque animation est demandé + temps de changer
 */
    void changeColor();
};

#endif
