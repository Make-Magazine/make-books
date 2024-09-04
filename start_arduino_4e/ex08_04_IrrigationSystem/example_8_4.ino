/* 
 Example 8-4. The irrigation system sketch
 */
 
/*
 Sketch to accompany the automatic garden irrigation system in
 "Getting Started With Arduino, Third Edition". See that book for
 the schematic.
 
 http://shop.oreilly.com/product/0636920029267.do
 
 09/04/2014 - Written by Michael Shiloh
 12/09/2014 - 1) When displaying on and off times, 
              must convert back to hours and minutes 
              2) Humidity threshold was too low
              3) Forgot to set digital pins as output
              4) new function printSettings() since the same
              thing was being done in two different places
              
 This example code is in the public domain.
 */

#include <Wire.h>   // Wire library, used by RTC library
#include "RTClib.h" // RTC library
#include "DHT.h"    // DHT temperature/humidity sensor library

// Analog pin usage
const int RTC_5V_PIN = A3;
const int RTC_GND_PIN = A2;

// Digital pin usage
const int DHT_PIN  = 2;     // temperature/humidity sensor
const int WATER_VALVE_0_PIN = 8;
const int WATER_VALVE_1_PIN = 7;
const int WATER_VALVE_2_PIN = 4;

const int NUMBEROFVALVES = 3; // How many valves we have
const int NUMBEROFTIMES = 2;  // How many times we have

// Array to store ON and OFF times for each valve
// Store this time as the number of minutes since midnight
// to make calculations easier
int onOffTimes [NUMBEROFVALVES][NUMBEROFTIMES];
int valvePinNumbers[NUMBEROFVALVES];

// Which column is ON time and which is OFF time
const int ONTIME = 0;
const int OFFTIME = 1;

#define DHTTYPE DHT11
DHT dht(DHT_PIN, DHTTYPE); // Create a DHT object

RTC_DS1307 rtc;    // Create an RTC object

// Global variables set and used in different functions
DateTime dateTimeNow; // to store results from the RTC

// to store humidity result from the DHT11 sensor
float humidityNow;       

void setup(){

  // Power and ground to RTC
  pinMode(RTC_5V_PIN, OUTPUT);
  pinMode(RTC_GND_PIN, OUTPUT);
  digitalWrite(RTC_5V_PIN, HIGH);
  digitalWrite(RTC_GND_PIN, LOW);

  // Initialize the wire library
  #ifdef AVR
    Wire.begin();
  #else
    // Shield I2C pins connect to alt I2C bus on Arduino Due
    Wire1.begin(); 
  #endif

  rtc.begin();        // Initialize the RTC object
  dht.begin();        // Initialize the DHT object
  Serial.begin(9600); // Initialize the Serial object

  // Set the water valve pin numbers into the array
  valvePinNumbers[0] = WATER_VALVE_0_PIN;
  valvePinNumbers[1] = WATER_VALVE_1_PIN;
  valvePinNumbers[2] = WATER_VALVE_2_PIN;
  
  // and set those pins all to outputs
  for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
    pinMode(valvePinNumbers[valve], OUTPUT);
  }

};

void loop() {

  // Remind user briefly of possible commands
  Serial.print("Type 'P' to print settings or ");$
  Serial.println("'S2N13:45' to set valve 2 ON time to 13:34");$


  // Get (and print) the current date, time, 
  // temperature, and humidity
  getTimeTempHumidity();

  // Check for request from the user
  checkUserInteraction();

  // Check to see whether it's time to turn any valve ON or OFF
  checkTimeControlValves();

  // No need to do this too frequently
  delay(5000);
}


/*
 * Get, and print, the current date, time, 
 * humidity, and temperature
 */
void getTimeTempHumidity() {
  // Get and print the current time
  dateTimeNow = rtc.now();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // use this to set the RTC to the date and time 
    // this sketch was compiled
    // use this ONCE and then comment it out
    // rtc.adjust(DateTime(__DATE__, __TIME__));
    return; // if the RTC is not running don't continue
  }

  Serial.print(dateTimeNow.hour(), DEC);
  Serial.print(':');
  Serial.print(dateTimeNow.minute(), DEC);
  Serial.print(':');
  Serial.print(dateTimeNow.second(), DEC);

  // Get and print the current temperature and humidity
  humidityNow = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidityNow) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return; // if the DHT is not running don't continue;
  }

  Serial.print(" Humidity ");
  Serial.print(humidityNow);
  Serial.print("% ");
  Serial.print("Temp ");
  Serial.print(t);
  Serial.print("C ");
  Serial.print(f);
  Serial.print("F");
  Serial.println();
} // end of getTimeTempHumidity()


/*
 * Check for user interaction, which will be in the form of 
 * something typed on the serial monitor
 * If there is anything, make sure it's proper, and perform the 
 * requested action
 */
