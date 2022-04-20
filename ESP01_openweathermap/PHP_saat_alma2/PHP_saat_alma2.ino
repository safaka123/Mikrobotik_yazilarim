/**************************************************************************************

 Internet weather station using ESP8266 Wi-Fi module
 This is a free software with NO WARRANTY.
 http://simple-circuit.com/

***************************************************************************************/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // http web access library

const char *ssid     = "ZYXEL_SAF";
const char *password = "5f7JXDQeeYzT";
String temp2="";
String temp6="";
String temp7="";
int temp5=0;
int temp1=0;
int temp4=0;
float temp3=0;
String payload="";


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
//==============================================
delay(1000);
    http.begin("http://mikrobotikradyo.ml/api/openweather/clocksade.php");
     int httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code

      payload = http.getString();   //Get the request response payload
      Serial.println(payload);

      delay(5000);
    }
    http.end();   //Close connection

//==============================================    
/* Bu linkten geri dönen bilgi budur.PHP dosyasıyla zamanı elde edip bu şekilde türkçeleştirebiliriz.  
   ESP01 modül bunu aldıktan sonra değişkenlere aktarmalı. Bu program sadece gelen bilgiyi göstermek içindir. 
   
 20-04-202217:40:48 +0300
3 =haftanın günü

Çarşamba ==> türkçe gün ismi

Wednesday =haftanın günü

16 = kaçıncı hafta

Nisan ==> türkçe ay ismi

April ==> Ay ismi

20-04-2022 =kısa tarih
17:40 =saniyesiz saat
 */
  }

  delay(10000);   // wait 1 minute

}
// End of code.
