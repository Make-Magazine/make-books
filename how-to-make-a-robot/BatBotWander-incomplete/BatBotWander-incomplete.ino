#include <Servo.h>
Servo servoRight;
Servo servoLeft;
#define Trigger 7
#define Echo 8
void setup() {
  servoRight.attach(9);
  servoLeft.attach(10);
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);
  randomSeed(analogRead(3));
  delay(200);
  goForward();
}
void loop() {
  int distance = doPing();
  if (distance <= 2)
    goReverse();
  delay(500);
  if (random(2) == 0)
    goRight();
  else
    goLeft();
}
// Motion Routines: forward, reverse, turn, stop
void goForward() {
  servoRight.write(0);
  servoLeft.write(180);
}
void goReverse() {
  servoRight.write(180);
  servoLeft.write(0);
}
void goRight() {
  servoRight.write(180);
  servoLeft.write(180);
}
void goLeft() {
  servoRight.write(0);
  servoLeft.write(0);
}
void allStop() {
  servoRight.write(90);
  servoLeft.write(90);
}
