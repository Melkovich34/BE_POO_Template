#include "WebServer.h"

// Page HTML stockée en flash
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP8266 LED</title>

<style>
button{
  padding:20px;
  font-size:18px;
  border-radius:10px;
  background:%COLOR%;
  color:white;
  border:none;
}
</style>

</head>
<body>

<h2>Contrôle LED ESP8266</h2>

<p>Etat : %STATE%</p>

<form action="/toggle">
  <button type="submit">%BTN_TEXT%</button>
</form>

</body>
</html>
)rawliteral";

WebServerLED::WebServerLED(uint8_t ledPin)
    : server(80), _ledPin(ledPin), ledState(false) {}

void WebServerLED::begin(const char* ssid, const char* password) {
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, LOW);

    Serial.println("Connexion au WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnecté !");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());

    server.on("/", [this]() { handleRoot(); });
    server.on("/toggle", [this]() { handleToggle(); });

    server.begin();
}

void WebServerLED::handle() {
    server.handleClient();
}

void WebServerLED::handleRoot() {
    server.send(200, "text/html", pageHTML());
}

void WebServerLED::handleToggle() {
    ledState = !ledState;
    digitalWrite(_ledPin, ledState ? HIGH : LOW);
    server.send(200, "text/html", pageHTML());
}

String WebServerLED::pageHTML() {
    String page = index_html;

    page.replace("%STATE%", ledState ? "ON" : "OFF");
    page.replace("%BTN_TEXT%", ledState ? "Éteindre" : "Allumer");
    page.replace("%COLOR%", ledState ? "red" : "green");

    return page;
}