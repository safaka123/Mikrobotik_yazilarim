// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>

#include "DHT.h"

#include <SoftwareSerial.h>    // ************  SADECE PROTEUSTA GÖSTERİLSİN DİYE KULLANILIYOR GERÇEK PROGRAMDA OLMASINA GEREK YOK

SoftwareSerial mySerial(10, 11); // RX, TX

#define DHTPIN 2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

__FlashStringHelper *srv1 ;
__FlashStringHelper *srv2 ;
__FlashStringHelper *srv3 ;
__FlashStringHelper *srv4 ;
__FlashStringHelper *srv5 ;
__FlashStringHelper *srv6 ;
__FlashStringHelper *srv7 ;
__FlashStringHelper *srv8 ;
__FlashStringHelper *srv9 ;
__FlashStringHelper *srv10 ;
__FlashStringHelper *srv11 ;
__FlashStringHelper *srv12 ;
__FlashStringHelper *srv13 ;

String idstr="1";
String tempstr;
String humstr;
String subindata ;
String indata ;
String strdata ;
int say=0;
int say2=0;
int findstart;
int findend;
int incomingByte = 0;
long unsigned int milissay;
int kont=0;
 
// ******   BU SENSOR NUMARASINA GÖRE DEĞİŞECEK.
void sensoku() {
   delay(100);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
      tempstr=String(t);
      humstr=String(h);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    mySerial.println("Failed to read from DHT sensor!");
    return;
  }

  
  mySerial.print("Humidity: ");
  mySerial.print(h);
  mySerial.println(" %\t");
  mySerial.print("Temperature: ");
  mySerial.print(t);
  mySerial.println(" *C ");
  
}

void bakgel(){        // bekleme komutunu tekrar tekrar kullanmak yerine bu şekilde yapıldı hafıza kaplamasın diye. 
  
  while(Serial.available() > 0)
    {
        subindata = Serial.read();

    }
  delay(100); // 1000 delay ver. esp datası yollanırken kullanılıyor. 
  
  
}


void setup() {
  // Initialize serial port
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.println("STARTUP");
 dht.begin();
pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
//  Serial.println("SSIDNO");
//  Serial.println("PASSNO");
      espready();    // *************** son halinde 
} 

// ***** ESP 8266-01 AT KOMUTLARIYLA MODEME BAĞLANTI **********************

void espready() {
srv1=F("AT+CWMODE=3");        // F fonksiyonu ile program belleğine gönderildi bu değişkenler. 
srv2=F("AT+CIPMODE=0");
srv3=F("AT+CIPMUX=1");
srv4=F("AT+CWDHCP=1,0");
srv5=F("AT+CIPSTA=\"192.168.1.140\"");
srv6=F("AT+CWJAP=\"Guest_SSID_1_4A09\",\"misafir1234\"");
srv7=F("AT+CIPSTART=0,\"TCP\",\"www.mikrobotik.com\",80");
srv8=F("AT+CIPSEND=0,66");
srv9=F("GET /api/led/Lreadmysql.php HTTP/1.1");
srv10=F("Host: www.mikrobotik.com");
srv11=F("GET /api/weather/wupdate.php?id=1&hum=28 HTTP/1.1");
srv12=F("Host: www.mikrobotik.com");
  
// Serial.println("AT+RST");  //3000 delay ver
//  delay(2000);
  Serial.println(srv1);
 bakgel();delay(500);
 Serial.println(srv2);
 bakgel();delay(500);
  Serial.println(srv3);
bakgel();delay(500);
  Serial.println(srv4);
  bakgel();delay(500);
 Serial.println(srv5);
  bakgel();delay(500);
  Serial.println(srv6);
  delay(3000);
  bakgel();
  
  
       
}

// **************  GELEN JSON FORMATLI BİLGİNİN AYRIŞTIRILMASI VE UYGULANMASI
 
