#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "AndroidAPBA03";
const char* password = "MOHAMMED2003";
WebServer server(80);

int analogPin = 35;

void handleSensorData() {

  int sensorValue = analogRead(analogPin);
  String data = "Sensor value: " + String(sensorValue);
  server.send(200, "text/plain", data); }

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(analogPin, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..."); }
  Serial.println("Connected to WiFi");

  server.on("/", []() {
    server.send(200, "text/html", "<a href=\"/sensor\">Get Sensor Data</a>"); });

  server.on("/sensor", handleSensorData);
  server.begin();
  Serial.println("Web server with sensor data started"); }

void loop() {
  server.handleClient(); }