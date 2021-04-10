
// Copyright 2012 by Zipwhip.
// You are free to use and modify this code in your own software.

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

#define motor1_pin         8  // 26 or 39. Any pin on the Arduino or Mega will work.
#define motor2_pin         9  // 26 or 39. Any pin on the Arduino or Mega will work.
float ham1;
float ham2;
float temp1;
float temp2;
int temp3;
float derece;
int motor1;
int motor2;
int potpin1 = 0;  // analog pin used to connect the potentiometer
int potpin2 = 1;
String seral="";
String Red="";
String Green="";
String Blue="";
String Topx="";
String Topy="";
int red=0;
int green=0;
int blue=0;
int topx=0;
int topy=0;



void startpos(){
  for (int i = 0; i <=3; i++) {
   digitalWrite (motor1_pin,HIGH);
 delayMicroseconds(1500);
 digitalWrite (motor1_pin,LOW);
 delay(20); 
  }
  delay(500);
}
void degispos(){
  for (int i = 0; i <=3; i++) {
   digitalWrite (motor1_pin,HIGH);
 delayMicroseconds(temp1);
 digitalWrite (motor1_pin,LOW);
 delay(25); 
  }
  
}

void motorayar(){
// ****************** 1. motor ayarı *************************************** 

 //for (int i = 0; i <= 210; i=i+10) {
 //ham1=i;
 temp1=(2000000/200)*0.001;  // 2000usn /200 yapılarak her derece kaç usn eklenecek bulunur. 
 Serial.print("Zaman  : ");Serial.print(temp1);
 temp1=ham1*temp1;
 
 temp1=500+temp1;  // servo high sinyali 0.99ms den büyük 2.01ms den küçük olmalı. 
 Serial.print("Zaman  : ");Serial.print(temp1);
 Serial.print("   derece  : ");Serial.println(ham1);Serial.println(" ");
 degispos();
 //*****************  dönüş zamanını bitirdikten sonra home pozisyonuna dönecek ve kameradan yeni veri isteyecek. **************
 
 delay(1250);  
// }
  
}


void hesapla(){
 //seri port gelen bilgi : 211,76,103,187,279-  sağda duran
 //                         217,70,83,319,277-   solda duran
// string to int int degisken=inString.toInt()
//*********************************************************************String ham0="211,76,103,300,279-";
// seri porttan gelen string datayı parçalayarak int şekline çevirir. 
String ham0=seral;
int birbul = ham0.indexOf(',');

Red=ham0.substring(0,birbul); 
Serial.print("KIRMIZI : ");Serial.println(Red);
int ikibul = ham0.indexOf(',',birbul+1);

Green=ham0.substring(birbul+1,ikibul); 
Serial.print("YESiL : ");Serial.println(Green);
birbul=ham0.indexOf(',',ikibul+1);

Blue=ham0.substring(ikibul+1,birbul); 
Serial.print("MAVi : ");Serial.println(Blue);
ikibul = ham0.indexOf(',',birbul+1);

Topx=ham0.substring(birbul+1,ikibul); 
Serial.print("KOOR-X : ");Serial.println(Topx);
birbul=ham0.indexOf('-',ikibul+1);

Topy=ham0.substring(ikibul+1,birbul); 
Serial.print("KOOR-Y : ");Serial.println(Topy);
red=Red.toInt();
green=Green.toInt();
blue=Blue.toInt();
topx=Topx.toInt();
topy=Topy.toInt();

  if (topx<=250){
    temp3=(100-((250-topx)/3.4));
    Serial.print("sola git : ");Serial.println(temp3);
  }
  if (topx>250){
   temp3=((topx-250)/3.4)+100;
   Serial.print("saga git : ");Serial.println(temp3);
  }
ham1=temp3;
//ham1=73;

}

void setup()
{
  pinMode(motor1_pin, OUTPUT);
  pinMode(motor2_pin, OUTPUT);
  Serial.begin(9600);
   
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  

}

void loop()
{
 //******************* her butona basışta OK işareti yollayarak yeni veri isteyecek. ******************
 
if (mySerial.available()) {
  seral = mySerial.readString();
    Serial.println(seral);
    hesapla();
    motorayar();
    delay(1000);
    startpos();
    delay(1000);
    Serial.println("OK");
    mySerial.println("OK");
    delay(1000);
  }
  /*   hesapla();
    motorayar();
    delay(3000);
    startpos();
    delay(1000);
    Serial.println("OK");
    delay(1000);
  */
}
