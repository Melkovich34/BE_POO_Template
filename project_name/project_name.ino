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
#define LIGHT_SENSOR_PIN A0   

//Création des instances de class
matriceRGB rgbMatrix;
VibrationMotor vibrationMotor(MOTOR_PIN);
LightSensor lightSensor(LIGHT_SENSOR_PIN, rgbMatrix, 500);
WebServerController webServer(LED_PIN, rgbMatrix, vibrationMotor, lightSensor);


void setup() {

  //Initialisation capteur/actionneur + lancement connexion serveur web
  Serial.begin(115200);
  rgbMatrix.begin();
  rgbMatrix.start(1000);
  vibrationMotor.begin();
  lightSensor.begin();
  lightSensor.start(250);
  webServer.begin(ssid, password);

}

void loop() {
  //Vérification update du serveur pour réaliser action
  webServer.handle();

}
