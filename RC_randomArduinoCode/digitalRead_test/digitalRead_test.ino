float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int digitalVal = digitalRead(A0);
  int analogVal = analogRead(A0);
//  analogVal = floatMap(analogVal, 0, 1024, 0, 3.3); 
  Serial.print("Digital value: ");
  Serial.println(digitalVal);
  Serial.print("Analog value: ");
  Serial.println(analogVal);
  delay(1000);
}
