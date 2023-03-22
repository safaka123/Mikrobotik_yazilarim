// arduino 2 led 2 sensör yerine switch olacak. 
// push buton sw olacak ve say değişkeni toggle çalışacak. 
// say değişkeni sw değerini thingspeak sistemine gönderilecek. 

//******  denemelerde softserial kullanırken bu satırları programa dahil edin.
// denemeler bitince sadece donanımsal seri kullanabilirsiniz. 
// donanımsal seri kullanırken ESP programınızı da 115200 hızına getirirsiniz. 
// #include <SoftwareSerial.h>
//SoftwareSerial mySerial(10, 11); // RX, TX
//mySerial.begin(9600)// setup içine koy
//mySerial.println("Hello World") // komut olarak her yerde kullan. 

 
#include <SoftwareSerial.h>


SoftwareSerial mySerial(8, 9); // RX, TX
const int BUTTON_1 = 4;
const int BUTTON_2 = 5;
String cs1="";
String cs2="";
String cs3="";
String cs4="";
String cs5="";
String cs6="";
String cs7="";
String cs8="";
String URL;
String cevap="";
String stringRX="";
int d2pwm=0;
int counttime=0;
int saybak=0;
int commandseq=1;
int RObak=0;
int writecontrol=0;
int startcontrol=0;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("START ");
 mySerial.begin(9600);// denemelerden sonra kapatılacak donanımsal seriye çevrilecek. 
  delay(100);
 
 
 pinMode(3,OUTPUT);// pwm device 2
 pinMode(2,OUTPUT);// device 1
 pinMode(BUTTON_1, INPUT_PULLUP);//d4 pim
pinMode(BUTTON_2, INPUT_PULLUP);//d5 pim
pinMode(LED_BUILTIN,OUTPUT);// ESP timeout verirse bu led yanacak normale döndüğünde sönecek. 
digitalWrite(LED_BUILTIN, HIGH);
}


void seripar() {
int say=4;
int say1=0;
say=stringRX.indexOf("R");// bu satır WO ile gelen satırda parazitten dolayı bir ekleme varsa
                                 //bunu iptal et demek için yapıldı. Mesela ?-!<WO:0,0,0,0,0,0,0,0> gibi gelirse
                                // ilk sütun <WO sütunu olacağından işlem hata yapmayacak. 

say=say+3;
say1=stringRX.indexOf(",",say);
cs1=stringRX.substring(say,say1);// say=4 say1=6  olduğunda 4. 5. karakteri alır 6. karakteri almaz. 
//Serial.println(cs1);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs2=stringRX.substring(say+1,say1);
//Serial.println(cs2);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs3=stringRX.substring(say+1,say1);
//Serial.println(cs3);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs4=stringRX.substring(say+1,say1);
//Serial.println(cs4);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs5=stringRX.substring(say+1,say1);
//Serial.println(cs5);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs6=stringRX.substring(say+1,say1);
//Serial.println(cs6);
say=say1;
say1=stringRX.indexOf(",",say+1);
cs7=stringRX.substring(say+1,say1);
//Serial.println(cs7);
say=say1;
say1=stringRX.indexOf(">",say+1);
cs8=stringRX.substring(say+1,say1);
//Serial.println(cs8);
}


void sensorcontrol(){
// tüm sensörler her 25sn de bir kontrol edilecek. şayet alarm durumu yoksa 5 kontrolde bir internete gönderilecek. 
cs1="23";
cs2="24";
cs3="25";
cs4="26";
cs5="27";
cs6="28";
cs7="29";
cs8="30";
// gönderilecek format bu şekilde olmalı. <WS:200,211,212,23,2,25,26,271> ESP bunu ayrıştırır. Şayet sensör yoksa 0 girin
String sendsens="<WS:"+cs1+","+cs2+","+cs3+","+cs4+","+cs5+","+cs6+","+cs7+","+cs8+">";
//Serial.print("gonderilen sensor : ");
delay(200); 
Serial.println(sendsens); 
delay(1000);

}

//===============================================
void device1(){ // pin d2 device 1
  if (cs1=="1"){
    digitalWrite(2, HIGH);
    //Serial.print("device 1 : "); Serial.println("HIGH"); 
  }else{
    digitalWrite(2, LOW);//Serial.print("device 1 : "); Serial.println("LOW");
  }
}

void device2(){
 //PWM olarak kontrol et.
 //d2pwm=cs2.toInt();
 //Serial.print("device 2 de2pwm : "); Serial.println(d2pwm);
 analogWrite(3,d2pwm); // 0-255 arasında değer gir.
 delay(100); 
 
}
void device3(){
  cs3="0";
}
void device4(){
  cs4="0";
  }
void device5(){
  cs5="0";
  }
void device6(){
  cs6="0";
  }
void device7(){
  cs7="0";
  }
