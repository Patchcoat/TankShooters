/* Blink Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "queue.h"
#include "packet.h"
#include <Arduino.h>

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/

uint8_t broadcastAddress[] = {0x0,0x0,0x0,0x0,0x0,0x0};

#define VRX1_PIN (gpio_num_t) 34
#define VRY1_PIN (gpio_num_t) 35
#define SW1_PIN (gpio_num_t) 27
#define VRX2_PIN (gpio_num_t) 32
#define VRY2_PIN (gpio_num_t) 33

Queue controller_queue;
Queue tank_queue;
bool dead;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    TankPacket tank_packet;
    memcpy(&tank_packet, incomingData, sizeof(tank_packet));
    queue_push_back(&tank_queue, &tank_packet);
}

static void wireless(void *pvParameters) {
    while (1) {
        vTaskDelay(200/portTICK_PERIOD_MS);
        ControllerPacket controller_packet;
        int value_exists = queue_pop_front(&controller_queue, &controller_packet);
        if (value_exists) {
            esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &controller_packet, sizeof(controller_packet));
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("In Setup Function"));

    queue_init(&controller_queue, 32, sizeof(ControllerPacket));
    queue_init(&tank_queue, 32, sizeof(TankPacket));
    gpio_pad_select_gpio(VRX1_PIN);
    gpio_pad_select_gpio(VRY1_PIN);
    gpio_pad_select_gpio(SW1_PIN);
    gpio_pad_select_gpio(VRX2_PIN);
    gpio_pad_select_gpio(VRY2_PIN);
    gpio_set_direction(VRX1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(VRY1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(SW1_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(VRX2_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(VRY2_PIN, GPIO_MODE_INPUT);
    xTaskCreatePinnedToCore(wireless, "WirelessComm", 1000, NULL, 2, NULL, 0);
    queue_free(&controller_queue);
    queue_free(&tank_queue);

    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
}
void loop() {
    vTaskDelay(200 / portTICK_PERIOD_MS);

    TankPacket tank_packet;
    int value_exists = queue_pop_front(&tank_queue, &tank_packet);
    if (value_exists) { // if there is a packet
        if (tank_packet.hit) {
            // It's time to play the music
            // it's time to light the lights
        }
        dead = tank_packet.dead;
    }

    if (dead)
    {
        JoystickValue joystick1;
        JoystickValue joystick2;
        ControllerPacket packet;
        joystick1.VRx = gpio_get_level(VRX1_PIN);
        joystick1.VRy = gpio_get_level(VRY1_PIN);
        joystick1.SW = gpio_get_level(SW1_PIN);
        joystick2.VRx = gpio_get_level(VRX2_PIN);
        joystick2.VRy = gpio_get_level(VRY2_PIN);
        packet.joystick1 = joystick1;
        packet.joystick2 = joystick2;
        queue_push_back(&controller_queue, &packet);
    }
}