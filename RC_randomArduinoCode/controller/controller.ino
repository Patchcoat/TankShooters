#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
// #include <pitches.h>
//#include <ezBuzzer.h>


// Replace with the MAC Address of your receiver 

uint8_t tankAddress[] = {0xC8, 0xF0, 0x9E, 0x50, 0x3B, 0x94};     // Board B (player's tank)
uint8_t opponentAddress[] = {0x40, 0x22, 0xD8, 0x76, 0xE0, 0x98}; // Board C (opponent's controller)

// uint8_t tankAddress[] = {0x8C, 0xAA, 0xB5, 0xB5, 0x98, 0x94};      // Board D (player's tank)
// uint8_t opponentAddress[] = {0xC8, 0xF0, 0x9E, 0x4F, 0xE6, 0xDC};  // Board A (opponent's controller)

#define MOTOR_VRX_PIN   35
#define MOTOR_VRY_PIN   34
#define SERVO_VRX_PIN   32
#define SERVO_VRY_PIN   33
#define LASER_SW_PIN    5
#define LED1_PIN     13
#define LED2_PIN     12
#define LED3_PIN     14

// ezBuzzer buzzer(BUZZER_PIN);

// notes in the melody:
// int lostMelody[] = {
//   NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
// };
// int lostMelody[] = {
//   NOTE_E5, NOTE_E5, NOTE_E5,
//   NOTE_E5, NOTE_E5, NOTE_E5,
//   NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
//   NOTE_E5,
//   NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
//   NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
//   NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
//   NOTE_D5, NOTE_G5
// };

// int wonMelody[] = {
//   NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_B3, NOTE_C4
// };

// // note durations: 4 = quarter note, 8 = eighth note, etc.:
// int lostNoteDurations[] = {
//   4, 8, 8, 4, 4, 4, 4
// };
// int lostNoteDurations[] = {
//   8, 8, 4,
//   8, 8, 4,
//   8, 8, 8, 8,
//   2,
//   8, 8, 8, 8,
//   8, 8, 8, 16, 16,
//   8, 8, 8, 8,
//   4, 4
// };

// int wonNoteDurations[] = {
//   8, 4, 4, 8, 8, 8, 8
// };

// Define variable to store value to be sent and received
int MLR;
int MFB;
int SLR;
int SUD;
int hit;
int shoot_laser;
int player_reset;
int opponent_reset;
int player_dead;
int opponent_dead;

int melody_iterations = 0;

int hit_lock = 0;

bool wave = false;
unsigned long waveMillis = 0;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_values {
  unsigned short MLR_val;
  unsigned short MFB_val;
  unsigned short SLR_val;
  unsigned short SUD_val;
  unsigned short hit_val;
  unsigned short shoot_laser;
  unsigned short player_reset_val;
  unsigned short opponent_reset_val;
  unsigned short player_dead_val;
  unsigned short opponent_dead_val;
} struct_values;

// Create a struct_values called ToTank for sending values to the tank
//struct_values ToTank;

// // Create a struct_values called FromTank to hold incoming tank value
struct_values FromTank;

// Create a struct_health called PlayerHealth for sending your health value to opponent
struct_values ToOpponent;

// // Create a struct_health called OpponentHealth for receiving your opponent's health value
struct_values FromOpponent;

struct_values recData;

esp_now_peer_info_t peerInfo;

// Wireless Interrupts
esp_now_send_status_t data_sent_status;
bool data_sent = false;
bool data_recieved = false;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  data_sent_status = status;
  data_sent = true;
}

// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&recData, incomingData, sizeof(recData));
  data_recieved = true;
}

