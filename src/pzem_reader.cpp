#include <ArduinoJson.h>
#include "pzem_reader.h"
#include "json_payload.h"

void printAllValues(String name, float volt, float ampere, float power, float energy, float frequency, float pf, float apparentPower, float reactivePower, LiquidCrystal_I2C &lcd)
{
  Serial.print("\n========== PZEM ");
  Serial.print(name);
  Serial.println(" Readers ==========");

  Serial.print("Voltage        : ");
  Serial.print(volt, 1);
  Serial.println(" V");

  Serial.print("Current        : ");
  Serial.print(ampere, 3);
  Serial.println(" A");

  Serial.print("Power          : ");
  Serial.print(power, 1);
  Serial.println(" W");

  Serial.print("Energy         : ");
  Serial.print(energy, 3);
  Serial.println(" kWh");

  Serial.print("Frequency      : ");
  Serial.print(frequency, 1);
  Serial.println(" Hz");

  Serial.print("Power Factor   : ");
  Serial.println(pf, 3);

  Serial.print("Apparent Power : ");
  Serial.print(apparentPower, 1);
  Serial.println(" VA");

  Serial.print("Reactive Power : ");
  Serial.print(reactivePower, 1);
  Serial.println(" VAR");

  Serial.println("====================================\n");
}

bool checkNanValue(String name, int row, int sensorName, float volt, float ampere, float power, float energy, float frequency, float pf, LiquidCrystal_I2C &lcd)
{
  bool isNan = isnan(volt) || isnan(ampere) || isnan(power) || isnan(energy) || isnan(frequency) || isnan(pf);

  if (isNan)
  {
    lcd.setCursor(sensorName, row);
    lcd.print(name + ":");
    lcd.setCursor(sensorName + 3, row);
    lcd.print("Sensor Error");
  }

  return isNan;
}

String pzemReader(PZEM004Tv30 &pzem, int rxPin, int txPin, const String &name, const int &row, LiquidCrystal_I2C &lcd)
{
  Serial2.end();
  Serial2.begin(9600, SERIAL_8N1, rxPin, txPin);

  float volt = pzem.voltage();
  float ampere = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  float apparPower, reactPower;

  if (pf == 0)
  {
    apparPower = 0;
  }
  else
  {
    apparPower = power / pf;
  }
  if (pf == 0)
  {
    reactPower = 0;
  }
  else
  {
    reactPower = power / pf * sqrt(1 - sq(pf));
  }

  printAllValues(name, volt, ampere, power, energy, frequency, pf, apparPower, reactPower, lcd); // Pass lcd to the function

  int sensorName = 0, ampereValue = 3, ampereUnit = 8, powerValue = 10, powerUnit = 15;

  if (row >= 2)
  {
    sensorName -= 4;
    ampereValue -= 4;
    ampereUnit -= 4;
    powerValue -= 4;
    powerUnit -= 4;
  }

  String sensor = constructJsonPayload("Sensor " + name, volt, ampere, power, pf, frequency, energy, apparPower, reactPower);

  if (checkNanValue(name, row, sensorName, volt, ampere, power, energy, frequency, pf, lcd))
  {
    return ""; // Exit if any value is NaN
  }

  // Display values on the LCD
  lcd.setCursor(sensorName, row);
  lcd.print(name + ":");
  lcd.setCursor(ampereValue, row);
  lcd.print(ampere, 3);
  lcd.setCursor(ampereUnit, row);
  lcd.print("A");
  lcd.setCursor(powerValue, row);
  lcd.print(power, 1);
  lcd.setCursor(powerUnit, row);
  lcd.print("W");

  return sensor;
}
