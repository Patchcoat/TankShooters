/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick-servo-motor
 */

#include <Servo.h>


#define VRX_PIN      A0 // Micro pin connected to VRX pin of joystcik
#define VRY_PIN      A1 // Micro pin connected to VRY pin of joystick
#define SW_PIN       A2 // Micro pin connected to SW  pin of joystick
#define SERVO_X_PIN  5  // Micro pin connected to horizontal Servo motor (xServo)
#define SERVO_Y_PIN  6  // Micro pin connected to vertical Servo motor (yServo)

#define COMMAND_NO     0x00   // Used for identifying that we are not wanting to move any servo
#define COMMAND_LEFT   0x01   // Used for identifying that we are wanting to move horizontal servo to the left
#define COMMAND_RIGHT  0x02   // Used for identifying that we are wanting to move horizontal servo to the right
#define COMMAND_UP     0x04   // Used for identifying that we are wanting to move vertical servo upward
#define COMMAND_DOWN   0x08   // Used for identifying that we are wanting to move vertical servo downward

#define LEFT_THRESHOLD  400   // Used to specify at what point joystick is considered being pushed to left
#define RIGHT_THRESHOLD 800   // Used to specify at what point joystick is considered being pushed to right
#define UP_THRESHOLD    400   // Used to specify at what point joystick is considered being pushed upward
#define DOWN_THRESHOLD  800   // Used to specify at what point joystick is considered being pushed downward

#define UPDATE_INTERVAL 100   // Used to delay by 100ms (0.1s) between servo updates to avoid for oversampling I guess 

Servo xServo;     // Creates a servo object to control the horizontal servo
Servo yServo;     // create servo object to control the vertical servo

int xValue = 0 ;  // Used to store the value of the x location (0° to 180°)
int yValue = 0 ;  // Used to store the value of the y location (0° to 180°)
int xAngle = 90;  // the center position of the horizontal servo
int yAngle = 90;  // the center position of the vertical servo
int command = COMMAND_NO;   // Used to initialize the command as "I don't want to do anything" at start

unsigned long lastUpdateTime = 0;   // Used to initialize the time since we last updated the command and positions to 0ms
                                      

// Sets up the serial communnication rate and servos
void setup() {
  Serial.begin(9600);           // Used to view command and positions/angles in Serial Monitor

  xServo.attach(SERVO_X_PIN);   // Attachs pin 2 of Arduino to the horizontal servo
  yServo.attach(SERVO_Y_PIN);   // Attachs pin 3 of Arduino to the vertical servo
  xServo.write(90);             // Sets the initial position of the horizontal servo to 90°
  yServo.write(90);             // Sets the initial position of the vertical servo to 90°

}

// Fancy clamp function made by Spencer to keep positions between 0° and 180°
int clamp(int min, int max, int angle) {
  // condition ? true : false
  // If the angle is less than the minimum, then continue to only return the minimum to avoid going negative.
  // Else, if the angle is greater than the maximum, then continue to only return the maximum to avoid 
  //  going beyound 180°. Else, we are between the min and max so just return the angle.
  return angle < min ? min : (angle > max ? max : angle);
}

// Continually updates and checks the joystick and servo locations
void loop() {
  // If it has been longer than the predefined update interval, then begin updating
  if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
    lastUpdateTime = millis();    // update the value of the last time that we updated to just now or 0ms

    // read analog X and Y values from joystick pins
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);

    // converts the analog value to commands
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
      xAngle-=15;     // Move horizontal servo 20° to the left
    }

    if (command & COMMAND_RIGHT) {
      Serial.println("COMMAND RIGHT");
      xAngle+=15;     // Move horizontal servo 20° to the right
    }

    if (command & COMMAND_UP) {
      Serial.println("COMMAND UP");
      yAngle-=15;     // Move vertical servo 20° downward
    }

    if (command & COMMAND_DOWN) {
      Serial.println("COMMAND DOWN");
      yAngle+=15;     // Move vertical servo 20° upward
    }

    // Check that 0° ≤ angle ≤ 180° before sending it to the servo
    xAngle = clamp(0, 180, xAngle); 
    yAngle = clamp(0, 220, yAngle);
  }


  xServo.write(xAngle); // rotate horizontal servo motor
  yServo.write(yAngle); // rotate vertical servo motor

  // print data to Serial Monitor on Arduino IDE
  Serial.print("Servo Motor's Angle: ");
  Serial.print(xAngle);
  Serial.println(yAngle);
}
