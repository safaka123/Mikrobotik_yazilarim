//{"USD":{"buying":14.6079,"selling":14.6664,"cross":0,"CR1":"USD","CR2":"USD"},"EURO":{"buying":15.7945,"selling":15.8578,"cross":1.0812,"CR1":"EURO","CR2":"USD"},
//"openweathermap":{"Temperature":"22.97","Min_Temp":"22.97","Max_Temp":"23.73","Feels_Like":"22.37","Pressure":"1017","Humidity":"40","Country":"TR","City":"Izmir",
//"Clouds":"0","Speed":"6.17","W_deg":"360","update":"15-04-2022 16:40:37 +0300","sunrise":"15-04-2022 06:35:52 +0300","sunset":"15-04-2022 19:47:08 +0300","Cdate":"15-04-2022  16:40:37 +0300"}}

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
http.begin("http://mikrobotikradyo.ml/api/openweather/openweather_json1.php");
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
// geri dönen bilgi budur. Örnektir. 
//{"USD":{"buying":14.6079,"selling":14.6664,"cross":0,"CR1":"USD","CR2":"USD"},"EURO":{"buying":15.7945,"selling":15.8578,"cross":1.0812,"CR1":"EURO","CR2":"USD"},
//"openweathermap":{"Temperature":"22.97","Min_Temp":"22.97","Max_Temp":"23.73","Feels_Like":"22.37","Pressure":"1017","Humidity":"40","Country":"TR","City":"Izmir",
//"Clouds":"0","Speed":"6.17","W_deg":"360","update":"15-04-2022 16:40:37 +0300","sunrise":"15-04-2022 06:35:52 +0300","sunset":"15-04-2022 19:47:08 +0300","Cdate":"15-04-2022  16:40:37 +0300"}}


      float temp = (float)(root["openweathermap"]["Temperature"]) ;
      float min_temp = (float)(root["openweathermap"]["Temperature"]) ;
      float max_temp = (float)(root["openweathermap"]["Temperature"]) ;
      float feels_like = (float)(root["openweathermap"]["Temperature"]) ;
      int   hhumidity = root["openweathermap"]["Humidity"];                  
      float pressure = (float)(root["openweathermap"]["Pressure"]) / 1000; 
      float wind_speed = root["openweathermap"]["Speed"];                   
      int  wind_degree = root["openweathermap"]["W_deg"]; 
      String city=root["openweathermap"]["City"];  
      String country=root["openweathermap"]["Country"]; 
      int  clouds = root["openweathermap"]["Clouds"];
      String Sunrise=root["openweathermap"]["sunrise"]; 
      String Sunset=root["openweathermap"]["sunset"];
      String Cdate=root["openweathermap"]["Cdate"]; 
      float dolar_alis = (float)(root["USD"]["buying"]) ;
      float dolar_satis = (float)(root["USD"]["selling"]) ;
      float euro_alis = (float)(root["EURO"]["buying"]) ;
      float euro_satis = (float)(root["EURO"]["selling"]) ;
      float euro_dolar = (float)(root["EURO"]["cross"]) ;
                         

      // print data
      Serial.printf("Temperature = %.2f°C\r\n", temp);
      Serial.printf("Humidity    = %d %%\r\n", hhumidity);
      Serial.printf("Pressure    = %.3f bar\r\n", pressure);
      Serial.printf("Wind speed  = %.1f m/s\r\n", wind_speed);
      Serial.printf("Wind degree = %d°\r\n\r\n", wind_degree);
delay(500);
      Serial.printf("DOLAR ALIS = %.4f TL\r\n", dolar_alis);
      Serial.printf("DOLAR SATIS = %.4f TL\r\n", dolar_satis);
      Serial.printf("EURO ALIS = %.4f TL\r\n", euro_alis);
      Serial.printf("EURO SATIS = %.4f TL\r\n", euro_satis);
      Serial.printf("EURO/DOLAR = %.4f TL\r\n", euro_dolar);
     Serial.print(" City / Country = ");Serial.print(city);Serial.print(" / ");Serial.println(country);
    // Serial.println(city);
    // Serial.println(country);



      delay(500);
    }

    http.end();   //Close connection

  }

  delay(60000);   // wait 1 minute

}
// End of code.
