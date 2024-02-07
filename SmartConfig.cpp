#include <WiFi.h>

void setup()
{
    Serial.begin(115200);

    // Khởi tạo kết nối Serial
    while (!Serial)
        ;

    // Bắt đầu SmartConfig
    WiFi.beginSmartConfig();

    Serial.println("Waiting for SmartConfig...");

    // Đợi kết nối thông qua SmartConfig trong 30 giây
    unsigned long start = millis();
    while (!WiFi.smartConfigDone() && (millis() - start < 30000))
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.smartConfigDone())
    {
        Serial.println("SmartConfig received.");

        // Lấy thông tin SSID và mật khẩu từ SmartConfig
        String ssid = WiFi.SSID();
        String password = WiFi.psk();

        Serial.print("SSID: ");
        Serial.println(ssid);
        Serial.print("Password: ");
        Serial.println(password);

        // Kết nối WiFi với thông tin từ SmartConfig
        WiFi.begin(ssid.c_str(), password.c_str());

        // Đợi kết nối WiFi
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi connected.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("SmartConfig timeout. Waiting for manual input...");
        // Thực hiện các công việc khác tại đây nếu cần
    }
}

void loop()
{
    // Chương trình chính của bạn ở đây
}