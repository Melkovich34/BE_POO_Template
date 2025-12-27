#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "matriceRGB.h"  

class  WebServerController{
public:
    WebServerController(uint8_t ledPin, matriceRGB &rgbMatrix);

    void begin(const char* ssid, const char* password);
    void handle();

private:
    ESP8266WebServer server;
    uint8_t _ledPin;
    bool ledState;

    matriceRGB &matrixController; 
    bool ledStateRGB;

    void handleRoot();
    void handleToggle();
    void handleRGB_Animation();
    String pageHTML();
};

#endif
