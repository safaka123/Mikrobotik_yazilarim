
#include <Wire.h>
//byte xx = 0;
byte temp1, temp2;
int say=0;


void setup()
{
  pinMode(2, INPUT);
  Serial.begin(9600);
  Wire.begin(); 
  Wire.beginTransmission(32); // transmit to device #4
  Wire.write(B00001111);              // sends one byte 
   
  Wire.endTransmission();    // stop transmitting
  
  delay(1000);
}


void oku(){
  // wait keypress  // INT = HIGH olabilmesi için 1 kere read komutu çalışmalı sonrasında INT her butona basışta LOW olacaktır. 
                    //  ayrıca çıkışı değiştirdiğimizde INT=LOW olacaktır. 
  //while (digitalRead(2) == 0) {
   //delay(300);
  Wire.requestFrom(0x20, 1);
  temp1 = Wire.read();
  Wire.endTransmission();
  Serial.println(temp1, BIN);
  
  Serial.print("TEMP1 : ");
  Serial.println(temp1, HEX);
  Serial.print("TEMP222 : ");
  Serial.println(temp2, HEX);
  
  //delay(3000);
 
  temp2 = temp1 << 4 | B00001111;
  Serial.print("TEMP22222 : ");
  Serial.println(temp2, HEX);
  Wire.beginTransmission(0x20);
  Wire.write(temp2);
  Wire.endTransmission();
//  }
 
 Serial.println("sonnnn");
say=say+1;
Serial.print("say : ");
Serial.println(say);
}

void loop()
{
 int val=digitalRead(2); 
  if (val==0){
    
    oku();
    delay(1000);
  }
 
}

