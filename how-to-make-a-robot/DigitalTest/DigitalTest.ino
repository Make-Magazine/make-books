#define SWITCH 3 // Switch to pin 3 (left)
int swValue; // Variable holds value
void setup() {
  pinMode(SWITCH, INPUT); // Left switch input
  pinMode(4, OUTPUT); // Ground for switches
  digitalWrite(SWITCH, HIGH); // Set internal pullup
  Serial.begin (9600); // Start Serial Monitor
}
void loop() {
  swValue = digitalRead(SWITCH); // Read switch value
  Serial.println (swValue); // Display value
  delay(250); // Wait 1/4 sec
}
