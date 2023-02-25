// Arduino joystick DC motor speed and rotation direction control using L293D
// https://simple-circuit.com/arduino-joystick-motor-control/

#define VX           A0   // VX pin of the joystick
#define VY           A1   // VY pin of the joystick
#define PWMA         9    // PWM signal for motor A
#define PWMB         10   // PWM signal for motor B


int motor_LR;
int motor_FB;

void setup() {
  pinMode(pwm1,   OUTPUT);
  pinMode(pwm2,   OUTPUT);
  pinMode(pwm3,   OUTPUT);
  pinMode(pwm4,   OUTPUT);
}

void loop() {
  motor_LR = analogRead(LR);
  motor_FB = analogRead(FB);
  motor_LR >>= 1;
  motor_FB >>= 1;
  if(motor_LR > 255){
    digitalWrite(pwm2, 0);
    analogWrite(pwm1, (motor_LR - 256));
  }
  else
    if(motor_LR < 255){
      digitalWrite(pwm1, 0);
      analogWrite(pwm2, (255 - motor_LR));
    }
    else{
      digitalWrite(pwm1, 0);
      digitalWrite(pwm2, 0);
    }

  if(motor_FB > 255){
    digitalWrite(pwm4, 0);
    analogWrite(pwm3, (motor_FB - 256));
  }
  else
    if(motor_FB < 255){
      digitalWrite(pwm3, 0);
      analogWrite(pwm4, (255 - motor_FB));
    }
    else{
      digitalWrite(pwm3, 0);
      digitalWrite(pwm4, 0);
    }
}
