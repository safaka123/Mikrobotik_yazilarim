String readString;
String bak[5]="";
String denek = "";

__FlashStringHelper *den1 ;
__FlashStringHelper *den2 ;
__FlashStringHelper *den3 ;
__FlashStringHelper *den4 ;
__FlashStringHelper *den5 ;
__FlashStringHelper *den6 ;
__FlashStringHelper *den7 ;
__FlashStringHelper *den8 ;
__FlashStringHelper *den9 ;
__FlashStringHelper *srv1 ;
__FlashStringHelper *srv2 ;
__FlashStringHelper *srv3 ;
__FlashStringHelper *srv4 ;
__FlashStringHelper *srv5 ;
__FlashStringHelper *srv6 ;
__FlashStringHelper *srv7 ;

char * pch;
char * str;
int say=0;
int say2=0;
int x=1;
int bekle=0;
int wc=0;
int prob=0;
int sayac=0;
int saybak=0;

void bakgel(){        // bekleme komutunu tekrar tekrar kullanmak yerine bu şekilde yapıldı hafıza kaplamasın diye. 
  delay(1000);
}

void serverac(){          // ****** server bilgilerini gönder ****************
srv1=F("AT+CWMODE=3");        // F fonksiyonu ile program belleğine gönderildi bu değişkenler. 
srv2=F("AT+CIPMODE=0");
srv3=F("AT+CIPMUX=1");
srv4=F("AT+CWDHCP=2,0");
srv5=F("AT+CIPAP=\"192.168.4.1\"");
srv6=F("AT+CWSAP=\"ESP8266\",\"12345678\",6,4");
srv7=F("AT+CIPSERVER=1,80");
  
  Serial.println("AT+RST");
  delay(5000);
  Serial.println(srv1);
  bakgel();
  Serial.println(srv2);
  bakgel();
  Serial.println(srv3);
  bakgel();
  Serial.println(srv4);
  bakgel();
  Serial.println(srv5);
  bakgel();
  Serial.println(srv6);
  bakgel();
  Serial.println(srv7);
  bakgel();
  
}

void ipdcontrol(){
  
      
      sayac=0;
str = bak[1].c_str(); 
   pch=strstr (str,"IPD");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
    denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
    say=denek.length();           // string uzunluğunu buluruz.
      if (say>0){
        prob=1;
        sayac=1;
        //Serial.print("bak[1]ipdcontrol ") ;Serial.println(bak[1]) ;
        }
      
}



void kontrol(){         // ***************  string ifadesinde 2. bir string ifadeyi bulur yoksa null döndürür. 
//Serial.println(" kontrol") ;
    if (say2==0) {      // bu devamlı buraya geldiğinde işlem yapmadan gitsin diye yapıldı. vakit kaybetmesin
      wc=2;
      denek=bak[2];
      str = bak[2].c_str();   // bu ifade normal string ifadesini const char şekline dönüştürür. normal şekilde const char ifadelere  str=bak[2] şeklinde çeviriyi kabul etmez.
 
      //**********  buton tanımlamaları ***********************
      
     pch=strstr (str,"LIGHT1+ON");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
     denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
     say=denek.length(); // string uzunluğunu buluruz.
        if (say>0){digitalWrite(11,HIGH);
        wc=1;
        //Serial.println(bak[2]) ;
        }
  
     pch=strstr (str,"LIGHT2+ON");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
     denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
     say=denek.length();           // string uzunluğunu buluruz.
       if (say>0){digitalWrite(12,HIGH);wc=1;}
  
     pch=strstr (str,"LIGHT1+OFF");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
     denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
     say=denek.length();           // string uzunluğunu buluruz.
       if (say>0){digitalWrite(11,LOW);wc=1;}
  
    pch=strstr (str,"LIGHT2+OFF");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
    denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
    say=denek.length();           // string uzunluğunu buluruz.
      if (say>0){digitalWrite(12,LOW);wc=1;}

        if (wc==2){
   str = bak[1].c_str(); 
   pch=strstr (str,"IPD");    // 2. string ifadenin bulunduğu yerden itibaren string ifadenin sonuna kadar okur. 
    denek=pch;                      // bu pch  char şeklinde olduğundan bunu string değişkenine çevirip uzunluğunu bulmak istiyoruz.
    say=denek.length();           // string uzunluğunu buluruz.
      if (say>0){
        prob=1;
        //digitalWrite(12,HIGH);
        htmlpage();         // ****  şayet ilk defa web isteği geliyorsa kullanıcıya uygun web sayfasını yollar. 
        wc=1;
        }
   }
        // Serial.println(wc) ;
        // Serial.println(denek) ;
       // Serial.print("bak[1]") ;Serial.println(bak[1]) ;        // ******************** videoda bunları AÇ göster ****************************************************
   //  Serial.println(bak[2]) ;
    bak[1]="";
    bak[2]="";
    say2=1;x=1;bekle=0;
    }
 bekle=0;  
}

