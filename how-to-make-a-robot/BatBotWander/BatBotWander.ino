#include <Servo.h> 

Servo servoRight;
Servo servoLeft;
 
#define Trigger 7
#define Echo 8
 
void setup(){
   
  // Set the baud rate to 9600. 9600 means that 
  // the serial port is capable of transferring 
  // a maximum of 9600 bits per second.
  Serial.begin(9600);
 
  servoRight.attach(9);      // Right servo to pin 9
  servoLeft.attach(10);      // Left servo to pin 10  
 
  // Define each pin as an input or output.
  pinMode(Echo, INPUT);
  pinMode(Trigger, OUTPUT);
 
  // Initializes the pseudo-random number generator
  // Needed for the robot to wander around the room
  randomSeed(analogRead(3));
 
  delay(200);     // Pause 200 milliseconds               
  go_forward();   // Go forward
}

void loop(){
  int distance = doPing();
 
  // If obstacle <= 2 inches away
  if (distance >= 0 && distance <= 2) {    
    Serial.println("Obstacle detected ahead");  
    go_backwards();   // Move in reverse for 0.5 seconds
    delay(500);
 
    /* Go left or right to avoid the obstacle*/
    if (random(2) == 0) {  // Generates 0 or 1, randomly        
      go_right();  // Turn right for one second
    }
    else {
      go_left();  // Turn left for one second
    }
    delay(1000);
    go_forward();  // Move forward
  }
  delay(50); // Wait 50 milliseconds before pinging again
}
 
/*
 * Returns the distance to the obstacle as an integer
 */
int doPing () {
  int distance = 0;
  int average = 0;
 
  // Grab four measurements of distance and calculate
  // the average.
  for (int i = 0; i < 4; i++) {
 
    // Make the Trigger LOW (0 volts) 
    // for 2 microseconds
    digitalWrite(Trigger, LOW);
    delayMicroseconds(2);
 
     
    // Emit high frequency 40kHz sound pulse
    // (i.e. pull the Trigger) 
    // by making Trigger HIGH (5 volts) 
    // for 10 microseconds
    digitalWrite(Trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trigger, LOW);
      
    // Detect a pulse on the Echo pin 8. 
    // pulseIn() measures the time in 
    // microseconds until the sound pulse
    // returns back to the sensor.    
    distance = pulseIn(Echo, HIGH);
 
    // Speed of sound is:
    // 13511.811023622 inches per second
    // 13511.811023622/10^6 inches per microsecond
    // 0.013511811 inches per microsecond
    // Taking the reciprocal, we have:
    // 74.00932414 microseconds per inch 
    // Below, we convert microseconds to inches by 
    // dividing by 74 and then dividing by 2
    // to account for the roundtrip time.
    distance = distance / 74 / 2;
 
    // Compute running sum
    average += distance;
 
    // Wait 10 milliseconds between pings
    delay(10);
  }
 
  // Return the average of the four distance 
  // measurements
  return (average / 4);
}
 
/*   
 *  Forwards, backwards, right, left, stop.
 */
void go_forward() {
  servoRight.write(0);
  servoLeft.write(180);
}
void go_backwards() {
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
void stop_all() {
  servoRight.write(90);
  servoLeft.write(90);
}
