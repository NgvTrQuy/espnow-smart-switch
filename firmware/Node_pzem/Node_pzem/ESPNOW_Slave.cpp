#include <Arduino.h>
#include "ESPNOW_Slave.h"

// Instance slave (gắn với ID trong header)
ESPNOW_Slave espSlave;

// Địa chỉ MAC của Server
uint8_t serverMAC[] = SERVER_MAC_INIT;

static message recvData;

// Khởi tạo ESP-NOW
void ESPNOW_Slave::begin() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        Serial.println("[ESP-NOW] ❌ Lỗi khởi tạo ESP-NOW");
        return;
    }
    Serial.println("[ESP-NOW] ✅ ESP-NOW khởi tạo thành công");
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_recv_cb(OnDataRecv);
    esp_now_register_send_cb(OnDataSent);
    Serial.print("[ESP-NOW] Device Slave MAC: ");
    Serial.println(WiFi.macAddress());
}

// Thêm peer vào ESP-NOW
void ESPNOW_Slave::addPeer(const uint8_t *peer_addr) {
    // Địa chỉ MAC của Server
    uint8_t mac[6];
    // Sao chép địa chỉ MAC của Server vào mac
    memcpy(mac, peer_addr, 6);
    // Hiển thị địa chỉ MAC của Server
    Serial.printf("[ESP-NOW] ➕ Adding peer: %02X:%02X:%02X:%02X:%02X:%02X  ",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // Lấy channel của WiFi
    uint8_t channel = WiFi.channel();
    // Thêm peer vào ESP-NOW với role COMBO là một peer có thể gửi và nhận dữ liệu
    int result = esp_now_add_peer(mac, ESP_NOW_ROLE_COMBO, channel, NULL, 0);
    // Hiển thị kết quả thêm peer
    if (result == 0) Serial.println("✅ Peer added successfully");
    else Serial.printf("❌ Failed to add peer (Code: %d)\n", result);
}

// Kết nối WiFi Gateway
void ESPNOW_Slave::connectWiFi() {
    Serial.print("[WiFi] Connecting to ");
    Serial.println(GATEWAY_AP_SSID);// Hiển thị SSID của WiFi Gateway
    WiFi.begin(GATEWAY_AP_SSID, GATEWAY_AP_PASS);// Kết nối WiFi Gateway

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("✅ Kết nối WiFi Gateway thành công!");
        Serial.printf("[WiFi] Channel: %d, Status: %d\n", WiFi.channel(), WiFi.status());
    } else {
        Serial.println("🚨 Không thể kết nối WiFi Gateway.");
    }
}

// Gửi dữ liệu đến Server
void ESPNOW_Slave::sendData(uint8_t data, uint16_t value) {
    //đóng gói msg
    message msg = {};
    msg.id = ID;
    msg.data = data;
    msg.value = value;

    // Hiển thị dữ liệu gửi đến Server
    Serial.printf("[ESP-NOW] 📤 Slave%d Data:%d value:%d ", msg.id, msg.data, msg.value);

    int result = esp_now_send(serverMAC,(uint8_t *)&msg, sizeof(msg));
    // Kiểm tra kết quả gửi dữ liệu
    if (result == 0) {  Serial.println("✅ Data sent (callback pending)");
    } else {    Serial.printf("❌ Send failed! Code: %d\n", result);
    }
    // Cho hệ thống WiFi thở
    delay(30);
    yield();
}

// Nhận dữ liệu từ Server
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
    (void)mac;
    if (len != sizeof(message)) {
        Serial.printf("[ESP-NOW] Unexpected length: %d\n", len);
        return;
    }

    memcpy(&recvData, incomingData, sizeof(message));
    Serial.printf("[ESP-NOW] 📩 Data: %d | Val: %d\n", recvData.data, recvData.value);

    switch (recvData.data) {
        case DATA_RELAY:   digitalWrite(relay1, recvData.value); break;
        case DATA_RESET_ENERGY:
            extern void requestEnergyReset();
            if (recvData.value) {requestEnergyReset();}          break;
        case DATA_CURRENT_LIMIT:
            currentLimit = recvData.value;
            Serial.printf("Current Limit = %.1fA\n",currentLimit); break;
    }
}

// Gửi trạng thái đến Server
void OnDataSent(uint8_t *mac_addr, uint8_t status) {
    (void)mac_addr;
    Serial.print("[ESP-NOW] Send Status: ");
    Serial.println(status == 0 ? "✅ Success" : "❌ Fail");
}
