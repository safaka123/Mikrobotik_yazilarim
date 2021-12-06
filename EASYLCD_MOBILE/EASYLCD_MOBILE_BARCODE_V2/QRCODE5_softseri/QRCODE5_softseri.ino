// Arduino EASYMOBiL LCD VE BARKOD OKUYUCU. ARDUINO NANO,UNO KULLANILABİLİR

// SOFTSERIAL SERİ PORT İLE BLUETOOTH BAĞLANACAK.
  #include <SoftwareSerial.h>
  
  SoftwareSerial mySerial(10, 11); // RX, TX
     int a = 0;   // değişken
 
      String stringThree = "LCDWR 1,1-";
       String YAZI ="";
 
      
 String readString="29.12.2021";
     float bugun;
     float buay;
     float buyil;
     unsigned int  butoplam;
     float gelgun;
     float gelay;
     float gelyil;
    unsigned int  geltoplam; 
    unsigned int  sontoplam;
    int  sonay;  
    String nowdate="";  
    String controlstring=""; 
    int uretsay=0;
    int hurdasay=0;
    int altiaykucuk=0;
     int altiaybuyuk=0;


     
  void setup() { //*****************************
    mySerial.begin(9600);
   delay(100);
    
    Serial.begin(9600);
  Serial.println("LCDDD");
  stringThree="LCDDD";EkranYaz();
   
      delay(200);
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
    delay(25);  //small delay to allow input buffer to fill
    char c = mySerial.read();  //gets one byte from serial buffer
     
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
 
 void ayikla(){//*********************************************
  int temp=-1;
  temp=readString.indexOf('OKUNAN');
  if (temp>=0){
    sontoplam=0;uretsay=uretsay+1;hurdasay=hurdasay+1;
    goto atla;
  }
  temp=nowdate.indexOf('.',0);
  bugun=nowdate.substring(0,temp).toInt();
  int temp1=nowdate.indexOf('.',temp+1);
   buay=nowdate.substring(temp+1,temp1).toInt();
   temp=nowdate.indexOf('-',temp1+1);
   buyil=nowdate.substring(temp1+1,temp-1).toInt(); 
   temp=controlstring.indexOf('.',0);
   gelgun=controlstring.substring(0,temp).toInt();
   temp1=controlstring.indexOf('.',temp+1);
   gelay=controlstring.substring(temp+1,temp1).toInt();
   temp=controlstring.indexOf('-',temp1+1);
   gelyil=controlstring.substring(temp1+1,temp-1).toInt(); 
   butoplam=(((buyil-1900)*365.25)+((buay-1)*30.44)+(bugun-1));
   geltoplam=(((gelyil-1900)*365.25)+((gelay-1)*30.44)+(gelgun-1));
   if (butoplam<geltoplam){sontoplam=geltoplam-butoplam;}
   if (butoplam>geltoplam){sontoplam=butoplam-geltoplam;uretsay=uretsay+1;hurdasay=hurdasay+1;}
   if (butoplam==geltoplam){sontoplam=0;uretsay=uretsay+1;hurdasay=hurdasay+1;}
   if (butoplam < geltoplam && sontoplam >= 183){ uretsay=uretsay+1;altiaybuyuk=altiaybuyuk+1;}
   if (butoplam < geltoplam && sontoplam < 183) {uretsay=uretsay+1;altiaykucuk=altiaykucuk+1;}
   
   sonay=ceil(sontoplam/30.44);
      Serial.println("SONUCLAR");
      Serial.println(nowdate);
     Serial.println(gelgun);
     Serial.println(gelay);
     Serial.println(gelyil);
     Serial.println(bugun);
     Serial.println(buay);
     Serial.println(buyil);
      Serial.println(butoplam);
      Serial.println(controlstring);
      Serial.println(geltoplam);
      Serial.println(sontoplam);
      Serial.println(sonay);
      Serial.println("==========================");
      Serial.println(uretsay);
      Serial.println(hurdasay);
      Serial.println(altiaykucuk);
      Serial.println(altiaybuyuk);
    delay(20);
    atla:
   stringThree=("LCDWR 2,1-HURDASAY : ");stringThree=stringThree+hurdasay+" / "+uretsay+"  ";EkranYaz();
   delay(20);
      stringThree=("LCDWR 3,1-6 AYDA   : ");stringThree=stringThree+altiaykucuk+" / "+uretsay+"  ";EkranYaz();
   delay(20);
      stringThree=("LCDWR 4,1-6 AYSONRA: ");stringThree=stringThree+altiaybuyuk+" / "+uretsay+"  ";EkranYaz();
   delay(20);
   stringThree="LCDWR 1,1-***** SONUCLAR *****";EkranYaz();
  
      delay(20);
 }
  
  void loop() {  //***************************************************  
   
    
      stringThree="LCDTW";EkranYaz();
      nowdate=readString;//.substring(0,10);
     Serial.print("nowdate   ");Serial.println(nowdate);
      delay(200);
       stringThree="BARRD";EkranYaz();
      controlstring=readString;//.substring(0,10);
      Serial.print("controlstring   ");Serial.println(controlstring);
      delay(500);
   ayikla();   

 
 delay(100);// burası sensör yeni ürünü göresiye kadar kapan yap.
 
  }
  

