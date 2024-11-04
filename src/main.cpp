#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <ArduinoJson.h> // Include ArduinoJson library
#include <HTTPClient.h>
#include "wifi_setup.h"  // Include WiFi setup header
#include "pzem_reader.h" // Include PZEM reader header
#include "api_request.h" // Include API request header

#define RX1 16
#define TX1 17
#define RX2 18
#define TX2 19
#define RX3 32
#define TX3 33

const char *ssid = "Daffa Angga";
const char *password = "Daf@111099";

// Each PZEM should have its own Serial
PZEM004Tv30 pzem1(Serial2, RX1, TX1);
PZEM004Tv30 pzem2(Serial2, RX2, TX2);
PZEM004Tv30 pzem3(Serial2, RX3, TX3);

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RX1, TX1); // Setup for the first PZEM

  lcd.init();
  lcd.backlight();

  wifiSetup(lcd, ssid, password); // Pass lcd and credentials to the function

  delay(2000);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Status: ");
  lcd.setCursor(0, 1);
  lcd.print("                    ");

  lcd.setCursor(-4, 2);
  lcd.print("                    ");

  lcd.setCursor(-4, 3);
  lcd.print("                    ");

  StaticJsonDocument<1024> doc; // Adjust size based on your needs
  JsonArray sensors = doc.createNestedArray("se");

  String sensorReader1 = pzemReader(pzem1, RX1, TX1, "1", 1, lcd); // Pass lcd to the reader function
  String sensorReader2 = pzemReader(pzem2, RX2, TX2, "2", 2, lcd); // Pass lcd to the reader function
  String sensorReader3 = pzemReader(pzem3, RX3, TX3, "3", 3, lcd); // Pass lcd to the reader function

  if (!sensorReader1.isEmpty() && !sensorReader2.isEmpty() && !sensorReader3.isEmpty())
  {
    JsonObject sensorObj1 = sensors.createNestedObject();
    StaticJsonDocument<256> tempDoc1;
    deserializeJson(tempDoc1, sensorReader1);
    sensorObj1.set(tempDoc1.as<JsonObject>());

    JsonObject sensorObj2 = sensors.createNestedObject();
    StaticJsonDocument<256> tempDoc2;
    deserializeJson(tempDoc2, sensorReader2);
    sensorObj2.set(tempDoc2.as<JsonObject>());

    JsonObject sensorObj3 = sensors.createNestedObject();
    StaticJsonDocument<256> tempDoc3;
    deserializeJson(tempDoc3, sensorReader3);
    sensorObj3.set(tempDoc3.as<JsonObject>());

    String jsonData;
    serializeJson(doc, jsonData);

    sendSensorData(jsonData, lcd);
  }

  delay(500); // Delay for readability
}
