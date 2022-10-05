#include <Servo.h> 
 
#define SPKR 5
 
// Create two servo objects, one for each wheel
Servo servoRight;
Servo servoLeft;
 
// Volatile keyword is used because these variables
// can change at any time without any action having been
// taken by the compiled code. 
 
volatile int left_switch = LOW;   // Left switch flag
volatile int right_switch = LOW;  // Right switch flag
boolean already_started = false;  
 

void setup() {
  // Set the pin modes for the switches
  pinMode(2, INPUT); // Right switch is input
  pinMode(3, INPUT); // Left switch is input
  pinMode(4, OUTPUT); // Pin 4 is ground
   
  // Turn on the internal pull up resistors for the switches
  // Keeps input from floating when the switches are not
  // pressed
  digitalWrite(2, HIGH);     // Right switch default to high
  digitalWrite(3, HIGH);     // Left switch default to high
  digitalWrite(4, LOW);      // Pin 4 default is ground
 
  servoRight.attach(9);      // Right servo is pin 9
  servoLeft.attach(10);      // Left servo is pin 10
  
  // Declare the interrupts
  // attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
  // Interrupt when go from high to low
  attachInterrupt(digitalPinToInterrupt(2), hit_right, FALLING); 
  attachInterrupt(digitalPinToInterrupt(3), hit_left, FALLING);  
   
  already_started = true;  // Bot can now move
}
 
void loop() {
  if (left_switch == HIGH) {       // If the left switch is hit
    go_backwards();                // Go backwards for one second
    delay(1000); 
    go_right();                    // Turn to the right for one second
    delay(1000);
    go_forward();                  // Move forward
    left_switch = LOW;             // Reset the flag
  }
   
  if (right_switch == HIGH) {      // If the right switch is hit
    go_backwards();                // Go backwards for one second
    delay(1000); 
    go_left();                     // Turn left for one second
    delay(1000);
    go_forward();                  // Move forward
    right_switch = LOW;            // Reset the flag
  }
}
   
// Interrupt routine for left switch bumping into an object
void hit_left() {
  if (already_started)              // Valid if the program has begun
    left_switch = HIGH;             
}
 
// Interrupt routine for right switch bumping into an object
void hit_right() {
  if (already_started)              // Valid if the program has begun
    right_switch = HIGH;
}
 
/*   
 *  Forwards, backwards, right, left, stop.
 */
void go_forward() {
  servoRight.write(0);
  servoLeft.write(180);
}
void go_backwards() {
 
  // Make a noise before you go backwards
  tone(SPKR, 247, 300); //247 Hz, 300ms
  delay(200);
  tone(SPKR, 131, 300);
  delay(200);
  tone(SPKR, 1175, 300);
  delay(200);
  servoRight.write(180);
  servoLeft.write(0);
}
void go_right() {
  servoRight.write(180);
  servoLeft.write(180);
}
void go_left() {
  servoRight.write(0);
  servoLeft.write(0);
}
/*
void stop_all() {
  servoRight.write(90); // Tweak the 90
  servoLeft.write(90);  // Tweak the 90
}
*/
