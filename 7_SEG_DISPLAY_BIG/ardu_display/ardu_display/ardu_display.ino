/*

  Shift Register Example

  Turning on the outputs of a 74HC595 using an array

 Hardware:

 * 74HC595 shift register

 * LEDs attached to each of the outputs of the shift register

 */
//Pin connected to ST_CP of 74HC595
//int latchPin = 3;
//Pin connected to SH_CP of 74HC595
//int clockPin = 4;
////Pin connected to DS of 74HC595
//int dataPin = 2;
int data0=2;
int data1=3;
int data2=4;
int data3=5;
int data4=6;
int data5=7;
int data6=8;
int data7=9;


//holders for information you're going to pass to shifting function
byte data;
byte dataArray[10];

void setup() {

  //set pins to output because they are addressed in the main loop

// pinMode(latchPin, OUTPUT);
  pinMode(data0, OUTPUT);
  pinMode(data1, OUTPUT);
  pinMode(data2, OUTPUT);
  pinMode(data3, OUTPUT);
  pinMode(data4, OUTPUT);
  pinMode(data5, OUTPUT);
  pinMode(data6, OUTPUT);
  pinMode(data7, OUTPUT);

  Serial.begin(9600);

  //Binary notation as comment

  dataArray[0] =0x30;// 0xFF; //0b11111111
/*
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

  */
}

void loop() {
  int number=0x30;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(1);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);

   number=0x6D;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(2);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
number=0x79;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(3);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
number=0x72;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(4);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
number=0x5B;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(5);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
number=0x5F;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(6);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
number=0x31;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(7);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);   
   number=0x7F;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(8);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
   number=0x7B;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(9);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
   number=0x3F;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println(0);
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(1000);
   number=0x80;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println("LED ON DISPLAY OFF");
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(3000);
   number=0x00;
  Serial.println("");
   
     digitalWrite(2,(data0=bitRead(number, 0)));
     Serial.println("LED OFF DISPLAY OFF");
     digitalWrite(3,(data0=bitRead(number, 1)));
     digitalWrite(4,(data0=bitRead(number, 2)));
     digitalWrite(5,(data0=bitRead(number, 3)));
     digitalWrite(6,(data0=bitRead(number, 4)));
     digitalWrite(7,(data0=bitRead(number, 5)));
     digitalWrite(8,(data0=bitRead(number, 6)));
     digitalWrite(9,(data0=bitRead(number, 7)));
   delay(3000);
   
   
}
