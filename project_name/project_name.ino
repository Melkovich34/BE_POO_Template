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

//Création des instances de class
matriceRGB rgbMatrix;
VibrationMotor vibrationMotor(MOTOR_PIN);
WebServerController webServer(LED_PIN, rgbMatrix, vibrationMotor);


void setup() {

  //Initialisation capteur/actionneur + lancement connexion serveur web
  Serial.begin(115200);
  rgbMatrix.begin();
  rgbMatrix.start(1000);
  vibrationMotor.begin();
  webServer.begin(ssid, password);

}

void loop() {
  //Vérification update du serveur pour réaliser action
  webServer.handle();

}
