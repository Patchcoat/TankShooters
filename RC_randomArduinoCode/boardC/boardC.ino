#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>


// REPLACE WITH THE MAC Address of your receiver 
// uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0xE8, 0xCE, 0xA0}; // Board D
uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x76, 0xE4, 0x30}; // Board B


#define TANK_VRX   25
#define TANK_VRY   26
#define SERVO_VRX  32
#define SERVO_VRY  33

// Define variable to store value to be sent
int TLR_send;
int TFB_send;
int SLR_send;
int SUD_send;

// Define variable to store value to be received
int TLR_rec;
int TFB_rec;
int SLR_rec;
int SUD_rec;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  int TLRval;
  int TFBval;
  int SLRval;
  int SUDval;
} struct_message;

// Create a struct_message called ToTank for sending values to the tank
struct_message ToTank;

// Create a struct_message called FromTank to hold incoming tank values (diodes)
struct_message FromTank;

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
  memcpy(&FromTank, incomingData, sizeof(FromTank));
  Serial.print("Bytes received: ");
  Serial.println(len);
  TLR_rec = FromTank.TLRval;
  TFB_rec =  FromTank.TFBval;
  SLR_rec = FromTank.SLRval;
  SUD_rec = FromTank.SUDval;
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
  TLR_send = analogRead(TANK_VRX);   // Determine x-position of tank joystick
  TFB_send = analogRead(TANK_VRY);   // Determine y-position of tank joystick
  SLR_send = analogRead(SERVO_VRX);   // Determine x-position of servo joystick
  SUD_send = analogRead(SERVO_VRY);   // Determine y-position of servo joystick

  ToTank.TLRval = TLR_send;
  ToTank.TFBval = TFB_send;
  ToTank.SLRval = SLR_send;
  ToTank.SUDval = SUD_send;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &ToTank, sizeof(ToTank));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Values Tank Sent: ");
  Serial.print(TLR_rec);
  Serial.println(TFB_rec);
  Serial.print(SLR_rec);
  Serial.println(SUD_rec);
  
}