void htmlpage(){
 // Serial.println(den1,den2,den3) ;
  Serial.println("AT+CIPSEND=0,450");
         delay(200);
  Serial.print(den1) ;
  Serial.print(den9) ;
  Serial.print(den2) ;
  Serial.print(den3) ;
  Serial.print(den4) ;
  Serial.print(den5) ;
  Serial.print(den6) ;
  Serial.print(den7) ;
  Serial.println(den8) ;
  delay(100);
  prob=0;
}

void setup() {
   Serial.begin(115200);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
 // Serial.println("baslangic");
  say2=1;
  prob=0;
  // **************  aşağıdaki denx değişkenleri saklama alanına F donksiyonu ile gönderiliyor. ******************
  den1 = F("<!DOCTYPE html><html><form action=\"\" method=\"post\">");
  den9 = F("<input type=\"\" name=\"action\" value=\"Butonlari kullanin\" /><br><br>");
  den2 = F("<input id=\"LIGHT1ON\" type=\"submit\" name=\"submit\" value=\"LIGHT1 ON\">");
  den3 = F("<input id=\"LIGHT1OFF\" type=\"submit\" name=\"submit\" value=\"LIGHT1 OFF\">");
  den4 = F("<p><input id=\"LIGHT2ON\" type=\"submit\" name=\"submit\" value=\"LIGHT2 ON\">");
  den5 = F("<input id=\"LIGHT2OFF\" type=\"submit\" name=\"submit\" value=\"LIGHT2 OFF\"></p>");
  den6 = F("</form></html>");
  den7 = F("<?php");
  den8 = F("if (isset($_POST['action'])) {}?>");
   serverac();
}

void loop() {
  if (Serial.available() > 0){
    delay(5);
    lightkontrol();
/*    char c = Serial.read();
               readString += c;
               readString.trim();
    
    if (readString == "+IPD"){
      Serial.println("Ok");
      bak[1]=readString;
      lightkontrol();
       readString="";
    }*/
  }
}

void lightkontrol(){
 sayac=0;bak[1]="";
  readString="";
  basadon:
  say2=0;
  delay(10);
  if (Serial.available() > 0){
    sayac=1;say2=1;
    if (bak[1]==""){
      saybak=0;  
    }
    
while  (Serial.available() > 0){
        char c = Serial.read();
        saybak++;
      

  if (saybak<=20){
        readString += c;
  }
   if (saybak==20){
    bak[1]=readString;
         readString=""; 
    }
  if (saybak>=285 ){
        readString += c;
  }
   
}  
  bak[2]=readString;
  //Serial.print("saybak" );Serial.println(saybak);
  }
  if (sayac==1){
    sayac=0;
    goto basadon;
  }
//Serial.print("say2" );Serial.println(say2);
//Serial.print("bak1light" );Serial.println(bak[1]);
//Serial.print("bak2 light");Serial.println(bak[2]);

kontrol();
}