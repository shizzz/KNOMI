#ifndef MTTQT_CLIENT_H
#define MTTQT_CLIENT_H

#include <WiFiClient.h>
#include <PubSubClient.h>

class MQTTClient {
public:
    MQTTClient();  // Без параметров

    void begin();
    void loop();

    void publish(const char* topic, const char* payload);
    void publishFloat(const char* topic, float value, int precision = 2);
    void setSwitchCallback(std::function<void(bool)> callback);

private:
    WiFiClient wifiClient;
    PubSubClient client;

    void connectMQTT();
    void handleMessage(char* topic, byte* payload, unsigned int length);

    std::function<void(bool)> switchCallback;
    bool switchState = false;
};

extern MQTTClient mqtt;

void mqtt_task(void* parameter);

#endif