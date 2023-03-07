/***************************************************************************************************
                            ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   01-TaskSwitching
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the free rtos example to demonstarte the task switching.

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider 
buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <Servo.h>

#define VRX_PIN A0
#define VRY_PIN A1
#define SW_PIN 8

#define TANK 0

//Global Variables:
Servo servo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
typedef struct JoystickValue {
  float VRx = 0;
  float VRy = 0;
  bool SW = false;
} JoystickValue;

QueueHandle_t queue;

void setup()
{ 
  Serial.begin(9600);
  Serial.println(F("In Setup function"));
  servo.attach(9);  // attaches the servo on pin 9 to the servo object

  /* Create two tasks with priorities 1 and 2. An idle task is also created, 
     which will be run when there are no tasks in RUN state */

  queue = xQueueCreate(32, sizeof(JoystickValue));

#if TANK
  // Tank Tasks
  xTaskCreate(servoWrite, "ServoTask", 100, NULL, 2, NULL);
  //TaskCreate(dcMotorWrite)
  //TaskCreate(photodiodeRead)
  xTaskCreate(wirelessReadWriteTank, "WirelessTask", 100, NULL, 1, NULL);
#else
  // Controller tasks
  xTaskCreate(joystickRead, "JoystickTask", 100, NULL, 2, NULL);
  //TaskCreate(ledWrite)
  xTaskCreate(wirelessReadWriteController, "WirelessTask", 100, NULL, 1, NULL);
#endif
  
  xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);
}


void loop()
{
  // DO nothing
}

#if TANK
/* servoWrite with priority 1 Servo Task*/
static void servoWrite(void* pvParameters)
{
  while(1)
  {
    //Serial.println(F("servoWrite"));
    vTaskDelay(100/portTICK_PERIOD_MS);

    JoystickValue jv;
    xQueueReceive(queue, &jv, 4);
    float servo_angle = (jv.VRx / 1024) * 180;
    Serial.println(jv.VRx);
    servo.write(servo_angle);
  }
}

static void wirelessReadWriteTank(void* pvParameters)
{
  while(1)
  {
    vTaskDelay(100/portTICK_PERIOD_MS);

    // TODO Read value from the airwaves
    // TODO Write value to queue for servo to read
  }
}
#else
/* Task2 with priority 2 */
static void joystickRead(void* pvParameters)
{
  while(1)
  {    
    //Serial.println(F("joystickRead"));
    vTaskDelay(150/portTICK_PERIOD_MS);

    JoystickValue jv;
    jv.VRx = analogRead(VRX_PIN);
    jv.VRy = analogRead(VRY_PIN);

    xQueueSend(queue, &jv, 4);
  }
}

static void wirelessReadWriteController(void* pvParameters)
{
  while(1)
  {
    vTaskDelay(100/portTICK_PERIOD_MS);

    // TODO read value from joystick queue
    // TODO write value into the airwaves
  }
}
#endif

/* Idle Task with priority Zero */ 
static void MyIdleTask(void* pvParameters)
{
  while(1)
  {
    //Serial.println(F("Idle state"));
    delay(50);
  }
}
