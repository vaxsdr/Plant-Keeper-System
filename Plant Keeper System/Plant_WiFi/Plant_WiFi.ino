#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "ESP32_Server";
const char* password = "12345678";

#define DHTPIN 2
#define DHTTYPE DHT11
#define SOILPIN 1
#define LIGHTPIN 3

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

String getSoilCondition(int soilValue) {
    if (soilValue > 2800) return "Dry";
    else if (soilValue > 1300) return "Moist";
    else return "Wet";
}

void handleData() {
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    int soil = analogRead(SOILPIN);
    int light = analogRead(LIGHTPIN);

    String json = "{";
    json += "\"temperature\": \"" + String(temp) + "\", ";
    json += "\"humidity\": \"" + String(humidity) + "\", ";
    json += "\"soil\": \"" + getSoilCondition(soil) + "\", ";
    json += "\"light\": \"" + String(light) + "\"";
    json += "}";

    server.send(200, "application/json", json);
}

void handleRoot() {
    String html = "<html><head><meta charset='utf-8'>";
    html += "<style>";
    html += "body {font-family: Arial, sans-serif; text-align: center; background: linear-gradient(180deg, #0a002b, #240070); color: white;}";
    html += ".container {margin: 40px auto; padding: 20px; width: 400px; background: rgba(50, 0, 100, 0.8); border-radius: 15px;}";
    html += "h1 {color: #a68eff;}";
    html += ".data {font-size: 26px; margin: 10px; padding: 10px; border-radius: 8px; background: rgba(255, 255, 255, 0.1);}";
    html += "</style>";
    html += "<script>";
    html += "function updateData() {";
    html += "fetch('/data').then(response => response.json()).then(data => {";
    html += "document.getElementById('temperature').innerHTML = data.temperature + ' °C';";
    html += "document.getElementById('humidity').innerHTML = data.humidity + ' %';";
    html += "document.getElementById('soil').innerHTML = data.soil;";
    html += "document.getElementById('light').innerHTML = data.light;";
    html += "});";
    html += "}";
    html += "setInterval(updateData, 2000);";
    html += "</script>";
    html += "</head><body onload='updateData()'>";
    html += "<div class='container'>";
    html += "<h1>ESP32 Sensor Dashboard</h1>";
    html += "<div class='data'><b>Temperature:</b> <span id='temperature'>Loading...</span></div>";
    html += "<div class='data'><b>Humidity:</b> <span id='humidity'>Loading...</span></div>";
    html += "<div class='data'><b>Soil Moisture:</b> <span id='soil'>Loading...</span></div>";
    html += "<div class='data'><b>Light:</b> <span id='light'>Loading...</span></div>";
    html += "</div></body></html>";

    server.send(200, "text/html", html);
}

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);
    dht.begin();

    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.begin();
}

void loop() {
    server.handleClient();
}
