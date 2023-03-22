// son eklenen cs1 sensöründeki değer 60 tan fazla ise alarm email gonder. 
// ***************** email sadece 30dk da 2 kez gönderilir. **************
// bunu thingspeak uygulamalarında HTTP request alert request isimli link ile yapıyorum. 
// Profilimde emailim belli. Bu emaile gönderiyor. alert api key kullanılıyor profilden görebilirsiniz. 
// esp httprequest dosyasına oradan da gerçek email alert api keyine gönderiliyor 
// o da email gönderiyor. 


// GA thingspeaktan İFTTT ile okuyabilir. MIT APP INVENTOR ile bilgi gönderip alabilirsiniz. Ev otomasyonu programınıza ekleyebilirsiniz. IFTTT olmadan.
// ayrıca internet bağlantısı sağlanmadıysa Arduino Built in ledi yanık kalacak.  

// ******** Programı deneyerek seri port monitoru kullanmak için kapattığım **********
//**********   tüm Serial satırlarını açın. ************

 
 
 

#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
const char* ssid     = "ZYXEL_SAF";     // your network SSID (name of wifi network)
const char* password = "5f7JXDQeeYzT"; // your network password


const char*  server ="api.thingspeak.com";// "script.google.com";  // Server URL
WiFiClientSecure client;
String cs1="";
String cs2="";
String cs3="";
String cs4="";
String cs5="";
String cs6="";
String cs7="";
String cs8="";
String URL;
String cevap="";

String stringRX="";


void setup() {
  delay(3000);
  Serial.begin(115200);// bağlantı kurunca gpio2 ye bir led bağla. 
 //Serial.println(ssid);
  delay(100);
 
  //Serial.println("Attempting to connect to SSID: ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
//***** thingspeak ile free olarak haberleşme zamanı 15 sn den küçük olmayacak.Olursa limit'e takılırsınız. 
//***** Şayet paralı olursa her saniye güncelleme yapabilirsiniz. 

}

void GONDER(){ // ESP nin URL değişkeni ile belirtilen adresi gönderip cevap alması. 
while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
//****  burada bir zaman sayacı kullan internet yoksa hata verip seri porttan göndersin ve HATA ledi yaksın. 
//**** Bu led gpio2 den olabilir. İnternet ile haberleşemediyse bu led yansın haberleştiğinde sönsün
// Kullanıcı ne olduğunu görsün. Ardu ise hata giderilesiye kadar beklesin ve hata giderildiğinde güncellesin.
    delay(1000);
  }

  //Serial.print("Connected to ");
  //Serial.println(ssid);

  //Serial.println("\nStarting connection to server...");
  client.setInsecure();//skip verification
  if (!client.connect(server, 443))
   //Serial.println("Connection failed!");
   client.setInsecure();//skip verification
  else {
 //   Serial.println("Connected to server!");
 
 // Make a HTTP request:

    client.println(URL);
    
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        //Serial.println("headers received");
        break;
      }
    }

    // sunucudan gelen cevap değişkenine atanır. 
   cevap="";
    while (client.available()) {
      char c = client.read();
      //Serial.write(c);
      cevap=cevap+c;
      
    }
    //Serial.println("");
    //Serial.println("cevap");
    //Serial.println(cevap);
    client.stop();
  } 
}

void seripar() {// ardu dan gelen seri port bilgisi parçalanarak field değişkenleri ayrılır. Tek seferde yazılır okunur.
int say=4;
int say1=0;
say=stringRX.indexOf("W");// bu satır WO ile gelen satırda parazitten dolayı bir ekleme varsa
                                 //bunu iptal et demek için yapıldı. Mesela ?-!<WO:0,0,0,0,0,0,0,0> gibi gelirse
                                 // ilk sütun <WO sütunu olacağından işlem hata yapmayacak. 
say=say+3;
say1=stringRX.indexOf(",",say);
cs1=stringRX.substring(say,say1);// say=4 say1=6  olduğunda 4. 5. karakteri alır 6. karakteri almaz. 
//Serial.println(cs1);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs2=stringRX.substring(say+1,say1);
//Serial.println(cs2);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs3=stringRX.substring(say+1,say1);
//Serial.println(cs3);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs4=stringRX.substring(say+1,say1);
//Serial.println(cs4);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs5=stringRX.substring(say+1,say1);
//Serial.println(cs5);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs6=stringRX.substring(say+1,say1);
//Serial.println(cs6);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs7=stringRX.substring(say+1,say1);
//Serial.println(cs7);
say=say1;
say1=stringRX.indexOf(">",say+1);
cs8=stringRX.substring(say+1,say1);
//Serial.println(cs8);
delay(200);
}


