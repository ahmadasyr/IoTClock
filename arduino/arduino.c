#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Replace with your network credentials
const char *ssid = "your-SSID";
const char *password = "your-PASSWORD";

// Replace with your ESP8266 IP address
IPAddress serverIP(192, 168, 1, 2); // Change to your server's IP address
const int serverPort = 1234;         // Change to your server's port

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize server connection
  // Use the IP address of your server
  // Make sure your server is listening for socket connections on the specified port
}

void loop() {
  // Request current time from the server
  String currentTime = getCurrentTime();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(currentTime);

  // Check for messages from the server
  String receivedMessage = checkForMessages();
  if (receivedMessage.length() > 0) {
    lcd.setCursor(0, 1);
    lcd.print("Msg: ");
    lcd.print(receivedMessage);
  }

  delay(1000); // Delay to avoid flooding the server with requests
}

String getCurrentTime() {
  HTTPClient http;

  // Replace with your time zone API URL
  String url = "http://your-timezone-api-url";

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    // Parse the payload to extract the current time
    // Replace the following line with your parsing logic
    String currentTime = "Parsed Time"; 
    http.end();
    return currentTime;
  } else {
    Serial.println("Failed to get time from API");
    http.end();
    return "Error";
  }
}

String checkForMessages() {
  WiFiClient client;

  if (client.connect(serverIP, serverPort)) {
    if (client.available()) {
      String message = client.readStringUntil('\n');
      client.stop();
      return message;
    }
    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }

  return ""; // Return an empty string if no message is received
}
