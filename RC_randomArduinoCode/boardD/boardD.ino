#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>
#include <Servo.h>


// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x76, 0xE0, 0x98}; // Board C

#define AIN1        17
#define BIN1        18
#define AIN2        16
#define BIN2        19
#define PWMA        4
#define PWMB        21
#define STBY        5

#define S_VRX       14
#define S_VRY       27
// #define 
// #define RESTART     00
// #define PHOTODIO    00

#define MOTOR_L_THRESH     150
#define MOTOR_R_THRESH     4000
#define MOTOR_F_THRESH     150
#define MOTOR_B_THRESH     4000
#define SERVO_L_THRESH     1000
#define SERVO_R_THRESH     3000
#define SERVO_U_THRESH     1000
#define SERVO_D_THRESH     3000

#define COMMAND_NO        0x00    // Do not want to move servo or tank
#define COMMAND_LEFT      0x01    // Want to move horizontal servo to the left
#define COMMAND_RIGHT     0x02    // Want to move horizontal servo to the right
#define COMMAND_UP        0x04    // Want to move vertical servo upward
#define COMMAND_DOWN      0x08    // Want to move vertical servo downward
#define COMMAND_FORWARD   0x04    // Want to move tank forward
#define COMMAND_BACKWARD  0x08    // Want to move tank backward

int xAngle = 90;  // the center position of the horizontal servo
int yAngle = 90;  // the center position of the vertical servo

int servoCommand = COMMAND_NO;   // Used to initialize the command as "I don't want to do anything" at start
int motorCommand = COMMAND_NO;   // Used to initialize the command as "I don't want to do anything" at start

const int offsetA = 1;
const int offsetB = 1;

// Create the motors
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

Servo xServo;
Servo yServo;     

// Define variable to store value to be sent
int MLR_send;
int MFB_send;
int SLR_send;
int SUD_send;

// Define variable to store value to be received
int MLR_rec;
int MFB_rec;
int SLR_rec;
int SUD_rec;

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
  int MLRval;
  int MFBval;
  int SLRval;
  int SUDval;
} struct_message;

// Create a struct_message called ToController to hold values to be sent from the tank to the controller
struct_message ToController;

// Create a struct_message called FromController to hold values sent from the controller to the tank
struct_message FromController;

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
  memcpy(&FromController, incomingData, sizeof(FromController));
  Serial.print("Bytes received: ");
  Serial.println(len);
  MLR_rec = FromController.MLRval;
  MFB_rec =  FromController.MFBval;
  SLR_rec = FromController.SLRval;
  SUD_rec = FromController.SUDval;
}

int clamp(int min, int max, int angle) {
  // condition ? true : false
  // If the angle is less than the minimum, then continue to only return the minimum to avoid going negative.
  // Else, if the angle is greater than the maximum, then continue to only return the maximum to avoid 
  //  going beyound 180°. Else, we are between the min and max so just return the angle.
  return angle < min ? min : (angle > max ? max : angle);
}

void servoControl(){
  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS.
  //        THIS ALLOWS FOR HORIZONTAL AND VERTICAL MOVEMENT AT THE SAME TIME.

  // reset commands
  servoCommand = COMMAND_NO;

  // check left/right commands
  if (SLR_rec < SERVO_L_THRESH)
    servoCommand = servoCommand | COMMAND_LEFT;
  else if (SLR_rec > SERVO_R_THRESH)
    servoCommand = servoCommand | COMMAND_RIGHT;

  // check up/down commands
  if (SUD_rec < SERVO_U_THRESH)
    servoCommand = servoCommand | COMMAND_UP;
  else if (SUD_rec > SERVO_D_THRESH)
    servoCommand = servoCommand | COMMAND_DOWN;

  // print command to serial and process command
  if (servoCommand & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    xAngle-=15;     // Move horizontal servo 20° to the left
  }

  if (servoCommand & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    xAngle+=15;     // Move horizontal servo 20° to the right
  }

  if (servoCommand & COMMAND_UP) {
    Serial.println("COMMAND UP");
    yAngle-=15;     // Move vertical servo 20° downward
  }

  if (servoCommand & COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    yAngle+=15;     // Move vertical servo 20° upward
  }

  // Check that 0° ≤ angle ≤ 180° before sending it to the servo
  xAngle = clamp(0, 180, xAngle); 
  yAngle = clamp(0, 180, yAngle);

  xServo.write(xAngle); // rotate horizontal servo motor
  yServo.write(yAngle); // rotate vertical servo motor
}

void motorControl(){
  // reset commands
  motorCommand = COMMAND_NO;

  // check left/right commands
  if (MLR_rec < MOTOR_L_THRESH)
    motorCommand = motorCommand | COMMAND_LEFT;
  else if (MLR_rec > MOTOR_R_THRESH)
    motorCommand = motorCommand | COMMAND_RIGHT;

  // check up/down commands
  if (MFB_rec < MOTOR_F_THRESH)
    motorCommand = motorCommand | COMMAND_FORWARD;
  else if (MFB_rec > MOTOR_B_THRESH)
    motorCommand = motorCommand | COMMAND_BACKWARD;



  // print command to serial and process command
  if (motorCommand & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    right(motor1, motor2, 150); 
  }
  else if (motorCommand & COMMAND_LEFT) {
    Serial.println("COMMAND UP");
    left(motor1, motor2, 150);
  }
  else if (motorCommand & COMMAND_BACKWARD) {
    Serial.println("COMMAND BACKWARD");
    back(motor1, motor1, 150);
  }
  else if (motorCommand && COMMAND_FORWARD) {
    Serial.println("COMMAND FORWARD");
    forward(motor1, motor2, 150);
  }
  else{
    brake(motor1, motor2);
  }

  // if( (TLR_rec > 1500 && TLR_rec < 2300) && (TFB_rec > 4000) ){
  //   back(motor1, motor2, 150);
  // }
  // else if( (TLR_rec > 1500) && (TFB_rec < 100) ){
  //   forward(motor1, motor2, 150);
  // }
  // else if( (TLR_rec < 100) && (TFB_rec > 1500) ){
  //   left(motor1, motor2, 150);
  // }
  // else if( (TLR_rec > 4000) && (TFB_rec > 1500) ){
  //   right(motor1, motor2, 150);
  // }
  // else{
  //   brake(motor1, motor2);
  // }
}

void sendData(){
  // Set values to send
  MLR_send = 1;
  MFB_send = 1;
  SLR_send = 1;
  SUD_send = 1;

  ToController.MLRval = MLR_send;
  ToController.MFBval = MFB_send;
  ToController.SLRval = SLR_send;
  ToController.SUDval = SUD_send;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &ToController, sizeof(ToController));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

void displayRecData(){
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Values Controller Sent: ");
  Serial.print(MLR_rec);
  Serial.println(MFB_rec);
  Serial.print(SLR_rec);
  Serial.println(SUD_rec);
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Init servos
  xServo.attach(S_VRX);   // Attachs pin 2 of Arduino to the horizontal servo
  yServo.attach(S_VRY);   // Attachs pin 3 of Arduino to the vertical servo
  xServo.write(90);             // Sets the initial position of the horizontal servo to 90°
  yServo.write(90);             // Sets the initial position of the vertical servo to 90°


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
  Serial.println("LOOOOOOOOOP");
  sendData();
  displayRecData();
  servoControl();
  motorControl();
}