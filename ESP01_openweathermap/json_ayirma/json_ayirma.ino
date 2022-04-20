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
int sat=0;
int sut=0;

void setup() {

  Serial.begin(115200);
  delay(500);
  //Serial.print("Connecting.");
  //Serial.println(ssid);
  //Serial.println(password);
  WiFi.begin(ssid, password);   // access Wi-FI point

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
   // Serial.print(".");
  }
 // Serial.println("connected\r\n");
Serial.print("LCDSC 12,3-");
delay(500);

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
   //   Serial.println(payload);

      DynamicJsonBuffer jsonBuffer(512);

      // Parse JSON object
      JsonObject& root = jsonBuffer.parseObject(payload);
      if (!root.success()) {
        Serial.print(F("LCDDD"));
        delay(300);
        Serial.print(F("LCDWR 1,3- JSON HATASI"));
        delay(60000);
        return;
      }
//{"USD":{"buying":14.6079,"selling":14.6664,"cross":0,"CR1":"USD","CR2":"USD"},"EURO":{"buying":15.7945,"selling":15.8578,"cross":1.0812,"CR1":"EURO","CR2":"USD"},
//"openweathermap":{"Temperature":"19.73","Min_Temp":"19.73","Max_Temp":"20.97","Feels_Like":"20.25","Pressure":"1002","Humidity":"43","Country":"TR","City":"Izmir",
//"Clouds":"75","Speed":"10.8","W_deg":"120","update":"17-04-2022 15:36:52 +0300","sunrise":"17-04-2022 06:33:01 +0300","sunset":"17-04-2022 19:49:02 +0300",
//"Cdate":"17-04-2022  15:42:58 +0300","CMname":"Apr","CWno":"15","CDno":"0","CDname":"Sun","CMday":"30","datesh":"17-04-2022","hoursh":"15:42","CMno":"17"}}


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
      String datesh=root["openweathermap"]["datesh"];
      String hoursh=root["openweathermap"]["hoursh"];
      String CMname=root["openweathermap"]["CMname"];
      String CWno=root["openweathermap"]["CWno"];
      String CDname=root["openweathermap"]["CDname"];
      String CMno=root["openweathermap"]["CMno"];
      String CMday=root["openweathermap"]["CMday"];
                         

      // print data
/*      Serial.printf("Temperature = %.2f°C\r\n", temp);
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
*/     
  Serial.print ("LCDDD");
       delay(200);
      Serial.print ("LCDWR 1,1"+String("-")+"SICAKLIK: "+temp+" ");Serial.write(0x03);Serial.print("C");// .write(0x03) 3. yeni karakter. başlarken sc ile 3. karaktere derece işareti koy.
      delay(200);
      Serial.print ("LCDWR 2,5"+String("-")+"NEM:   "+hhumidity+" ");Serial.print("%");
      delay(200);
      Serial.print ("LCDWR 3,5"+String("-")+"BULUT: "+clouds+" ");Serial.print("%");
      delay(200);
      Serial.print ("LCDWR 4,1"+String("-")+"RUZGAR: "+wind_speed+"");Serial.print("kmh ");Serial.print(wind_degree);Serial.write(0x03);
      
      delay(10000);
      
      Serial.print ("LCDDD");
      delay(200);
      Serial.print ("LCDWR 1,1"+String("-")+"USD    AL: "+dolar_alis+" TL");
      delay(200);
      Serial.print ("LCDWR 2,1"+String("-")+"USD   SAT: "+dolar_satis+" TL");
      delay(200);
      Serial.print ("LCDWR 3,1"+String("-")+"EURO   AL: "+euro_alis+" TL");
      delay(200);
      Serial.print ("LCDWR 4,1"+String("-")+"EURO  SAT: "+euro_satis+" TL");
      delay(200);
 //     Serial.print ("LCDWR 4,1"+String("-")+"Euro/$: "+euro_dolar);
 //     delay(100);

      delay(10000);
      Serial.print ("LCDDD");
      delay(200);
      
      Serial.print ("LCDWR 1,6"+String("-")+datesh);
      delay(200);
      Serial.print ("LCDWR 2,8"+String("-")+hoursh);
      delay(200);
      Serial.print ("LCDWR 3,5"+String("-")+CMname+"  WEEK:"+CWno);
      delay(200);
      Serial.print ("LCDWR 4,5"+String("-")+CDname+"   "+CMno+"/"+CMday  );
      delay(200);

      delay(40000);
      
       
    }

    http.end();   //Close connection

  }

  //delay(60000);   // wait 1 minute

}
// End of code.
