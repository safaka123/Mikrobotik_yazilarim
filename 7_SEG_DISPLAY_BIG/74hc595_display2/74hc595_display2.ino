/*

  Shift Register Example

  Turning on the outputs of a 74HC595 using an array

 Hardware:

 * 74HC595 shift register

 * LEDs attached to each of the outputs of the shift register

 */
//Pin connected to ST_CP of 74HC595
int latchPin = 3;
//Pin connected to SH_CP of 74HC595
int clockPin = 4;
////Pin connected to DS of 74HC595
int dataPin = 2;

//holders for information you're going to pass to shifting function
byte data;
byte dataArray[10];

void setup() {

  //set pins to output because they are addressed in the main loop

  pinMode(latchPin, OUTPUT);

  Serial.begin(9600);

  //Binary notation as comment

  dataArray[0] =0x30;// 0xFF; //0b11111111

  dataArray[1] =0x6D;// 0xFE; //0b11111110

  dataArray[2] =0x79;// 0xFC; //0b11111100

  dataArray[3] =0x72;// 0xF8; //0b11111000

  dataArray[4] =0x5B;// 0xF0; //0b11110000

  dataArray[5] =0x5F;// 0xE0; //0b11100000

  dataArray[6] =0x31;// 0xC0; //0b11000000

  dataArray[7] =0x7F;// 0x80; //0b10000000

  dataArray[8] =0x7B;// 0x00; //0b00000000

  dataArray[9] =0x3F;// 0xE0; //0b11100000

  dataArray[10] =0x80;// LED ON

  dataArray[11] =0x00;// LED OFF

  //function that blinks all the LEDs

  //gets passed the number of blinks and the pause time

  blinkAll_2Bytes(2,500);
}

void loop() {

  for (int j = 0; j < 12; j++) {

    //load the light sequence you want from array

    data = dataArray[j];

    //ground latchPin and hold low for as long as you are transmitting

    digitalWrite(latchPin, 0);

    //move 'em out

    shiftOut(dataPin, clockPin, data);

    //return the latch pin high to signal chip that it

    //no longer needs to listen for information

    digitalWrite(latchPin, 1);

    delay(800);

  }
}

// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {

  // This shifts 8 bits out MSB first,

  //on the rising edge of the clock,

  //clock idles low

  //internal function setup

  int i=0;

  int pinState;

  pinMode(myClockPin, OUTPUT);

  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to

  //prepare shift register for bit shifting

  digitalWrite(myDataPin, 0);

  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut&#xFFFD;

  //NOTICE THAT WE ARE COUNTING DOWN in our for loop

  //This means that %00000001 or "1" will go through such

  //that it will be pin Q0 that lights.

  for (i=7; i>=0; i--)  {

    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result

    // true then... so if we are at i=6 and our value is

    // %11010100 it would the code compares it to %01000000

    // and proceeds to set pinState to 1.

    if ( myDataOut & (1<<i) ) {

      pinState= 1;

    }

    else {

      pinState= 0;

    }

    //Sets the pin to HIGH or LOW depending on pinState

    digitalWrite(myDataPin, pinState);

    //register shifts bits on upstroke of clock pin

    digitalWrite(myClockPin, 1);

    //zero the data pin after shift to prevent bleed through

    digitalWrite(myDataPin, 0);

  }

  //stop shifting

  digitalWrite(myClockPin, 0);
}

//blinks the whole register based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {

  digitalWrite(latchPin, 0);

  shiftOut(dataPin, clockPin, 0);

  shiftOut(dataPin, clockPin, 0);

  digitalWrite(latchPin, 1);

  delay(200);

  for (int x = 0; x < n; x++) {

    digitalWrite(latchPin, 0);

    shiftOut(dataPin, clockPin, 255);

    shiftOut(dataPin, clockPin, 255);

    digitalWrite(latchPin, 1);

    delay(d);

    digitalWrite(latchPin, 0);

    shiftOut(dataPin, clockPin, 0);

    shiftOut(dataPin, clockPin, 0);

    digitalWrite(latchPin, 1);

    delay(d);

  }
}
