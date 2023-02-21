// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;
int i = 0;

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
    getData();
    showData();
}

//==============

void getData() {
    delay(1000);
    Serial.println("Trying to get new data");

    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
    }
    else{
      Serial.println("Failed to get new data :(");
      Serial.println(i++);
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived);
        newData = false;
    }
}
