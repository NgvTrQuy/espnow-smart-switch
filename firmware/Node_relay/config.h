#ifndef CONFIG_H
#define CONFIG_H

// --- Slave identity --- muốn thêm từng slave chỉ cần đổi ID 
#define ID 1

// --- Gateway (phải trùng softAP trên Server) ---
#define GATEWAY_AP_SSID   "ESP_SERVER"
#define GATEWAY_AP_PASS   "quyquyquy"

// --- Địa chỉ MAC của Server ---
#define SERVER_MAC_INIT {0x8c,0x94, 0xdf, 0x47, 0x71, 0xa5}   // MAC AP của Gateway
//SMAC1: a0:20:a6:16:e7:65

// --- GPIO ---
#define relay1 5   // D1
#define relay2 4   // D2

#define switch1 14  // D5
#define switch2 12  // D6   

// --- Timing ---
#define SERIAL_BAUD              115200
#define WIFI_RECONNECT_INTERVAL_MS 5000
#define SWITCH_DEBOUNCE_MS       50
#define WIFI_CONNECT_MAX_ATTEMPTS 20
#define WIFI_CONNECT_RETRY_MS    500

#endif
