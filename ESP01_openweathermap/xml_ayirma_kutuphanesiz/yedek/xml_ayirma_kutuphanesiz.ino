//String jsondize="{"coord":{"lon":27.0923,"lat":38.4622},"weather":[{"id":800,"main":"Clear","description":"açık","icon":"01d"}],"base":"stations","main":{"temp":20.92,"feels_like":20.24,"temp_min":20.73,"temp_max":20.97,"pressure":1011,"humidity":45},"visibility":10000,"wind":{"speed":9.77,"deg":210},"clouds":{"all":0},"dt":1648896104,"sys":{"type":1,"id":6979,"country":"TR","sunrise":1648871717,"sunset":1648917295},"timezone":10800,"id":311044,"name":"İzmir","cod":200}"
/**************************************************************************************

 Internet weather station using ESP8266 Wi-Fi module
 This is a free software with NO WARRANTY.
 http://simple-circuit.com/

***************************************************************************************/

//String xmldize="<current><city id="311044" name="İzmir"><coord lon="27.0923" lat="38.4622"/><country>TR</country><timezone>10800</timezone><sun rise="2022-04-07T03:47:38" set="2022-04-07T16:39:35"/></city><temperature value="20.73" min="20.73" max="20.73" unit="celsius"/><feels_like value="20.53" unit="celsius"/><humidity value="64" unit="%"/><pressure value="1000" unit="hPa"/><wind><speed value="6.17" unit="m/s" name="Moderate breeze"/><gusts/><direction value="160" code="SSE" name="South-southeast"/></wind><clouds value="75" name="parçalı bulutlu"/><visibility value="10000"/><precipitation mode="no"/><weather number="803" value="parçalı bulutlu" icon="04d"/><lastupdate value="2022-04-07T13:08:01"/></current>";
//<?xml version="1.0" encoding="UTF-8"?>  38 karakter
//<current><city id="311044" name="İzmir"><coord lon="27.0923" lat="38.4622"></coord><country>TR</country><timezone>10800</timezone><sun rise="2022-04-07T03:47:38" set="2022-04-07T16:39:35"></sun></city><temperature value="22.06" min="20.73" max="23.98" unit="celsius"></temperature><feels_like value="21.52" unit="celsius"></feels_like><humidity value="46" unit="%"></humidity><pressure value="1000" unit="hPa"></pressure><wind><speed value="8.23" unit="m/s" name="Fresh Breeze"></speed><gusts></gusts><direction value="150" code="SSE" name="South-southeast"></direction></wind><clouds value="75" name="parçalı bulutlu"></clouds><visibility value="10000"></visibility><precipitation mode="no"></precipitation><weather number="803" value="parçalı bulutlu" icon="04d"></weather><lastupdate value="2022-04-07T13:15:46"></lastupdate></current>






#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  // http web access library

//String names[]={"name","country","rise","set","tempreture value","min","max","feels_like value","humidity value","pressure value"};


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

    // specify request destination
    //http.begin("http://api.openweathermap.org/data/2.5/weather?q=London,uk&APPID=1041444a18cfb8448343254a45721b1d");
http.begin("http://api.openweathermap.org/data/2.5/weather?q=izmir,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric&lang=en&mode=xml");
    int httpCode = http.GET();  // send the request

    if (httpCode > 0) { // check the returning code

      payload = http.getString();   //Get the request response payload
      //Serial.println(payload);
//String bul1="temperature value";
//bul1=bul1 + "=\"";
//Serial.println(bul1);
temp1=payload.indexOf("temperature value=");
temp4=0;
//Serial.println(temp1);// 242. karakterden başlıyor ve + karakter sayısı=substring başlama noktası. temperature value=
temp2=payload.substring(temp1+18+1, temp1+18+1+5);
temp3=temp2.toFloat();//toInt();   
   // Serial.printf("Temperature2 = %.2f°C\r\n", temp3);// monitörde gösterilen Temperature2 = 21.97°C


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

  }

  delay(30000);   // wait 1 minute

}
// End of code.
