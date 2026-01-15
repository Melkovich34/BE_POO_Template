// #include <Ultrasonic.h>

// #include "Application.h"
#include <Arduino.h>
#include <ChainableLED.h>
#include "matriceRGB.h"
#include "WebServerController.h"
#include "VibrationMotor.h"  
#include "passwords.h"
#include "DFPlayerMini.h"
#include "Device.h"
#define MOTOR_PIN D5
#define LIGHT_SENSOR_PIN A0   

//Création des instances de class
matriceRGB rgbMatrix;
VibrationMotor vibrationMotor(MOTOR_PIN);
LightSensor lightSensor(LIGHT_SENSOR_PIN, rgbMatrix, 500);
DFPlayerMini dfplayer(Serial1);
WebServerController webServer( rgbMatrix, vibrationMotor, lightSensor, dfplayer);
Device* allDevices[] = { &rgbMatrix, &vibrationMotor, &lightSensor };

void setup() {

  //Initialisation capteur/actionneur + lancement connexion serveur web
    Serial.begin(115200);
    Serial1.begin(9600);
    delay(5000);
    dfplayer.reset();
    delay(3000);
    dfplayer.setVolume(20);
    delay(1000);
    for (Device* d : allDevices) {
          d->begin();
      }
    rgbMatrix.start(1000);
    lightSensor.start(250);
    webServer.begin(ssid, password);
  
}

void loop() {
  //Vérification update du serveur pour réaliser action
  webServer.handle();

}
