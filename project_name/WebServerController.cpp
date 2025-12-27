#include "WebServerController.h"

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
button.RGB{
  padding:20px;
  font-size:18px;
  border-radius:10px;
  background:gray;
  color:white;
  border:none;
}
</style>
</head>
<body>
<h2>Controle LED ESP8266</h2>
<p>Etat : %STATE%</p>
<form action="/toggle">
  <button type="submit">%BTN_TEXT%</button>
</form>
<form action="/RGB_Animation">
  <button type="submit" class="RGB">%BTN_TEXT_2%</button>
</form>
</body>
</html>
)rawliteral";

WebServerController::WebServerController(uint8_t ledPin, matriceRGB &rgbMatrix)
    : server(80), _ledPin(ledPin), ledState(false), matrixController(rgbMatrix), ledStateRGB(false) {}

void WebServerController::begin(const char* ssid, const char* password) {
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, LOW);

    Serial.begin(115200);
    Serial.println("Connexion au WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnecté !");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());

    // init matrice
    matrixController.begin();

    // routes serveur
    server.on("/", [this]() { handleRoot(); });
    server.on("/toggle", [this]() { handleToggle(); });
    server.on("/RGB_Animation", [this]() { handleRGB_Animation(); });

    server.begin();
}

void WebServerController::handle() {
    server.handleClient();
}

void WebServerController::handleRoot() {
    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleToggle() {
    ledState = !ledState;
    digitalWrite(_ledPin, ledState ? HIGH : LOW);
    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleRGB_Animation() {
    ledStateRGB = !ledStateRGB;
    if (ledStateRGB) {
        matrixController.start(2000); // démarre l'animation toutes les 500 ms
    } else {
        matrixController.stop();
    }
    server.send(200, "text/html", pageHTML());
}

String WebServerController::pageHTML() {
    String page = index_html;
    page.replace("%STATE%", ledState ? "ON" : "OFF");
    page.replace("%BTN_TEXT%", ledState ? "Eteindre" : "Allumer");
    page.replace("%COLOR%", ledState ? "red" : "green");
    page.replace("%BTN_TEXT_2%", ledStateRGB ? "ON" : "OFF");
    return page;
}
