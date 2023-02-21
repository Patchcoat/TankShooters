#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define SwitchPin 8 // Arcade switch is connected to Pin 8 on NANO
int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(void){
  Serial.begin(9600);
  pinMode(SwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
  digitalWrite(SwitchPin,HIGH); // Set Pin to HIGH at beginning
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void){
//  Serial.println(digitalRead(SwitchPin));
  if (digitalRead(SwitchPin) == LOW){ // If Switch is Activated
    SentMessage[0] = 111;
    radio.write(SentMessage, 1); // Send value through NRF24L01
  }
  else {
    SentMessage[0] = 000;
    radio.write(SentMessage, 1);
  }
  Serial.println(SentMessage[0]);

}
