#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHT_PIN 26  // GPIO pin to which DHT11 sensor is connected
#define DHT_TYPE DHT11

const char *ssid = "gd_labs_wnepal";
const char *password = "CLB352511D";
const char *serverUrl = "https://sunilregmi233:sunil871@sunilregmi233.pythonanywhere.com/api/sensor-data/";

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
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
  delay(60000);  // Delay for 5 seconds

  // Read temperature and humidity data from DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // if (isnan(temperature) || isnan(humidity)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   return;
  // }

  // Create form-encoded payload
  String payload = "temperature=" + String(temperature) + "&humidity=" + String(humidity);

  // Send HTTP POST request
  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    
    String response = http.getString();
    Serial.println("Server response: " + response);
  } else {
    Serial.print("HTTP Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}
