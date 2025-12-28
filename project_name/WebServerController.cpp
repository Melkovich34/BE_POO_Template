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

button.Light_sensor{
  padding:20px;
  font-size:18px;
  border-radius:10px;
  background:gray; // ou #888
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


<hr>

<h2>Reglage des vibrations</h3>

<div style="width:250px; border:1px solid #aaa; border-radius:10px;">
  <div id="barre"
       style="height:20px; width:0%; background:green; border-radius:10px;">
  </div>
</div>

<br>

<input
  id="slider"
  type="range"
  min="0"
  max="200"
  value="0"
  style="width:250px;"
>

<p id="val">Valeur : 0</p>

<script>
const slider = document.getElementById("slider");
const barre  = document.getElementById("barre");
const val    = document.getElementById("val");

// mise à jour visuelle en temps réel
slider.addEventListener("input", () => {
  const pct = (slider.value / slider.max) * 100;
  barre.style.width = pct + "%";
  val.textContent = "Valeur : " + slider.value;
});
slider.addEventListener("change", () => {
  fetch("/set?niveau=" + slider.value);
});
</script>

<hr>

<h2>Controle Light Mode</h2>
<form action="/Light_Mode">
  <button class="Light_sensor" type="submit">%BTN_TEXT_3%</button>
</form>

<hr>

<h2>Seuil de luminosite</h2>

<div style="width:250px; border:1px solid #aaa; border-radius:10px;">
  <div id="barreLight"
       style="height:20px; width:50%; background:green; border-radius:10px;">
  </div>
</div>

<br>

<input
  id="sliderLight"
  type="range"
  min="0"
  max="1024"
  value="500"
  style="width:250px;"
>

<p id="valLight">Seuil : 500</p>

<script>
const sliderLight = document.getElementById("sliderLight");
const barreLight  = document.getElementById("barreLight");
const valLight    = document.getElementById("valLight");

sliderLight.addEventListener("input", () => {
  const pct = (sliderLight.value / sliderLight.max) * 100;
  barreLight.style.width = pct + "%";
  valLight.textContent = "Seuil : " + sliderLight.value;
});

sliderLight.addEventListener("change", () => {
  fetch("/setLight?niveau=" + sliderLight.value);
});
</script>

</body>
</html>
)rawliteral";

WebServerController::WebServerController(uint8_t ledPin, matriceRGB &rgbMatrix, VibrationMotor &motor,LightSensor &light)
    : server(80), _ledPin(ledPin), ledState(false), matrixController(rgbMatrix), vibrationMotor(motor), lightSensor(light), modeAuto(false), ledStateRGB(false) {}

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
    Serial.println("\nConnected !");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());

    // init matrice
    matrixController.begin();

    // routes serveur
    server.on("/", [this]() { handleRoot(); });
    server.on("/toggle", [this]() { handleToggle(); });
    server.on("/RGB_Animation", [this]() { handleRGB_Animation(); });
    server.on("/set", [this]() {int val = server.arg("niveau").toInt(); vibrationMotor.setSpeed(val); server.send(200, "text/plain", "OK");});
    server.on("/setLight", [this]() {int seuil = server.arg("niveau").toInt(); lightSensor.setSeuil(seuil); server.send(200, "text/plain", "OK");});
    server.on("/Light_Mode", [this]() { handleLightMode(); });

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

void WebServerController::handleRGB_Animation()
{
    if (modeAuto)
    {
        // on ignore simplement le clic
        server.send(200, "text/html", pageHTML());
        return;
    }

    ledStateRGB = !ledStateRGB;

    if (ledStateRGB)
        matrixController.start(2000);
    else
        matrixController.stop();

    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleLightMode() {
    modeAuto = !modeAuto;

    if (modeAuto) {
        lightSensor.start(250);
    } else {
        lightSensor.stop();
    }

    server.send(200, "text/html", pageHTML());
}

String WebServerController::pageHTML() {
    String page = index_html;
    page.replace("%STATE%", ledState ? "ON" : "OFF");
    page.replace("%BTN_TEXT%", ledState ? "Eteindre" : "Allumer");
    page.replace("%COLOR%", ledState ? "red" : "green");
    page.replace("%BTN_TEXT_2%", ledStateRGB ? "ON" : "OFF");
    page.replace("%BTN_TEXT_3%", modeAuto ? "Auto" : "Manuel");
    return page;
}
