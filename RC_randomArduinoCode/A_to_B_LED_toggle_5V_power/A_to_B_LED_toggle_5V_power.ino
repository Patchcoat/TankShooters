/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
*/

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x02, 0xE1, 0x58}; // Board B

#define RED_LED    34
#define BLUE_LED   35

// Define variable to store value to be sent
int red_send;
int blue_send;

// Define variable to store value to be received
int red_rec;
int blue_rec;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int redVal;
    int blueVal;
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
  red_rec = BoardIn.redVal;
  blue_rec = BoardIn.blueVal;
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

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
  if (red_rec == 1){
    BoardOut.redVal = 1;
    digitalWrite(RED_LED, HIGH);
  }
  else{
    BoardOut.redVal = 0;
    digitalWrite(RED_LED, LOW);
  }
  if (blue_rec == 1){
    BoardOut.blueVal = 1;
    digitalWrite(BLUE_LED, HIGH);
  }
  else{
    BoardOut.blueVal = 0;
    digitalWrite(BLUE_LED, LOW);
  }
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
  Serial.println(BoardIn.redVal);
  Serial.println(BoardIn.blueVal);
  
  delay(1000);
}