void URLYAP() {


//Ardudan gelen bilgi formatı stringRX="<RO:10,11,12,20,23,24,25,26>";
int akt=0;

//Serial.println(stringRX);
akt=stringRX.indexOf("WS:");// SENSÖR BİLGİLERİNİ THINGSPEAK SİTESİNE GÖNDERME. 
if (akt>0){
 
  seripar();// arduinodan gelen seri bilgiyi parçalar. 
  
  int senscontrol=cs1.toInt();// cs1 string değişkeni. bunu int değişkenine çeviriyoruz.
   
  if (senscontrol>60){// **** cs1 değişkenindeki sensör değeri 60tan büyükse alarm email ver. 
    URL="GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=7YKN63N1ZR7DGMJV HTTP/1.0";
    
  GONDER();
  delay(200);
  }
  // WS sensör kanalına yazma olduğundan kanalın yazma apikey kullanıldı.
 URL="GET https://api.thingspeak.com/update?api_key=YP3I8CIVOENRW51U&field1="+cs1+"&field2="+cs2+"&field3="+cs3+"&field4="+cs4+"&field5="+cs5+"&field6="+cs6+"&field7="+cs7+"&field8="+cs8+" HTTP/1.0";  
 // Serial.println(URL); 
  akt=0;
  GONDER();
  delay(15000);
  Serial.println("<READY>"); 
}

akt=stringRX.indexOf("WO:");
  if (akt>0){
  delay(100);
  seripar();//arduinodan gelen seri bilgiyi parçalar.
  
  // WO OUTPUT kanalına yazma olduğundan kanalın yazma apikey kullanıldı.
 URL="GET https://api.thingspeak.com/update?api_key=7Z4I8Q9QOJHGPQE9&field1="+cs1+"&field2="+cs2+"&field3="+cs3+"&field4="+cs4+"&field5="+cs5+"&field6="+cs6+"&field7="+cs7+"&field8="+cs8+" HTTP/1.0";  
  //Serial.println(URL); 
  akt=0;
  GONDER();
  delay(15000);
  Serial.println("<READY>");
  }
akt=stringRX.indexOf("RS:");
  if (akt>0){
// sadece okuma yapılıyor. SENSÖR kanalından 
 URL="GET https://api.thingspeak.com/channels/2053406/feeds.json?api_key=LMEY4F3VNKHTFBDK&results=1 HTTP/1.0";
  //Serial.println(URL); 
  akt=0;

  GONDER();
  delay(100);
// gelen veriyi ayıkla kısmına gönder ve her field numarasına göre bir seri bilgi oluşturup arduinoya göndersin. 
  GELPAR();
  String sergonder="<RS:"+cs1+","+cs2+","+cs3+","+cs4+","+cs5+","+cs6+","+cs7+","+cs8+">";
  Serial.println(sergonder);// arduinoya gönderiliyor.
  delay(1000);
  Serial.println("<READY>");
  }
akt=stringRX.indexOf("RO:");
  if (akt>0){
  // sadece okuma yapılıyor output kanalından.   
  URL="GET https://api.thingspeak.com/channels/2053404/feeds.json?api_key=LQLK5X78VS3YEY63&results=1 HTTP/1.0";
  //Serial.println(URL); 
  akt=0;

  GONDER();
  delay(100);
  // gelen veriyi ayıkla kısmına gönder ve her field numarasına göre bir seri bilgi oluşturup arduinoya göndersin. 
  GELPAR();
    String sergonder="<RO:"+cs1+","+cs2+","+cs3+","+cs4+","+cs5+","+cs6+","+cs7+","+cs8+">";
  Serial.println(sergonder);// Arduinoya gönderiliyor.
  delay(1000);
  Serial.println("<READY>");
  } 
}

