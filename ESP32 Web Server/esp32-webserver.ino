#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Set GPIO pin
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Serve HTML page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", "<h1>ESP32 Web Server</h1><button onclick=\"fetch('/on')\">Turn ON</button><button onclick=\"fetch('/off')\">Turn OFF</button>");
    });

    // Handle LED ON
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(ledPin, HIGH);
        request->send(200, "text/plain", "LED ON");
    });

    // Handle LED OFF
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        digitalWrite(ledPin, LOW);
        request->send(200, "text/plain", "LED OFF");
    });

    // Start server
    server.begin();
}

void loop() {
    // Nothing here since AsyncWebServer handles requests
}
