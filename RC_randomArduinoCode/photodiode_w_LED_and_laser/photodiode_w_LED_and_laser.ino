/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   



//Constants
constexpr int PHOTODIO = A0; // Photoresistor connected Arduino analog pin A0
const int LED = A1;          // LED pin connected to Arduino pin 9
const int LASER = 2;         // Laser module connected to Arduino pin 2

//Variables
int value;				  // Store value from photoresistor (0-1023)

void setup(){
  Serial.begin(9600);
  pinMode(LASER, OUTPUT);     // Set lasre pin (2) as an output
  pinMode(LED, OUTPUT);       // Set external LED pin (9) as an output
  pinMode(PHOTODIO, INPUT);   // Set  photoresistor pin (A0) as an input
  digitalWrite(LASER, HIGH);  // Turn the laser on and leave it on
}

void loop(){
  value = analogRead(PHOTODIO);
  Serial.println(value);
  //You can change the threshold value
  if (value > 900){
    digitalWrite(LED, LOW);  //Turn led off
  }
  else{
    digitalWrite(LED, HIGH); //Turn led on
  }

  delay(10); //Small delay
}
