#include <Servo.h> 
 
 
// Each servo is an object with its own data and behavior
Servo servoLeft;
Servo servoRight;
 
// Sensors connected to analog pins 4 (left sensor) and 5 (right sensor)
const int left_line = A4;
const int right_line = A5;
 
// Store sensor readings here
int irleft_reflect = 0;
int irright_reflect = 0;
 
// Try values between 400 and 800. 
// Helps determine if robot is over the line
int threshold = 800;           
 
void setup() { 
  // Assign each servo to its own digital pin on the Arduino
  servoRight.attach(9);  
  servoLeft.attach(10); 
} 
 
void loop() { 
 
  // Read the reflectance sensors
  irleft_reflect = analogRead(left_line);  
  irright_reflect = analogRead(right_line);
 
  // robot is right over the line
  if (irleft_reflect >= threshold && irright_reflect >= threshold) {
    line_forward();   
  }
 
  // robot is veering off to the right
  if (irleft_reflect >= threshold && irright_reflect <= threshold) {
    line_left_slip();  
    delay(4);
  }
 
  // robot is veering off to the left
  if (irleft_reflect <= threshold && irright_reflect >= threshold) {
    line_right_slip();  
    delay(4);
  }
 
  // If robot has lost the line, go find it
  if (irleft_reflect < threshold && irright_reflect < threshold) {
    line_right_spin();
    delay(20);
  }
}
 
// On the continuous rotation servo, the write() 
// method sets the speed of the servo.
// 0 is full speed in one direction.
// 180 is full speed in the other direction.
// ~90 is no movement (You will have to tweak to
//   get no movement).
void line_forward() {
  servoRight.write(0);  
  servoLeft.write(180);
}
void line_right_slip() {
  servoRight.write(90);  
  servoLeft.write(180);
}
void line_left_slip() {
  servoRight.write(0);  
  servoLeft.write(90);
}
void line_right_spin() {
servoRight.write(180);  
  servoLeft.write(180);
}
void line_left_spin() {
  servoRight.write(0);  
  servoLeft.write(0);
}
