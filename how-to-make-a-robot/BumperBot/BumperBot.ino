#include <Servo.h>
Servo servoRight;
Servo servoLeft;
volatile int pbLeft = LOW; // Flag for left switch
volatile int pbRight = LOW; // Flag for right switch
boolean started = false; // True after first start
void setup() {
  // Set pin modes for switches
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  // Set internal pull up resistors for switches
  digitalWrite(2, HIGH); // Right switch
  digitalWrite(3, HIGH); // Left switch
  digitalWrite(4, LOW); // Pin 4 as ground
  servoRight.attach(9); // Right servo to pin 9
  servoLeft.attach(10); // Left servo to pin 10
  // Set up interrupts
  attachInterrupt(0, hitRight, FALLING);
  attachInterrupt(1, hitLeft, FALLING);
  started = true; // Okay to start moving
}
void loop() {
  if (pbLeft == HIGH) { // If left bumper hit
    goReverse(); // Reverse for 1/2 sec
    delay(500);
    goRight(); // Spin 1 sec
    delay(1000);
    goForward(); // Go forward again
    pbLeft = LOW; // Reset flag shows "hit"
  }
  if (pbRight == HIGH) { // If right bumper hit
    goReverse();
    delay(500);
    goLeft();
    delay(1000);
    goForward();
    pbRight = LOW;
  }
}
// Interrupt handlers
void hitLeft() {
  if (started) // Only if robot has started
    pbLeft = HIGH;
}
void hitRight() {
  if (started) // Same as left switch handler
    pbRight = HIGH;
}
// Add Motion Routines from ServoTaiChi here
// CODE REQUIRES MOTION ROUTINES TO COMPILE AND RUN
