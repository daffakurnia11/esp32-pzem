#include <HTTPClient.h>
#include "wifi_setup.h" // Include WiFi setup header

// String apiUrl = "https://mf745t99-8000.asse.devtunnels.ms/api/sensors/bulk";
String apiUrl = "https://fp-backend.finalproject-be.dafkur.com/api/v1/sensors";

// Function to send the HTTP POST request
void sendSensorData(const String &jsonData, LiquidCrystal_I2C &lcd)
{
  // Send HTTP POST request
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(apiUrl);
    http.addHeader("Content-Type", "application/json"); // Specify content-type header

    Serial.print("Status API Request : "); // Print return code

    int httpResponseCode = http.POST(jsonData); // Send the request
    if (httpResponseCode > 0)
    {
      Serial.println(httpResponseCode); // Print return code
      lcd.setCursor(8, 0);
      lcd.print(httpResponseCode);
    }
    else
    {
      Serial.println(httpResponseCode); // Print error code
      lcd.setCursor(8, 0);
      lcd.print(httpResponseCode);
    }
    http.end(); // Free resources
  }
  else
  {
    Serial.println("WiFi not connected");
  }
}