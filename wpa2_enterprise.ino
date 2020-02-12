#include <WiFi.h>
#include "esp_wpa2.h"
#include <Wire.h>
#include "cert.h"

#define EAP_ANONYMOUS_IDENTITY "anon_identity"
#define EAP_IDENTITY "identity"
const char* ssid = "ssid";

#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP  10
RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("MAC address: " + WiFi.macAddress());
  Serial.println();
  Serial.println("Connecting to network: " + (String)ssid);
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_cert_key(user_cert, sizeof(user_cert), user_key, sizeof(user_key), 0, 0);
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);
  WiFi.begin(ssid);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    counter++;
    if (counter >= 60) {
      ESP.restart();
    }
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address set: ");
  Serial.println(WiFi.localIP());
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() {
}
