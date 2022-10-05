void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, INPUT); // Right switch
  pinMode(3, INPUT); // Left switch
  pinMode(4, OUTPUT); // Ground for switches
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW); // Set to 0 volts
}

  void loop() {
    if ((digitalRead(2) == LOW) || (digitalRead(3) == LOW))
      digitalWrite(LED_BUILTIN, HIGH);
    else
      digitalWrite(LED_BUILTIN, LOW);
    delay (100);
  }
