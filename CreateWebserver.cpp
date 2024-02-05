#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "webpage.h"

const char *ssid = "wangwang";
const char *password = "quang123";

WebServer server(80);

void connectToWiFi(const char *ssid, const char *password)
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

void SendWebPage();

void setup()
{
    Serial.begin(115200);

    // wifi connect
    connectToWiFi(ssid, password);

    // server router
    server.on("/", HTTP_GET, SendWebPage);
    server.begin();
}

void loop()
{
    // handle connection of client
    server.handleClient();
}

void SendWebPage()
{
    server.send(200, "text/html", webpage);
}
