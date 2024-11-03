#ifndef PZEM_READER_H
#define PZEM_READER_H

#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>

void printAllValues(String name, float volt, float ampere, float power, float energy, float frequency, float pf, LiquidCrystal_I2C &lcd);
bool checkNanValue(String name, int row, int sensorName, float volt, float ampere, float power, float energy, float frequency, float pf, LiquidCrystal_I2C &lcd);
String pzemReader(PZEM004Tv30 &pzem, int rxPin, int txPin, const String &name, const int &row, LiquidCrystal_I2C &lcd);

#endif // PZEM_READER_H