void device8(){
  cs8="0";
  }
//========================================================

void devicecontrol(){  // cihaz bilgileri geldiğinde değiştiğinde uygular. 
 //seripar();  
 if (RObak==1){
  seripar();d2pwm=cs2.toInt();//Serial.print("d2pwm");Serial.println(d2pwm);
  RObak=0;
 }
//Şayet pwm ile kontrol edilecekse PWM ayarlama yerine gidecek. 
device1();
device2();
device3();
device4();
device5();
device6();
device7();
device8();
delay(100);
// sadece 2 cihaz kullandım siz 8 adede kadar yazabilirsiniz.
 
  }
  

void devicesend(){ // butonlara basıldığında son durumu thingspeak kayıt eder. 
  // switch basıldığında device bilgilerini gönder
  // format budur. <WO:0,130,42,43,44,45,46,47>
cs1=digitalRead(2);// Çıkış piminin son durumunu okur ve değişkene aktarır. 
cs2=d2pwm;// pwm olduğu için son gelen pwm değerini aktarır. 
cs3="0";
cs4="0";
cs5="0";
cs6="0";
cs7="0";
cs8="0";

String devices="<WO:"+cs1+","+cs2+","+cs3+","+cs4+","+cs5+","+cs6+","+cs7+","+cs8+">";
//Serial.print("gonderilen cihaz bilgisi : "); 
delay(200); 
Serial.println(devices); 
delay(150);
//Serial.println("butonlar aktif basılabilir.  ");
  }
  

void deviceread(){
  Serial.println("<RO:>");
  
  delay(100); 
  //Serial.println("<RO:>");// esp den thingspeak okuyup bilgileri göndermesini ister. 
  //*******  while ile seri port cevabı geldi mi diye bekle gelince döngüden çık. 
 // while (!Serial.available());
  digitalWrite(LED_BUILTIN, HIGH);
  delay(150);// okumada trafik sorunu olmuyor. yazarken 15 sn beklemek lazım. 
  }

void sensorread(){// ***** loop döngüsünde buraya göndermedim isterseniz kullanabilirsiniz.
 Serial.println("<RS:>");// esp den thingspeak okuyup sensör bilgileri göndermesini ister. 
 delay(200); 
  //Serial.println("<RS:>");
  delay(1000);// okumada trafik sorunu olmuyor. yazarken 15 sn beklemek lazım. 
} 
  
