#ifndef ESPNOW_SLAVE_H
#define ESPNOW_SLAVE_H

#include "config.h"
#include <ESP8266WiFi.h>
#include <espnow.h>

// Định nghĩa struct message
struct message {
    uint8_t id = ID;
    uint8_t relay;
    uint16_t command;
};

class ESPNOW_Slave {
public:
    ESPNOW_Slave() {}

    void begin(); // Khởi tạo ESP-NOW
    void addPeer(const uint8_t *peer_addr); // Thêm peer vào ESP-NOW
    void connectWiFi(); // Kết nối WiFi Gateway
    void sendData(uint8_t relay, uint16_t command); // Gửi dữ liệu đến Server
};

// Instance dùng chung (không cần tạo trong .ino)
extern ESPNOW_Slave espSlave;

// Địa chỉ MAC của Server
extern uint8_t serverMAC[];

// Định nghĩa callback nhận dữ liệu
void OnDataRecv(uint8_t *mac, uint8_t *data, uint8_t len);
// Định nghĩa callback gửi dữ liệu
void OnDataSent(uint8_t *mac, uint8_t status);

#endif
