#ifndef CONFIG_H
#define CONFIG_H

// --- Slave identity --- muốn thêm từng slave chỉ cần đổi ID 
#define ID 3

// --- Gateway (phải trùng softAP trên Server) ---
#define GATEWAY_AP_SSID   "ESP_SERVER"
#define GATEWAY_AP_PASS   "quyquyquy"

// --- Địa chỉ MAC của Server ---
#define SERVER_MAC_INIT {0x8c,0x94, 0xdf, 0x47, 0x71, 0xa5}   // MAC AP của Gateway
//SMAC1: a0:20:a6:16:e7:65

// --- GPIO ---
#define relay1 12   //D6 

// PZEM-004T (SoftwareSerial trên ESP8266)
// #define PZEM_RX 14   // D5
// #define PZEM_TX 12   // D6
#define PZEM_RX 4   // D2
#define PZEM_TX 5   // D1

//LIMIT
extern float currentLimit;
#define CURRENT_LIMIT_VALUE 1   //mặc định 1A
// data slot gửi lên Gateway (vpin = data + 4*ID → Slave3: V13..V16)
#define DATA_RELAY   1
#define DATA_CURRENT 2
#define DATA_POWER   3
#define DATA_ENERGY  4
#define DATA_RESET_ENERGY  5
#define DATA_CURRENT_LIMIT  6
// --- Timing ---
#define SERIAL_BAUD              115200
#define WIFI_RECONNECT_INTERVAL_MS 5000
#define SWITCH_DEBOUNCE_MS       50
#define WIFI_CONNECT_MAX_ATTEMPTS 20
#define WIFI_CONNECT_RETRY_MS    500

#endif
