// TRANSMITTER (JOYSTICK)

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

FOR THE JOYSTICK MODULE
VCC  ->  VCC
GND  ->  GND
VRX  ->  A1
VRY  ->  A0
SW   ->  CURRENTLY NOT USED
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);
const byte xAddress[6] = "00001";
const byte yAddress[6] = "00010";

int x_key = A1;                                               
int y_key = A0;                                               
int x_pos;
int y_pos;

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(xAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  radio.openWritingPipe(yAddress);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(x_key, INPUT);                     
  pinMode(y_key, INPUT);    
}

void loop() {
  x_pos = analogRead(x_key);  
  y_pos = analogRead(y_key);   
  radio.write(&x_pos, sizeof(x_pos));
  radio.write(&y_pos, sizeof(y_pos));
  delay(100);
  Serial.println(x_pos);
  Serial.println(y_pos);
}
