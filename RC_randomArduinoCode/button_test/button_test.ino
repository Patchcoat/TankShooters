#define button 8
int state = 0;

void setup ()
{
  Serial.begin(9600);
   pinMode (button, INPUT_PULLUP); 
}
void loop () {
   state = digitalRead(button);
   if (state){
    Serial.println("Not Pressed");
   }
   else{
    Serial.println("Pressed");
   }
   delay (100);
}
