#include "mqtt_client.h"
#include <Arduino.h>
#include "knomi.h"

#ifndef MQTT_SERVER
#error "MQTT_SERVER not defined"
#endif

#ifndef MQTT_PORT
#error "MQTT_PORT not defined"
#endif

#ifndef MQTT_USER
#error "MQTT_USER not defined"
#endif

#ifndef MQTT_PWD
#error "MQTT_PWD not defined"
#endif

#ifndef MQTT_TOPIC
#error "MQTT_TOPIC not defined"
#endif

#ifndef MQTT_CLIENT
#error "MQTT_CLIENT not defined"
#endif

MQTTClient::MQTTClient()
    : client(wifiClient)
{}

void MQTTClient::begin() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    connectMQTT();
}

void MQTTClient::loop() {
    if (!client.connected()) {
        connectMQTT();
    }
    client.loop();
}

void MQTTClient::connectMQTT() {
    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect(MQTT_CLIENT, MQTT_USER, MQTT_PWD)) {
            Serial.println("MQTT connected");
        } else {
            Serial.print("MQTT connect failed, rc=");
            Serial.print(client.state());
            Serial.println(" retrying in 5 seconds");
            delay(5000);
        }
    }
}

void MQTTClient::publish(const char* topic, const char* payload) {
    client.publish(topic, payload);
}

void MQTTClient::publishFloat(const char* topic, float value, int precision) {
    char buffer[32];
    dtostrf(value, 0, precision, buffer);
    publish(topic, buffer);
}

void MQTTClient::handleMessage(char* topic, byte* payload, unsigned int length) {
    payload[length] = '\0';
    String message = String((char*)payload);

    char set_topic[64];
    snprintf(set_topic, sizeof(set_topic), "%s/switch/state", MQTT_TOPIC);
    if (strcmp(topic, set_topic) == 0) {
        bool newState = message == "ON";
        if (newState != switchState) {
            switchState = newState;

            char state_topic[64];
            snprintf(state_topic, sizeof(state_topic), "%s/switch/state", MQTT_TOPIC);
            Serial.printf("Switch changed to: %s\n", newState ? "ON" : "OFF");
            publish(state_topic, switchState ? "ON" : "OFF");

            if (switchCallback) {
                switchCallback(switchState);
            }
        }
    }
}

void MQTTClient::setSwitchCallback(std::function<void(bool)> callback) {
    this->switchCallback = callback;
}

MQTTClient mqtt;

void mqtt_task(void * parameter) {
    bool mqttStarted = false;

    for (;;) {
        if (wifi_get_connect_status() == WIFI_STATUS_CONNECTED) {
            if (!mqttStarted) {
                mqtt.begin();
                mqttStarted = true;
            } else {
                float voltage = 4.2;

                if (voltage < 3.6) {
                    Serial.println("Battery too low, shutting down...");
                    delay(1000);
                    esp_deep_sleep_start();
                }

                char topic[64];
                snprintf(topic, sizeof(topic), "%s/battery_voltage", MQTT_TOPIC);
                mqtt.publishFloat(topic, voltage);
                mqtt.loop();
            }
        } else {
            mqttStarted = false;
        }

        delay(10000);
    }
}