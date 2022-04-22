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

void ayirma1(){
temp5=temp2.length();
temp1=payload.indexOf(temp2,temp4);
temp4=payload.indexOf(temp6,temp1+temp5+1);
temp2=payload.substring(temp1+temp5+1, temp4);
Serial.print(temp7);Serial.println(temp2);
  
}
void ayirma2(){ // float değişken için. 
temp5=temp2.length();
temp1=payload.indexOf(temp2);
temp4=payload.indexOf("\"",temp1+temp5+1);
temp2=payload.substring(temp1+temp5+1, temp4);
temp3=temp2.toFloat();//toInt();   
    
}


void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
 
   
    //http.begin("http://api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=1041444a18cfb8448343254a45721b1d");// örnek sitenin link'i çalışıyor. 
http.begin("http://api.openweathermap.org/data/2.5/weather?q=izmir,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric&lang=en&mode=xml");
    int httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code

      payload = http.getString();   //Get the request response payload
      //Serial.println(payload);

temp1=payload.indexOf("temperature value=");
//temp4=0;
//Serial.println(temp1);// 242. karakterden başlıyor ve + karakter sayısı=substring başlama noktası. temperature value=
//temp2=payload.substring(temp1+18+1, temp1+18+1+5);
//temp3=temp2.toFloat();//toInt();   
   // Serial.printf("Temperature2 = %.2f°C\r\n", temp3);// monitörde gösterilen Temperature2 = 21.97°C

Serial.println(" ");
temp4=0;
temp2="name=";temp6="\"";temp7="City : ";
ayirma1();

temp2="country";temp6="<";temp7="Country : ";
ayirma1();
temp2="sun rise=";temp6="\"";temp7="SUN Rise : ";
ayirma1();
temp2="set=";temp6="\"";temp7="SUN Set : ";
ayirma1();
temp2="temperature value=";temp6="\"";temp7="Temperature2 = ";
ayirma2();
Serial.printf("Temperature Value = %.2f°C\r\n", temp3);// monitörde gösterilen Temperature2 = 21.97°C

temp2="min=";temp6="\"";temp7="Temperature Min = ";
ayirma2();
Serial.printf("Temperature Min = %.2f°C\r\n", temp3);
temp2="min=";temp6="\"";temp7="Temperature Max = ";
ayirma2();
Serial.printf("Temperature Max = %.2f°C\r\n", temp3);

temp2="feels_like value=";temp6="\"";temp7="Temperature Max = ";
ayirma2();
Serial.printf("feels_like value = %.2f°C\r\n", temp3);

temp2="humidity value=";temp6="\"";temp7="Humidity Value = ";
ayirma2();
Serial.printf("Humidity Value = %.2f percent \r\n", temp3);
temp2="pressure value=";temp6="\"";temp7="Pressure Value ";
ayirma2();
Serial.printf("Pressure Value = %.2f hPa \r\n", temp3); 
temp2="speed value=";temp6="\"";temp7="Speed Value ";
ayirma2();
Serial.printf("Speed Value = %.2f m/s \r\n", temp3); 
 
temp2="direction value=";temp6="\"";temp7="direction value= ";
ayirma2();
Serial.printf("direction value = %.2f degree ", temp3); 
temp2="code=";temp6="\"";temp7=" ";// rüzgar yönü directionla birlikte yazılıyor.
ayirma1();

temp2="clouds value=";temp6="\"";temp7="Clouds Value= ";
ayirma2();
Serial.printf("Clouds Value= = %.f percent ", temp3); 
temp2="name=";temp6="\"";temp7=" ";// rüzgar yönü directionla birlikte yazılıyor.
ayirma1();

temp2="visibility value=";temp6="\"";temp7="Visibility Value = ";
ayirma1();

temp2="precipitation mode=";temp6="\"";temp7="Precipitation Mode = ";
ayirma1();

temp2="value=";temp6="\"";temp7="Value = ";
ayirma1();

temp2="lastupdate value=";temp6="\"";temp7="Lastupdate Value = ";
ayirma1();

 

    


      delay(5000);
    }

    http.end();   //Close connection
//==============================================
Serial.println(" ");// 2 çağrı çıktısı arasında ayrım yapmak 
delay(1000);
    http.begin("http://mikrobotikradyo.ml/api/openweather/clocksade.php");
     httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code // fakat bu 200 de olabilir 400 de olabilir 
                        // şayet biraz geliştirmek isterseniz doğru okuma yaptığında 200 döner. yanlış olursa hata mesajı iletilebilir.

      payload = http.getString();   //gönderilen link'in cevabı dönüyor.
     // Serial.println(payload);// gelen bilgiyi görmek için aç. 
      String curdate=payload.substring(0,10);
      String curtime=payload.substring(10,24);
      Serial.print("DATE : ");Serial.println(curdate);
      Serial.print("DATE : ");Serial.println(curtime);
      delay(1500);
    }

    http.end();   //Close connection

//============================================== 
    

  }

  delay(10000);   // wait 1 minute

}
// End of code.
