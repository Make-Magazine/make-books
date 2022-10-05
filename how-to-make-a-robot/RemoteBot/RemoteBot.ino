#include <Servo.h>

Servo servoLeft;              // Define left servo
Servo servoRight;             // Define right servo

#include <IRremote.h>
int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);
decode_results results;
volatile int active_left = LOW;
volatile int active_right = LOW;
boolean started = false;

void setup() {
  // Set pin modes for switches
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);     // Serves as ground connection

  pinMode(A1, OUTPUT);       // IR power, ground pins
  pinMode(A2, OUTPUT);
  digitalWrite(A1, LOW);     // IR ground
  digitalWrite(A2, HIGH);    // IR power

  servoRight.attach(9);    // Set right servo to digital pin 9
  servoLeft.attach(10);    // Set left servo to digital pin 10
  irrecv.enableIRIn();     // Start the receiver

  Serial.begin(9600);

  // Set up interrupts
  attachInterrupt(0, bump_right, FALLING);
  attachInterrupt(1, bump_left, FALLING);

  started = true;
}

void loop() {

  if (active_left == HIGH) {           // If left bumper hit
    go_backwards();
    delay(500);
    spin_right();
    delay(1000);
    go_forward();
    active_left = LOW;
    Serial.println("active_left");
  }

  if (active_right == HIGH) {          // If right bumper hit
    go_backwards();
    delay(500);
    spin_left();
    delay(1000);
    go_forward();
    active_right = LOW;
    Serial.println("active_right");
  }

  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0x10:
        Serial.println("1");     // Turn left forward
        left_turn_fwd();
        break;
      case 0x810:
        Serial.println("2");     // Forward
        go_forward();
        break;
      case 0x410:
        Serial.println("3");     // Turn right forward
        right_turn_fwd();
        break;
      case 0xC10:
        Serial.println("4");    // Spin left
        spin_left();
        break;
      case 0x210:
        Serial.println("5");    // Stop
        stop_all();
        break;
      case 0xA10:
        Serial.println("6");    // Spin right
        spin_right();
        break;
      case 0x610:
        Serial.println("7");    // Turn left reverse
        left_turn_backwards();
        break;
      case 0xE10:
        Serial.println("8");    // Reverse
        go_backwards();
        break;
      case 0x110:
        Serial.println("9");    // Turn right reverse
        turn_right_backwards();
        break;
    }
    irrecv.resume(); // Receive the next value
    delay(2);
  }
}

// Routines for forward, reverse, turns, and stop
void go_forward() {
  servoLeft.write(180);
  servoRight.write(0);
}
void go_backwards() {
  servoLeft.write(0);
  servoRight.write(180);
}
void spin_right() {
  servoLeft.write(180);
  servoRight.write(180);
}
void spin_left() {
  servoLeft.write(0);
  servoRight.write(0);
}
void right_turn_fwd() {
  servoLeft.write(180);
  servoRight.write(90);
}
void left_turn_fwd() {
  servoLeft.write(90);
  servoRight.write(0);
}
void left_turn_backwards() {
  servoLeft.write(90);
  servoRight.write(180);
}
void turn_right_backwards() {
  servoLeft.write(0);
  servoRight.write(90);
}
void stop_all() {
  servoLeft.write(90);
  servoRight.write(90);
}

// Interrupt service routines
void bump_left() {
  if (started)
    active_left = HIGH;
}
void bump_right() {
  if (started)
    active_right = HIGH;
}
