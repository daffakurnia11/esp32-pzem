#include <ArduinoJson.h>
#include "json_payload.h"

// Function to construct JSON payload for a sensor
String constructJsonPayload(const String &sensorName, float voltage, float current, float power, float pf, float frequency, float energy, float apparentPower, float reactivePower)
{
  StaticJsonDocument<256> doc; // Choose an appropriate size based on your data

  // Fill the JSON document
  JsonObject sensor = doc.to<JsonObject>();
  sensor["name"] = sensorName;
  sensor["voltage"] = voltage;
  sensor["current"] = current;
  sensor["power"] = power;
  sensor["power_factor"] = pf;
  sensor["frequency"] = frequency;
  sensor["energy"] = energy;
  sensor["apparent_power"] = apparentPower;
  sensor["reactive_power"] = reactivePower;

  String jsonData;
  serializeJson(doc, jsonData);

  // Serialize JSON to String
  return jsonData; // Return the constructed JSON string
}