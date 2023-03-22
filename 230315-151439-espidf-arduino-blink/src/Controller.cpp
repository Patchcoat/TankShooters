/* Blink Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "queue.h"
#include <Arduino.h>

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/

#define VRX1_PIN (gpio_num_t) 34
#define VRY1_PIN (gpio_num_t) 35
#define SW1_PIN (gpio_num_t) 27
#define VRX2_PIN (gpio_num_t) 32
#define VRY2_PIN (gpio_num_t) 33

typedef struct JoystickValue {
    float VRx = 0;
    float VRy = 0;
    bool SW = false;
} JoystickValue;
typedef struct ControllerPacket {
    JoystickValue joystick1;
    JoystickValue joystick2;
} ControllerPacket;
typedef struct TankPacket {
    bool hit;
    bool dead;
} TankPacket;

Queue controller_queue;
Queue tank_queue;
bool dead;

static void wireless(void *pvParameters) {
    while (1) {
        vTaskDelay(200/portTICK_PERIOD_MS);
        ControllerPacket controller_packet;
        int value_exists = queue_pop_front(&controller_queue, &controller_packet);
        if (value_exists) {
            // Send wireless data
        }
        // Read wireless data
        TankPacket tank_packet;
        queue_push_back(&tank_queue, &tank_packet);
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