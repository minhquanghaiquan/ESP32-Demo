#include <WiFi.h>
#include <EEPROM.h>

#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 64

String readEEPROMString(int address, int maxLength);
void writeEEPROMString(int startAddress, String data);
void eraseAllEEPROM();

void setup()
{
    eraseAllEEPROM();
}

void loop()
{
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