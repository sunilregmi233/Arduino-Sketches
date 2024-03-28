#include <ESP8266WiFi.h>

const char* ssid = "gd_labs_wnepal";
const char* password = "CLB352511D";

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  // Your main code can go here
}

void connectWiFi() {
  Serial.println("Connecting to WiFi...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}
