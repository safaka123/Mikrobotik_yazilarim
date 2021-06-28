
/*
  DigitalReadSerial
  Reads a digital input on pin 2, prints the result to the Serial Monitor
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

#include <Serial.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 5;
int inByte = 0;         // incoming serial byte




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
   if (Serial_available() > 0) {
    // get incoming byte:
    inByte = Serial_read();
    Serial_write(inByte); // ascii olarak gönderir. 100=d harfidir. ekranda d harfi görünür. 
    Serial_println_s("");
    Serial_println_u(inByte);
    Serial_println_s(" DENEME yazisi ");
    Serial_print_c('A');
    Serial_println_s("");
    Serial_println_ub(19,HEX);
    Serial_println_ub(19,DEC);
    Serial_println_ub(19,BIN);
   }
  delay(1000);        // delay in between reads for stability
}

