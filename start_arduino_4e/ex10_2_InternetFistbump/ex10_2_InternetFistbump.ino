void setup() {
/*
A simple MQTT client with a servo motor
which connects to a broker and subscribes to a topic.
When a message is received, the servo motor moves
to the position in the message.
Connect a picture of a fist to the servo motor arm
and you can receive a "fistbump"
from friends around the world
/*
A simple MQTT client with a servo motor
which connects to a broker and subscribes to a topic.
When a message is received, the servo motor moves
to the position in the message.
Connect a picture of a fist to the servo motor arm
and you can receive a "fistbump"
from friends around the world
This sketch uses https://shiftr.io/try as the MQTT broker.
the circuit:
- A servo motor attached to pin 9
the secrets.h file:
#define SECRET_SSID "sammydog" // your WiFi network name
#define SECRET_PASS "12345678" // your WiFi network password
#define SECRET_MQTT_USER "public" // Shiftr.io broker username
#define SECRET_MQTT_PASS "public" // Shiftr.io broker password
20 May 2021 - Created by Michael Shiloh
Based almost entirely on MqttClientButtonLed
example by Tom Igoe. See
https://tigoe.github.io/mqtt-examples/
*/
#include <WiFiNINA.h> // Library for WiFi functionality on the
// Nano 33 Iot. See
// https://www.arduino.cc/en/Reference/
WiFiNINA
#include <ArduinoMqttClient.h> // Library for MQTT protocol. See
//
#include "arduino_secrets.h" // Usernames and passwords
// initialize WiFi connection:
WiFiClient wifi; // WiFi client object
MqttClient mqttClient(wifi); // Create the MQTT client object
// and attach it to the WiFi object
// details for MQTT client:
char broker[] = "public.cloud.shiftr.io";
int port = 1883; // The Internet Protocol (IP) uses different port
// numbers to identify different services running
// on the same IP address. The MQTT protocol
// has been assigned the number 1883
char topic[] = "fistbump"; // You choose topic
char clientID[] = "GSWA4E_ARM_Demo_Arduino"; // You choose the
client ID
#include <Servo.h>
Servo servo; // Each servo motor needs an object of class Servo
const int servoPin = 9;
void setup() {
  Serial.begin(9600);
// wait for serial monitor to open.
// This is necessary only if you want to catch all
// messages. The Serial object will not exist until
// you open the serial monitor, so effectively the
// setup() function will loop here until you open
// the serial monitor
while (!Serial) // As long as there is no serial monitor ...
; // ... do nothing
// WiFi setup
// initialize WiFi, if not connected:
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting to ");
Serial.println(SECRET_SSID);
WiFi.begin(SECRET_SSID, SECRET_PASS);
delay(2000);
} // Keep retrying until WiFi connection is established
// print IP address once connected:
Serial.print("Connected. My IP address: ");
Serial.println(WiFi.localIP());
// MQTT broker setup
// set the credentials for the MQTT client:
mqttClient.setId(clientID);
mqttClient.setUsernamePassword(SECRET_MQTT_USER,
SECRET_MQTT_PASS);
// try to connect to the MQTT broker:
while (!connectToBroker()) {
Serial.println("attempting to connect to broker");
delay(1000);
} // Keep retrying until connection to Shiftr.io is established
Serial.println("connected to broker");
// Servo motor setup
// The servo object is attached to the relevant pin
servo.attach(servoPin);
}
void loop() {
// Sometimes the connection to the Shiftr.io MQTT broker
// is dropped. This is normal, as the MQTT protocol
// does not require a permanent connection.
// if not connected to the broker, try to connect:
if (!mqttClient.connected()) {
Serial.println("reconnecting");
// Note that the return value from connectToBroker()
// is not checked, so we may in fact not be connected.
// That won't cause trouble, because in the next step we
// won't have a message, so we will loop back here and
// try again anyway.
connectToBroker();
}
// if a message comes in, read it:
if (mqttClient.parseMessage() > 0) {
Serial.print("Got a message on topic: ");
Serial.println(mqttClient.messageTopic());
// read the message:
while (mqttClient.available()) {
// convert numeric string to an int:
int message = mqttClient.parseInt();
Serial.println(message);
servo.write(message);
}
}
}
// Connect to the MQTT broker
// Returns: true if connection established
// false otherwise
boolean connectToBroker() {
// if the MQTT client is not connected:
if (!mqttClient.connect(broker, port)) {
// print out the error message:
Serial.print("MOTT connection failed. Error no: ");
Serial.println(mqttClient.connectError());
// return that you're not connected:
return false;
}
Serial.print("Connected to broker ");
Serial.print( broker );
Serial.print( " port " );
Serial.print( port );
Serial.print( " topic " );
Serial.print( topic);
Serial.println();
// once connected, subscribe to the topic
mqttClient.subscribe(topic);
// return that you're connected:
return true;
}
