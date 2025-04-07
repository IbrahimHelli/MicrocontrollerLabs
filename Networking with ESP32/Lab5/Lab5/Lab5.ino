#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const char* ssid = "ssid";
const char* password = "password";
const char* apiEndpoint = "http://api.openweathermap.org/data/2.5/weather?q=Istanbul&appid=c210d995d3bca996b1c0bbeb65d2e703&units=metric";
const int lm35Pin = 35;

WebServer server(80);
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Wi-Fi'ye bağlaniliyor...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");  }
  Serial.println("\nWi-Fi bağlantisi başarili!");
  Serial.print("IP Adresi: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server başlatildi!"); }

void loop() {
  server.handleClient();
  Serial.print("LM35 ile ölçülen sıcaklık: ");
  Serial.print(analogRead(lm35Pin)* (3.3 / 4095.0) * 100.0);
  Serial.println(" C");
  delay(3000); }

void handleRoot() {
  float localTemp = readTemperature();
  String weatherData = fetchWeatherData();
  String html = "<html><head><title>ESP32 Hava Durumu</title></head><body>";
  html += "<h1>ESP32 Hava Durumu ve Sicaklik Olcumu</h1>";
  html += "<p><b>LM35 ile Olculen Sicaklik:</b> " + String(localTemp) + " C</p>";
  html += "<p><b>API'den Alinan Veri:</b></p><pre>" + weatherData + "</pre>";
  html += "</body></html>";
  server.send(200, "text/html", html); }

float readTemperature() {
  int analogValue = analogRead(lm35Pin);
  float voltage = analogValue * (3.3 / 4095.0);
  float temperature = voltage * 100.0;
  return temperature; }
  
String fetchWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(wifiClient, apiEndpoint);
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      http.end();
      return payload; } 
      else {
      http.end();
      return "API Hatasi: " + String(httpCode); } } 
      else {
    return "Wi-Fi bağlanti hatasi!"; } }