#ifndef JSON_PAYLOAD_H
#define JSON_PAYLOAD_H

#include <ArduinoJson.h>

String constructJsonPayload(const String &sensorName, float voltage, float current, float power, float pf, float frequency, float energy, float apparentPower, float reactivePower);

#endif