
/*
  DigitalReadSerial
  Reads a digital input on pin 2, prints the result to the Serial Monitor
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

//#include <Serial.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 5;
int inByte = 0;         // incoming serial byte
const int ledPin =  13;
int outputValue = 0;
char myCharArray[] = "128";
int inByte1 = 0;
   int inByte2 =0;
   int inByte3 = 0;

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
  
   
   while (Serial_available() > 0){
  inByte1 = Serial_read();
    inByte2 = Serial_read();
    inByte3 = Serial_read();
   
   }
   myCharArray[0]=inByte1;
   myCharArray[1]=inByte2;
   myCharArray[2]=inByte3;
   int test = atoi(myCharArray);  // Array şeklindeki veriyi int değişkenine çevirir. pwm 0-255 arası olması için böyle yapıldı. 
   //Serial_write(test);
    Serial_println_ub(test,DEC);   
   analogWrite(ledPin,test); // pwm çıkışı
     
  delay(1000);        // delay in between reads for stability
  
}

