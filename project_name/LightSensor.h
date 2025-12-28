#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>
#include <Ticker.h>
#include "matriceRGB.h"

class LightSensor {
public:
    /**
    * @brief  Constructeur LightSensor
    *
    * @details
    * - 
    * 
    * @param pin : branchement du capteur sur ESP8266
    */
    LightSensor(uint8_t pin, matriceRGB& matrix, int seuil = 500);

    /**
    * @brief  Initialisation LightSensor
    *
    * @details
    * - Initialisation de la Pin en INPUT
    * 
    */
    void begin();

    /**
    * @brief  Lancement d'un timer pour LightSensor
    *
    * @details
    * - Lis toutes les interval_ms spécifié la nouvelle valeur mesurée par le capteur
    * 
    * @param interval_ms : intervalle de lecture du capteur en millisecondes
    */
    void start(uint32_t interval_ms);

    /**
    * @brief  Arrêt du timer pour LightSensor
    *
    * @details
    * - Désassociation du timer et du capteur : le capteur arrête de lire la donnée en fonction du timer
    * 
    */
    void stop();

    /**
    * @brief  Sélection du seuil du Light Sensor
    *
    * @details
    *  - Permet de modifier la valeur à partir de laquelle on considère que la lumière est suffisament faible/éteinte
    *  - Controllable par jauge sur site Web
    *
    * @param value : 0 < value < 1024 => choix de seuil
    */
    void setSeuil(uint8_t value) ;

    /**
    * @brief  Lis la valeur mesuré par le Light Sensor
    *
    * @details
    * - Lis la nouvelle valeur mesurée par le capteur
    * 
    * @return la nouvelle valeur mesurée par le capteur
    */
    int readSensor();

    /**
    * @brief  Contrôle la matrice en fonction du seuil
    *
    * @details
    * - Allume la matrice si la valeur mesurée est supérieure ou égal au seuil
    * - Eteint la matrice sinon
    */
    void controlMatrix();


private:
    uint8_t _pin;
    int _seuil;
    bool _animationState;
    matriceRGB& _matrix;

    Ticker _timer;

};

#endif