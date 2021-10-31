// ***************  Arduino ve EASYLCD kullanımı HARDWARE SERIAL************  
 // #include <SoftwareSerial.h>
  
 //                            SoftwareSerial mySerial(10, 11); // RX, TX
     int a = 0;   // değişken
 //  int b = 5;   // değişken
 //     String SATIR ="";
 //     String SUTUN= "";
 //     String KOMUT="";
   //   String stringOne ="denek";
      String stringThree = "";
       String YAZI ="";
     //  char kont;
 //     String stringnew =  String(53, HEX);
 //     int thisByte = 3;
 // char inChar ;    
// boolean newData = false;
      
      
  void setup() {
    // Open serial communications and wait for port to open:
    // set the data rate for the SoftwareSerial port
    //                                             mySerial.begin(19200);
    delay(1000);
    
  Serial.begin(115200);
 // while (!Serial) {
     // wait for serial port to connect. Needed for Leonardo only
//  }
 //Serial.println("Goodnight moon!");
  
  }
 
 
 
 void EkranHex(){
       
  char inChar ; 
          while (inChar == 'R'){
        
         inChar = (char) Serial.read();
    
  }
  delay(1000);
    }
  void EkranYaz(){
          
        Serial.print(stringThree);
char inChar ; 
         while (inChar != 'R'){
            
         inChar = Serial.read();
  }
 delay(1000);
    }


 
  void loop() { // run over and over                                             
   
   stringThree= "LCDDD" ;EkranYaz();
   Serial.print("LCDWR 1,1-1.SATIR ==> ");EkranHex();
   YAZI="2.SATIR" ; stringThree= "LCDWR 2,1-"+ YAZI +" ==> " ;EkranYaz();
  // YAZI="3.SATIR" ; stringThree= "LCDWR 3,1-"+ YAZI +" ==> " ;EkranYaz();
  // YAZI="4.SATIR" ; stringThree= "LCDWR 4,1-"+ YAZI +" ==> " ;EkranYaz();
    stringThree= "LCDWR 1,1-DISP WILL CLOSE " ;EkranYaz();
   stringThree= "LCDDC" ;EkranYaz();
   YAZI="DISP OPENED     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
    stringThree= "LCDDO" ;EkranYaz();
    
   // stringThree= "LCDDD" ;EkranYaz();
   stringThree= "LCDEW 5-";Serial.print(stringThree);Serial.write(0x0E);Serial.write(0x11);Serial.write(0x10);Serial.write(0x10);Serial.write(0x11);Serial.write(0x0E);Serial.write(0x04);Serial.write(0x01); delay(1000);
   stringThree= "LCDNC 3-" ; Serial.print(stringThree); Serial.write(0x0E);Serial.write(0x11);Serial.write(0x10);Serial.write(0x0E);Serial.write(0x01);Serial.write(0x15);Serial.write(0x0E);Serial.write(0x04);delay(1000);
   stringThree= "LCDWR 2,1-A" ; Serial.print(stringThree); Serial.write(0x03);delay(100);stringThree= "LCDWR 2,3-IK            ";Serial.print(stringThree);EkranHex();delay(1500);
  
   YAZI="CUR.UNDER  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
   stringThree= "LCDCU" ;EkranYaz();
   YAZI="CUR.HIDDEN " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
   stringThree= "LCDCH" ;EkranYaz();
    YAZI="CUR.BOX    " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
   stringThree= "LCDCB" ;EkranYaz();
   stringThree= "LCDWR 2,1-HEX ";Serial.print(stringThree);Serial.print(65,HEX); EkranHex();stringThree= "LCDWR 2,8-DEC ";Serial.print(stringThree);Serial.print(65,DEC); EkranHex();stringThree= "LCDWR 2,14-(A)";EkranYaz();
   YAZI="CUR SHIFT L<=" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();EkranYaz();
    stringThree= "LCDCL" ;EkranYaz();
     stringThree= "LCDCL" ;EkranYaz();
    //  stringThree= "LCDCL" ;EkranYaz();
   YAZI="CUR SHIFT R=>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();    
       stringThree= "LCDCR" ;EkranYaz();
       stringThree= "LCDCR" ;EkranYaz();
    //   stringThree= "LCDCR" ;EkranYaz();
    YAZI="DISP. SHIFT R==>" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
      stringThree= "LCDSR" ;EkranYaz();
      stringThree= "LCDSR" ;EkranYaz();
     // stringThree= "LCDSR" ;EkranYaz();
     YAZI="DISP. SHIFT L<==" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
       stringThree= "LCDSL" ;EkranYaz();
       stringThree= "LCDSL" ;EkranYaz();
      // stringThree= "LCDSL" ;EkranYaz();
     YAZI="CURSOR HOME     " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();   
       stringThree= "LCDHO" ;EkranYaz();
     YAZI="BACKLIGHT CLOSE " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
       stringThree= "LCDBC" ;EkranYaz();//delay(1000);
   // YAZI="BACKLIGHT OPENED " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
    Serial.print("LCDWR 1,1-BACKLIGHT OPENED ");EkranHex();
        stringThree= "LCDBO" ;EkranYaz();
      YAZI="BACKLIGHT  %40  " ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz();
       // stringThree= "LCDWR 1,1-BACKLIGHT  %40  ";EkranYaz();
   // Serial.print("LCDWR 1,1-BACKLIGHT  %40  ");EkranHex();
       stringThree= "LCDBL 4" ;EkranYaz();
      // stringThree= "LCDSC 5,3-" ;EkranYaz();  // Epromdaki 3. karakteri yeni karakter alanına kopyalar  SWAP CHARACTER(SC)
      // stringThree= "LCDWR 1,1-A" ; Serial.print(stringThree); Serial.write(0x03);delay(100);stringThree= "LCDWR 1,3-IK          ";EkranYaz();
   
      YAZI="READ 1 CHARACTER" ; stringThree= "LCDWR 1,1-"+ YAZI ;EkranYaz(); 
     //  Serial.print("LCDWR 1,1-READ 1 CHARACTER");EkranHex();delay(1000);
       stringThree= "LCDRC 1,14-" ;EkranYaz();delay(1000);
       stringThree= "LCDCH" ;EkranYaz();
       Serial.print("LCDWR 1,16- ");EkranHex();
    YAZI=" READ CH. EPROM" ; stringThree= "LCDWR 2,1-"+ YAZI ;EkranYaz();
       stringThree= "LCDER" ;EkranYaz(); delay(24000); 


       
 
  
     
 
  
  }
  

