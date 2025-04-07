#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "AndroidAPBA03";  // Your Wi-Fi SSID
const char* password = "MOHAMMED2003"; // Your Wi-Fi Password

// Replace with your OpenAI API key
const char* apiKey = "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"; // Your OpenAI API Key

String apiUrl = "https://api.openai.com/v1/chat/completions";

void setup() {
    // Initialize Serial
    Serial.begin(115200);

    // Connect to Wi-Fi network
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected");
}

void loop() {
    if (Serial.available() > 0) {
        String prompt = Serial.readStringUntil('\n'); // Read user input
        prompt.trim(); // Trim whitespace
        Serial.print("USER: ");
        Serial.println(prompt); // Print user input
        String response = sendToChatGPT(prompt); // Send to ChatGPT
        Serial.print("CHATGPT: ");
        Serial.println(response); // Print response from ChatGPT
    }
    delay(1000); // Short delay before the next loop
}

String sendToChatGPT(String prompt) {
    HTTPClient http;
    http.begin(apiUrl); // Specify the API URL

    // Specify the headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(apiKey));
    
    // Create the payload
    String payload = "{\"model\": \"gpt-3.5-turbo\",\"messages\":[{\"role\":\"user\",\"content\":\"" + prompt + "\"}]}";

    // Send the request
    int httpResponseCode = http.POST(payload);
    
    String response = "";
    if (httpResponseCode == 200) { // Check for successful response
        response = http.getString(); // Get the response from the server
    } else {
        Serial.printf("Error: %s\n", http.errorToString(httpResponseCode).c_str());
        // Handle quota exceeded error (HTTP 429)
        if (httpResponseCode == 429) { // 429 Too Many Requests
            Serial.println("Quota exceeded. Please wait before retrying.");
            delay(5000); // Wait for 1 minute before the next attempt
        }
    }

    http.end(); // End the HTTP request
    return response; // Return the response
}
