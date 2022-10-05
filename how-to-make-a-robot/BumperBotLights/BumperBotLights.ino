#include <Servo.h> 

Servo servoRight;
Servo servoLeft;
 
volatile int left_switch = LOW;   // Flag for left switch
volatile int right_switch = LOW;  // Flag for right switch
boolean started = false;     // True after first start
 
#define LED_RED 11
#define LED_GREEN 12
 
void setup() {
  // Set pin modes for switches
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
   
  // Set internal pull up resistors for switches
  // These go LOW when pressed as connection
  // is made with Ground.
  digitalWrite(2, HIGH);     // Right switch
  digitalWrite(3, HIGH);     // Left switch
   
  digitalWrite(4, LOW);      // Pin 4 is ground
 
  servoRight.attach(9);      // Right servo to pin 9
  servoLeft.attach(10);      // Left servo to pin 10
  
  // Set up the interrupts
  attachInterrupt(0, bump_right, FALLING);
  attachInterrupt(1, bump_left, FALLING);
   
  started = true;            // OK to start moving
   
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_GREEN, LOW);
}
 
void loop() {
  if (left_switch == HIGH) {   // If the left switch hit
    go_backwards();            // Go backwards for 0.5 sec
    delay(500); 
    turn_right();              // Spin for 1 second
    delay(1000);
    go_forward();              // Go forward
    left_switch = LOW;         // Reset flag shows bumped
  }
   
  if (right_switch == HIGH) {  // If right switch hit
    go_backwards();
    delay(500); 
    turn_left();
    delay(1000);
    go_forward();
    right_switch = LOW;
  }
}
   
// Interrupt handlers
void bump_left() {
  if (started)              // If robot has begun
    left_switch = HIGH;
}
void bump_right() {
  if (started)             
    right_switch = HIGH;
}
 
// Motion Routines: forward, backwards, turn, stop
// Continuous servo motor
void go_forward() {
  servoRight.write(0);
  servoLeft.write(180);
  led_green();
}
void go_backwards() {
  servoRight.write(180);
  servoLeft.write(0);
  led_red();
}
void turn_right() {
  servoRight.write(180);
  servoLeft.write(180);
  led_off();
}
void turn_left() {
  servoRight.write(0);
  servoLeft.write(0);
  led_off();
}
void stop_all() {
  servoRight.write(90);
  servoLeft.write(90);
}
 
void led_green() {
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);      
} 
void led_red() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}
void led_off() {
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
}
