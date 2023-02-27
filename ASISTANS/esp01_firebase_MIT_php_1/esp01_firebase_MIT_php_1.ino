
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

 
const char* ssid = "ZYXEL_SAF";
const char* password = "5f7JXDQeeYzT";
String gelen="";
String Mlamba1="";
String Mlamba2="";
String Olamba1="";
String Olamba2="";
String URL="";
int lastsw1=1;
int lastsw2=1;
int sw1=0;
int sw2=0;
int sayconnect=0;

#define RelayPin1 0  //gpio 0 OUTPUT // gpio 0 input olarak kullanılacaksa ilk güç verirken HIGH durumda olması lazım. Şayet GND ye bağlanırsa Programlama moduna girer.
#define RelayPin2 1  //gpio 1 TX yerine bir OUTPUT olarak kullanılıyor.Arduino programına göre 
#define SwitchPin1 2  //gpio 2 INPUT
#define SwitchPin2 3   //gpio 3 RX yerine INPUT olarak kullan SW tak. Arduino programına göre ****DİKKAT**** Burada PULL UP direncini 3.3V a bağlayın. 

void setup () {
  
 
  Serial.begin(115200);
// gerçek devrede seri port ipyal ve pimleri devreye al. *************************************************
pinMode(RelayPin1, OUTPUT);
pinMode(RelayPin2, OUTPUT);
pinMode(SwitchPin1, INPUT);
pinMode(SwitchPin2, INPUT);
digitalWrite (RelayPin1,LOW);
digitalWrite (RelayPin2,LOW);

 delay(3000);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite (RelayPin2,HIGH);
    delay(1000);
    sayconnect=sayconnect+1;
    if (sayconnect==20){
      break;
    }
    Serial.println("Connecting..");
    digitalWrite (RelayPin2,LOW);
 
  }
 
}

void newconnect(){  // ilk bağlantı kurulamaz ise tekrar denesin diye yapıldı devreye alınmadı. 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 digitalWrite (RelayPin2,LOW);
    delay(1000);
    Serial.println("Connecting..");
    digitalWrite (RelayPin2,HIGH);
 
  }
}

void swsend(){
    if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    int deger=25;

//String URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=false&komut=oturma/lamba%202";// lamba 2 lamba%202yazıldı. boşluk http ile iletilemediği için %20 boşluk yerine kullanılıyor . bu sadece http request yapılacaksa kullanılıyor. 
    //String URL="http://mikrobotikradyo.tk/api/firebasechange1.php?deger="+String (deger);
  //String URL="http://mikrobotikradyo.tk/api/firebase_read_MIT.php";
  Serial.println(URL);
  
    http.begin(URL);  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
      gelen=payload;
    }
 
    http.end();   //Close connection
 
  }
}

