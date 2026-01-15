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
    WebServerController(matriceRGB &rgbMatrix,
                        VibrationMotor &motor,
                        LightSensor &light,
                        DFPlayerMini &player);

    void begin(const char* ssid, const char* password);
    void handle();

private:
    ESP8266WebServer server;


    matriceRGB &matrixController; 
    bool ledStateRGB;
    
    VibrationMotor &vibrationMotor;

    LightSensor &lightSensor;
    DFPlayerMini &dfplayer;

    bool modeAuto = false;

    void handleRoot();
    void handleToggle();
    void handleRGB_Animation();
    void handleLightMode();
    void handleSound();
    String pageHTML();
};

#endif
