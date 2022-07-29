// POT OKUMA İLe seri porttan gönder ve lcd r bekle
// geldiğinde tekrar oku. Hızlı olmasın diye gecikme ver. 
// 10 kez oku ortalama al ve 1 kez yaz. 
// Arduino EASYMOBiL LCD VE BARKOD OKUYUCU. ARDUINO NANO,UNO KULLANILABİLİR
//
// DONANIMSAL SERİ PORT İLE BLUETOOTH BAĞLANACAK.
 // #include <SoftwareSerial.h>
  
 // SoftwareSerial mySerial(10, 11); // RX, TX
  int a = 0;   // değişken
  String stringThree = "LCDWR 1,1-";
  String YAZI ="";     
  String readString="29.12.2021";    
  float sensorValue;

     
  void setup() { //*****************************
  //  mySerial.begin(9600);
  //  delay(100);
    
    Serial.begin(9600);
  //Serial.println("LCDDD");
  stringThree="LCDDD";EkranYaz();
   
      delay(200);
  }

  void EkranYaz(){//*********************************************
   tekrarla:
   readString="";
   int bul=-1;
   int bull=-1;
   int sergel=0;
   Serial.print(stringThree);
 bekle:
   while (Serial.available()) {
    delay(25);  
    char c = Serial.read();  
    readString += c;
    sergel=1;
  } 
 
    bul=readString.indexOf("LCD R");
    bull=readString.indexOf("LCD P");
  if (bul>=0){
  }else if (bull>=0){
    delay(100);
    goto tekrarla;
  }else if (bul<0 && bull<0 && sergel==0){
    delay(100);
    goto bekle;
  }else {
    goto tekrarla; 
  }
    
  delay(100);
  
    }
 
 void ayikla(){//*********************************************

   stringThree=("LCDWR 3,1-");stringThree=stringThree+sensorValue+" A";EkranYaz();
   delay(20);
 }
  
  void loop() {  //***************************************************  
     
      delay(100);
      sensorValue = analogRead(A0);
  sensorValue =sensorValue*(5.0/1023);
   ayikla();    
 delay(100);
  }
  

