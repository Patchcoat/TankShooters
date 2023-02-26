#define VRX_PIN      A0 // Micro pin connected to VRX pin of joystcik
#define VRY_PIN      A1 // Micro pin connected to VRY pin of joystick

int VX;
int VY;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  VX = analogRead(VRX_PIN);
  VY = analogRead(VRY_PIN);
  Serial.print("VRX: ");
  Serial.println(VX);
  Serial.print("VRY: ");
  Serial.println(VY);
  delay(1000);
}
