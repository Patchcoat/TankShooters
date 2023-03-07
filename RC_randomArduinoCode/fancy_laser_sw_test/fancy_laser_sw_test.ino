#define LASER  7
#define SW     A1

int swValueDig;
int swValueAna;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SW, INPUT);
  pinMode(LASER, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  swValueDig = digitalRead(SW);
  swValueAna = analogRead(SW);

  Serial.print("Digital: ");
  Serial.println(swValueDig);
  Serial.print("Analog: ");
  Serial.println(swValueAna);

  if(!swValueAna){
    digitalWrite(LASER, HIGH);
//    delay(2000);
//    digitalWrite(LASER, LOW);
  }
  else{
    digitalWrite(LASER, LOW);
  }

//  delay(2000);
  
}
