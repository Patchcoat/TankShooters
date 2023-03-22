/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick-servo-motor
 */

#include <Servo.h>
#include <ezButton.h>


#define VRX_PIN      25  // ESP32 pin connected to VRX pin of joystcik
#define VRY_PIN      26  // ESP32 pin connected to VRY pin of joystick
#define SW_PIN       27 // ESP32 pin connected to SW  pin of joystick
#define SERVO_X_PIN  32  // ESP32 pin connected to horizontal Servo motor (xServo)
#define SERVO_Y_PIN  33  // ESP32 pin connected to vertical Servo motor (yServo)
#define LASER_PIN    14

#define LEFT_THRESHOLD  1000   // Used to specify at what point joystick is considered being pushed to left
#define RIGHT_THRESHOLD 3500   // Used to specify at what point joystick is considered being pushed to right
#define UP_THRESHOLD    1000   // Used to specify at what point joystick is considered being pushed upward
#define DOWN_THRESHOLD  3500   // Used to specify at what point joystick is considered being pushed downward

#define UPDATE_INTERVAL 500  // Used to delay by 100ms (0.1s) between servo updates to avoid for oversampling I guess 

Servo xServo;     // Creates a servo object to control the horizontal servo
Servo yServo;     // create servo object to control the vertical servo
ezButton button(SW_PIN);

int xValue = 0 ;  // Used to store the value of the x location (0° to 180°)
int yValue = 0 ;  // Used to store the value of the y location (0° to 180°)
int xAngle = 90;  // the center position of the horizontal servo
int yAngle = 90;  // the center position of the vertical servo
bool switchValue = false;

unsigned long lastUpdateTime = 0;   // Used to initialize the time since we last updated the command and positions to 0ms
                                      

// Sets up the serial communnication rate and servos
void setup() {
  Serial.begin(9600);           // Used to view command and positions/angles in Serial Monitor

  xServo.attach(SERVO_X_PIN);   // Attachs pin 2 of Arduino to the horizontal servo
  yServo.attach(SERVO_Y_PIN);   // Attachs pin 3 of Arduino to the vertical servo
  xServo.write(90);             // Sets the initial position of the horizontal servo to 90°
  yServo.write(80);             // Sets the initial position of the vertical servo to 90°

  pinMode(LASER_PIN, OUTPUT);

  //button.setDebounceTime(50);
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
  button.loop();
  // If it has been longer than the predefined update interval, then begin updating
  //   lastUpdateTime = millis();    // update the value of the last time that we updated to just now or 0ms

  // read analog X and Y values from joystick pins
  xValue = analogRead(VRX_PIN);   // Reversed becasue of joystick orientation
  yValue = analogRead(VRY_PIN);   // Reversed because of joystick orientation
  Serial.printf("VRX = %d\nVRY= %d\n\n", xValue, yValue);

  // converts the analog value to commands
  // NOTE: AT A TIME, THERE MAY BE NO COMMAND, ONE COMMAND OR TWO COMMANDS.
  //        THIS ALLOWS FOR HORIZONTAL AND VERTICAL MOVEMENT AT THE SAME TIME.

  // check left/right commands
  if (xValue < LEFT_THRESHOLD) {
    Serial.println("COMMAND LEFT");
    xAngle+=5;     // Move horizontal servo 20° to the left
  } else if (xValue > RIGHT_THRESHOLD) {
    Serial.println("COMMAND RIGHT");
    xAngle-=5;     // Move horizontal servo 20° to the right
  }
  // check up/down commands
  if (yValue < UP_THRESHOLD) {
    Serial.println("COMMAND UP");
    yAngle+=5;     // Move vertical servo 20° downward
  } else if (yValue > DOWN_THRESHOLD) {
    Serial.println("COMMAND DOWN");
    yAngle-=5;     // Move vertical servo 20° upward
  }
  // Check that 0° ≤ angle ≤ 180° before sending it to the servo
  xAngle = clamp(0, 180, xAngle); 
  yAngle = clamp(50, 80, yAngle);

  xServo.write(xAngle); // rotate horizontal servo motor
  yServo.write(yAngle); // rotate vertical servo motor

  // print data to Serial Monitor on Arduino IDE
  Serial.print("Servo Motor's Angle: ");
  Serial.printf("X angle =  %d     Y angle = %d\n", xAngle, yAngle);

  switchValue = button.getState();
  Serial.printf("Switch Value = %s\n", switchValue ? "True" : "False");
  if(!switchValue){
    digitalWrite(LASER_PIN, HIGH);
  }
  else{
    digitalWrite(LASER_PIN, LOW);
  }
}
