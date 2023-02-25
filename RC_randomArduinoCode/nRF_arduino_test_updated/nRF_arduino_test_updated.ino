#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(9, 10, 4000000);

void setup()
{
radio.begin(); 
radio.openWritingPipe(10101); 
radio.stopListening();
}
void loop()
{
const char data[] = "DATA";
radio.write(&data, sizeof(data));
delay(2000);
}
