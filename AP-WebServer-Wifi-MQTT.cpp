#include <WiFi.h>
#include <WebServer.h>
#include <JsonHelper.h>
#include <PubSubClient.h>
#include <EEPROM.h>

#include "webpage.h"

const char *apSSID = "ESP32";
const char *apPassword = "quang123"; // Đặt mật khẩu cho AP của bạn
unsigned long lastMillis = 0;

#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 64

String readEEPROMString(int address, int maxLength);
void writeEEPROMString(int startAddress, String data);
void eraseAllEEPROM();
void connectMQTT();
void startAP();
void callbackMQTT(char *topic, byte *payload, unsigned int length);

WebServer server(80);

const char *mqttBroker = "192.168.172.95";
const int mqttPort = 1883;
const char *mqttClientID = "242512b04f5b493e949b44ff9b314740";
const char *mqttUsername = "tbnet_smartsite";
const char *mqttPassword = "pass1234567@";
const char *mqttTopic = "wang/esp32/demo";

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    EEPROM.begin(512);
    Serial.println("Set up");
    // Kiểm tra xem có thông tin WiFi trong EEPROM hay không
    String ssid = readEEPROMString(0, MAX_SSID_LENGTH);
    String password = readEEPROMString(64, MAX_PASSWORD_LENGTH);

    if (ssid.length() > MAX_SSID_LENGTH || password.length() > MAX_PASSWORD_LENGTH)
    {
        Serial.println("Erase All EEPROM...");
        eraseAllEEPROM();
    }

    Serial.println("SSID FROM EEPROM " + ssid);
    Serial.println("PASSWORD FROM EEPROM " + password);

    if (ssid.length() > 0 && password.length() > 0)
    {
        // Kết nối WiFi nếu có thông tin
        Serial.println("WIFI begin...");
        WiFi.begin(ssid.c_str(), password.c_str());
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
        Serial.println(WiFi.localIP());
        // Kết nối đến MQTT Broker
        connectMQTT();
    }
    else
    {
        // Nếu không có thông tin, bật AP và yêu cầu người dùng nhập thông tin
        startAP();
    }
}

void startAP()
{
    Serial.println("Starting AP...");
    WiFi.softAP(apSSID, apPassword);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    // Tạo server để xử lý trang web và thông tin nhập liệu
    server.on("/", HTTP_GET, []()
              { server.send(200, "text/html", webpage); });

    server.on("/submit", HTTP_POST, []()
              {
        String body = server.arg("plain");
        JsonDocument jsonDoc = parseJson(body);

        if (jsonDoc["ssid"] && jsonDoc["password"])
        {
            server.send(200, "text/plain", "POST request received successfully!");
            String ssid = jsonDoc["ssid"];
            String password = jsonDoc["password"];

            // Lưu thông tin vào EEPROM
            writeEEPROMString(0, ssid);
            writeEEPROMString(64, password);

            server.send(200, "text/plain", "WiFi configuration complete. Restarting...");
            delay(2000);
            ESP.restart();
        }
        else
        {
            server.send(400, "text/plain", "Bad Request");
        } });
    server.begin();
}

void connectMQTT()
{
    Serial.println("Connecting to MQTT Broker");
    client.setServer(mqttBroker, mqttPort);
    client.setCallback(callbackMQTT);

    while (!client.connected())
    {
        Serial.println("have clinet");
        if (client.connect(mqttClientID, mqttUsername, mqttPassword))
        {
            Serial.println("Connected to MQTT Broker");
            // Đăng ký các topic hoặc thực hiện các công việc khác sau khi kết nối MQTT
            client.subscribe(mqttTopic);
        }
        else
        {
            Serial.println("Failed to connect to MQTT Broker, retrying in 5 seconds");
            delay(5000);
        }
    }
}

void callbackMQTT(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void loop()
{
    server.handleClient();

    if (millis() - lastMillis > 10000)
    {
        client.publish(mqttTopic, "Hello from ESP32");
        lastMillis = millis();
    }

    // Gọi client.loop() để duy trì kết nối MQTT và xử lý tin nhắn
    client.loop();

    // Chương trình chính ở đây
}

void eraseAllEEPROM()
{
    EEPROM.begin(512);
    for (int i = 0; i < 512; ++i)
    {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
}

String readEEPROMString(int address, int maxLength)
{
    String value = "";
    for (int i = 0; i < maxLength; ++i)
    {
        char c = EEPROM.read(address + i);
        if (c == 0)
        {
            break;
        }
        value += c;
    }
    return value;
}

void writeEEPROMString(int startAddress, String data)
{
    for (int i = 0; i < data.length(); ++i)
    {
        EEPROM.write(startAddress + i, data[i]);
    }
    EEPROM.write(startAddress + data.length(), '\0');
    EEPROM.commit();
}