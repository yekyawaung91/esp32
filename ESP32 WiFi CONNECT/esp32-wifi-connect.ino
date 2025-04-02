#include <WiFi.h>

// WiFi credentials
const char* ssid = "Wirelessnet_AGB"; // Replace with your WiFi name
const char* password = "eeeeeeee"; // Replace with your WiFi password

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    
    // Wait until connected
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    
    Serial.println("\nConnected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    // Keep checking the WiFi connection
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi Disconnected! Reconnecting...");
        WiFi.disconnect();
        WiFi.reconnect();
    } else {
        Serial.println("WiFi Connected.");
    }
    delay(5000);
}
