#define LED_RED 11
#define LED_GREEN 12

void setup() {
   
  // Define output pins
  pinMode(LED_RED, OUTPUT);  
  pinMode(LED_GREEN, OUTPUT);
  
  // Set output values
  digitalWrite(LED_RED, LOW); 
  digitalWrite(LED_GREEN, LOW);
}
 

void loop() {
digitalWrite(LED_GREEN, HIGH);
delay(250);
digitalWrite(LED_GREEN, LOW);
delay(250);
}
