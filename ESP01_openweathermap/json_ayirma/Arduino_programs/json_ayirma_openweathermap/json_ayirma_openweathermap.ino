//jsondize dönen bilgi ="{"coord":{"lon":27.0923,"lat":38.4622},"weather":[{"id":800,"main":"Clear","description":"açık","icon":"01d"}],"base":"stations","main":{"temp":20.92,"feels_like":20.24,"temp_min":20.73,"temp_max":20.97,"pressure":1011,"humidity":45},"visibility":10000,"wind":{"speed":9.77,"deg":210},"clouds":{"all":0},"dt":1648896104,"sys":{"type":1,"id":6979,"country":"TR","sunrise":1648871717,"sunset":1648917295},"timezone":10800,"id":311044,"name":"İzmir","cod":200}"
/**************************************************************************************

 Internet weather station using ESP8266 Wi-Fi module
 This is a free software with NO WARRANTY.
 http://simple-circuit.com/

***************************************************************************************/


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // http web access library
#include <ArduinoJson.h>        // JSON decoding library

const char *ssid     = "ZYXEL_SAF";
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
    //http.begin("http://api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=1041444a18cfb8448343254a45721b1d");
http.begin("http://api.openweathermap.org/data/2.5/weather?q=izmir,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric&lang=tr");
    int httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);

      DynamicJsonBuffer jsonBuffer(512);

      // Parse JSON object
      JsonObject& root = jsonBuffer.parseObject(payload);
      if (!root.success()) {
        Serial.println(F("Parsing failed!"));
        delay(60000);
        return;
      }

      float temp = (float)(root["main"]["temp"]);// - 273.15;        // get temperature
      int   humidity = root["main"]["humidity"];                  // get humidity
      float pressure = (float)(root["main"]["pressure"]) / 1000;  // get pressure
      float wind_speed = root["wind"]["speed"];                   // get wind speed
      int  wind_degree = root["wind"]["deg"];                     // get wind degree

      // print data
      Serial.printf("Temperature = %.2f°C\r\n", temp);
      Serial.printf("Humidity    = %d %%\r\n", humidity);
      Serial.printf("Pressure    = %.3f bar\r\n", pressure);
      Serial.printf("Wind speed  = %.1f m/s\r\n", wind_speed);
      Serial.printf("Wind degree = %d°\r\n\r\n", wind_degree);
      Serial.println(payload);
      delay(500);
    }

    http.end();   //Close connection

  }

  delay(10000);   // wait 1 minute

}
// End of code.