void switchcontrol(){
  sw1=digitalRead(SwitchPin1);
  if(sw1==HIGH){
    Serial.print("switchpin1 durum : HIGH ");Serial.println(sw1);
  }
  if(sw1==LOW){
    Serial.print("switchpin1 durum : LOW ");Serial.println(sw1);
  }
  
  Serial.print("switchpin1 durum : ");Serial.println(sw1);
  Serial.print("lastsw1 durum : ");Serial.println(lastsw1);
  if (lastsw1==sw1){
    
  }else{

    digitalWrite(RelayPin1, !digitalRead(RelayPin1));
     Serial.println(digitalRead(RelayPin1));
     if (digitalRead(RelayPin1)==HIGH){
      Serial.println ("pin1 high");
      URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"true\"&komut=oturma/lamba%201";
      lastsw1=sw1;
      swsend();
     }
     if (digitalRead(RelayPin1)==LOW){
      Serial.println ("pin1 LOW");
      URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"false\"&komut=oturma/lamba%201";
      lastsw1=sw1;
      swsend();
     }
  }
    sw2=digitalRead(SwitchPin2);
  if(sw2==HIGH){
    Serial.print("switchpin2 durum : HIGH ");Serial.println(sw2);
  }
  if(sw2==LOW){
    Serial.print("switchpin2 durum : LOW ");Serial.println(sw2);
  }
  
  Serial.print("switchpin2 durum : ");Serial.println(sw2);
  Serial.print("lastsw2 durum : ");Serial.println(lastsw2);
  if (lastsw2==sw2){
    
  }else{

    digitalWrite(RelayPin2, !digitalRead(RelayPin2));
     Serial.println(digitalRead(RelayPin2));
     if (digitalRead(RelayPin2)==HIGH){
      Serial.println ("pin2 high");
      URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"true\"&komut=oturma/lamba%202";
      lastsw2=sw2;
      swsend();
     }
     if (digitalRead(RelayPin2)==LOW){
      Serial.println ("pin2 LOW");
      URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"false\"&komut=oturma/lamba%202";
      lastsw2=sw2;
      swsend();
     }
  }      
  
  
  
/*  
  if (Olamba1=="true"){
 
      digitalWrite (RelayPin1,LOW);
      Serial.println("SWrelaypin1 LOW");
     URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"false\"&komut=oturma/lamba%201";// lamba 2 lamba%202yazıldı. boşluk http ile iletilemediği için %20 boşluk yerine kullanılıyor . bu sadece http request yapılacaksa kullanılıyor.  
     Serial.println (URL);
     lastsw1=sw1;
     swsend();
    }else{
     URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"true\"&komut=oturma/lamba%201";// lamba 2 lamba%202yazıldı. boşluk http ile iletilemediği için %20 boşluk yerine kullanılıyor . bu sadece http request yapılacaksa kullanılıyor.  
     Serial.println (URL);
      digitalWrite (RelayPin1,HIGH);
      Serial.println("SWrelaypin1 HIGH");
      lastsw1=sw1;
      swsend();
    }
  
      sw2=digitalRead(SwitchPin2);
 
  Serial.print("switchpin2 durum : ");Serial.println(sw2);
  Serial.print("lastsw2 durum : ");Serial.println(lastsw2);
  if (lastsw2==sw2){
    
  }else if (Olamba2=="true"){
 
     digitalWrite (RelayPin2,LOW);
      Serial.println("SWrelaypin2 LOW");
     URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"false\"&komut=oturma/lamba%202";// lamba 2 lamba%202yazıldı. boşluk http ile iletilemediği için %20 boşluk yerine kullanılıyor . bu sadece http request yapılacaksa kullanılıyor.  
     Serial.println (URL);
     lastsw2=sw2;
     swsend();
    }else{
     URL="http://mikrobotikradyo.tk/api/firebasechange_MIT.php?deger=\"true\"&komut=oturma/lamba%202";// lamba 2 lamba%202yazıldı. boşluk http ile iletilemediği için %20 boşluk yerine kullanılıyor . bu sadece http request yapılacaksa kullanılıyor.  
     Serial.println (URL);
      digitalWrite (RelayPin2,HIGH);
      Serial.println("SWrelaypin2 HIGH");
      lastsw2=sw2;
      swsend();
    }
  
  
// swsend();// bunu her sw ayarından sonra yap sw değişmediyse yapma. değiştiğini anlamak için değişken koy bir de 2 gönderim arası delay 5sn
  */
}
 
void loop() {
  
  
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    int deger=25;

    
  URL="http://mikrobotikradyo.tk/api/firebase_read_MIT.php";
  Serial.println(URL);
  
    http.begin(URL);  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
      gelen=payload;
    }
 
    http.end();   //Close connection
    sayconnect=0;
 
  }else{ // 10 kez internet kopuk ise tekrar bağlantı dene dakikada 1 kez deneme
    sayconnect=sayconnect+1;
    if (sayconnect>10){
      newconnect();
    }
  }
// GELEN VERİLERİN AYRILMASI
int say=gelen.indexOf(":");
int say1=gelen.indexOf(":",say+1);
int say2=gelen.indexOf(",",say1+1);
String subgelen=gelen.substring(say1+2, say2-1);
Mlamba1=subgelen;
Serial.println (say);Serial.println(say1);Serial.println(subgelen);
say=gelen.indexOf(":",say2);
say1=gelen.indexOf("},",say+1);
//say2=gelen.indexOf(",",say1+1);
subgelen=gelen.substring(say+2, say1-1);
Serial.println (say);Serial.println(say1);Serial.println(subgelen);
Mlamba2=subgelen;

say=gelen.indexOf(":",say1);
say1=gelen.indexOf(":",say+1);
say2=gelen.indexOf(",",say1+1);
subgelen=gelen.substring(say1+2, say2-1);
Serial.println (say);Serial.println(say1);Serial.println(subgelen);
Olamba1=subgelen;
say=gelen.indexOf(":",say2);
say1=gelen.indexOf("}}",say+1);
//say2=gelen.indexOf(",",say1+1);
subgelen=gelen.substring(say+2, say1-1);
Serial.println (say);Serial.println(say1);Serial.println(subgelen);
Olamba2=subgelen;

//digitalWrite(RelayPin2, !digitalRead(RelayPin2));

if (Olamba1=="true"){
  digitalWrite (RelayPin1,HIGH);
  Serial.println("relaypin1 high");
}else if (Olamba1=="false"){
  digitalWrite (RelayPin1,LOW);
  Serial.println("relaypin1 LOW");
}
if (Olamba2=="true"){
 digitalWrite (RelayPin2,HIGH);
  Serial.println("relaypin2 high");
}else if (Olamba2=="false"){
  digitalWrite (RelayPin2,LOW);
  Serial.println("relaypin2, LOW");
}
switchcontrol();

 
  delay(5000);    //Send a request every 30 seconds
}
