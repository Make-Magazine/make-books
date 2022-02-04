/*
Example 8-1. Parsing the commands sent to the irrigation system
*/
const int NUMBEROFVALVES = 3;
const int NUMBEROFTIMES = 2;
int onOffTimes [NUMBEROFVALVES][NUMBEROFTIMES];
const int ONTIME = 0;
const int OFFTIME = 1;
void setup(){
Serial.begin(9600);
};
void loop() {
// Read a string of the form "2N1345" and separate it
// into the first digit, the letter, and the second number
// read only if there is something to read
while (Serial.available() > 0) {
// The first integer should be the valve number
int valveNumber = Serial.parseInt();
// the next character should be either N or F
// do it again:
char onOff = Serial.read();
// next should come the time
int desiredTime = Serial.parseInt();
//Serial.print("time = ");
//Serial.println(desiredTime);
// finally expect a newline which is the end of
// the sentence:
if (Serial.read() == '\n') {
if ( onOff == 'N') { // it's an ON time
onOffTimes[valveNumber][ONTIME] = desiredTime;
}
else if ( onOff == 'F') { // it's an OFF time
onOffTimes[valveNumber][OFFTIME] = desiredTime;
}
else { // something's wrong
Serial.println ("You must use upper case N or F only");
}
} // end of sentence
else {
// Sanity check
Serial.println("no Newline character found");
}
// now print the entire array so we can see if it works
for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
Serial.print("valve # ");
Serial.print(valve);
Serial.print(" will turn ON at ");
Serial.print(onOffTimes[valve][ONTIME]);
Serial.print(" and will turn OFF at ");
Serial.print(onOffTimes[valve][OFFTIME]);
Serial.println();
}
} // end of Serial.available()
}