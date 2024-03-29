#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "de1bf7ab-1ca8-40a3-b797-6221c2acb33d"
#define CHARACTERISTIC_UUID "3559f95b-3857-43f1-a7e0-cc0ab0542afc"

class callBackBLE : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        Serial.print("here ");
        std::string rxValue = pCharacteristic->getValue();
        if (rxValue.length() > 0)
        {
            Serial.println("**********");
            Serial.print("Recieved Value : ");
            for (int i = 0; i < rxValue.length(); i++)
            {
                Serial.print(rxValue[i]);
            }
            Serial.println();
            Serial.println("**********");
        }
    }
};

void setup()
{
    Serial.begin(115200);

    BLEDevice::init("ESP32_BLE");

    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setValue("Hello this is BLE default value");
    pCharacteristic->setCallbacks(new callBackBLE());

    pService->start();

    BLEDevice::startAdvertising();

    Serial.println("BLE READY!!!");
}

void loop()
{
}