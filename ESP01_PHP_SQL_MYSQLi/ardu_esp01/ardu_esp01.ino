/**************************************************************************************

 php ve msql database ile dünyadan evinizi kontrol edin. ESP01 modülü
 kullanılmıştır. 
 http ile çalıştığından security kütüphanesi dahil edilmedi
 https ile çalıştıracaksanız bu security kütüphanesini dahil edin. 

***************************************************************************************/


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // http web access library


const char *ssid     = "SUPER5960";
const char *password = "5f7JXDQeeYzT";

void setup() {

  Serial.begin(115200);
  delay(500);
  Serial.print("Connecting.");
  Serial.println(ssid);
Serial.println(password);
  WiFi.begin(ssid, password);   // access Wi-FI point

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected\r\n");

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    // specify request destination
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=1041444a18cfb8448343254a45721b1d");
    //http.begin("http://mikrobotikradyo.unaux.com/api2/led/read_db_mysqli2.php?id=1");
    int httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);

    http.end();   //Close connection

  }

  delay(60000);   // wait 1 minute

  }
}
