/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ZYXEL_SAF", "5f7JXDQeeYzT");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://mikrobotikradyo.tk/api/alexa_littlenodes.php")) {  // HTTP
//https://www.littlenodes.com/api/alexa/triggeralexa.php?email=safakagustoslu@hotmail.com&apikey=IoUDV5wENJnP6q1cvmx8jkWKyGZ9e70LrQtHhlTBgRsSb
//yukarıdaki https link'i direkt kendi sitesinden alarm verdirir. 
//Bir web sayfasına yazdığınızda görebilirsiniz. Fakat https client esp programını kullanmanız gerekir.
//ESP01 arduino örneklerinin içerisinde https client seçebilirsiniz. 
// bundan dolayı kendi sitemdeki php dosyasına gönderdim ve o da gerçek link'e gönderiyor. 
//http://mikrobotikradyo.tk/api/alexa_littlenodes.php  // kendi sitemdeki adres.

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
