/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // initialize serial:
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("Hello, world? softserial");
}

void loop() {
  // print the string when a newline arrives:
  
    Serial.println(" serial port working ");
 delay(300);
mySerial.println(" SOFT serial port working ");
 delay(300);
 
}
