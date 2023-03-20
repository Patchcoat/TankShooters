/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
*/

#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x76, 0xE4, 0x30}; // Board A

#define AIN1    12
#define BIN1    14
#define AIN2    27
#define BIN2    26
#define PWMA    32
#define PWMB    33
#define STBY    25

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


// Define variable to store value to be sent
int LR_send;
int FB_send;

// Define variable to store value to be received
int LR_rec;
int FB_rec;

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
  LR_rec = BoardIn.LRval;
  FB_rec = BoardIn.FBval;
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
  LR_send = 1;
  FB_send = 1;
  BoardOut.LRval = LR_send;
  BoardOut.FBval = FB_send;
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
  Serial.print("Value Board A Sent: ");
  Serial.println(BoardIn.LRval);
  Serial.println(BoardIn.FBval);

  // // The back, forward, left, right, brake functions are from the SparkFun_TB6612 library.
  
  if( (LR_rec>1500 && LR_rec<2300) && (FB_rec>4000) ){
    back(motor1, motor2, 150);
  }
  else if( (LR_rec>1500) && (FB_rec<100) ){
    forward(motor1, motor2, 150);
  }
  else if( (LR_rec<100) && (FB_rec>1500) ){
    left(motor1, motor2, 150);
  }
  else if( (LR_rec>4000) && (FB_rec>1500) ){
    right(motor1, motor2, 150);
  }
  else{
    brake(motor1, motor2);
  }
  
  // delay(1000);
}
