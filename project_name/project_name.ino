// #include <Ultrasonic.h>

// #include "Application.h"
#include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>

// #define SONIC_PIN D3
// #define LED_PIN D4


// Application myApplication;



// void setup() 
// {
//   // put your setup code here, to run once:
//   //myApplication.init();


//   // Ultrasonic(SONIC_PIN);
//   // pinMode(LED_PIN, OUTPUT);

// }

// void loop() 
// {
//   // put your main code here, to run repeatedly:
//   //myApplication.run();

//   // if(MeasureInCentimeters(500)== 10000)
//   //   digitalWrite(LED_PIN, HIGH);
//   // else
//   //   digitalWrite(LED_PIN, LOW);
 
// }

#include "WebServer.h"
#include "passwords.h"
#define LED_PIN LED_BUILTIN

WebServerLED webServer(LED_PIN);

void setup() {
  Serial.begin(115200);
  webServer.begin(ssid, password);


}

void loop() {
  webServer.handle();
}
