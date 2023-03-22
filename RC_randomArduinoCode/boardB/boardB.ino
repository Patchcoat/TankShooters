#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>

// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x8C, 0xAA, 0xB5, 0xB5, 0x98, 0x94}; // Board A

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

// Create a struct_message called FromTank to send values from the tank (diodes)
struct_message FromTank;

// Create a struct_message called ToTank to hold incoming controller readings
struct_message ToTank;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
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

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&ToTank, incomingData, sizeof(ToTank));
  Serial.print("Bytes received: ");
  Serial.println(len);
  LR_rec = ToTank.LRval;
  FB_rec = ToTank.FBval;
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
  FromTank.LRval = 1;
  FromTank.FBval = 1;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &FromTank, sizeof(FromTank));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Values Controller Sent: ");
  Serial.println(LR_rec);
  Serial.println(FB_rec);

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
  
  // delay(100);
}
