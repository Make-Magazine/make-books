const int SENSOR = 0;
const int R_LED = 9;
const int G_LED = 10;
const int B_LED = 11;
const int BUTTON = 12;

int val = 0; // variable to store the value coming from the sensor

int btn = LOW;
int old_btn = LOW;
int state = 0;
char buffer[7] ;
int pointer = 0;
byte inByte = 0;

byte r = 0;
byte g = 0;
byte b = 0;

void setup() {
  Serial.begin(9600);  // open the serial port
  pinMode(BUTTON, INPUT);
}

void loop() {
  val = analogRead(SENSOR); // read the value from the sensor
  Serial.println(val);      // print the value to
                            // the serial port

  if (Serial.available() > 0) {

    // read the incoming byte:
    inByte = Serial.read();

    // If the marker's found, next 6 characters are the colour
    if (inByte == '#') {

      while (pointer < 6) { // accumulate 6 chars
        buffer[pointer] = Serial.read(); // store in the buffer
        pointer++; // move the pointer forward by 1
      }

      // now we have the 3 numbers stored as hex numbers
      // we need to decode them into 3 bytes r, g and b
      r = hex2dec(buffer[1]) + hex2dec(buffer[0]) * 16;
      g = hex2dec(buffer[3]) + hex2dec(buffer[2]) * 16;
      b = hex2dec(buffer[5]) + hex2dec(buffer[4]) * 16;

      pointer = 0; // reset the pointer so we can reuse the buffer

    }
  }

  btn = digitalRead(BUTTON); // read input value and store it

  // Check if there was a transition
  if ((btn == HIGH) && (old_btn == LOW)){
    state = 1 - state;
  }

  old_btn = btn; // val is now old, let's store it

  if (state == 1) { // if the lamp is on

    analogWrite(R_LED, r);  // turn the leds on
    analogWrite(G_LED, g);  // at the colour
    analogWrite(B_LED, b);  // sent by the computer
  } else {

    analogWrite(R_LED, 0);  // otherwise turn off
    analogWrite(G_LED, 0);
    analogWrite(B_LED, 0);
   }

  delay(100);                // wait 100ms between each send
}

int hex2dec(byte c) { // converts one HEX character into a number
    if (c >= '0' && c <= '9') {
      return c - '0';
    } else if (c >= 'A' && c <= 'F') {
      return c - 'A' + 10;
    }
}