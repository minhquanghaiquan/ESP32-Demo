#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "wangwang";
const char *password = "quang123";
// WiFiServer webServer(80);

void connectToWiFi()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);

    Serial.print("Connecting to wifi ");
    Serial.println(ssid);
    connectToWiFi();
}

void loop()
{
}