void GELPAR(){ // RO ve RS dediğimiz kanalların thingspeaktan okunan bilgilerin parçalanması yapılır. 
  //CS değişkenlerine aktarılacak. 
  // gelen RO datası 
  // {"channel":{"id":2053404,"name":"OUTPUTS_1","description":"Bütün lamba ve prizler 1. bölüm","latitude":"0.0","longitude":"0.0","field1":"3","field2":"1","field3":"1","field4":"1","field5":"1","field6":"1","field7":"1","field8":"1","created_at":"2023-03-05T13:02:18Z","updated_at":"2023-03-06T21:25:50Z","last_entry_id":8},"feeds":[{"created_at":"2023-03-08T08:30:38Z","entry_id":8,"field1":"40","field2":"41","field3":"42","field4":"43","field5":"44","field6":"45","field7":"46","field8":"47"}]}
  // gelen RS datası 
  // {"channel":{"id":2053406,"name":"INPUTS_1","description":"Tüm sensörler buraya bağla. ayrıca REACTburaya göre kur. ALARM kur. ","latitude":"0.0","longitude":"0.0","field1":"sensor 1","field2":"mutfak sensör","field3":"gaz sensör","field4":"ortam sıcaklık","field5":"nem 1","field6":"nem2","field7":"ışık sensörü","field8":"su sensör","created_at":"2023-03-05T13:10:36Z","updated_at":"2023-03-07T12:19:45Z","last_entry_id":6},"feeds":[{"created_at":"2023-03-08T09:56:53Z","entry_id":6,"field1":"30","field2":"31","field3":"32","field4":"33","field5":"34","field6":"35","field7":"36","field8":"37"}]}
int say=0;
int say1=0;
int akt=0;
 say=cevap.indexOf("feeds");
say1=cevap.indexOf("field1",say);
say=cevap.indexOf(",",say1);//say1 98 ise 98-2 yap 1 geride " var ondan öncesini de kabul etmediği için.
cs1=cevap.substring(say1+9,say-1);
//Serial.println(cs1); 


say1=cevap.indexOf("field2",say);
say=cevap.indexOf(",",say1);
cs2=cevap.substring(say1+9,say-1);
//Serial.println(cs2); 


say1=cevap.indexOf("field3",say);
say=cevap.indexOf(",",say1);
cs3=cevap.substring(say1+9,say-1);
//Serial.println(cs3); 


say1=cevap.indexOf("field4",say);
say=cevap.indexOf(",",say1);
cs4=cevap.substring(say1+9,say-1);
//Serial.println(cs4); 


say1=cevap.indexOf("field5",say);
say=cevap.indexOf(",",say1);
cs5=cevap.substring(say1+9,say-1);
//Serial.println(cs5); 


say1=cevap.indexOf("field6",say);
say=cevap.indexOf(",",say1);
cs6=cevap.substring(say1+9,say-1);
//Serial.println(cs6); 


say1=cevap.indexOf("field7",say);
say=cevap.indexOf(",",say1);
cs7=cevap.substring(say1+9,say-1);
//Serial.println(cs7); 


say1=cevap.indexOf("field8",say);
say=cevap.indexOf("}",say1);
cs8=cevap.substring(say1+9,say-1);
//Serial.println(cs8); 
delay(200);
}


void loop() {

  stringRX="";
if (Serial.available() > 0) { // Arduinodan gelen komutların alınması. 
    stringRX = Serial.readString(); // Serial Porttaki girdi değerini oku ve string e ata.
    //Serial.println("");
    //Serial.println(stringRX); // okunan değeri ekrana yazdır.
  }
    
  if(stringRX!=""){  //stringRX boş değilse işlemler başlar. 
    URLYAP(); 
   // Serial.println("<READY>");   
  }
  
  // Thingspeak erişimi free plana göre  15 sn den küçük olmayacak. 
  // Şayet paralı olursa her saniye güncellenir.
/*  uint32_t newtime=0;
  newtime=millis()+5000;
  int saysay=0;
  Serial.println(newtime);
  while(millis()<newtime){
        //wait approx. [period] ms
delay (1000);
saysay=1;
    }
  
  Serial.println(millis());
  Serial.println(saysay);
  if (saysay==1){
    Serial.println(URL="GET https://api.thingspeak.com/channels/2053404/feeds.json?api_key=LQLK5X78VS3YEY63&results=1 HTTP/1.0"); 
    //GONDER();
    
  }
  */
  delay(100);
}
