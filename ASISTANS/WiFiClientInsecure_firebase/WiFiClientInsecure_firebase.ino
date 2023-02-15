#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
const char* ssid     = "ZYXEL_SAF";     // your network SSID (name of wifi network)
const char* password = "5f7JXDQeeYzT"; // your network password

const char*  server ="esp8266-4140a.firebaseio.com";// "script.google.com";  // Server URL
String URL;
float t=0;

WiFiClientSecure client;

void setup() {
  //Initialize serial and wait for port to open:
  //Serial.begin(115200);
  
  //Serial.println(ssid);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);// lamba sönük başlamıyor sanırım ssid bağlantısını bekliyor. 
  // bunun için bir while döngüsünde beklet ve lamba söndüyse devam et. 
  

  //Serial.print("Attempting to connect to SSID: ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  
}

void GONDER(){
while (WiFi.status() != WL_CONNECTED) {
   // Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }

 // Serial.print("Connected to ");
 // Serial.println(ssid);

 // Serial.println("\nStarting connection to server...");
  client.setInsecure();//skip verification
  if (!client.connect(server, 443))
   //Serial.println("Connection failed!");
   client.setInsecure();//skip verification
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:

    client.println(URL);//"GET https://script.google.com/macros/s/AKfycbwJAB0-leruVZNJhsgD4I7mewHy_fT842Ae7cafYdvhmakAggGSvjCg4Sz4PghsVyNOgg/exec?func=addData&id=7&val=30 HTTP/1.0");
    
    client.println("Host: esp8266-4140a.firebaseio.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        //Serial.println("headers received");
        break;
      }
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    String cevap="";
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
      cevap=cevap+c;
      
    }
    Serial.println(cevap);
    int var=cevap.indexOf("close");
    
    if (var>0){
      //Serial.println("open");
      
      digitalWrite(LED_BUILTIN, HIGH);
    }
    var=0;
    var=cevap.indexOf("open");
   
    if (var>0){
      //Serial.println("close");
      
      digitalWrite(LED_BUILTIN, LOW);
    }
    

    client.stop();
  }


  
}

void loop() {
for (int i = 0; i <= 20; i++){
  t = i;
  delay(10);


    URL="GET /bool_mit.json?auth=2NaRXXwRefCCxTx9KBarrDm957KKDJsN4nJj1Dqq HTTP/1.0";// OK.
    //"GET /LED1.json?auth=2NaRXXwRefCCxTx9KBarrDm957KKDJsN4nJj1Dqq HTTP/1.0";// OK.
    //"GET https://script.google.com/macros/s/AKfycbwJAB0-leruVZNJhsgD4I7mewHy_fT842Ae7cafYdvhmakAggGSvjCg4Sz4PghsVyNOgg/exec?func=addData&id=7&val="+ String(t)+" HTTP/1.0";// e-tablo OK.
 //Serial.println(URL);
GONDER();

delay(5000);
}
  
  // do nothing
}
