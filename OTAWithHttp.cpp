#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

void update();

const char *ssid = "wangwang";
const char *password = "quang123";

void setup()
{
    Serial.begin(115200);
    // Connect to Wi-Fi
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    update();
}

void loop()
{
}

void update()
{
    if ((WiFi.status() == WL_CONNECTED))
    {

        t_httpUpdate_return ret = ESPhttpUpdate.update("https://server-demo-esp32.onrender.com/public/ota.bin");

        switch (ret)
        {
        case HTTP_UPDATE_FAILED:
            Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;

        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("HTTP_UPDATE_NO_UPDATES");
            break;

        case HTTP_UPDATE_OK:
            Serial.println("HTTP_UPDATE_OK");
            break;
        }
    }
}