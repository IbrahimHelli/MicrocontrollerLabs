#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "AndroidAPBA03";
const char* password = "MOHAMMED2003";

// Create a WebServer on port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);
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

  // Define what to do when the browser requests the root URL "/"
  server.on("/", []() {
    server.send(200, "text/html", "<h1>Hello Emci!</h1><p>This is your ESP32 web page.</p>");
  });

  // Start the server
  server.begin();
}

void loop() {
  // Listen for client requests
  server.handleClient();
}