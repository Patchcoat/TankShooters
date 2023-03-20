/* Blink Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include <Arduino.h>

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/

#define LED_PIN (gpio_num_t) 12
#define LED_PIN2 (gpio_num_t) 14
#define VRX_PIN 34
#define VRY_PIN 35
#define SW_PIN GND

int pos = 0;
typedef struct JoystickValue {
    float VRx = 0;
    float VRy = 0;
    bool SW = false;
} JoystickValue;
QueueHandle_t queue;


static void servoWrite(void *pvParameters) {
    while (1) {
        vTaskDelay(200/portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 14, HIGH);
        vTaskDelay(200/portTICK_PERIOD_MS);
        gpio_set_level((gpio_num_t) 14, LOW);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println(F("In Setup Function"));

    queue = xQueueCreate(32, sizeof(JoystickValue));

    gpio_pad_select_gpio(LED_PIN);
    gpio_pad_select_gpio(LED_PIN2);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_PIN2, GPIO_MODE_OUTPUT);
    xTaskCreatePinnedToCore(servoWrite, "ServoTask", 1000, NULL, 2, NULL, 0);
}
void loop() {
    vTaskDelay(200 / portTICK_PERIOD_MS);
    gpio_set_level((gpio_num_t)12, HIGH);
    vTaskDelay(200 / portTICK_PERIOD_MS);
    gpio_set_level((gpio_num_t)12, LOW);
}