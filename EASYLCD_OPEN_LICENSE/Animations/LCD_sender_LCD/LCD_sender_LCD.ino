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
      
 
      
      
  void setup() {
    // Open serial communications and wait for port to open:
    // set the data rate for the SoftwareSerial port
    mySerial.begin(19200);
    delay(100);
    
 // Serial.begin(19200);
 // while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
//  }
 // Serial.println("Goodnight moon!");
  
  }
 
 
 
 void EkranHex(){
       
       // mySerial.print(stringThree);
         //char inChar = (char) mySerial.read();
         char inChar ;
          while (inChar != 'R'){
          inChar = (char) mySerial.read();
    //    Serial.write(inChar);
  }
  delay(10); // ********* Animasyon hızlı olursa bununla yavaşlatabilirsiniz. 
    }
  void EkranYaz(){
       
        mySerial.print(stringThree);
         //char inChar = (char) mySerial.read();
         char inChar ;
          while (inChar != 'R'){
          inChar = (char) mySerial.read();
  //      Serial.write(inChar);
  
  }
  delay(10);
    }
 
      // örnek istenirse yukarıda tanımlanan smiley kullanılabilir ;  if ( a == 2 ) {a=a+1; stringThree= "LCDEW 5-";mySerial.print(stringThree);mySerial.write(smiley[0]);mySerial.write(smiley[1]);mySerial.write(smiley[2]);mySerial.write(smiley[3]);mySerial.write(smiley[4]);mySerial.write(smiley[5]);mySerial.write(smiley[6]);mySerial.write(smiley[7]); delay(100);}    // smiley yerine hex değerlerini koy. ****************************    
 
 
 
 
 
 
  
  void loop() { // run over and over                                             
   
      if ( a == 1 ) {stringThree= "LCDDD";EkranYaz();delay(100); };    // Display Delete = Screen Clear
      if ( a == 2 ) {a=a+1; stringThree= "LCDEW 5-";mySerial.print(stringThree);mySerial.write(0x0E);mySerial.write(0x11);mySerial.write(0x10);mySerial.write(0x10);mySerial.write(0x11);mySerial.write(0x0E);mySerial.write(0x04);mySerial.write(0x01); delay(100);}    // smiley yerine hex değerlerini koy. ****************************
      if ( a == 3 ) {a=a+1; stringThree= "LCDNC 3-" ; mySerial.print(stringThree); mySerial.write(0x0E);mySerial.write(0x11);mySerial.write(0x10);mySerial.write(0x0E);mySerial.write(0x01);mySerial.write(0x15);mySerial.write(0x0E);mySerial.write(0x04);delay(100);};
      if ( a == 4 ) {a=a+1; stringThree= "LCDWR 1,1-A" ; mySerial.print(stringThree); mySerial.write(0x03);delay(10);stringThree= "LCDWR 1,3-IK";EkranYaz();delay(150);};
      if ( a == 5 ) { YAZI="1.SATIR" ; stringThree= "LCDWR 1,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
      if ( a == 6) { YAZI="2.SATIR" ; stringThree= "LCDWR 2,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
     if ( a == 7) { YAZI="3. SATIR" ; stringThree= "LCDWR 3,1-"+ YAZI +" ==> "+ a ; EkranYaz(); }
     if ( a == 8) { YAZI="4. SATIR" ; stringThree= "LCDWR 4,1-"+ YAZI +" ==> "+ a ;EkranYaz();  }                                                                                                                                // alt satırda 14 yazıldığında alıcıdan dolayı problem yapıyor
       if ( a == 9 ) {stringThree= "LCDDD";EkranYaz(); };
      if ( a == 10) { stringThree= "LCDWR 2,1-HEX ";mySerial.print(stringThree);mySerial.print(65,HEX); EkranHex();stringThree= "LCDWR 2,8-DEC ";mySerial.print(stringThree);mySerial.print(65,DEC); EkranHex();stringThree= "LCDWR 2,14-(A)";EkranYaz();};    //stringThree= "LCDWR 2,14- (A)";mySerial.print(stringThree);EkranHex();
        if ( a == 11) { YAZI="DISP WILL CLOSE " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 12) { stringThree= "LCDDC" ;EkranYaz();  }
      if ( a == 13) { YAZI="DISP OPENED     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 14) { stringThree= "LCDDO" ;EkranYaz();  }
      if ( a == 15) { YAZI="CUR.BOX    " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 16) { stringThree= "LCDCB" ;EkranYaz();  }
      if ( a == 17) { YAZI="CUR.UNDER  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 18) { stringThree= "LCDCU" ;EkranYaz();  }
      if ( a == 19) { YAZI="CUR.HIDDEN " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 20) { stringThree= "LCDCH" ;EkranYaz();delay(100);  }
      if ( a == 21) { stringThree= "LCDCB" ;EkranYaz();  }
      
      if ( a == 22) { YAZI="CUR SHIFT L<=" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 23) { stringThree= "LCDCL" ;EkranYaz();  }
      if ( a == 24) { stringThree= "LCDCL" ;EkranYaz();  }
      if ( a == 25) { stringThree= "LCDCL" ;EkranYaz();  }
      if ( a == 26) { YAZI="CUR SHIFT R=>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 27) { stringThree= "LCDCR" ;EkranYaz();  }
      if ( a == 28) { stringThree= "LCDCR" ;EkranYaz();  }      
      if ( a == 29) { stringThree= "LCDCR" ;EkranYaz();  }  
      if ( a == 30) { YAZI="DISP. SHIFT R==>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 31) { stringThree= "LCDSR" ;EkranYaz();  }
      if ( a == 32) { stringThree= "LCDSR" ;EkranYaz();  }
      if ( a == 33) { YAZI="DISP. SHIFT L<==" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 34) { stringThree= "LCDSL" ;EkranYaz();  }
      if ( a == 35) { stringThree= "LCDSL" ;EkranYaz();  }
      
      if ( a == 36) { YAZI="CURSOR HOME     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 37) { stringThree= "LCDHO" ;EkranYaz();  }

     if ( a == 38) { YAZI="BACKLIGHT CLOSE " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 39) { stringThree= "LCDBC" ;EkranYaz();  }
      if ( a == 40) { YAZI="BACKLIGHT OPENED " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
     if ( a == 41) { stringThree= "LCDBO" ;EkranYaz();  }
  //    if ( a == 42) { YAZI="BACKLIGHT  %10  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
  //    if ( a == 43) { stringThree= "LCDBL 1" ;EkranYaz();  }      
  //    if ( a == 44) { YAZI="BACKLIGHT  %90  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
   //   if ( a == 45) { stringThree= "LCDBL 9" ;EkranYaz();  }      
     if ( a == 42) { YAZI="BACKLIGHT  %40  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 43) { stringThree= "LCDBL 4" ;EkranYaz();  }      

     if ( a == 44) { stringThree= "LCDSC 5,3-" ;EkranYaz();  }   // Epromdaki 3. karakteri yeni karakter alanına kopyalar  SWAP CHARACTER(SC)
      if ( a == 45 ) {a=a+1; stringThree= "LCDWR 1,1-A" ; mySerial.print(stringThree); mySerial.write(0x03);delay(10);stringThree= "LCDWR 1,3-IK          ";mySerial.print(stringThree);delay(200);};
      if ( a == 46) { YAZI=" READ CH. EPROM" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();  }
      if ( a == 47) { stringThree= "LCDER" ;EkranYaz(); delay(100); } 
      if ( a == 48) { YAZI="READ 1 CHARACTER" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();delay(100);  }
     if ( a == 49) { stringThree= "LCDRC 1,14-" ;EkranYaz(); delay(100);  } 
     
      if ( a == 50) { stringThree= "LCDDD" ;EkranYaz(); } 

 
      

  
 
  
      a=a+1;
    if ( a >50 ) { YAZI="STARTUP         " ; stringThree= "LCDWR 1,1-"+ YAZI +" ==> "+ a ; EkranYaz();a=0; }
      delay(10);
    
  
     
 
  
  }
  

