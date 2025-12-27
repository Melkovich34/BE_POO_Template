#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class WebServerLED {
  public:
      WebServerLED(uint8_t ledPin);

      void begin(const char* ssid, const char* password);
      void handle();

  private:
      ESP8266WebServer server;
      uint8_t _ledPin;
      bool ledState;

      void handleRoot();
      void handleToggle();
      String pageHTML();
};

#endif