#define SPKR 5

void setup() {
}

// Play sounds over and
// over again
void loop() {
  tone(SPKR, 247, 300); //247 Hz, 300ms
  delay(200);
  tone(SPKR, 131, 300);
  delay(200);
  tone(SPKR, 1175, 300);
  delay(200);
  tone(SPKR, 262, 300);
  delay(200);
  tone(SPKR, 1175, 300);
  delay(200);
  tone(SPKR, 131, 300);
  delay(200);
  tone(SPKR, 262, 300);
  delay(200);
  tone(SPKR, 1175, 300);
  delay(200);
  tone(SPKR, 247, 300); //247 Hz, 300ms
  delay(200);
}
