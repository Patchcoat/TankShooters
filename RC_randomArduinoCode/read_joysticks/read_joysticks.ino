
/* This code is used for reading the positions of the joysticks and the
 *  push-button aspect of the aiming joystick. This code is to be called
 *  in a central controller transmitter code. Note, that the pin definitions 
 *  can easily changed within the transmitter code so that can have all of 
 *  our defines in one place. It should be placed in the loop() method
 *  of the central controller transmitter code.
 */

//#define VRX_M   A0
//#define VRY_M   A1
//#define VRX_S   A2
//#define VRY_S   A3
//#define SW_L    A4

int xMotor;
int yMotor;
int xServo;
int yServo;
int swLaser;

int readXMotor(int pin);
int readYMotor(int pin);
int readXServo(int pin);
int readYServo(int pin);
int readSWLaser(int pin);

//void setup() {
//  // put your setup code here, to run once:
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  readXMotor(VRX_M);
//  readYMotor(VRY_M);
//  readXServo(VRX_S);
//  readYServo(VRY_S);
//  readSWLaser(SW_L);
//}

int readXMotor(int pin){
  xMotor = analogRead(pin);
  return xMotor;
}

int readYMotor(int pin){
  yMotor = analogRead(pin);
  return yMotor;
}

int readXServo(int pin){
  xServo = analogRead(pin);
  return xServo;
}

int readYServo(int pin){
  yServo = analogRead(pin);
  return yServo;
}

int readSWLaser(int pin){
  swLaser = analogRead(pin);
  return swLaser;
}
