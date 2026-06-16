#include "config.h"
#include "BlynkModule.h"
#include "WiFiModule.h"
#include <WiFi.h>
#include <esp_now.h>
#include <BlynkSimpleEsp32_SSL.h>


#define BLYNK_PRINT Serial

WidgetLED led_connect(VPIN_LED_CONNECT);

void beginBlynk() {
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void blynkRun() {
    Blynk.run();
}

void blynkVirtualWrite(int vPin, int value) {
    Blynk.virtualWrite(vPin, value);
}

BLYNK_CONNECTED() {
    Serial.println("✅ Kết nối Blynk thành công!");
    led_connect.on();
    Blynk.syncAll();  // Blynk Server gửi lại trạng thái mới nhất của all Virtual Pins (Vpin) về ESP32
}

void checkMessage(bool *newMsg, message msg) {
    if (*newMsg) {
        *newMsg = false;
        Serial.printf("📩 Slave%d gửi: Relay:%d | Cmd:%d\n", msg.id, msg.relay, msg.command);
        int vpin = msg.relay + 4*msg.id;
        Blynk.virtualWrite(vpin, msg.command);
    }
}

BLYNK_WRITE(V1) { digitalWrite(relay1, param.asInt()); }
BLYNK_WRITE(V2) { digitalWrite(relay2, param.asInt()); }
BLYNK_WRITE(V3) { digitalWrite(relay3, param.asInt()); }
BLYNK_WRITE(V4) { digitalWrite(relay4, param.asInt()); }

BLYNK_WRITE(V5) { espNow.sendSlaveCommand(1, 1, param.asInt()); } //Blynk gửi lệnh  V5 đến Slave1 Relay1 
BLYNK_WRITE(V6) { espNow.sendSlaveCommand(1, 2, param.asInt()); }
BLYNK_WRITE(V7) { espNow.sendSlaveCommand(1, 3, param.asInt()); }
BLYNK_WRITE(V8) { espNow.sendSlaveCommand(1, 4, param.asInt()); }

BLYNK_WRITE(V9) { espNow.sendSlaveCommand(2, 1, param.asInt()); }
BLYNK_WRITE(V10) { espNow.sendSlaveCommand(2, 2, param.asInt()); }
BLYNK_WRITE(V11) { espNow.sendSlaveCommand(2, 3, param.asInt()); }
BLYNK_WRITE(V12) { espNow.sendSlaveCommand(2, 4, param.asInt()); }

BLYNK_WRITE(V13) { espNow.sendSlaveCommand(3, 1, param.asInt()); }
// BLYNK_WRITE(V14) { espNow.sendSlaveCommand(3, 2, param.asInt()); }
// BLYNK_WRITE(V15) { espNow.sendSlaveCommand(3, 3, param.asInt()); }
// BLYNK_WRITE(V16) { espNow.sendSlaveCommand(3, 4, param.asInt()); }
BLYNK_WRITE(V17) { espNow.sendSlaveCommand(3, 5, param.asInt()); }//reset energy
BLYNK_WRITE(V18) { espNow.sendSlaveCommand(3, 6, param.asFloat()); }//ngắt tải