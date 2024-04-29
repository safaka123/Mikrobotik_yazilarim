#include "WiFi.h"
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;
 String s="";
 int ss=0;
 int L=0;
 String subs="";
const char* ssid = "SUPER5960";
const char* password =  "5f7JXDQeeYzT";
 
WiFiServer wifiServer(80);
// statik ip adresi **********************************
IPAddress local_IP(192, 168, 1, 184);
// gateway ip (modem arayüzüne girişte kullandığınız ip adresi)
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //isteğe bağlı google dnsleri
IPAddress secondaryDNS(8, 8, 4, 4); 

//******************************************************* 
int relayPin = 23;

void SCCODE(){
  int L=s.length();
  Serial.println(s);
  Serial.println(L);
  String subs=s.substring(3,L-2);
  Serial.println(subs); 
}



 
void processReceivedValue(char command){
  //Serial.print(" s string değeri ");Serial.println(s);
 if(s == "PP"){
  ss=1;BLE_KEYB();s="";return;
}
if(s == "ENT"){
  ss=2;BLE_KEYB();s="";return;
}
if(s == "MU"){
  ss=3;BLE_KEYB();s="";return;
}
if(s == "NT"){
  ss=4;BLE_KEYB();s="";return;
}
if(s == "PT"){
ss=5;BLE_KEYB();s="";return;
}
if(s == "VI"){
ss=6;BLE_KEYB();s="";return;
}
if(s == "VD"){
ss=7;BLE_KEYB();s="";return;
}
if(s == "RG"){
ss=8;BLE_KEYB();s="";return;
}
if(s == "UP"){
ss=9;BLE_KEYB();s="";return;
}
if(s == "DO"){
ss=10;BLE_KEYB();s="";return;
}
if(s == "LE"){
ss=11;BLE_KEYB();s="";return;
}
if(s == "D"){
ss=12;BLE_KEYB();s="";return;
}
if(s == "M"){
ss=13;BLE_KEYB();s="";return;
}
if(s == "S"){
ss=14;BLE_KEYB();s="";return;
}
if(s == "A"){
ss=15;BLE_KEYB();s="";return;
}

if(s == "1"){
ss=16;BLE_KEYB();s="";return;
}
if(s == "2"){
ss=17;BLE_KEYB();s="";return;
}

if(s == "3"){
ss=18;BLE_KEYB();s="";return;
}
if(s == "4"){
ss=19;BLE_KEYB();s="";return;
}
if(s == "5"){
ss=20;BLE_KEYB();s="";return;
}
if(s == "6"){
ss=21;BLE_KEYB();s="";return;
}
if(s == "7"){
ss=22;BLE_KEYB();s="";return;
}
if(s == "8"){
ss=23;BLE_KEYB();s="";return;
}
if(s == "9"){
ss=24;BLE_KEYB();s="";return;
}
if(s == "0"){
ss=25;BLE_KEYB();s="";return;
}
if(s.indexOf('SC')>0){
ss=26;BLE_KEYB();s="";return;
}
if(s == "EQ"){
ss=27;BLE_KEYB();s="";return;
}
if(s == "PE"){
ss=28;BLE_KEYB();s="";return;
}








  if(s == "R1ON"){ 
    digitalWrite(relayPin, HIGH);
    Serial.println("RELAY HIGH");
    s="";return;
    
    }
  else if(s == "R1OFF"){
    digitalWrite(relayPin, LOW);
    Serial.println("RELAY LOW");
    s="";return;
    
    }

    
 s="";
   return;
}


