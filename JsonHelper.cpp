#include "JsonHelper.h"

// Hàm Parse Json, chuyển từ String(JSON) về dạng object
JsonDocument parseJson(const String &jsonBody)
{
    JsonDocument jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, jsonBody);
    if (error)
    {
        Serial.println("Failed to parse JSON");
    }
    return jsonDoc;
}

String convertToJsonString(JsonDocument &doc)
{

    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
}