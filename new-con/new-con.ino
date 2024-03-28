#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char *ssid = "suman_5";
const char *password = "CLB2711665";
const char *server = "sunilregmi233.pythonanywhere.com";
const String path = "/api/sensor-data";

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Send HTTP POST request
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Construct the complete URL
    String url = String("http://") + server + path;

    // Create JSON payload with sensor data
    String payload = "{\"humidity\":" + String(humidity) + ",\"temperature\":" + String(temperature) + "}";

    // Send the POST request
    http.begin(client, url);  // Pass the WiFiClient object
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);

    // Check for a successful response
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("HTTP Error code: ");
      Serial.println(httpResponseCode);
    }

    // End the request
    http.end();
  }

  delay(5000); // Wait for 5 seconds before sending the next request
}
