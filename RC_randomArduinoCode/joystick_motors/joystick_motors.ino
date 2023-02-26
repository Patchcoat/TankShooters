// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch

// MAKE SURE THAT BLACK SHARPIED PIN OF MOTOR1/DRIVER-SIDE MOTOR IS
//  CONNECTED TO A02
// MAKE SURE THAT BLACK SHARPIED PIN OF MOTOR2/PASSENGER-SIDE MOTOR IS
//  CONNECTED TO B01

#define AIN1  2 
#define BIN1  7
#define AIN2  4
#define BIN2  8
#define PWMA  5
#define PWMB  6
#define STBY  9
#define VRX   A0   // VRX pin of the joystick
#define VRY   A1   // VRY pin of the joystick

// these constants are used to allow you to make your motor configuration 
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors according to SparkFun_TB6612 library.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

// Used for storing the value of the analog joystick readings.
int joyX = 0;
int joyY = 0;

void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() {
  joyX = analogRead(VRX);   // Determine x-position of joystick
  joyY = analogRead(VRY);   // Determine y-position of joystick

  /*Assuming header pins are facing to the left.
    If the joystick is all the way up, y=0.
    If the joystick is all the way down, y=1023;
    If the joystick is all the way left, x=0;
    If the joystick is all the way right, x=1023.
    Resing position is about (517,513) for the joystick I was using
      so I set the threshold as 450. There is no need for a specific 
      range since the joystick behaves differently on the diagonals.
  */
  
  // The back, forward, left, right, brake functions are from the SparkFun_TB6612 library.
  
  if( (joyX>450) && (joyY>1000) ){
    back(motor1, motor2, 150);
  }
  else if( (joyX>450) && (joyY<20) ){
    forward(motor1, motor2, 150);
  }
  else if( (joyX<10) && (joyY>450) ){
    left(motor1, motor2, 150);
  }
  else if( (joyX>1000) && (joyY>450) ){
    right(motor1, motor2, 150);
  }
  else{
    brake(motor1, motor2);
  }
}
