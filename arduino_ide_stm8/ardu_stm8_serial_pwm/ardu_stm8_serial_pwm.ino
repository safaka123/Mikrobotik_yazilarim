/*
  Analog input, analog output, serial output
  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.
  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +3.3V and ground
  - LED connected from digital pin 9 to ground
  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe
  modified 28 Feb 2017 for use with sduino
  by Michael Mayer
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 13; // Analog output pin that the LED is attached to. sadece D13 ve D7 kullanılır. 

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial_begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = 1023; // 0-1000 arası ayarlanır. gerçek satır okuma : analogRead(analogInPin);
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255);// sensör 1023 olduğunda çıkış pwm değeri 255 olur. 
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial_print_s("sensor = ");
  Serial_print_u(sensorValue);
  Serial_print_s("output = ");
  Serial_println_u(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(500);
}
