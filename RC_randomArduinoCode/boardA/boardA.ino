/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>


// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x02, 0xE1, 0x58}; // Board B

#define VRX   34
#define VRY   35

// Define variable to store value to be sent
int joyX = 0;
int joyY = 0;

// Define variable to store value to be received
int LR_suc;
int FB_suc;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int LRval;
    int FBval;
} struct_message;

// Create a struct_message called BME280Readings to hold sensor readings
struct_message BoardOut;

// Create a struct_message to hold incoming sensor readings
struct_message BoardIn;

esp_now_peer_info_t peerInfo;

// Callck when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

// Callck when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&BoardIn, incomingData, sizeof(BoardIn));
  Serial.print("Bytes received: ");
  Serial.println(len);
  LR_suc = BoardIn.LRval;
  FB_suc =  BoardIn.FBval;
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callck function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  // Set values to send
  joyX = analogRead(VRX);   // Determine x-position of joystick
  joyY = analogRead(VRY);   // Determine y-position of joystick
  Serial.print("joyX: ");
  Serial.println(joyX);
  Serial.print("joyY: ");
  Serial.println(joyY);
  BoardOut.LRval = joyX;
  BoardOut.FBval = joyY;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &BoardOut, sizeof(BoardOut));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Value Board B Sent: ");
  Serial.println(BoardIn.LRval);
  Serial.println(BoardIn.FBval);
  
  // delay(100);
}
