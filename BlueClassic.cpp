#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("esp32");
    delay(500);
    Serial.println("Bluetooth Ready");
}

void loop()
{
    if (SerialBT.available())
    {
        String dataReceive = SerialBT.readString();
        Serial.print(dataReceive);
    }

    if (Serial.available())
    {
        String dataTransmit = Serial.readString();
        SerialBT.println(dataTransmit);
    }
}