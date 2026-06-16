#ifndef CONFIG_H
#define CONFIG_H

// --- WiFi router (STA) ---
//const char* ssid = "nợ e một nàng dâu";
//const char* pass = "12345678";
//#define WIFI_ROUTER_SSID  "Tra My"
//#define WIFI_ROUTER_PASS  "tramy2013"

#define WIFI_ROUTER_SSID  "Tra My"
#define WIFI_ROUTER_PASS  "tramy2013"

// --- SoftAP (ESP-NOW gateway) ---
#define GATEWAY_AP_SSID   "ESP_SERVER"
#define GATEWAY_AP_PASS   "quyquyquy"

// --- Blynk ---
#define BLYNK_TEMPLATE_ID "TMPL6BjjVAi5R"
#define BLYNK_TEMPLATE_NAME "Đo điện"
#define BLYNK_AUTH_TOKEN "a3p7snHheCTSHe_G7ey50x5YqQcEUE_B"

// --- Server MAC ---
//[ESP-NOW] Device Server MAC: 8c:94:df:47:71:a4  

// --- Slave MAC ---
#define SLAVE1_MAC_INIT {0xa0, 0x20, 0xa6, 0x16, 0xe7, 0x65}
#define SLAVE2_MAC_INIT  {0xc8, 0xc9, 0xa3, 0x25, 0x68, 0x25}
#define SLAVE3_MAC_INIT  {0x48, 0x3f, 0xda, 0x33, 0x51, 0xc7}

#define NUM_SLAVES 3

// --- GPIO (ESP32 DevKit — chỉnh theo board thực tế) ---
#define relay1 26
#define relay2 27
#define relay3 14
#define relay4 12

#define switch1 32
#define switch2 33
#define switch3 25
#define switch4 22

// --- Blynk virtual pins (local relay + switch sync) ---
#define VPIN_LED_CONNECT 0
#define VPIN_RELAY1 1
#define VPIN_RELAY2 2
#define VPIN_RELAY3 3
#define VPIN_RELAY4 4


// --- Timing ---
#define SERIAL_BAUD                115200
#define WIFI_RECONNECT_INTERVAL_MS 5000
#define SWITCH_DEBOUNCE_MS         50
#define WIFI_CONNECT_TIMEOUT_SEC   20
#define WIFI_CONNECT_RETRY_MS      500
#define SETUP_DELAY_MS             50

#endif
