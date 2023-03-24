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
#include <Servo.h>
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

#define SERVO1_PIN (gpio_num_t) 34
#define SERVO2_PIN (gpio_num_t) 35
#define LASER_PIN (gpio_num_t) 27
#define HIT_PIN (gpio_num_t) 32
#define RESET_PIN (gpio_num_t) 33

Queue controller_queue;
Queue tank_queue;
bool dead;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    ControllerPacket controller_packet;
    memcpy(&controller_packet, incomingData, sizeof(controller_packet));
    queue_push_back(&controller_queue, &controller_packet);
}

static void wireless(void *pvParameters) {
    while (1) {
        vTaskDelay(200/portTICK_PERIOD_MS);
        TankPacket tank_packet;
        int value_exists = queue_pop_front(&tank_queue, &tank_packet);
        if (value_exists) {
            esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &tank_packet, sizeof(tank_packet));
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("In Setup Function"));

    queue_init(&controller_queue, 32, sizeof(ControllerPacket));
    queue_init(&tank_queue, 32, sizeof(TankPacket));
    gpio_pad_select_gpio(SERVO1_PIN);
    gpio_pad_select_gpio(SERVO2_PIN);
    gpio_pad_select_gpio(LASER_PIN);
    gpio_pad_select_gpio(HIT_PIN);
    gpio_pad_select_gpio(RESET_PIN);
    gpio_set_direction(SERVO1_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(SERVO2_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LASER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(HIT_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(RESET_PIN, GPIO_MODE_INPUT);
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

    // reset the tank
    int reset = gpio_get_level(RESET_PIN);
    if (reset) {
        dead = false;
    }

    // check hit and set death
    TankPacket tank_packet;
    tank_packet.hit = false;
    int hit = gpio_get_level(HIT_PIN);
    if (hit && !dead) {
        dead = true;
        tank_packet.hit = true;
    }
    tank_packet.dead = dead;
    queue_push_back(&tank_queue, &tank_packet);

    // Only move the motors if the tank isn't dead
    if (dead)
        return;

    // Get values from controller packets and adjust motor speeds/servo directions
    ControllerPacket controller_packet;
    int value_exists = queue_pop_front(&controller_queue, &controller_packet);
    if (value_exists) { // if there is a packet
        // set motor values based on the controller packet
    }
}