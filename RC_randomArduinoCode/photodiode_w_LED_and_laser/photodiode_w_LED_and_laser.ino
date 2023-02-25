/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   
/* WIRING DESCRIPTION
 * 
 * 
 *  
 */


/* DESCRIPTION
 * This code uses a laser module, photodiode, and LED. The laser module is used to 
 *  simulate one tank shooting the other tank. The photodiode is used to simulate
 *  the enemy tank being hit. The LED is used as a visual indicator that the enemy
 *  tank has been hit. The boolean value "hit" will be used to send back to the 
 *  controller for the LED on the user's controller.
 *  
 * Ideally, the laser module would be in a separate code but it is currently in here
 *  just for testing purposes. We would like it to receive input from the push/SW pin 
 *  of the servo joystick. 
 *  
 * If I uploaded this code to Tank 1, then the photodiode 
 *  and LED would detect changes for Tank 1 and not for Tank 2.
 *  
 * The LED should be set as HIGH in the setup() portion but is currently in the loop()
 *  portion just for debugging purposes.  
 */


// Constants
const int PHOTODIO = A0;    // Photoresistor connected Arduino analog pin A0
const int LED = 9;         // LED pin connected to Arduino pin 9
const int LASER = 2;        // Laser module connected to Arduino pin 2

//Variables
int value;				  // Store value from photoresistor (0-1023)
bool hit = false;   // Used to indicate whether the tank has been hit or not

void setup(){
  Serial.begin(9600);         // Used for viewing photodiode voltage value
  pinMode(LASER, OUTPUT);     // Set laser pin (2) as an output
  pinMode(LED, OUTPUT);       // Set external LED pin (9) as an output
  pinMode(PHOTODIO, INPUT);   // Set  photoresistor pin (A0) as an input
  
  digitalWrite(LASER, HIGH);  // Turn the laser on and leave it on
  digitalWrite(LED, HIGH);    // Turn the LED on to start with
}

void loop(){
  value = analogRead(PHOTODIO);   // Read the analog value from the photodiode's cathode
  Serial.println(value);          // Display this value in the serial monitor

  // The threshold value can be changed as needed
  if (value > 100){               
    digitalWrite(LED, LOW);   // Turn LED off to indicate you lost a life
    hit = true;               // Indicates that your tank has been hit
  }
  else{
//    digitalWrite(LED, HIGH);  // Turn LED on to indicate that you gained that life back
    hit = false;              // Indicates that your tank has not been hit

  delay(10); //Small delay so that if the laser just briefly passes over diode then we catch it
  }
}
