// RECEIVER (SERVOS)

/* 
FOR THE NRF MODULE
VCC  ->  VCC
GND  ->  GND
CSN  ->  8
CE   ->  7
SCLK ->  15
MISO ->  14
MOSI ->  16
IRQ  ->  CURRENTLY NOT USED

FOR THE HORIZONTAL (X) SERVO MODULE
VCC  ->  VCC
GND  ->  GND
PWM  ->  A10

FOR THE VERTICAL (Y) SERVO MODULE
VCC  ->  VCC
GND  ->  GND
PWM  ->  A9
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo xServo;
Servo yServo;

RF24 radio(7, 8);
const byte xAddress[6] = "00001";
const byte yAddress[6] = "00002";

#define COMMAND_NO     0x00   // Used for identifying that we are not wanting to move any servo
#define COMMAND_LEFT   0x01   // Used for identifying that we are wanting to move horizontal servo to the left
#define COMMAND_RIGHT  0x02   // Used for identifying that we are wanting to move horizontal servo to the right
#define COMMAND_UP     0x04   // Used for identifying that we are wanting to move vertical servo upward
#define COMMAND_DOWN   0x08   // Used for identifying that we are wanting to move vertical servo downward

#define LEFT_THRESHOLD  400   // Used to specify threshold of when joystick is considered being pushed to left
#define RIGHT_THRESHOLD 800   // Used to specify threshold of when joystick is considered being pushed to right
#define UP_THRESHOLD    400   // Used to specify threshold of when joystick is considered being pushed upward
#define DOWN_THRESHOLD  800   // Used to specify threshold of when joystick is considered being pushed downward

#define UPDATE_INTERVAL 100   // Used to delay by 100ms (0.1s) between servo updates to avoid for oversampling I guess 

constexpr int X_SERVO_PIN = 10;      // PWM pin of Arduino used for the signal to the horizontal direction servo
constexpr int Y_SERVO_PIN = 9;       // PWM pin of Arduino used for the signal to the vertical direction servo

int command = COMMAND_NO;           // Used to initialize the command as "I don't want to do anything" at start
unsigned long lastUpdateTime = 0;   // Used to initialize the time since we last updated the command and positions to 0ms

int xAngle = 90;  // Used to store the value of the x location (0° to 180°)
int yAngle = 90;  // Used to store the value of the y location (0° to 180°)
int xValue = 0 ;  // Used for storing the analog value read from the joystick's x-direction 
int yValue = 0 ;  // Used for storing the analog value read from the joystick's y-direction


void setup() {
  Serial.begin(9600);

  radio.begin();  
  radio.openReadingPipe(0, xAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  radio.openReadingPipe(0, yAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  xServo.attach(X_SERVO_PIN); 
  yServo.attach(Y_SERVO_PIN);
}


// Fancy clamp function made by Spencer to keep positions between 0° and 180°
// condition ? true : false
// If the angle is less than the minimum, then continue to only return the minimum to avoid going negative.
// Else, if the angle is greater than the maximum, then continue to only return the maximum to avoid 
//  going beyound 180°. Else, we are between the min and max so just return the angle.
int clamp(int min, int max, int angle) {
  return angle < min ? min : (angle > max ? max : angle);
}

// Continually checks and updates the joystick and servo locations
void loop() {
  if (radio.available()) {
    int xValue;
    int yValue;
    radio.read(&xValue, sizeof(xValue));
    radio.read(&yValue, sizeof(yValue));

    // If it has been longer than the predefined update interval, then begin updating
    if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
      lastUpdateTime = millis();    // update the value of the last time that we updated to just now or 0ms

      // Convert the analog value to commands
      // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS.
      //        THIS ALLOWS FOR HORIZONTAL AND VERTICAL MOVEMENT AT THE SAME TIME.

      // reset commands
      command = COMMAND_NO;

      // check left/right commands
      if (xValue < LEFT_THRESHOLD)
        command = command | COMMAND_LEFT;
      else if (xValue > RIGHT_THRESHOLD)
        command = command | COMMAND_RIGHT;

      // check up/down commands
      if (yValue < UP_THRESHOLD)
        command = command | COMMAND_UP;
      else if (yValue > DOWN_THRESHOLD)
        command = command | COMMAND_DOWN;

      // print command to serial and process command
      if (command & COMMAND_LEFT) {
        Serial.println("COMMAND LEFT");
        xAngle-=20;     // Move horizontal servo 20° to the left
      }

      if (command & COMMAND_RIGHT) {
        Serial.println("COMMAND RIGHT");
        xAngle+=20;     // Move horizontal servo 20° to the right
      }

      if (command & COMMAND_UP) {
        Serial.println("COMMAND UP");
        yAngle-=20;     // Move vertical servo 20° downward
      }

      if (command & COMMAND_DOWN) {
        Serial.println("COMMAND DOWN");
        yAngle+=20;     // Move vertical servo 20° upward
      }

      // Check that 0° ≤ angle ≤ 180° before sending it to the servo
      xAngle = clamp(0, 180, xAngle); 
      yAngle = clamp(0, 180, yAngle);
    }


    xServo.write(xAngle); // rotate horizontal servo motor
    yServo.write(yAngle); // rotate vertical servo motor

    // print data to Serial Monitor on Arduino IDE
    Serial.print("Servo Motor's Angle: ");
    Serial.print(xAngle);
    Serial.print("°, ");
    Serial.print(yAngle);
    Serial.println("°");
  }
}