void BLE_KEYB() {
  Serial.println(s);
  Serial.println(ss);
  if(bleKeyboard.isConnected()) {
/** // BU tüm ascii kodları yazdırıyor. sadece türkçe harfleri bu şekilde yazdırabiliriz. 
 *  // fakat arada klavye bileşimleri olduğundan ekranda farklı pencereler gelebiliyor özellikle asci. 128 den sonrası
 *  // bazıları basılabilir karakterdir bazıları komuttur mesela page down gibi 
 *  // ayrıca bilgisayarda scroll lock kilitleniyor klavyede scroll butonu toksa win10 da denetim masası erişilebilirlik
 *  // kısmına giderek ekran klavyesini açın oradan kapatın. 
**/
// gerçek tuşlar başlar
  switch (ss) {
  case 1:
   bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
   delay(100);
    break;
  case 2:
   bleKeyboard.write(KEY_RETURN);
   delay(100);    
    break;
  case 3:
   bleKeyboard.write(KEY_MEDIA_MUTE);
   delay(100);    
    break;
  case 4:
   bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
   delay(100);    
    break;
  case 5:
   bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
   delay(100);    
    break;
  case 6:
   bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
   delay(100);    
    break;
  case 7:
   bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
   delay(100);    
    break;
  case 8:
   bleKeyboard.write(KEY_RIGHT_ARROW);
   delay(100);    
    break;
  case 9:
   bleKeyboard.write(KEY_UP_ARROW);
   delay(100);    
    break;
  case 10:
   bleKeyboard.write(KEY_DOWN_ARROW);
   delay(100);    
    break;
  case 11:
   bleKeyboard.write(KEY_LEFT_ARROW);
   delay(100);    
    break;
  case 12:
   bleKeyboard.write(KEY_NUM_SLASH);
   delay(100);    
    break;
  case 13:
   bleKeyboard.write(KEY_NUM_ASTERISK);
   delay(100);    
    break;
  case 14:
   bleKeyboard.write(KEY_NUM_MINUS);
   delay(100);    
    break;
  case 15:
   bleKeyboard.write(KEY_NUM_PLUS);
   delay(100);    
    break;
  case 16:
   bleKeyboard.write(KEY_NUM_1);
   delay(100);    
    break;
  case 17:
   bleKeyboard.write(KEY_NUM_2);
   delay(100);    
    break;
  case 18:
   bleKeyboard.write(KEY_NUM_3);
   delay(100);    
    break;
  case 19:
   bleKeyboard.write(KEY_NUM_4);
   delay(100);    
    break;
  case 20:
   bleKeyboard.write(KEY_NUM_5);
   delay(100);    
    break;
  case 21:
   bleKeyboard.write(KEY_NUM_6);
   delay(100);    
    break;
  case 22:
   bleKeyboard.write(KEY_NUM_7);
   delay(100);    
    break;
  case 23:
   bleKeyboard.write(KEY_NUM_8);
   delay(100);    
    break;
  case 24:
   bleKeyboard.write(KEY_NUM_9);
   delay(100);    
    break;
  case 25:
   bleKeyboard.write(KEY_NUM_0);
   delay(100);    
    break;
  case 26:
   L=s.length();
   subs=s.substring(2,L);
   Serial.println(subs); 
   
   bleKeyboard.write(subs.toInt());
   delay(100);    
    break;
  case 27:
   bleKeyboard.write(41);
   delay(100);    
    break;
  case 28:
   bleKeyboard.write(KEY_NUM_PERIOD);
   delay(100);    
    break;
  default:
    // statements
    break;
}
 
 
 
 
/** 
 for (int i = 32; i <= 50; i++) {
    Serial.println(i);
    bleKeyboard.write(i);
    delay(100);
   bleKeyboard.write(KEY_RETURN);
   delay(100);
  }
  Serial.println("Sending key num 0...");
   bleKeyboard.write(KEY_NUM_0);
   delay(3000);
   bleKeyboard.write(KEY_RETURN);
   delay(100);
Serial.println("Sending key num 1...");
   bleKeyboard.write(KEY_NUM_1);
   delay(3000);
   bleKeyboard.write(KEY_RETURN);
   delay(100);

   Serial.println("Sending key num 2...");
   bleKeyboard.write(KEY_NUM_2);
   delay(3000);
   bleKeyboard.write(KEY_RETURN);
   delay(100);

   Serial.println("Sending key num 4...");
   bleKeyboard.write(KEY_NUM_4);
   delay(3000);
   bleKeyboard.write(KEY_RETURN);
   delay(100);
**/
   



/**
    Serial.println("Sending , virgul");
    bleKeyboard.write(0x2D);
   delay(5000);
   Serial.println("Sending SHIFT, virgul");
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press(0x2D);
   delay(100);
    bleKeyboard.releaseAll();
    delay(5000);
  
  
  
  
  
  
   Serial.println("Sending 'Ab,;d'...");
   bleKeyboard.print("A");//"hello da yazabilirsiniz"
   delay(3000);
   bleKeyboard.print("b");
   delay(3000);
      bleKeyboard.print(",");
   delay(3000);
      bleKeyboard.print(";");
   delay(3000);
      bleKeyboard.print("d");
   delay(3000);
   bleKeyboard.write(0xC0);
   delay(3000);
   Serial.println("Sending , virgul");
    bleKeyboard.write(0xBA);
   delay(3000);
Serial.println("Sending Enter key...");
   bleKeyboard.write(KEY_RETURN);
   delay(3000);
   

  Serial.println("Sending UP...");
   bleKeyboard.write(KEY_UP_ARROW);
   delay(3000);
  Serial.println("Sending RIGHT...");
   bleKeyboard.write(KEY_RIGHT_ARROW);
   delay(3000);
   Serial.println("Sending DOWN...");
   bleKeyboard.write(KEY_DOWN_ARROW);
   delay(3000);
   Serial.println("Sending LEFT...");
   bleKeyboard.write(KEY_LEFT_ARROW);
   delay(3000);
   Serial.println("Sending PAGE DOWN...");
   bleKeyboard.write(KEY_PAGE_DOWN);
   delay(3000);
   Serial.println("Sending PAGE UP...");
   bleKeyboard.write(KEY_PAGE_UP);
   delay(3000);
   Serial.println("Sending HOME...");
   bleKeyboard.write(KEY_HOME);
   delay(3000);
**/   
   
  
/**
    Serial.println("Sending Enter key...");
   bleKeyboard.write(KEY_RETURN);
   delay(3000);
 //  Serial.println("Sending hello world..");
 //bleKeyboard.print("Hello world");
//delay(5000);
    
  //  bleKeyboard.print("şŞçÇöÖüÜğĞ Hello world");// bu şekilde yazmıyor asc 222 olarak ya da keyboard örneğinde olduğu gibi kütüphane değişikliği
    
//delay(1000);

//
    Serial.println("Sending Play/Pause media key...");
    //bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    delay(1000);
    Serial.println("Sending KEY NUM 0...");
   bleKeyboard.write(KEY_NUM_1);
   delay(3000);
    Serial.println("Sending KEY NUM 1...");
   bleKeyboard.print(KEY_NUM_0);
   delay(3000);
   Serial.println("Sending KEY NUM 1...");
   bleKeyboard.print(KEY_NUM_2);
   delay(3000);
  **/
  }
}
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("sta hatasi");
  }
//*********** wifi ayarlar ********** 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
  //********** wifi ayarlar son **********
// ********** BLE AYARLAR **********
Serial.println("Starting BLE work!");
  bleKeyboard.begin();
// ********** BLE AYARLAR SON **********
 
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}
 
 void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        char c ='c'; //client.read();
        s= client.readStringUntil('\r');
        
        //s+=c;// /r ile bitince alt satıra geçsin yazdırmaya gitsin. 
        
        processReceivedValue(c);
        //Serial.write(c);
      }
 
      delay(10);
    }
 
    client.stop();
    Serial.println("Client disconnected");
 
  }
}
