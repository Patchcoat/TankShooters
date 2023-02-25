#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(9, 10,4000000); 

void setup()
{
  Serial.begin(9600);
radio.begin(); 
radio.openReadingPipe(0,00001); 
radio.startListening();
}
void loop()
{
if (radio.available())
{
char data[32] = {0};
radio.read(&data, sizeof(data));
Serial.println(&data);
}
}
