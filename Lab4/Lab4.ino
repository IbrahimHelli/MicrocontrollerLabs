#include <WebServer.h>
#include <WiFi.h>
const char* ssid = "AndroidAPBA03"; 
const char* password = "MOHAMMED2003"; 
WebServer server(80);
const int motorPin = 16;
bool motorState = false;

void setup() {
  Serial.begin(115200);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {}
  server.on("/", handleRoot);
  server.on("/motor_on", handleMotorOn);
  server.on("/motor_off", handleMotorOff);
  server.begin(); }
void loop() {
  server.handleClient(); }
void handleRoot() {
  String html = "<html>\
  <head>\
    <title>Motor Kontrol</title>\
  </head>\
  <body>\
    <h1>ESP32 Motor Kontrol</h1>\
    <p>Motor durumu: " + String(motorState ? "ON" : "OFF") + "</p>\
    <button onclick=\"location.href='/motor_on'\">Motor ON</button>\
    <button onclick=\"location.href='/motor_off'\">Motor OFF</button>\
  </body>\
  </html>";
  server.send(200, "text/html", html); }

void handleMotorOn() {
  motorState = true;
  analogWrite(motorPin, 255);
  handleRoot(); }

void handleMotorOff() {
  motorState = false;
  analogWrite(motorPin, 0);
  handleRoot(); }