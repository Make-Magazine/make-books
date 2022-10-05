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
  red_blink();
  green_blink();
}
 
// Method to blink the red LED
void red_blink() {
  digitalWrite(LED_RED, HIGH);
  delay(250);                          
  digitalWrite(LED_RED, LOW);     
  delay(250);                         
} 
 
// Method to blink the green LED
void green_blink() {
  digitalWrite(LED_GREEN, HIGH);
  delay(250);                         
  digitalWrite(LED_GREEN, LOW);     
  delay(250);                         
}
