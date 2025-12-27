// #include <Ultrasonic.h>

// #include "Application.h"
#include <Arduino.h>
#include <ChainableLED.h>
#include "matriceRGB.h"
#include "WebServerController.h"
#include "VibrationMotor.h"  
#include "passwords.h"
#define LED_PIN LED_BUILTIN
#define MOTOR_PIN D5


matriceRGB rgbMatrix;
VibrationMotor vibrationMotor(MOTOR_PIN);
WebServerController webServer(LED_PIN, rgbMatrix, vibrationMotor);


void setup() {
  Serial.begin(115200);
  rgbMatrix.begin();
  rgbMatrix.start(1000);
  vibrationMotor.begin();
  webServer.begin(ssid, password);

}

void loop() {
  webServer.handle();

}
