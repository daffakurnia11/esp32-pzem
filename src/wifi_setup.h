#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

void wifiSetup(LiquidCrystal_I2C &lcd, const char *ssid, const char *password);

#endif // WIFI_SETUP_H
