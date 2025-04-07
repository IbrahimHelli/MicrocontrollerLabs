#include <WiFi.h>

const char* ssid = "AndroidAPBA03";
const char* password = "MOHAMMED2003";

void setup() {
  Serial.begin(115200);
  delay(2000); // Wait for a moment
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Hello emci my ");
  delay(1000);
}