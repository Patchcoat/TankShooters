int pdPin = A4; // photodiode connected to pin A4 (Analog)

void setup() {
  Serial.begin(9600);
  pinMode(pdPin, INPUT);
}

void loop() {
  int anaVal = analogRead(pdPin);         // read the analog voltage from photodiode
  float voltage = 5-(anaVal/1024.0)*5;    // convert to appropriate voltage
  Serial.println(String(voltage,2)+"V");  // display voltage in serial monitor
  delay(2000);                            // delay by 2000ms to prevent any duplicates
}
