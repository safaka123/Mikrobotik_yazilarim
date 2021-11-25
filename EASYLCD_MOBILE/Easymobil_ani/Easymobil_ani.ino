// Arduino EASYLCD kullan. Proteus simülatöründe. Software serial. ATMEGA 328 entegre kullanıldı.  
  #include <SoftwareSerial.h>
  
  SoftwareSerial mySerial(10, 11); // RX, TX
     int a = 0;   // değişken
 //  int b = 5;   // değişken
 //     String SATIR ="";
 //     String SUTUN= "";
 //     String KOMUT="";
   //   String stringOne ="denek";
      String stringThree = "LCDWR 1,1-";
       String YAZI ="";
 //     String stringnew =  String(53, HEX);
 //     int thisByte = 3;
      
 String readString="";
      
      
  void setup() {
    // Open serial communications and wait for port to open:
    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
    delay(100);
    //mySerial.println("Arduino Easymobile Animasyon");
    Serial.begin(9600);
  Serial.println("Arduino Easymobile Animasyon");
  }
 
 
 
 void EkranHex(){
       
       // mySerial.print(stringThree);
         //char inChar = (char) mySerial.read();
 //        char inChar ;
 //         while (inChar != 'R'){
 //         inChar = (char) mySerial.read();
    
 //   if (inChar !=""){
 //   readString += inChar;
 //   }
readString="";
while (mySerial.available()) {
    delay(5);  //small delay to allow input buffer to fill
    char c = mySerial.read();  //gets one byte from serial buffer
     
    readString += c;
    if (readString == "LCD R") {
      Serial.println(readString);
      break; //breaks out of capture loop to print readstring
    } 
if (readString == "LCD P") {
      Serial.print(readString);Serial.println(" HATALI SONUC");
      break; //breaks out of capture loop to print readstring
    } 
 
        }
        Serial.println(readString);
   delay(100); // ********* Animasyon hızlı olursa bununla yavaşlatabilirsiniz. 
  
    }
  void EkranYaz(){
      
        mySerial.print(stringThree);
         //char inChar = (char) mySerial.read();
 //        char inChar ;
 //         while (inChar != 'R'){
 //         inChar = (char) mySerial.read();
  
  //if (inChar !=""){
  //  readString += inChar;
  //  }
while (mySerial.available()) {
    delay(5);  //small delay to allow input buffer to fill
    char c = mySerial.read();  //gets one byte from serial buffer
     
    readString += c;
    if (readString == "LCD R") {
      break; //breaks out of capture loop to print readstring
    } 
  }
  Serial.println(readString);
  delay(500);
  readString="";
    }
 
  
  void loop() {                                           
   
      if ( a == 1 ) {stringThree= "LCDDD";EkranYaz();delay(100); };    // Display Delete = Screen Clear
      //if ( a == 2 ) {a=a+1; stringThree= "LCDEW 5-";mySerial.print(stringThree);mySerial.write(0x0E);mySerial.write(0x11);mySerial.write(0x10);mySerial.write(0x10);mySerial.write(0x11);mySerial.write(0x0E);mySerial.write(0x04);mySerial.write(0x01); delay(100);}    // smiley yerine hex değerlerini koy. ****************************
      //if ( a == 3 ) {a=a+1; stringThree= "LCDNC 3-" ; mySerial.print(stringThree); mySerial.write(0x0E);mySerial.write(0x11);mySerial.write(0x10);mySerial.write(0x0E);mySerial.write(0x01);mySerial.write(0x15);mySerial.write(0x0E);mySerial.write(0x04);delay(100);};
                            
      if ( a == 2 ) { YAZI="1.SATIR" ; stringThree= "LCDWR 1,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
      if ( a == 3) { YAZI="2.SATIR" ; stringThree= "LCDWR 2,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
     if ( a == 4) { YAZI="3. SATIR" ; stringThree= "LCDWR 3,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
     if ( a == 5) { YAZI="4. SATIR" ; stringThree= "LCDWR 4,1-"+ YAZI +" ==> "+ a ;EkranYaz(); delay(150); }                                                                                                                                // alt satırda 14 yazıldığında alıcıdan dolayı problem yapıyor
       if ( a == 6 ) {stringThree= "LCDDD";EkranYaz(); };
       
      if ( a == 7) { stringThree= "LCDWR 2,1-HEX ";mySerial.print(stringThree);mySerial.print(65,HEX);mySerial.print(" DEC ");mySerial.print(65,DEC);mySerial.print("(A)"); EkranHex();delay(200);};    //stringThree= "LCDWR 2,14- (A)";mySerial.print(stringThree);EkranHex();
      //if ( a == 7) { stringThree= "LCDWR 2,1-HEX ";mySerial.print(stringThree);mySerial.print(65,HEX); EkranHex();delay(200);stringThree= "LCDWR 2,8-DEC ";mySerial.print(stringThree);mySerial.print(65,DEC); EkranHex();delay(200);stringThree= "LCDWR 2,14-(A)";EkranYaz();};    //stringThree= "LCDWR 2,14- (A)";mySerial.print(stringThree);EkranHex();
  
   if ( a == 8 ) { stringThree= "LCDWR 4,1-A" ; mySerial.print(stringThree); mySerial.write(0xB4);mySerial.print("IK");EkranHex();delay(200);};
      
   //     if ( a == 11) { YAZI="DISP WILL CLOSE " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
   //   if ( a == 12) { stringThree= "LCDDC" ;EkranYaz();  }
   //   if ( a == 13) { YAZI="DISP OPENED     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
   //   if ( a == 14) { stringThree= "LCDDO" ;EkranYaz();  }
    //  if ( a == 15) { YAZI="CUR.BOX    " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
   //   if ( a == 16) { stringThree= "LCDCB" ;EkranYaz();  }
      if ( a == 9) { YAZI="CUR.UNDER  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 10) { stringThree= "LCDCU" ;EkranYaz();  }
      if ( a == 11) { YAZI="CUR.HIDDEN " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 12) { stringThree= "LCDCH" ;EkranYaz();delay(100);  }
      if ( a == 13) { stringThree= "LCDCU" ;EkranYaz();  }
      
      if ( a == 14) { YAZI="CUR SHIFT L<=" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 15) { stringThree= "LCDCL" ;EkranYaz();  }
      if ( a == 16) { stringThree= "LCDCL" ;EkranYaz();  }
      if ( a == 17) { stringThree= "LCDCL" ;EkranYaz();  }
      
      if ( a == 18) { stringThree= "LCDCR" ;EkranYaz();  }
      if ( a == 19) { stringThree= "LCDCR" ;EkranYaz();  }      
      if ( a == 20) { stringThree= "LCDCR" ;EkranYaz();  }  
      if ( a == 21) { YAZI="CUR SHIFT R=>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 22) { stringThree= "LCDCR" ;EkranYaz();  } 
     // if ( a == 30) { YAZI="DISP. SHIFT R==>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
     // if ( a == 31) { stringThree= "LCDSR" ;EkranYaz();  }
     // if ( a == 32) { stringThree= "LCDSR" ;EkranYaz();  }
     // if ( a == 33) { YAZI="DISP. SHIFT L<==" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
     // if ( a == 34) { stringThree= "LCDSL" ;EkranYaz();  }
     // if ( a == 35) { stringThree= "LCDSL" ;EkranYaz();  }
      
      if ( a == 23) { YAZI="CURSOR HOME     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 24) { stringThree= "LCDHO" ;EkranYaz();  }

    // if ( a == 38) { YAZI="BACKLIGHT CLOSE " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
    //  if ( a == 39) { stringThree= "LCDBC" ;EkranYaz();  }
   //   if ( a == 40) { YAZI="BACKLIGHT OPENED " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
   //  if ( a == 41) { stringThree= "LCDBO" ;EkranYaz();  }
      if ( a == 25) { YAZI="BACKLIGHT  %10  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 26) { stringThree= "LCDBL 1" ;EkranYaz();  }      
      if ( a == 27) { YAZI="BACKLIGHT  %90  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 28) { stringThree= "LCDBL 9" ;EkranYaz();  }      
     if ( a == 29) { YAZI="BACKLIGHT  %40  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 30) { stringThree= "LCDBL 4" ;EkranYaz();  }      

     if ( a == 31) { stringThree= "LCDSC 1,180-" ;EkranYaz();  };   // Epromdaki 3. karakteri yeni karakter alanına kopyalar  SWAP CHARACTER(SC)
     if ( a == 32 ) { stringThree= "LCDWR 3,1-A" ; mySerial.print(stringThree); mySerial.write(0xB4); mySerial.print("IK"); EkranHex();delay(200);}
     // if ( a == 46) { YAZI=" READ CH. EPROM" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
    //  if ( a == 47) { stringThree= "LCDER" ;EkranYaz(); delay(100); } 
      if ( a == 33) { YAZI="READ 1 CHARACTER" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();delay(100);  }
     if ( a == 34) { stringThree= "LCDRC 1,14-" ;EkranYaz(); delay(100);  } 
     if ( a == 36) { stringThree= "LCDSC 2,180-" ;EkranYaz();  };
     if ( a == 37) { stringThree= "LCDSC 3,180-" ;EkranYaz();  };
     if ( a == 38) { stringThree= "LCDSC 4,180-" ;EkranYaz();  };
     if ( a == 39) { stringThree= "LCDSC 5,180-" ;EkranYaz();  };
     if ( a == 40) { stringThree= "LCDTW" ;EkranYaz();  };
      //if ( a == 50) { stringThree= "LCDDD" ;EkranYaz(); } 
       if ( a > 50) {a=0 ;}
  
      a=a+1;
    //if ( a >50 ) { YAZI="STARTUP         " ; stringThree= "LCDWR 1,1-"+ YAZI +" ==> "+ a ; EkranYaz();a=0; }
      delay(1000);
 
  }
  

