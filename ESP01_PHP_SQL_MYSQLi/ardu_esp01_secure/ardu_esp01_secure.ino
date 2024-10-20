/**************************************************************************************

 php ve msql database ile dünyadan evinizi kontrol edin. ESP01 modülü
 kullanılmıştır. 
 http ile çalıştığından security kütüphanesi dahil edilmedi
 https ile çalıştıracaksanız bu security kütüphanesini dahil edin. 

***************************************************************************************/
#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
const char* ssid     = "SUPER5960";     // your network SSID (name of wifi network)
const char* password = "5f7JXDQeeYzT"; // your network password
String URL;
String cevap="";
//URL:https://www.mikrobotik.com/api2/led/read_tek.php
//GET /api2/led/read_tek.php HTTP/1.1
// örnek URL="GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=7YKN63N1ZR7DGMJV HTTP/1.0";

const char*  server ="www.mikrobotik.com";// "script.google.com";  // Server URL

WiFiClientSecure client;


// HTTP/1.1 YAP
void setup() {
  delay(3000);
  Serial.begin(115200);// bağlantı kurunca gpio2 ye bir led bağla. 
 //Serial.println(ssid);
  delay(100);
 
  //Serial.println("Attempting to connect to SSID: ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);
}

void GONDER(){ // ESP nin URL değişkeni ile belirtilen adresi gönderip cevap alması. 
while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
//****  burada bir zaman sayacı kullan internet yoksa hata verip seri porttan göndersin ve HATA ledi yaksın. 
//**** Bu led gpio2 den olabilir. İnternet ile haberleşemediyse bu led yansın haberleştiğinde sönsün
// Kullanıcı ne olduğunu görsün. Ardu ise hata giderilesiye kadar beklesin ve hata giderildiğinde güncellesin.
    delay(1000);
  }

  //Serial.print("Connected to ");
  //Serial.println(ssid);

  Serial.println("\nStarting connection to server...");
  client.setInsecure();//skip verification
  if (!client.connect(server, 443))
   //Serial.println("Connection failed!");
   client.setInsecure();//skip verification
  else {
    Serial.println("Connected to server!");
 
    Serial.println("Make a HTTP request:");

    client.println(URL);
    
    client.println("Host: www.mikrobotik.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
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
    Serial.println("cevap");
    Serial.println(cevap);
    client.stop();
  } 
}

// URL="GET https://www.mikrobotik.com/api2/led/read_tek_mysqli2.php HTTP/1.0";// HTTP/1.1 YAP

void loop() {
  URL="GET https://www.mikrobotik.com/api2/led/read_tek_mysqli2.php HTTP/1.0";
  
  delay (10000);
  GONDER();
}

  