void checkUserInteraction() {
  // Check for user interaction
  while (Serial.available() > 0) {

    // The first character tells us what to expect 
    // for the rest of the line
    char temp = Serial.read();

    // If the first character is 'P' then 
    // print the current settings
    // and break out of the while() loop
    if ( temp == 'P') {
      printSettings();
      Serial.flush();
      break;
    } // end of printing current settings

    // If first character is 'S' then the rest will be a setting
    else if ( temp == 'S') {
      expectValveSetting();
    }

    // Otherwise, it's an error. 
    // Remind the user what the choices are
    // and break out of the while() loop
    else
    {
      printMenu();
      Serial.flush();
      break;
    }
  } // end of processing user interaction
}


/*
 * Read a string of the form "2N13:45" and separate it
 * into the valve number, the letter indicating ON or OFF,
 * and the time
 */
void expectValveSetting() {

  // The first integer should be the valve number
  int valveNumber = Serial.parseInt();

  // the next character should be either N or F
  char onOff = Serial.read();

  // next should come the hour
  int desiredHour = Serial.parseInt();

  // the next character should be ':'
  if (Serial.read() != ':') {
    Serial.println("no : found"); // Sanity check
    Serial.flush();
    return;
  }

  // next should come the minutes
  int desiredMinutes = Serial.parseInt();

  // finally expect a newline which is the end of
  // the sentence:
  if (Serial.read() != '\n') { // Sanity check
    Serial.println(
      "Make sure to end your request with a Newline");
    Serial.flush();
    return;
  }

  // Convert the desired hour and minute time
  // to the number of minutes since midnight
  int desiredMinutesSinceMidnight 
    = (desiredHour*60 + desiredMinutes);
 
  // Now that we have all the information set it into the array
  // in the correct row and column

  if ( onOff == 'N') { // it's an ON time
    onOffTimes[valveNumber][ONTIME] 
    = desiredMinutesSinceMidnight;
  }
  else if ( onOff == 'F') { // it's an OFF time
    onOffTimes[valveNumber][OFFTIME] 
    = desiredMinutesSinceMidnight;
  }
  else { // user didn't use N or F
    Serial.print("You must use upper case N or F ");
    Serial.println("to indicate ON time or OFF time");
    Serial.flush();
    return;
  }

  // now print the entire array so user can see what they set
  printSettings();
} // end of expectValveSetting()


void checkTimeControlValves() {

  // First figure out how many minutes have passed 
  // since midnight, since we store ON and OFF time 
  // as the number of minutes since midnight.  The 
  // biggest number will be at 2359 which is 
  // 23 * 60 + 59 = 1159 which is less than the 
  // maximum that can be stored in an integer so an 
  // int is big enough
  int nowMinutesSinceMidnight =
    (dateTimeNow.hour() * 60) + dateTimeNow.minute();

  // Now check the array for each valve
  for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
  Serial.print("Valve ");
    Serial.print(valve);
    
    Serial.print(" is now ");
    if ( ( nowMinutesSinceMidnight >= 
           onOffTimes[valve][ONTIME]) &&
         ( nowMinutesSinceMidnight < 
           onOffTimes[valve][OFFTIME]) ) {
           
      // Before we turn a valve on make sure it's not raining
      if ( humidityNow > 70 ) {
        // It's raining; turn the valve OFF
        Serial.print(" OFF ");
        digitalWrite(valvePinNumbers[valve], LOW);
      }
      else {
        // No rain and it's time to turn the valve ON
        Serial.print(" ON ");
        digitalWrite(valvePinNumbers[valve], HIGH);
      } // end of checking for rain
    } // end of checking for time to turn valve ON
    else {
      Serial.print(" OFF ");
      digitalWrite(valvePinNumbers[valve], LOW);
    }
    Serial.println();
  } // end of looping over each valve
  Serial.println();
}


void printMenu() {
  Serial.println(
    "Please enter P to print the current settings");
  Serial.println(
    "Please enter S2N13:45 to set valve 2 ON time to 13:34");
}


void printSettings(){

  // Print the current on and off settings, converting the 
  // number of minutes since midnight back to the time
  // in hours and minutes
  
  Serial.println();

  for (int valve = 0; valve < NUMBEROFVALVES; valve++) {
    Serial.print("Valve ");
    Serial.print(valve);
    Serial.print(" will turn ON at ");

    // integer division by 60 gives the hours 
    // since integer division drops any remainder
    Serial.print((onOffTimes[valve][ONTIME])/60);

    Serial.print(":");

    // the minutes are the remainder after dividing by 60.
    // get the remainder with the modulo (%) operator 
    Serial.print((onOffTimes[valve][ONTIME])%(60));

    Serial.print(" and will turn OFF at ");
    Serial.print((onOffTimes[valve][OFFTIME])/60); // hours
    Serial.print(":");
    Serial.print((onOffTimes[valve][OFFTIME])%(60)); // minutes
    Serial.println();
  }
}
