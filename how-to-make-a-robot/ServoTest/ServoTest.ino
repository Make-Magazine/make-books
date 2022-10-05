#include <Servo.h>

Servo servoRight; Servo servoLeft;

void setup()
{
  servoRight.attach(9); servoLeft.attach(10);
}

void loop()
{

  servoRight.write(0);  // Fwd servoLeft.write(180); delay(2000);

  servoRight.write(180); // Rev servoLeft.write(0); delay(2000);

  servoRight.write(180); // Right servoLeft.write(180); delay(2000);

  servoRight.write(0);  // Left servoLeft.write(0); delay(2000);
}
