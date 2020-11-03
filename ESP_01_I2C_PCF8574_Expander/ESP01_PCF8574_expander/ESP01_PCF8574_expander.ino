/*********
  Rui Santos    ************ Web server buton çalışma kısmını buradan aldım ve kendime göre değiştirdim. 
  Faydalı bir sitesi var. Tavsiye ederim. 
  Complete project details at http://randomnerdtutorials.com  

  Ayarlar için önce ESP çalıştığında wifi ağlarına bakın. ESP soft AP bilgisini göreceksiniz. 
  bu ağa bağlanıp 192.168.4.1 adresine internet programınızla bağlanın. gelen sayfada 
  hem butonları görüp çalıştırabileceksiniz. hem de STA modunda yani ESP ağına bağlanmadan 
  kullanabileceğiniz IP adresini göreceksiniz. Kendi ağınızı değiştirmeden bu IP adresiyle de bağlanabilirsiniz. 
  *****************Bu programı webserver için kalıp olarak kullanabilirsiniz. ****************
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <Wire.h>
int adres=0x27;

// kendi modem bilgilerinizi girin
const char* ssid     = "Guest_SSID_1_4A09";
const char* password = "guest1997";
String adr="";

// Variable to store the HTTP request
String header;

// Set web server port number to 80
WiFiServer server(80);
int Led=0;  // buton basma numarası
int gonder=247;  // I2C modüle gidecek bilgi. 
int Ledler[] = {0,0,0,0,0,0,0,0};  // Buton renkleri için bilgi. dizi şeklinde gelen buton basma durumuna göre 1 ve 0 değişir.
// led1 on 246,led2=245 led3=243 led4=p3=255 led5=231 led6=215 led7=183  led8=119
int LedI2C[]={246,245,243,255,231,215,183,119};  // modül ledlerin yanması için gereken kod. binary şeklinde düşünün.

// ********* bu kısım bağlantı için bir timeout süresi tanımlar. 
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void aktar(){  // gelen bilginin karşılığı olan dizi bilgilerini alıp I2C üzerinden modüle gönderir. 
for(int i = 0; i<8; i++){
  if (Led==i){
    Ledler[i]=0;
    gonder=LedI2C[i];
  }else{
    Ledler[i]=1;
  }
}
 
Serial.println("Çıkışlar  P0,p1,p2,p3,p4,p5,p6,p7 ");
Serial.print(Ledler[0]);Serial.print(Ledler[1]);Serial.print(Ledler[2]);Serial.print(Ledler[3]);Serial.print(Ledler[4]);
Serial.print(Ledler[5]);Serial.print(Ledler[6]);Serial.println(Ledler[7]);
Serial.print("I2C olarak gönderilen sayı : ");
Serial.println(gonder, BIN);
I2Csend();  // gonder değişkeninin modüle gönderilmesi sağlanır. 
  
}
void I2Csend(){
    Wire.beginTransmission(adres); // transmit to device #4
  Wire.write(gonder);   // sends one byte p3 ters çalıştığından sönük olması için 0 verildi. 
  Wire.endTransmission();    // stop transmitting
}



void setup() {
  Serial.begin(115200);
   // Connect to Wi-Fi network with SSID and password
  Wire.begin(0,2); //*******************SDA=GPIO.0  SCL=GPIO.2
  Wire.beginTransmission(adres); // transmit to device #4
  Wire.write(B11110111);   // sends one byte p3 ters çalıştığından sönük olması için 0 verildi. 
  Wire.endTransmission();    // stop transmitting
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  
  Serial.println(WiFi.localIP());
  IPAddress myIP=WiFi.localIP();
  // Serial.println(myIP);
  adr=WiFi.localIP().toString();
 // Serial.println(adr);
  server.begin();
}




void loop(){
  
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /") >= 0) {// GET /0/on
              
              //Serial.println("Led1");
              Led=(header.substring(5)).toInt();
              Led=Led-1;
              Serial.print("Basılan Buton: ");
              Serial.println(Led);
            if (Led==-1){
              gonder=247;
              I2Csend();
            }
              aktar();
            }  
           
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #3EF706; border: none; color: white; padding: 10px 20px;");
            client.println("text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #FF0F00;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1><br>");

            if (Ledler[0]==0) {
              client.println("<a href=\"/1/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/1/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[1]==0) {
              client.println("<a href=\"/2/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/2/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[2]==0) {
              client.println("<a href=\"/3/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/3/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[3]==0) {
              client.println("<a href=\"/4/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/4/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[4]==0) {
              client.println("<a href=\"/5/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/5/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[5]==0) {
              client.println("<a href=\"/6/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/6/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[6]==0) {
              client.println("<a href=\"/7/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/7/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            if (Ledler[7]==0) {
              client.println("<a href=\"/8/on\"><button class=\"button\">ON</button></a><br>");
            } else {
              client.println("<a href=\"/8/off\"><button class=\"button button2\">OFF</button></a><br>");
            }
            client.println("<a href=\"/0/off\"><button class=\"button button2\">KAPAT</button></a><br>");
            client.println("<p>NOT STA mode uzerinden baglanmak icin  Bu IP adresine baglanin." +adr+" </p>");// <p>NOT STA mode uzerinden baglanmak icin Bu IP adresine baglanin. "
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    //Serial.println("");
  }
}

