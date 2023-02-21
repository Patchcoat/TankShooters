/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   
/*
 * This code is to determine when the laser forward biases the photodiode by turning on or off
 * the LED at a specific threshold.
 */


//Constants
constexpr int PHOTODIO = A0; // Photodiode connected Arduino analog pin A0
constexpr int LED = 9;       // LED pin connected to Arduino pin 9

//Variables
int value;				  // Store value from photoresistor (0-1023)

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);       // Set external LED pin (9) as an output
  pinMode(PHOTODIO, INPUT);   // Set photodiode pin (A0) as an input
}

void loop(){
  value = analogRead(PHOTODIO);
  Serial.println(value);
  //You can change the threshold voltage as needed
  if (value < 100){
    digitalWrite(LED, LOW);  //Turn LED off
  }
  else{
    digitalWrite(LED, HIGH); //Turn LED on
  }

  delay(10); //Small delay
}
