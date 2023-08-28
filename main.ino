#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

float PubelectricCurrent;
const char* apSSID = "MyESP8266AP";
const char* apPassword = "1234";
const IPAddress apIP(192, 168, 0, 1);

const int currentPin = A0;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  pinMode(currentPin, INPUT);

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID, apPassword);

  /*Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  */
  lcd.setCursor(0, 0);
  lcd.print("IP: ");
  lcd.print(WiFi.softAPIP());
  
  


  // Enable CORS headers
  server.onNotFound([]() {
    if (server.method() == HTTP_OPTIONS) {
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
      server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
      server.send(204);
    } else {
      server.send(404, "text/plain", "Not Found");
    }
  });

  server.on("/api", HTTP_GET, [](){
    float electricCurrent = analogRead(currentPin) * 0.0049;
    PubelectricCurrent = electricCurrent;
    // Create a JSON object to hold the electric current value
    StaticJsonDocument<64> jsonDocument;
    jsonDocument["current"] = electricCurrent;

    // Serialize the JSON to a string
    String jsonString;
    serializeJson(jsonDocument, jsonString);

    // Set CORS headers for the API response
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200, "application/json", jsonString);
  
  });

  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", "<h1>ESP8266 API</h1><p>Visit /api to get electric current data.</p>");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  lcd.setCursor(0, 1);
  lcd.print("Current:");
  lcd.print(PubelectricCurrent, 4);
  lcd.print(" A");
}
