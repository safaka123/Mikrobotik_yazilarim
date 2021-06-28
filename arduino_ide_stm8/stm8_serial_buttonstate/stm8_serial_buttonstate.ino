
/*
  DigitalReadSerial
  Reads a digital input on pin 2, prints the result to the Serial Monitor
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

#include <Serial.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 5;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial_begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);
  // print out the state of the button:
  Serial_println_u(buttonState);
  delay(1000);        // delay in between reads for stability
}
