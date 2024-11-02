#include "wifi_setup.h"

void wifiSetup(LiquidCrystal_I2C &lcd, const char *ssid, const char *password)
{
  lcd.setCursor(0, 0);
  lcd.print("PZEM Reader");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  lcd.setCursor(0, 1);
  lcd.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PZEM Reader");

  Serial.println();
  Serial.println("Connected to WiFi!");
  lcd.setCursor(0, 1);
  lcd.print("Connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0 - 4, 2);
  lcd.print("IP: ");
  lcd.setCursor(4 - 4, 2);
  lcd.print(WiFi.localIP());
}
