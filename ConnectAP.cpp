#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "ESP32-Wifi-AP-Mode";
const char *password = "12345678";

void setupAP()
{
  // Thiết lập Access Point với tên mạng và mật khẩu
  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started. IP: " + WiFi.softAPIP().toString());
}

void setup()
{
  Serial.begin(115200);
  setupAP();
}

void loop()
{
}
