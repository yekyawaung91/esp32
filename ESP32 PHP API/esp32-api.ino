#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "Wirelessnet_AGB";
const char* password = "eeeeeeee";

// Server URL
const char* serverUrl = "http://10.10.10.164:8888/esp32/api.php"; // Change to your local IP


void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        
        float temperature = 10;
        float humidity = 20;

        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        // Create JSON object
        StaticJsonDocument<200> jsonDoc;
        jsonDoc["temperature"] = temperature;
        jsonDoc["humidity"] = humidity;

        String jsonData;
        serializeJson(jsonDoc, jsonData);

        Serial.println("Sending JSON: " + jsonData);

        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        int httpResponseCode = http.POST(jsonData);
        
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Server Response: " + response);
        } else {
            Serial.println("Error sending request: ");
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected!");
    }

    delay(5000); // Send data every 5 seconds
}
