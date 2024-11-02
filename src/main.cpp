#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include "wifi_setup.h"  // Include WiFi setup header
#include "pzem_reader.h" // Include PZEM reader header

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
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Status: ");
  pzemReader(pzem1, RX1, TX1, "1", 1, lcd); // Pass lcd to the reader function
  pzemReader(pzem2, RX2, TX2, "2", 2, lcd); // Pass lcd to the reader function
  pzemReader(pzem3, RX3, TX3, "3", 3, lcd); // Pass lcd to the reader function

  delay(3000); // Delay for readability
}
