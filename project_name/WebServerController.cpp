#include "WebServerController.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP8266 Control</title>
<style>
button{
  padding:20px;
  font-size:18px;
  border-radius:10px;
  border:none;
  color:white;
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
  background:gray;
  color:white;
  border:none;
}

.sound-bar {
  display: flex;
  justify-content: center;
  gap: 20px;
  margin-top: 20px;
}

.sound-item {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.sound-item p {
  margin-bottom: 8px;
  font-weight: bold;
}

.sound-item button {
  padding: 15px 20px;
  font-size: 16px;
  border-radius: 10px;
  border: none;
  background-color: #555;
  color: white;
  cursor: pointer;
}

.sound-item button:hover {
  background-color: #777;
}
</style>
</head>
<body>
<h2>Controle RGB ESP8266</h2>
<form action="/RGB_Animation">
  <button type="submit" class="RGB">%BTN_TEXT_2%</button>
</form>

<hr>

<h2>Reglage des vibrations</h2>
<div style="width:250px; border:1px solid #aaa; border-radius:10px;">
  <div id="barre"
       style="height:20px; width:0%; background:green; border-radius:10px;">
  </div>
</div>

<br>
<input id="slider" type="range" min="0" max="200" value="0" style="width:250px;">
<p id="val">Valeur : 0</p>

<script>
const slider = document.getElementById("slider");
const barre  = document.getElementById("barre");
const val    = document.getElementById("val");

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
  <div id="barreLight" style="height:20px; width:50%; background:green; border-radius:10px;">
  </div>
</div>

<br>
<input id="sliderLight" type="range" min="0" max="1024" value="500" style="width:250px;">
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

<hr>

<h2>Sons d’ambiance</h2>
<div class="sound-bar">

  <div class="sound-item">
    <p>Suspicious</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Suspicious">
      <button type="submit">></button>
    </form>
  </div>
  
  <div class="sound-item">
    <p>Farfadet</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Farfadet">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Demogorgon</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Demogorgon">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Zelda Mechanism</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Zelda Mechanism">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Adventure</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Adventure">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Mickael Jackson</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Mickael Jackson">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Rick Roll</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Rick Roll">
      <button type="submit">></button>
    </form>
  </div>

  <div class="sound-item">
    <p>Mugiwara</p>
    <form action="/sound">
      <input type="hidden" name="play" value="Mugiwara">
      <button type="submit">></button>
    </form>
  </div>

</div>
</body>
</html>
)rawliteral";

// ------------------- Constructeur -------------------
WebServerController::WebServerController(matriceRGB &rgbMatrix, VibrationMotor &motor, LightSensor &light, DFPlayerMini &player)
    : server(80), matrixController(rgbMatrix), vibrationMotor(motor),
      lightSensor(light), dfplayer(player), modeAuto(false), ledStateRGB(false){}

// ------------------- Initialisation -------------------
void WebServerController::begin(const char* ssid, const char* password) {
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
    server.on("/RGB_Animation", [this]() { handleRGB_Animation(); });
    server.on("/set", [this]() {int val = server.arg("niveau").toInt(); vibrationMotor.setSpeed(val); server.send(200, "text/plain", "OK");});
    server.on("/setLight", [this]() {int seuil = server.arg("niveau").toInt(); lightSensor.setSeuil(seuil); server.send(200, "text/plain", "OK");});
    server.on("/Light_Mode", [this]() { handleLightMode(); });
    server.on("/sound", [this]() { handleSound(); });

    server.begin();
}

// ------------------- Gestion serveur -------------------
void WebServerController::handle() {
    server.handleClient();
}

void WebServerController::handleRoot() {
    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleRGB_Animation()
{
    ledStateRGB = !ledStateRGB;

    if (ledStateRGB)
        matrixController.start(2000);
    else
        matrixController.stop();

    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleLightMode() {
    modeAuto = !modeAuto;

    if (modeAuto) lightSensor.start(250);
    else lightSensor.stop();

    server.send(200, "text/html", pageHTML());
}

void WebServerController::handleSound()
{
    String sound = server.arg("play");
    Serial.println("Sound asked : " + sound);
    if (sound == "Suspicious") {
        dfplayer.play(1);
    }
    else if (sound == "Farfadet") {
        dfplayer.play(2);
    }
    else if (sound == "Demogorgon") {
        dfplayer.play(3);
    }
    else if (sound == "Zelda Mechanism") {
        dfplayer.play(4);
    }
    else if (sound == "Adventure") {
        dfplayer.play(5);
    }
    else if (sound == "Mickael Jackson") {
        dfplayer.play(6);
    }
    else if (sound == "Rick Roll") {
        dfplayer.play(7);
    }
    else if (sound == "Mugiwara") {
        dfplayer.play(8);
    }
    server.send(200, "text/html", pageHTML());
}

String WebServerController::pageHTML() {
    String page = index_html;
    page.replace("%BTN_TEXT_2%", ledStateRGB ? "ON" : "OFF");
    page.replace("%BTN_TEXT_3%", modeAuto ? "Auto" : "Manuel");
    return page;
}
