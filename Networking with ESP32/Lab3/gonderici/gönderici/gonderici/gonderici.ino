#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "AndroidAPBA03";
const char* password = "MOHAMMED2003";
WebServer server(80);
void handleClientRequest() {
  server.send(200, "text/plain", "Emçi. Haberleşme Sağlandi.");}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi bağlaniyor..."); }
  Serial.println("WiFi bağlandi !!");
  Serial.print("Server IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleClientRequest);
  server.begin();
  Serial.println("Server started!");
}
void loop() {
  server.handleClient();
}