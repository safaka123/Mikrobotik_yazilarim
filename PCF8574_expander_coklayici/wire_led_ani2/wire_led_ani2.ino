
#include <Wire.h>
//byte xx = 0;
byte temp1, temp2;

int adres=0x27;

void setup()
{
  temp1=255;
  pinMode(2, INPUT);
  Serial.begin(9600);
  Wire.begin(); 
  Wire.beginTransmission(adres); // transmit to device #4
  Wire.write(B11111111);              // sends one byte 
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(adres, 1);// silinecek**********************************
  temp1 = Wire.read();
  delay(300);
  temp1=254;
}
void anim(){
    Wire.beginTransmission(adres);
  Wire.write(temp1);
   Wire.endTransmission(); 
  
  Serial.println(temp1, BIN);
   temp1=temp1 << 1;
  
 // temp1=temp1+2;
//  Serial.println(temp1, DEC);
  delay(1000);
 if (temp1==0){
    temp1=127;
    Wire.beginTransmission(adres);
  Wire.write(temp1);
   Wire.endTransmission();
     Serial.println(temp1, BIN);
    delay(1000);
 Wire.beginTransmission(adres);
  Wire.write(B10000000);
   Wire.endTransmission(); 
   delay(1000);
    oku();
    temp1=254;
    
  }
}

void oku(){
  // wait keypress  // INT = HIGH olabilmesi için 1 kere read komutu çalışmalı sonrasında INT her butona basışta LOW olacaktır. 
                    //  ayrıca çıkışı değiştirdiğimizde INT=LOW olacaktır. 
  //while (digitalRead(2) == 0) {
 Wire.beginTransmission(adres);
  Wire.write(B00000011);
   Wire.endTransmission(); 
  Wire.requestFrom(adres, 1);
  temp2 = Wire.read();
  
  
  Serial.print("ANAHTAR Konumu Binary: ");
  Serial.println(temp2, BIN);
  Serial.print("ANAHTAR Konumu HEX: ");
  Serial.println(temp2, HEX);
  
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