void jsonpar() {
 mySerial.println("GELEN JSON FORMATLI BiLGi AYRISTIRILIYOR"); 
delay(1000);
  findstart=indata.indexOf("[");
  findend=indata.indexOf("]");
  if (findstart>0){
  subindata=indata.substring(findstart, findend+1);
  indata=subindata;
 
  }
  
//char responseBody[] = R"raw([{"id":"1","status":"on"},{"id":"2","status":"off"},{"id":"3","status":"on"},{"id":"4","status":"on"}],0 closed)raw";  // jsonda kullanılacak formatın tırnak işaretlerini \" yazmaktan kurtarıyor.
// *********************** şayet standart json formatını kopyalayıp gönderme yapılacaksa kullanılabilir.
//"[{\"id\":\"1\",\"status\":\"on\"},{\"id\":\"2\",\"status\":\"off\"},{\"id\":\"3\",\"status\":\"on\"}]"; ** arduinonun anladığı format
char responseBody[150] ;
indata.toCharArray(responseBody, 150); // seri porttan gelen string datayı chararray şekline dönüştürür. data eklendikçe karakter sayısını yükselt.*****

//____________________________________     
const size_t bufferSize = JSON_ARRAY_SIZE(4) + 4*JSON_OBJECT_SIZE(2) + 70;  // BU LİNKTEN FORMATINIZI KONTROL EDİN VE BU SATIRI DEĞİŞTİRİN https://arduinojson.org/v5/assistant/
DynamicJsonBuffer jsonBuffer(bufferSize);

const char* json = responseBody;
JsonArray& root = jsonBuffer.parseArray(json);
JsonArray& root_ = root;

// ****************************************************
const char* root_0_id = root_[0]["id"]; // "1"
mySerial.println(root_0_id);
say=atoi(root_0_id);
const char* root_0_status = root_[0]["status"]; // "on"
mySerial.println(root_0_status);
strdata=String(root_0_status);
if (say==1 && strdata=="on"){
  mySerial.println("LIGHT_1 ON");
  digitalWrite(6, HIGH);
}else if (say==1 && strdata=="off" ){
  mySerial.println("LIGHT_1 OFF");
 digitalWrite(6, LOW);
}
// ****************************************************
const char* root_1_id = root_[1]["id"]; // "2"
say=atoi(root_1_id);
mySerial.println(root_1_id);
const char* root_1_status = root_[1]["status"]; // "off"
mySerial.println(root_1_status);
strdata=String(root_1_status);
if (say==2 && strdata=="on"){
  mySerial.println("LIGHT_2 ON");
  digitalWrite(3, HIGH);
}else if (say==2 && strdata=="off" ){
  mySerial.println("LIGHT_2 OFF");
  digitalWrite(3, LOW);
}
// ****************************************************
const char* root_2_id = root_[2]["id"]; // "3"
say=atoi(root_2_id);
mySerial.println(root_2_id);
const char* root_2_status = root_[2]["status"]; // "off"
mySerial.println(root_2_status);
strdata=String(root_2_status);
if (say==3 && strdata=="on"){
  mySerial.println("LIGHT_3 ON");
  digitalWrite(4, HIGH);
}else if (say==3 && strdata=="off" ){
  mySerial.println("LIGHT_3 OFF");
  digitalWrite(4, LOW);
}
// ****************************************************   4 TEN FAZLA IŞIK VARSA BU KISMI KOPYALAYIP AYARLARINI YAP. **********************
 const char* root_3_id = root_[3]["id"]; // "4"
 say=atoi(root_3_id);
mySerial.println(root_3_id);
const char* root_3_status = root_[3]["status"]; // "on"
mySerial.println(root_3_status);
strdata=String(root_3_status);
if (say==4 && strdata=="on"){
  mySerial.println("LIGHT_4 ON");
  digitalWrite(5, HIGH);
}else if (say==4 && strdata=="off" ){
  mySerial.println("LIGHT_4 OFF");
  digitalWrite(5, LOW);
}
}

void weatherkontrol() {

srv11=F("GET /api/weather/wupdate.php?id=1&hum=28&temp=34 HTTP/1.1");

idstr="1";    // ******************** SENSOR NUMARASINA GORE DEĞİŞECEK ****************************
//tempstr="10";
//humstr="100";
 subindata="GET /api/weather/wupdate.php?id="+idstr+"&temp="+tempstr+" HTTP/1.1";
 strdata=subindata;
 say=subindata.length()+30;
 indata=String (say);
 indata="AT+CIPSEND=0,"+indata;

 mySerial.println(subindata);
 mySerial.println(indata);
delay(200);
  Serial.println(srv7);
  bakgel();delay(1000);
  Serial.println(indata);
   bakgel();delay(500);
    Serial.println(strdata);
   delay(500);
  Serial.println(srv10);
   bakgel();delay(500);
 Serial.println("");
 delay(1500);
 subindata="GET /api/weather/wupdate.php?id="+idstr+"&hum="+humstr+" HTTP/1.1";
 strdata=subindata;
 say=subindata.length()+30;
 indata=String (say);
 indata="AT+CIPSEND=0,"+indata;

 mySerial.println(subindata);
 mySerial.println(indata);
delay(500);
  Serial.println(srv7);
  bakgel();delay(1000);
  Serial.println(indata);
   bakgel();delay(500);
    Serial.println(strdata);
   delay(500);
  Serial.println(srv10);
   bakgel();delay(500);
 Serial.println("");
 delay(500);
// Serial.println("");
bakgel();

}


void webkontrol() {
  kont=0;
 
delay(200);
  Serial.println(srv7);
  bakgel();delay(500);
  Serial.println(srv8);
   bakgel();delay(500);
  Serial.println(srv9);
   bakgel();delay(500);
  Serial.println(srv10);
 bakgel();delay(500);
 Serial.println("");
 //delay(200);
// Serial.println("");



while (kont<1){
 
if(Serial.available() > 0)
    {
        indata = Serial.readStringUntil (']');
       //Serial.println(indata);
       indata =indata+"]";
       
    jsonpar();
       indata="";kont=1;
     }
     
 } 
 mySerial.println ("WEB UZERINDEN KOMUT ALINDI UYGULANDI");

}

void loop() {
milissay=millis();
while (milissay+1000>=millis()){

}
mySerial.println ("");
mySerial.println("WEB SAYFASINDAN BiLGi AL");
webkontrol();
delay(3000);
mySerial.println ("SENSOR OKUNUYOR VE GONDERiLiYOR");

sensoku();
delay(3000);
weatherkontrol();
delay(3000);




}