void loop() {
  if (startcontrol<1){
    Serial.println("<RO:>");
  }
  
  // SWitch control 
  if (digitalRead(BUTTON_2)==LOW){
    writecontrol=1;//**** Burada sw ile çıkış değiştiyse çıkışlar tekrar yazılasıya kadar RO yani okuma komutu yollanmaz. 
    int sec1=digitalRead(2);
  //Serial.print("button 1 : ");Serial.println(sec1);
  digitalWrite(2, !digitalRead(2));// çıkışı toggle yapar. 
  //Serial.print("button 11 : ");Serial.println(digitalRead(2));
  cs1=digitalRead(2);
  //Serial.print("cs1 : ");Serial.println(cs1);
  devicecontrol();
 
    while (digitalRead(BUTTON_2)==LOW){
      // buton bırakılasıya kadar bekleniyor. çiftleme yapmasın diye. 
    }  
  }

  if (digitalRead(BUTTON_1)==LOW){
    writecontrol=1;//**** Burada sw ile çıkış değiştiyse çıkışlar tekrar yazılasıya kadar RO yani okuma komutu yollanmaz. 
   if (d2pwm>0){
    d2pwm=0;
    cs2=d2pwm;
    //Serial.print("d2pwmsw1");Serial.println(d2pwm);
    
  }else{
    d2pwm=50;
    cs2=d2pwm;
    //Serial.print("d2pwmsw11");Serial.println(d2pwm);
  }
  devicecontrol();
    while (digitalRead(4)==LOW){
      // buton bırakılasıya kadar bekleniyor. çiftleme yapmasın diye.
    }
     
  }
  
  if (saybak==1 && writecontrol==1){
    counttime++; // **** bu karşılaştırma sw basıldığında RO yani bilgileri okuma kısmı çalışmadığından
                  //sayaç otomatik artmayacağından burada arttırılması için kullanıldı. 
  } 
  
  
  stringRX="";
  if (Serial.available() > 0) { // Serial Porta girdi değerinin olup olmadığını kontrol et
    stringRX = Serial.readString(); // Serial Porttaki girdi değerini oku ve string e ata.
    delay(200); 
    //Serial.println("");
   //Serial.println(stringRX); // okunan değeri ekrana yazdır.
   // Serial.println(counttime);
  }
  
  

 if(stringRX!=""){
    startcontrol=1;// ESP ilk çalıştırmada haberleşme yapamazsa Haberleşme için bir kelime yollar
    
  if((stringRX.indexOf("RO"))>0 && saybak==0 && writecontrol==0){
    RObak=1;// **** bu değişken devicecontrol() alt programında farklı işlem yapılmasını sağlar.  
      //Serial.println(stringRX.substring(4));
      devicecontrol();
      saybak=0;digitalWrite(LED_BUILTIN, LOW);
  }
    
  if((stringRX.indexOf("RS"))>0 && saybak==0){
      seripar(); // **** Bu alt program seri port üzerinden gelen bilgiyi parçalatıp değişkenlere aktarır.  
      // isterseniz gelen sensor bilgilerini bir yere kayıt edebilirsiniz. 
      // fakat gonderdiğimizi biliyorsak okumamıza gerek yoktur. 
      // cs değişkenleri devamlı değiştiğinden belki son kayıtlara ulaşmak isteyebilirsiniz. 
      // o zaman bunu kullanabilirsiniz. ESP size gönderecektir. 
      //Okuma linkini internet sayfasından gönderirseniz de yine de tüm sonuçları okuyabilirsiniz.  
      saybak=0;digitalWrite(LED_BUILTIN, LOW);// **** built in ledi internet bağlatısı yapıldığında söner. Yanık kalırsa ESP cevap veremiyor demektir. 
  }
 }
 
  if (counttime==25 && saybak==1){// 25 olduğunda araya girme değişkeni ayarlar ve saybak=1 olduğunda bu değişken komutu yollar. 
                                  // LOOP en altta commandseq 3 olarak bir karşılaştırma yapar ve komutu devreye alır. 
                                  // burada isterseniz sensörleri her saniye kontrol edebilirsiniz. 
                                  //sonrasında alarm durumu varsa öncelik verirsiniz yoksa 25 kez de bir gönderme yaparsınız. 
  commandseq=3;digitalWrite(LED_BUILTIN, LOW);
  }
  
  if (counttime==20 && saybak==1){// 20 olduğunda araya girme değişkeni ayarlar ve saybak=1 olduğunda bu değişken komutu yollar. 
                                  // burası WO yani çıkışları thingspeak sitesine yollar. 
                                  // BURAYA COUNTTIME KAÇ YAZDIYSANIZ ONU SWITCH BASMA KISMINA WRITECONTROL DEĞİŞKENİNE YAZIN.
                                  // loop en altında karşılaştırma satırında commandseq 2 durumuna göre çalışır.   
  commandseq=2;digitalWrite(LED_BUILTIN, LOW);
  }
  
  if (counttime==150 && saybak==1){// 150 olduğunda araya girme değişkeni ayarlar ve saybak=1 olduğunda bu değişken komutu yollar. 
                                    // bu sadece RS komutu yollar. Fakat gereksizdir örnek olsun diye yazdım kaldırabilirsiniz. 
                                    // gerektiğinde devreye almak için 15 yazın 25 ten büyük olamaz. 
  commandseq=4;digitalWrite(LED_BUILTIN, LOW);
  }


  
  if (saybak==1 && commandseq==1 && writecontrol==0){
    deviceread();// **** cihaz bilgisini ESP den ister <RO> komutu yollar
    saybak=0;counttime++;
  }
 
 if (saybak==1 && commandseq==2){ // **** WO ile tüm çıkış durumlarını thingspeak sitesine yollar.  
  devicesend(); // her 20 döngüde 1 kez cihaz değerlerini yollayacak. 
  saybak=0;commandseq=1;counttime++;writecontrol=0;
 }
 
 if (saybak==1 && commandseq==3){  
  sensorcontrol(); // **** her 25 döngüde 1 kez sensör değerlerini yollayacak.
                   // bu değerler normalde 25 döngüde bir gitse de ALARM olduğunda direkt olarak göndermeniz gerekir. 
                   // bunu alarm olarak bir kanala aktardğınızda thingspeak kullanıcıya e-mail gönderebilir. 
  saybak=0;commandseq=1;counttime=0;
 }
 
 if (saybak==1 && commandseq==4){// *** Bu ise <RS> komutunu yollayarak thingspeaktan sensör verilerini okumasını ister. 
                                 // fakat sensör verilerini çok gerekmedikçe oradan almayız. Bundan dolayı bu kısmı kaldırabilirsiniz.  
  sensorread(); 
  saybak=0;commandseq=1;counttime++;
 }
 
 if ((stringRX.indexOf("READY"))>0){// normalde READY aramam gerekir ama indexoff 1. karakteri görmüyor. hata yapıyor.
  saybak=1; //**** Bu değişken READY komutu geldiğinde hazır olduğunu bildirir. Her READY geldiğinde 1 komut devreye girer.
  //Serial.print("ready");
 }
  
  delay(1000); 
}
