#define SENSOR A5 // Right line analog pin A5
int sValue = 0; // Variable holds value
void setup() {
  Serial.begin (9600); // Start Serial Monitor
}
void loop() {
  sValue = analogRead(SENSOR); // Read sensor value
  Serial.println (sValue); // Display value
  delay(250); // Wait 1/4 second
}
