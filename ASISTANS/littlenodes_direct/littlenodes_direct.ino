#include <WiFiClientSecure.h>
#include <ESP8266WiFi.h>
const char* ssid     = "ZYXEL_SAF";     // your network SSID (name of wifi network)
const char* password = "5f7JXDQeeYzT"; // your network password

const char*  server ="www.littlenodes.com";
String URL;


WiFiClientSecure client;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  
  Serial.println(ssid);
  
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);// lamba sönük başlamıyor sanırım ssid bağlantısını bekliyor. 
  // bunun için bir while döngüsünde beklet ve lamba söndüyse devam et. 
  

  Serial.print("Attempting to connect to SSID: ");
  //Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  
}

void GONDER(){
while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
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

    client.println(URL);
    
    client.println("Host: esp8266-4140a.firebaseio.com");
    client.println("Connection: close");
    client.println();

    client.stop();
  }


  
}

void loop() {


    URL="GET https://www.littlenodes.com/api/alexa/triggeralexa.php?email=safakagustoslu@hotmail.com&apikey=IoUDV5wENJnP6q1cvmx8jkWKyGZ9e70LrQtHhlTBgRsSb HTTP/1.0";// LİTTLE NODES DİRECT
 Serial.println(URL);
GONDER();

delay(10000);

  

}
