#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <ArduinoJson.h>

JsonDocument parseJson(const String &jsonBody);
String convertToJsonString(JsonDocument &doc);

#endif