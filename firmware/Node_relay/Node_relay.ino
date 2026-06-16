#include "ESPNOW_Slave.h"

bool lastState1 = HIGH;
bool lastState2 = HIGH;

unsigned long lastReconnectAttempt = 0;

void setup() {
    Serial.begin(115200);
    delay(50);
    Serial.printf("\n =========ESPNOW SLAVE %d======== \n", ID);

    // Khởi tạo các relay và switch
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(switch2, INPUT_PULLUP);

    // Tắt relay ban đầu
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);


    // Kết nối WiFi Gateway
    espSlave.connectWiFi();
    yield();  // cho hệ thống WiFi thở
    delay(50);
     WiFi.setAutoReconnect(true);

    // Bật ESP-NOW
    espSlave.begin();
    // Thêm peer (Server)
    espSlave.addPeer(serverMAC);
}

// Kiểm tra trạng thái của switch và đồng bộ trạng thái relay và server
void checkSwitch(int touchPin, bool *lastState, int relayPin, uint8_t relay) {
    static unsigned long lastTouchTime[10] = {0};

    bool currentState = digitalRead(touchPin);

    // Phát hiện cạnh lên
    if (currentState == HIGH && *lastState == LOW) {

        // Chống nhiễu, chống chạm liên tiếp
        if (millis() - lastTouchTime[relay] > 300) {

            bool newRelayState = !digitalRead(relayPin);

            digitalWrite(relayPin, newRelayState);

            Serial.printf("Touch%d -> %d\n", relay, newRelayState);
            espSlave.sendData(relay, newRelayState);

            lastTouchTime[relay] = millis();
        }
    }

    *lastState = currentState;
}

void loop() {

    checkSwitch(switch1, &lastState1, relay1, 1);
    checkSwitch(switch2, &lastState2, relay2, 2);
}
