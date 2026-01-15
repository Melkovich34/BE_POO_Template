#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "matriceRGB.h"  
#include "VibrationMotor.h"
#include "LightSensor.h"
#include "DFPlayerMini.h"




class WebServerController {
public:
    /**
     * @brief  Constructeur de WebServerController
     *
     * @details
     * -
     *
     * @param param1 ledPin : branchement de led interne à ESP
     * @param param2 rgbMatrix : référence sur class matriceRGB
     * @param param3 motor : référence sur class VibrationMotor
     * @param param4 lightSensor : référence sur class LightSensor
     */
    WebServerController(matriceRGB &rgbMatrix,
                        VibrationMotor &motor,
                        LightSensor &light,
                        DFPlayerMini &player);

    /**
    * @brief  Initialisation de WebServerController
    *
    * @details
    * - Initialisation de la Pin en OUTPUT et mise à état bas
    * - Connexion Serial pour afficher retour info sur terminal PC
    * - Connexion Wifi entre ESP8266 et Téléphone utilisateur 
    * - Initialisation de matriceRGB
    * - Activation de toutes les fonctions d'interruptions de page HTML pour contrôler capteurs/actionneurs
    * - Lancement du serveur
    */
    void begin(const char* ssid, const char* password);

    /**
     * @brief  Traitement des requêtes sur page HTML
     *
     * @details
     * - Gestion de l'interruption à contrôler selon choix utilisateur sur page HTML
     */
    void handle();

private:
    ESP8266WebServer server;


    matriceRGB &matrixController; 
    bool ledStateRGB;
    
    VibrationMotor &vibrationMotor;

    LightSensor &lightSensor;
    DFPlayerMini &dfplayer;

    bool modeAuto = false;

    /**
     * @brief  Contrôle la MAJ de la page HTML
     *
     * @details
     * - Met à jour la page HTML
     */
    void handleRoot();

    /**
     * @brief  Contrôle état de la led Interne de l'ESP
     *
     * @details
     * - Changement état led Interne
     */
    void handleToggle();

    /**
     * @brief  Contrôle de l'animation sur matriceRGB
     *
     * @details
     * - Lancement animation ou non selon mode sélectionné (Auto/Manuel)
     */
    void handleRGB_Animation();

    /**
     * @brief  Contrôle le timer d'interruption du capteur LightSensor
     *
     * @details
     * - Lancement de routine d'interruption pour capteur LightSensor selon mode (Auto/Manuel)
     */
    void handleLightMode();

    /**
     * @brief  Contrôle le choix du son à jouer sur le DFPMiniplayer
     *
     * @details
     * - Récupération du son à jouer de la page HTML 
     * - Sélection du son à jouer
     */
    void handleSound();

    /**
     * @brief  Changement état des boutons de page HTML
     *
     * @details
     * - Changement état des attributs booléen lors de demande utilisateur
     */
    String pageHTML();
};

#endif
