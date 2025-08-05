#ifndef CONFIG_H
#define CONFIG_H

#if __has_include("config_secrets.h")
  #include "config_secrets.h"
#else
  #define STA_SSID "default_ssid"
  #define STA_PWD  "default_password"
  #define MQTT_USER "MQTT_USER"
  #define MQTT_PWD  "MQTT_PWD"
#endif

#define FW_VERSION "V1.0.2"

 // default 80 for http
#define SERVER_PORT 80

#define SCAN_SSIDS_NUM 10     //  The max number of SSIDs that we will scan for.

#define HOSTNAME "Dummy13"
#define AP_SSID "Knomi" // Create a SSID for BTT KNOMI Access Point
#define AP_PWD "" // Default no password
#define AP_LOCAL_IP IPAddress(192, 168, 20, 1) // access point IP
#define AP_GATEWAY  IPAddress(192, 168, 20, 1) // gateway IP
#define AP_SUBNET   IPAddress(255, 255, 255, 0) // subnet mask
#define MODE WIFI_MODE_STA

#define USE_MTTQT
#define MQTT_CLIENT "Dummy13"
#define MQTT_SERVER "192.168.137.28"
#define MQTT_PORT 1883
#define MQTT_TOPIC "dummy13"

#define WIFI_STA_TIMEOUT 15000  // 15s

// BTT red color for UI (RGB888)
#define LV_32BIT_BTT_RED    0xC02F30
#define LV_32BIT_BTT_BLUE   0x209ADE
#define LV_32BIT_BTT_PURPLE 0xA91DDA
#define LV_32BIT_BTT_GREEN  0x5DA910
#define LV_DEFAULT_COLOR    LV_32BIT_BTT_RED

#endif
