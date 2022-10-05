#define Trigger 7
#define Echo 8
void setup() {
  Serial.begin(9600);
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);
}
void loop() {
  digitalWrite(Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger, LOW);
  int distance = pulseIn(Echo, HIGH);
  distance = distance / 74 / 2;
  Serial.println(distance);
  delay(100);
}
