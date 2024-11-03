#ifndef API_REQUEST_H
#define API_REQUEST_H

#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

void sendSensorData(const String &jsonData, LiquidCrystal_I2C &lcd);

#endif // API_REQUEST_H