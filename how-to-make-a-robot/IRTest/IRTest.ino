#include <IRremote.h>

#define  show_code  false   // Test mode
// false means match to # buttons
// true means display raw code

const int RECV_PIN = A0;     // Receiver input on Analog 0
IRrecv irrecv(RECV_PIN);     // Define IR recever object
decode_results results;


void setup() {
  pinMode(A1, OUTPUT);       // IR power, ground pins
  pinMode(A2, OUTPUT);
  digitalWrite(A1, LOW);     // The ground for the IR
  digitalWrite(A2, HIGH);    // Power to the IR
  irrecv.enableIRIn();       // Initiate the receiver
  Serial.begin(9600);        // Set the baud rate
}

void loop() {

  if (irrecv.decode(&results)) {  // If valid value was received
    if (show_code) {               // If show_code=true
      Serial.print("0x");
      Serial.println(results.value, HEX);  // Display raw hex
    } else {                      // else show_code=false
      switch (results.value) {    // Match button to Sony codes
        case 0x10:
          Serial.println("1");
          break;
        case 0x810:
          Serial.println("2");
          break;
        case 0x410:
          Serial.println("3");
          break;
        case 0xC10:
          Serial.println("4");
          break;
        case 0x210:
          Serial.println("5");
          break;
        case 0xA10:
          Serial.println("6");
          break;
        case 0x610:
          Serial.println("7");
          break;
        case 0xE10:
          Serial.println("8");
          break;
        case 0x110:
          Serial.println("9");
          break;
      }
    }
    irrecv.resume();    // Receive the next value
    delay(10);          // Pause for 10 milliseconds
  }

}
