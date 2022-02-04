#include <Servo.h>
Servo myservo;
void setup() {
myservo.attach(9);
myservo.write(45); // move to position 45 degrees
}
void loop() {
}