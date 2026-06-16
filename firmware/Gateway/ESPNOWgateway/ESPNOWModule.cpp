#include <Arduino.h>
#include "WiFiModule.h"
#include "config.h"
#include "ESPNOWModule.h"

ESPNOW espNow;

uint8_t slave1MAC[] = SLAVE1_MAC_INIT;
uint8_t slave2MAC[] = SLAVE2_MAC_INIT;
uint8_t slave3MAC[] = SLAVE3_MAC_INIT;

uint8_t* slaveMACs[] = {slave1MAC, slave2MAC, slave3MAC};

//Biến status message
message lastMsg;      // Lưu dữ liệu nhận mới nhất
bool newMsg = false; 

// 🟢 Khởi tạo ESP-NOW (Server)
void ESPNOW::begin() {
 //   WiFi.mode(WIFI_AP_STA);
    WiFi.setSleep(false); // thử thêm để giảm delay từ blynk xuống!!!!! rất hiệu quả
    delay(100);
    uint8_t staChannel = WiFi.channel();
    // Bật AP cùng kênh với STA để ESP-NOW ổn định
    WiFi.softAP(GATEWAY_AP_SSID, GATEWAY_AP_PASS, staChannel);

    // 
    Serial.println("===== WiFi Channel Info =====");
    Serial.printf("STA Channel:%d Status:%d MAC:%s\n", WiFi.channel(), WiFi.status(), WiFi.macAddress().c_str());
    Serial.printf("AP  Channel:%d IP:%s MAC:%s\n",WiFi.channel(),WiFi.softAPIP().toString().c_str(), WiFi.softAPmacAddress().c_str());

    //Serial.printf("Num Slave Connect AP: %d\n", WiFi.softAPgetStationNum());                  // Số client đang kết nối 
    Serial.println("=============================");

    Serial.print("AP MAC: ");
    Serial.println(WiFi.softAPmacAddress());

    printWiFiStatus(); 

    // ⚙️ Khởi tạo ESP-NOW
     if (esp_now_init() != ESP_OK) {
        Serial.println("[ESP-NOW] ❌ Lỗi khởi tạo ESP-NOW");
        return;
    } else { Serial.println("[ESP-NOW] ✅ ESP-NOW khởi tạo thành công");}
        
        esp_now_register_recv_cb(OnDataRecv);
        esp_now_register_send_cb(OnDataSent);


        Serial.print("[ESP-NOW] Device Server MAC: ");
        Serial.println(WiFi.macAddress());
    }

// 🟢 Thêm peer (Slave)
void ESPNOW::addPeer(const uint8_t *peer_addr) {
    uint8_t mac[6];
    memcpy(mac, peer_addr, 6);

    Serial.printf("[ESP-NOW] ➕ Adding peer: %02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    uint8_t channel = WiFi.channel();

    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, mac, 6);
    peer.channel = channel;
    peer.encrypt = false;
    int result = esp_now_add_peer(&peer);


    if (result == 0)
        Serial.println("[ESP-NOW] ✅ Peer added successfully");
    else
        Serial.printf("[ESP-NOW] ❌ Failed to add peer (Code: %d)\n", result);
}

// 🟢 Gửi dữ liệu
void ESPNOW::sendData(message &data) {
    Serial.printf("[ESP-NOW] 📤 Send -> Slave%d: Relay%d | Cmd: %d ",data.id, data.relay, data.command);
    uint8_t* targetMac = slaveMACs[data.id - 1];  // nếu id bắt đầu từ 1

    int result = esp_now_send(targetMac, (uint8_t *)&data, sizeof(data)); // NULL = gửi broadcast        (uint8_t *)&data = ép kiểu data sang
    //Kiểm tra hàm gửi có được gọi thành công không

    if (result == 0) Serial.print("✅ Data sent (callback pending) ");
    else Serial.printf("❌ Send failed! Code: %d ", result);
}

// 🟢 Gửi lệnh xuống slave
void ESPNOW::sendSlaveCommand(uint8_t id,uint8_t relay, uint16_t command) {
    message msg; 
    msg.id = id;
    msg.relay = relay;
    msg.command = command;
    sendData(msg);
}


void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *data,int len){
    // MAC của thiết bị gửi
    const uint8_t *mac = info->src_addr;
    (void)mac;  // báo với compiler: mac tồn tại nhưng tạm thời chưa dùng đến, đừng cảnh báo.
    Serial.println("Nhận state từ slave");
    // Kiểm tra kích thước dữ liệu đúng với struct message
    if (len == (int)sizeof(message)) {
        memcpy(&lastMsg, data, sizeof(message));
        newMsg = true;
    }
}

void OnDataSent(const wifi_tx_info_t *info,esp_now_send_status_t status){
    // Có thể lấy MAC đích:
    const uint8_t *mac = info->des_addr;
    (void)info;
    Serial.print("State: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ?"✅ Success" :"❌ Fail");
}