void wireless(void *pvParameters) {
  while (1) {  // recieve data
    vTaskDelay(100);
    unsigned long currentMillis = millis();

    if (wave) {
      unsigned long difference = currentMillis - waveMillis;
      digitalWrite(LED1_PIN, difference < 500 ? HIGH : LOW);
      digitalWrite(LED2_PIN, difference > 500 && difference  < 1000 ?  HIGH : LOW);
      digitalWrite(LED3_PIN, difference > 1000 ? HIGH : LOW);
      if (difference > 1500) {
        waveMillis = currentMillis;
      }
    }

    // send data
    if (data_sent) {
      //Serial.print("\r\nLast Packet Send Status:\t");
      //Serial.println(data_sent_status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
      if (data_sent_status ==0){
        success = "Delivery Success :)";
      }else{
        success = "Delivery Fail :(";
      }
      data_sent = false;
    }

    if (data_recieved) {
      int recieve_hit = recData.hit_val;
      printf("Hit: %d\n", recieve_hit);
      switch (recieve_hit) {
        case 0:
          wave = false;
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, HIGH);
          break;
        case 1:
          wave = false;
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, HIGH);
          digitalWrite(LED3_PIN, LOW);
          break;
        case 2:
          wave = false;
          digitalWrite(LED1_PIN, HIGH);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
          break;
        case 3:
          wave = false;
          digitalWrite(LED1_PIN, LOW);
          digitalWrite(LED2_PIN, LOW);
          digitalWrite(LED3_PIN, LOW);
          break;
        case 4:
          wave = true;
          break;
        default:
          break;
      }
      player_reset = recData.player_reset_val;
      opponent_reset = recData.opponent_reset_val;
      opponent_dead = recData.opponent_dead_val;
      data_recieved = false;
    }
    // Send data to tank
    struct_values ToTank;
    ToTank.MLR_val = MLR;
    ToTank.MFB_val = MFB;
    ToTank.SLR_val = SLR;
    ToTank.SUD_val = SUD;
    ToTank.shoot_laser = shoot_laser;
    ToTank.player_dead_val = player_dead;
    ToTank.opponent_dead_val = opponent_dead;
    ToTank.opponent_reset_val = opponent_reset;
 
    // Send message via ESP-NOW
    esp_now_send(tankAddress, (uint8_t *) &ToTank, sizeof(struct_values));
    //Serial.print("To Tank: ");
    //Serial.println(success);

    // Send data to opponent
    ToOpponent.opponent_dead_val = player_dead;
    ToOpponent.opponent_reset_val = player_reset;
    // Send Message via ESP-NOW
    esp_now_send(opponentAddress, (uint8_t *) &ToOpponent, sizeof(struct_values));
    //Serial.print("To Opponent: ");
    //Serial.println(success);
  }
}

void setup() {
  
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init the pins
  pinMode(MOTOR_VRX_PIN, INPUT);
  pinMode(MOTOR_VRY_PIN, INPUT);
  pinMode(SERVO_VRX_PIN, INPUT);
  pinMode(SERVO_VRX_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);


  // Register and add peers
  memcpy(peerInfo.peer_addr, tankAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add tank");
    return;
  }
  else{
    Serial.println("Was able to add tank");
  }
  memcpy(peerInfo.peer_addr, opponentAddress, 6); 
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add opponent");
    return;
  }
  else{
    Serial.println("Was able to add opponent");
  }

  // Register for a callck function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

  // Multithreading
  xTaskCreatePinnedToCore(wireless, "WirelessComm", 1000, NULL, 2, NULL, 0);
}
 
void loop() {
  //Serial.println("Controller");
  // buzzer.loop();
  if (player_reset){
    hit = 0;
    melody_iterations = 0;
  }

  //digitalWrite(LED1_PIN, (hit>=1)?LOW:HIGH);
  //digitalWrite(LED2_PIN, (hit>=7)?LOW:HIGH);
  //digitalWrite(LED3_PIN, (hit>=13)?LOW:HIGH);

  // Set values to send to the tank
  // ***JOYSTICK ORIENTATION IS BACKWARDS THAT'S WHY VRX AND VRY SWITCHED FOR BOTH***
  MLR = analogRead(MOTOR_VRY_PIN);   // Determine LR-position of motor joystick
  MFB = analogRead(MOTOR_VRX_PIN);   // Determine FB-position of motor joystick
  SLR = analogRead(SERVO_VRY_PIN);   // Determine LR-position of servo joystick
  SUD = analogRead(SERVO_VRX_PIN);   // Determine UD-position of servo joystick
  // Serial.printf("MLR: %d   MFB: %d   SLR: %d   SUD: %d \n", MLR, MFB, SLR, SUD);

  shoot_laser = !digitalRead(LASER_SW_PIN);

  // if (player_dead && !melody_iterations) {
  //   Serial.println("BUZZER SHOULD START PLAYING MUSIC");
  //   buzzer.playMelody(lostMelody, lostNoteDurations, sizeof(lostNoteDurations));
  //   Serial.println("BUZZER HAS FINISHED PLAYING MUSIC");
  //   melody_iterations = 1;
  // }
  // if (opponent_dead) {
  //   // buzzer.playMelody(wonMelody, wonNoteDurations, sizeof(wonNoteDurations));
  // }


  // Serial.printf("Hit: %d   P_rst: %d   O_rst: %d   P_dead: %d   O_dead: %d\n", hit, player_reset, opponent_reset, player_dead, opponent_dead);
}