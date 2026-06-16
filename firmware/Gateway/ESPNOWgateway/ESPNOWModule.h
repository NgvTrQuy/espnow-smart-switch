#ifndef ESPNOWMODULE_H
#define ESPNOWMODULE_H

#include <WiFi.h>
#include <esp_now.h>

//Định nghĩa struct message
struct message {
    uint8_t id;
    uint8_t relay;
    uint16_t command;
};

// 🛰️ Lớp ESPNOW để gửi / nhận dữ liệu
class ESPNOW {
    public:
        ESPNOW() {}
    
        void begin();   // Khởi tạo ESP-NOW
        void addPeer(const uint8_t *peer_addr);
        void sendData(message &data);
        void setRecvCallback(void (*callback)(uint8_t *mac, uint8_t *data, uint8_t len));
        void setSendCallback(void (*callback)(uint8_t *mac, uint8_t status));
        void sendSlaveCommand(uint8_t id,uint8_t relay, uint16_t command);
    };

// --- KHAI BÁO EXTERN ---
extern ESPNOW espNow; 
extern message lastMsg;
extern bool newMsg;
extern uint8_t slave1MAC[];
extern uint8_t slave2MAC[];
extern uint8_t slave3MAC[];
extern uint8_t* slaveMACs[];

//void printWiFiStatus();


void OnDataRecv(const esp_now_recv_info_t *info,
                const uint8_t *data,
                int len);

void OnDataSent(const wifi_tx_info_t *info,
                esp_now_send_status_t status);


#endif
