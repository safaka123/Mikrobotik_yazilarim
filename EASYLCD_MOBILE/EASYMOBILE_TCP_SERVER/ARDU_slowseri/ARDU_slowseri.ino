// Arduino EASYMOBiL LCD VE TCP SERVER. ARDUINO NANO,UNO KULLANILABİLİR

// DONANIMSAL SERİ PORT İLE BLUETOOTH BAĞLANACAK.
  #include <SoftwareSerial.h>
  #define led1 2
  #define led2 3
  #define led3 4
  #define led4 5
  
  SoftwareSerial mySerial(10, 11); // RX, TX
   int a = 0;   // değişken
   String stringThree = "LCDWR 1,1-";
   String YAZI ="";
   String readString="29.12.2021";
   String nowdate="";  
   String controlstring=""; 
 
  void setup() { //*****************************
    mySerial.begin(9600);
   delay(100);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
    
    Serial.begin(9600);
  Serial.println("LCDDD");
  stringThree="LCDDD";EkranYaz();
  delay(200);
  stringThree="LCDWR 1,3-EASYLCD MOBILE";EkranYaz();
  delay(200);
  stringThree="LCDWR 2,2-LCD VE TCP SERVER";EkranYaz();
  delay(200);
  stringThree="LCDWR 3,7-PROJESi";EkranYaz();
  delay(200);
  stringThree="LCDWR 4,2-mikrobotik.com";EkranYaz();
  delay(200);
   stringThree="LCDTW";EkranYaz();
      delay(200);
      nowdate=readString;
  }

  void EkranYaz(){//*********************************************
   tekrarla:
   readString="";
   int bul=-1;
   int bull=-1;
   int sergel=0;
   mySerial.print(stringThree);
 bekle:
   while (mySerial.available()) {
    delay(25); 
    char c = mySerial.read();  
    readString += c;
    sergel=1;
   
  } 
  //Serial.print("readString");Serial.println(readString);
 // Serial.print("sergel");Serial.println(sergel);
    bul=readString.indexOf("LCD R");
    bull=readString.indexOf("LCD P");
  if (bul>=0){
  }else if (bull>=0){
    delay(1000);
    goto tekrarla;
  }else if (bul<0 && bull<0 && sergel==0){
    delay(1000);
    goto bekle;
  }else {
    goto tekrarla; 
  }
    
  delay(500);
  
    }
 
  void loop() {  //***************************************************  
   
    while (mySerial.available()) {
    delay(25); 
    char c = mySerial.read();  
    readString += c;
    
   } 
  
  if(readString.length()>0){
    Serial.println(readString);
  }
  
  if(readString.indexOf("ESPSD 1,1-ON")==0){
    mySerial.print("ESPSD 1,1-ON");
    digitalWrite(led1,HIGH);
  }
  if(readString.indexOf("ESPSD 1,1-OFF")==0){
    mySerial.print("ESPSD 1,1-OFF");
    digitalWrite(led1,LOW);
  }
  if(readString.indexOf("ESPSD 1,2-ON")==0){
    mySerial.print("ESPSD 1,2-ON");
    digitalWrite(led2,HIGH);
  }                 
  if(readString.indexOf("ESPSD 1,2-OFF")==0){
    mySerial.print("ESPSD 1,2-OFF");
    digitalWrite(led2,LOW);
  }
  if(readString.indexOf("ESPSD 1,3-ON")==0){
    mySerial.print("ESPSD 1,3-ON");
    digitalWrite(led3,HIGH);
  }                 
  if(readString.indexOf("ESPSD 1,3-OFF")==0){
    mySerial.print("ESPSD 1,3-OFF");
    digitalWrite(led3,LOW);
  }
  if(readString.indexOf("ESPSD 2,1-ON")==0){
    mySerial.print("ESPSD 2,1-ON");
    digitalWrite(led4,HIGH);
  }                 
  if(readString.indexOf("ESPSD 2,1-OFF")==0){
    mySerial.print("ESPSD 2,1-OFF");
    digitalWrite(led4,LOW);
  }
  if(readString.indexOf("ESPSD 1,1-ALL-ON")==0){
    mySerial.print("ESPSD 1,1-ALL-ON");
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    digitalWrite(led4,HIGH);
  }
if(readString.indexOf("ESPSD 1,1-ALL-OFF")==0){
    mySerial.print("ESPSD 1,1-ALL-OFF");
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
  }


  
  //Serial.print("readString2");Serial.println(readString);
 // Serial.println(readString.indexOf("ESPSD 1,2-ON"));
  readString="";
    
     delay(200);
     
 
  }
  

