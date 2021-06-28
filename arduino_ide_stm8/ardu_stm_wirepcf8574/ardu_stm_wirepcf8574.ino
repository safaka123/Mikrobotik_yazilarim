#include <Wire.h>
//byte xx = 0;
byte temp1, temp2;

int adres=0x27;

void setup()
{
  temp1=255;
  pinMode(2, INPUT);
  Serial_begin(9600);
  Wire_begin(); 
  Wire_beginTransmission(adres); // transmit to device #4
  Wire_write(B11111111);              // sends one byte 
  Wire_endTransmission();    // stop transmitting
  Wire_requestFrom(adres, 1);// silinecek**********************************
  temp1 = Wire_read();
  delay(300);
  temp1=254;
}
void anim(){
    Wire_beginTransmission(adres);
  Wire_write(temp1);
   Wire_endTransmission(); 
  
  Serial_println_ub(temp1, BIN);
   temp1=temp1 << 1;
  
 // temp1=temp1+2;
//  Serial_println(temp1, DEC);
  delay(1000);
 if (temp1==0){
    temp1=127;
    Wire_beginTransmission(adres);
  Wire_write(temp1);
   Wire_endTransmission();
     Serial_println_ub(temp1, BIN);
    delay(1000);
 Wire_beginTransmission(adres);
  Wire_write(B10000000);
   Wire_endTransmission(); 
   delay(1000);
    oku();
    temp1=254;
    
  }
}

void oku(){
  // wait keypress  // INT = HIGH olabilmesi için 1 kere read komutu çalışmalı sonrasında INT her butona basışta LOW olacaktır. 
                    //  ayrıca çıkışı değiştirdiğimizde INT=LOW olacaktır. 
  //while (digitalRead(2) == 0) {

 Wire_beginTransmission(adres);
  Wire_write(B00000011);
   Wire_endTransmission(); 
  Wire_requestFrom(adres, 1);
  temp2 = Wire_read();
  
  
  Serial_print_s("ANAHTAR Konumu Binary: ");
  Serial_println_ub(temp2, BIN);
  Serial_print_s("ANAHTAR Konumu HEX: ");
  Serial_println_ub(temp2, HEX);
  
  delay(1000);
 
  
}

void loop()
{
 /*
 int val=digitalRead(2); 
  if (val==0){
    oku();
    delay(1000);
  }
 */
 
 anim();
 
}


