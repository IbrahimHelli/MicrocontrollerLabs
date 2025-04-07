#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "ssid";
const char* password = "password";

WebServer server(80);

const int pinLED = 2;

void handleLED() {
  static bool ledState = LOW;
  
  ledState = !ledState;
  digitalWrite(pinLED, ledState);
  server.send(200, "text/plain", ledState ? "LED is ON" : "LED is OFF"); }

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(pinLED, OUTPUT);

  server.on("/", []() {
    server.send(200, "text/html", "<button onclick=\"fetch('/toggle').then(r => r.text()).then(alert)\">Toggle LED</button>");
  });

  server.on("/toggle", handleLED);
  server.begin();
  Serial.println("Web server with LED control started"); }

void loop() {
  server.handleClient(); }