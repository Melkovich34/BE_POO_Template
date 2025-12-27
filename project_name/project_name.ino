// #include <Ultrasonic.h>

// #include "Application.h"
#include <Arduino.h>
#include <ChainableLED.h>
#include "matriceRGB.h"
#include "WebServerController.h"
#include "passwords.h"
#define LED_PIN LED_BUILTIN


matriceRGB rgbMatrix;
WebServerController webServer(LED_PIN, rgbMatrix);

void setup() {
  Serial.begin(115200);
  webServer.begin(ssid, password);
  rgbMatrix.begin();
  rgbMatrix.start(1000);

}

void loop() {
  webServer.handle();
}
