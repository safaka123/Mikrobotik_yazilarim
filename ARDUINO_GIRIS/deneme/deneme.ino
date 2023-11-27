//String inputString = "";         // a String to hold incoming data
//bool stringComplete = false;
//int myInts[6];
//int myPins[] = {2, 4, 8, 3, 6, 4};
//int mySensVals[5] = {2, 4, -8, 3, 2};
//char message[6] = "hello";

float dene=0.123;

#define LEDPIN 2  // bu komutun sonunda ; işareti kullanılmaz. hata verir.

const int LEDPINS=3;
//const float pi = 3.14;// şayet bir sabiti programda kullanmak üzere bir değişken adına atama yapıyorsanız
                        // bu şekilde kullanırsınız. Bu değişkenin değeri bir daha değiştirilemez.
                        
//float x;// sadece değişken tanımlama yapıyorsunuz Bu değişken değeri program iöerisinde değişebilir.

/*SOFTSERIAL
The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
#include <SoftwareSerial.h>  // dahil edilir.
SoftwareSerial mySerial(10, 11); // RX, TX  // dahil edilir.
*/



void setup() {
//Serial.begin(9600); 
 
pinMode(LEDPIN,OUTPUT);// output küçük harf yazılamaz.hata verir.
pinMode(LEDPINS,OUTPUT);

//  mySerial.begin(4800);
//  mySerial.println("Hello, world?");
}

// ALT FONKSİYONLAR LOOP DÖNGÜNÜZDEN ÖNCE YAZILMASI İYİ OLUR. 
void deneme1(){
  
}
void deneme2(){
  
}


void loop() {
  int localvalue=0;// bu değişken sadece bu loop döngüsünde kullanılır. 
  // şayet her yerde kullanılacaksa GLOBAL değişken yeri olan en başta tanımlanmalı. 
  
 //Serial.println(" serial port working ");
 //delay(300);
 digitalWrite(LEDPIN, HIGH);// HIGH küçük harf tanımaz.
 delay(500);
 digitalWrite(LEDPIN, LOW);
 delay(500);
}
