
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "ZYXEL_SAF";
const char* password = "5f7JXDQeeYzT";
 
void setup () {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
    int deger=25;

    String URL="http://mikrobotikradyo.tk/api/firebasechange1.php?deger="+String (deger);
  //String URL="http://mikrobotikradyo.tk/api/firebase_read1.php";
  Serial.println(URL);
  
    http.begin(URL);  //Specify request destination
    int httpCode = http.GET();                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
 
    }
 
    http.end();   //Close connection
 
  }
 
  delay(10000);    //Send a request every 30 seconds
}
