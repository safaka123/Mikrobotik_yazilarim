// ardu yeni program
#include <LM35.h>
#include <HCSR04.h>
#include <SoftwareSerial.h>

const byte rxPin = A5;
const byte txPin = 13;

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);



word cihaz_durum = 0;

typedef struct {
  const char* deviceName;
  int bitPosition;
} DeviceMapping;

// const keyword'ü, dizinin içeriğinin değiştirilemeyeceğini belirtir,
// bu da bellekte daha verimli depolanmasına yardımcı olabilir.
// Dizinin boyutunu otomatik olarak hesaplamak için sizeof kullanıyoruz.
const DeviceMapping deviceMap[] = {
  {"mut_ayd",  0}, // Mutfak lambası
  {"mis_ayd",  1}, // Misafir oda lambası
  {"ot_ayd",   2}, // Oturma oda lambası
  {"ba_ayd",   3}, // Banyo lambası
  {"ko_ayd",   4}, // Koridor ışığı
  {"ya_ayd",   5}, // Yatak oda lambası
  {"wc_ayd",   6}, // WC lambası
  {"ot_ac",    7}, // Oturma oda AC (küçük harfe çevirdim, tutarlılık için)
  {"ya_ac",    8}, // Yatak oda AC (küçük harfe çevirdim, tutarlılık için)
  {"ba_fan",   9}, // Banyo fanı
  {"kombi",    10}, // Kombi
  {"ot_tv",    11}  // Oturma oda TV
  // Yeni cihazlar ekledikçe buraya ekleyebilirsiniz
};

// Dizinin eleman sayısını otomatik olarak hesaplamak için bir makro (veya const int) kullanabilirsiniz.
const int DEVICE_MAP_SIZE = sizeof(deviceMap) / sizeof(deviceMap[0]);


// Seri porttan gelen komutları geçici olarak depolamak için bir tampon (buffer)
char incomingCommand[150]; // Gelen en uzun komuta göre boyutu ayarlayın (örn. "MUT_AYD=1" 9 karakter)
int commandIndex = 0; // Buffer'ın mevcut doluluk indeksi

unsigned long sonOkumaZamani = 0;
const long intervalAlarmYok = 30000; // 30 saniye
const long intervalAlarmVar = 10000; // 10 saniye



int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 10;
////Pin connected to DS of 74HC595
int dataPin = 9;
bool ayrac = false;
bool hareket_var=false;
int harcount=0;

HCSR04 hc(12, 11); //initialisation class HCSR04 (trig pin , echo pin)

LM35 sensor(0);
const int pinSayA = 2;
const int pinSayB = 3;
const int pinSayC = 4;
const int duman_dig = 6;
const int su_dig = 5;
const int ayd_b_dig = 7;

word sayi = 0;
String gelenVeri = "";
bool veriBekleniyor = false;
int sayzaman=0;

int mut_su=0;
int mis_su=0;
int ot_su=0;
int ya_su=0;
int ba_su=0;
int ko_su=0;
int wc_su=0;

int mut_duman=0;
int mis_duman=0;
int ot_duman=0;
int ya_duman=0;
int kapi_ses=0;
int mut_gaz=0;

int mut_ayd=0;
int mis_ayd=0;
int ba_ayd=0;
int ko_ayd=0;
int ot_ayd=0;
int ya_ayd=0;
int wc_ayd=0;
int ot_ac=0;
int ya_ac=0;
int ot_tv=0;
int ba_fan=0;
int kombi=0;

int mut_ayd_b=0;
int mis_ayd_b=0;
int ba_ayd_b=0;
int ko_ayd_b=0;
int ot_ayd_b=0;
int ya_ayd_b=0;
int wc_ayd_b=0;
int zil_b=0;
bool mut_ayd_f=false;
bool mis_ayd_f=false;
bool ba_ayd_f=false;
bool ko_ayd_f=false;
bool ot_ayd_f=false;
bool ya_ayd_f=false;
bool wc_ayd_f=false;
bool zil_b_f=false;



int mut_temp=0;
int mis_temp=0;
int ba_temp=0;
int ko_temp=0;
int ot_temp=0;
int ya_temp=0;
int kapi_mes=0;

int bitDegeriA; // bitRead sonucunu saklamak için yeni değişken
int bitDegeriB;
int bitDegeriC;

int alarm=0;
String komut="";
bool ack_flag=false;

void setup() {
  Serial.begin(9600);
  pinMode(pinSayA, OUTPUT);
  pinMode(pinSayB, OUTPUT);
  pinMode(pinSayC, OUTPUT);
  pinMode(su_dig, INPUT);
  pinMode(duman_dig, INPUT);
  pinMode(ayd_b_dig, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  mySerial.begin(9600);
  mySerial.println(" soft serial basladi");
}
// ???????????????????????    aydınlatma butonlarının kontrolü ??????????????????
void butonkontrol(){ 
  //buton flag kontrol false ise aşağıda kontrol yap. 
  //Serial.print(" buton durumu : ");
  //Serial.println(mut_ayd_b);
  //Serial.println(mut_ayd_f);
  if (mut_ayd_b==1 & mut_ayd_f==false){
      cihaz_durum ^= (1 << 0);// bit işlem olarak ^= operatörü, XOR (özel VEYA) atamasını yapar.
      mut_ayd_f=true;
  }    
  if (mis_ayd_b==1 & mis_ayd_f==false){
      cihaz_durum ^= (1 << 1); 
      mis_ayd_f=true;
  }    
  if (ot_ayd_b==1 & ot_ayd_f==false){
      cihaz_durum ^= (1 << 2); 
      ot_ayd_f=true;
  }    
  if (ba_ayd_b==1 & ba_ayd_f==false){
      cihaz_durum ^= (1 << 3);
      ba_ayd_f=true; 
  }    
  if (ko_ayd_b==1 & ko_ayd_f==false){
      cihaz_durum ^= (1 << 4);
      ko_ayd_f=true; 
  }    
  if (ya_ayd_b==1 & ya_ayd_f==false){
      cihaz_durum ^= (1 << 5); 
      ya_ayd_f=true;
  }    
  if (wc_ayd_b==1 & wc_ayd_f==false){
      cihaz_durum ^= (1 << 6); 
      wc_ayd_f=true;
  }    
  
  //Serial.print(" cihaz durumu : ");
  //Serial.println(cihaz_durum);
  outputs();
}



void sensoroku(){
  alarm=0;
  harcount ++;
  mySerial.print(" KAPI ALARM sayac : ");
  mySerial.println(harcount);
   // hc_se04 sensör okuma bölümü
   //Serial.println(hc.dist()); // return curent distance in serial
    //delay(60);  
    if (hc.dist()<40){
       kapi_mes=0; 
       hareket_var=false;
       harcount=0;          
    }else{
      kapi_mes=hc.dist();
      mySerial.print(" KAPI ALARM : ");
      mySerial.println(kapi_mes);
     
    }
    if (zil_b==1){
      hareket_var=false;
      harcount=0;
    }
    if (harcount >= 3){
      alarm=2;
      harcount=0;
      hareket_var=true;
      mySerial.print("hareket alarm : ");
      mySerial.println(alarm);
    }
    if (hareket_var){
      alarm=2;
      mySerial.print("hareket var : ");
      mySerial.println(hareket_var);
      mySerial.print("hareket alarm : ");
      mySerial.println(alarm);
    }

    
    //=======================================
    // multiplexer sayıcısı sayma kısmı. 0-7 arası sayar. 3 bit. 
  for(int i = 0; i < 8; ++i) // 3 bit sayaç multiplexer için.
  {
    sayi=i;//Serial.println(sayi);
  bitDegeriA = bitRead(sayi, 0);
  if (bitDegeriA == 1) { 
    digitalWrite(pinSayA, HIGH); 
  } else {
    digitalWrite(pinSayA, LOW);  
  }
  
  bitDegeriB = bitRead(sayi, 1);
  if (bitDegeriB == 1) {
    digitalWrite(pinSayB, HIGH); 
  } else {
    digitalWrite(pinSayB, LOW); 
  }
  
  bitDegeriC = bitRead(sayi, 2);
  if (bitDegeriC == 1) {
    digitalWrite(pinSayC, HIGH); 
  } else {
    digitalWrite(pinSayC, LOW);  
  }

delay(50);
    // ***************   multiplexer semsor buton okuma başlangıç
    
    if (sayi==0){
        mut_duman=digitalRead(duman_dig);
        if (mut_duman==1){
          alarm=1;
         
        }
        mut_su=digitalRead(su_dig);
        if (mut_su==1){
          alarm=1;
          
        }
        mut_ayd_b=!(digitalRead(ayd_b_dig));// burada buton ters çalışsın diye tersini alıyorum buton kontrol bundan dolayı ters görünüyor. sebebi buton bırakıldığında 1 olması XOR gerçek tablosuna gçre çalışıyor.
          if (mut_ayd_b==1){
            butonkontrol();   
          }else{
            mut_ayd_f=false;
          }
        mut_temp=sensor.getTemp();
        
       //Serial.println(sensor.getTemp()); // Temp in celcius
       //Serial.println(mut_temp); // Temp in celcius
    }
    if (sayi==1){
        mis_duman=digitalRead(duman_dig);
        if (mis_duman==1){
          alarm=1;
          
        }
        mis_su=digitalRead(su_dig);
        if (mis_su==1){
          alarm=1;
          
        }
        mis_ayd_b=!(digitalRead(ayd_b_dig));
          if (mis_ayd_b==1){
            butonkontrol();   
          }else{
            mis_ayd_f=false;
          }
        mis_temp=sensor.getTemp();
       //Serial.println(mis_temp); // Temp in celcius
    }
    if (sayi==2){
        ot_duman=digitalRead(duman_dig);
        if (ot_duman==1){
          alarm=1;
          
        }
        ot_su=digitalRead(su_dig);
        if (ot_su==1){
          alarm=1;
          
        }
        ot_ayd_b=!(digitalRead(ayd_b_dig));
          if (ot_ayd_b==1){
            butonkontrol();   
          }else{
            ot_ayd_f=false;
          }
        ot_temp=sensor.getTemp();
       //Serial.println(ba_temp); // Temp in celcius
    }
    if (sayi==3){
        ya_duman=digitalRead(duman_dig);
        if (ya_duman==1){
          alarm=1;
          
        }
        ya_su=digitalRead(su_dig);
        if (ya_su==1){
          alarm=1;
          
        }
        ya_ayd_b=!(digitalRead(ayd_b_dig));
          if (ya_ayd_b==1){
            butonkontrol();   
          }else{
            ya_ayd_f=false;
          }
        ya_temp=sensor.getTemp();
       //Serial.println(ko_temp); // Temp in celcius
    }
    if (sayi==4){
        kapi_ses=digitalRead(duman_dig);
        if (kapi_ses==1){
          alarm=2;
          hareket_var=true;
        }


        
        //*** buradan kapı ses kontrol kısmına gidip hareket sensörü gibi sayaçlı kontrol yap. şayet 150 sayac olursa hala ses devam ediyorsa ve zil butonuna basılmadıysa alarm tetikle. 


        
        ba_su=digitalRead(su_dig);
        if (ba_su==1){
          alarm=1;
          
        }
        ba_ayd_b=!(digitalRead(ayd_b_dig));
          if (ba_ayd_b==1){
            butonkontrol();   
          }else{
            ba_ayd_f=false;
          }
        ba_temp=sensor.getTemp();
       //Serial.println(ot_temp); // Temp in celcius
    }
    if (sayi==5){
        mut_gaz=digitalRead(duman_dig);
        if (mut_gaz==1){
          alarm=1;
          
        }
        ko_su=digitalRead(su_dig);
        if (ko_su==1){
          alarm=1;
          
        }
        ko_ayd_b=!(digitalRead(ayd_b_dig));
          if (ko_ayd_b==1){
            butonkontrol();   
          }else{
            ko_ayd_f=false;
          }
        ko_temp=sensor.getTemp();
       //Serial.println(ya_temp); // Temp in celcius
    }
    if (sayi==6){
        wc_su=digitalRead(su_dig);
        if (wc_su==1){
          alarm=1;
          
        }
        wc_ayd_b=!(digitalRead(ayd_b_dig));
          if (wc_ayd_b==1){
            butonkontrol();   
          }else{
            wc_ayd_f=false;
          }
         
       
    }
    if (sayi==7){   
        zil_b=digitalRead(ayd_b_dig);
          if (zil_b==1){
            butonkontrol();   
          }else{
            zil_b_f=false;
          }
        //Serial.println(zil_b); // Temp in celcius
    }
   // **************    MULTIPLEXER sensör buton okuma sonu

}

}


// *************************  74HC595 ile kontrol edilen cihazlar.  ***************
void outputs(){
  //buraya python komut versin. hem button kontrolden hem de pythondan gelen bilgiye göre çıkış yapsın. 
  // cihaz_durum word değişkeni buraya geldiğinde direkt olarak yazılacak. 74hc595 çıkışları verecek.
  
// bit test için bu şekilde kontrol edilir. 
  //if ((mut_ayd_b >> 0) & 1) {
  //    cihaz_durum |= (1 << 0);
  //}else {
  //    bitClear(cihaz_durum, 0);
  //}

  //BİT SET YAPMAK İÇİN istersek bitset komutunu kullanırız
  //istersek de bunu kullanırız. 
  //  cihaz_durum|= (1 << 3);
  //bitclear komutunu da kullanırız ya da bu şekilde yapabiliriz. 
   // var &= ~(1 << 9);      // Clears bit 9

   
// cihaz durum parçalaması
    if ((cihaz_durum >> 0) & 1) {
      mut_ayd=1;
    }else{
      mut_ayd=0;
    }
    if ((cihaz_durum >> 1) & 1) {
      mis_ayd=1;
    }else{
      mis_ayd=0;
    }
    if ((cihaz_durum >> 2) & 1) {
      ot_ayd=1;
    }else{
      ot_ayd=0;
    }
    if ((cihaz_durum >> 3) & 1) {
      ba_ayd=1;
    }else{
      ba_ayd=0;
    }
    if ((cihaz_durum >> 4) & 1) {
      ko_ayd=1;
    }else{
      ko_ayd=0;
    }
    if ((cihaz_durum >> 5) & 1) {
      ya_ayd=1;
    }else{
      ya_ayd=0;
    }
    if ((cihaz_durum >> 6) & 1) {
      wc_ayd=1;
    }else{
      wc_ayd=0;
    }
    if ((cihaz_durum >> 7) & 1) {
      ot_ac=1;
    }else{
      ot_ac=0;
    }
    if ((cihaz_durum >> 8) & 1) {
      ya_ac=1;
    }else{
      ya_ac=0;
    }
    if ((cihaz_durum >> 9) & 1) {
      ba_fan=1;
    }else{
      ba_fan=0;
    }
    if ((cihaz_durum >> 10) & 1) {
      kombi=1;
    }else{
      kombi=0;
    }
    if ((cihaz_durum >> 11) & 1) {
      ot_tv=1;
    }else{
      ot_tv=0;
    }


    //Serial.print( " Cihaz durumlari : ");
    //Serial.println(cihaz_durum);
    digitalWrite(latchPin, LOW);    // ST_CP ucu LOW yapılır
    shiftOut(dataPin, clockPin, MSBFIRST, highByte(cihaz_durum));   // DATA ve CLOCK bilgisi seri olarak gönderilir ve 8 bit olarak 74HC595
    shiftOut(dataPin, clockPin, MSBFIRST, lowByte(cihaz_durum));   // DATA ve CLOCK bilgisi seri olarak gönderilir ve 8 bit olarak 74HC595
    digitalWrite(latchPin, HIGH); // ST_CP ucu HIGH yapılarak gelen bilginin paralel çıkışa yansıması sağlanır.
    
}

// python programına gönderilenler.
void send_info(){
if (ayrac==true){// bu seri port gönderirken ayrı ayrı gönderilsin diye yapıldı. ayrac true sensörleri ayrac false cihazları gönderir. 
      if (alarm==1){
          String sensors=("ALARM,"+String(mut_duman)+","+String(mis_duman)+","+String(ot_duman)+","+String(ya_duman)+","+String(mut_su)+","+String(mis_su)+","+String(ot_su)+","+String(ya_su)+","+String(ba_su)+","+String(ko_su)+","+String(wc_su)+","+String(zil_b)+","+String(kapi_ses)+","+String(mut_gaz)+","+String(mut_temp)+","+String(mis_temp)+","+String(ot_temp)+","+String(ba_temp)+","+String(ko_temp)+","+String(ya_temp)+","+String(kapi_mes)+","+kapi_mes);
          Serial.println(sensors);
    
      }else{
          String sensors=(String(mut_duman)+","+String(mis_duman)+","+String(ot_duman)+","+String(ya_duman)+","+String(mut_su)+","+String(mis_su)+","+String(ot_su)+","+String(ya_su)+","+String(ba_su)+","+String(ko_su)+","+String(wc_su)+","+String(zil_b)+","+String(kapi_ses)+","+String(mut_gaz)+","+String(mut_temp)+","+String(mis_temp)+","+String(ot_temp)+","+String(ba_temp)+","+String(ko_temp)+","+String(ya_temp)+","+String(kapi_mes)+","+kapi_mes);
          Serial.println(sensors);
      }

  }else{
            String cihazlar=("cihaz,"+String(mut_ayd)+","+String(mis_ayd)+","+String(ot_ayd)+","+String(ba_ayd)+","+String(ko_ayd)+","+String(ya_ayd)+","+String(wc_ayd)+","+String(ot_ac)+","+String(ya_ac)+","+String(ba_fan)+","+String(kombi)+","+String(ot_tv));
            Serial.println(cihazlar);
            Serial.println(cihaz_durum,BIN);
       }
  ayrac = !ayrac;
  //outputs(); // 74hc595 entegresine tüm bitleri yazdırır. 
 
  delay(100);  
}

// Gelen komutu işleyen fonksiyon

void komut_isle(String komutlar){
  if (komutlar == "guvenlik_modu"){
    mySerial.println(komutlar);
      return;
  }

  if (komutlar == "resume"){
    mySerial.println("resume");
      return;
  }

  komutlar +='\n';
  
    // Simüle edilecek komut stringi
const char* testCommand = "mut_ayd=1,ot_ayd=1,ot_ac=1,ya_ayd=1 \n";

// Test komutunu 'incomingCommand' tamponuna kopyala
// strncpy kullanırken tampon boyutunu aşmamaya dikkat edin.
// Son karakterin her zaman null sonlandırma olduğundan emin olmak önemlidir.
//strncpy(incomingCommand, testCommand, sizeof(incomingCommand) - 1);
strncpy(incomingCommand, komutlar.c_str(), sizeof(incomingCommand) - 1);
incomingCommand[sizeof(incomingCommand) - 1] = '\0'; // Null sonlandırma

mySerial.print("Simule edilen ana komut: ");
mySerial.println(incomingCommand);
mySerial.println("--- Alt Komutlar Isleniyor ---");

// Ana komut stringini virgüllere göre parçala
// strtok_r için bir bağlam işaretçisi (context pointer) tanımlayın
char* restOfMainCommand = incomingCommand; // Ana komut için bağlam

char* subCommand = strtok_r(restOfMainCommand, ",", &restOfMainCommand);

while (subCommand != NULL) {
  // Her bir alt komutu (örn. "mut_ayd=1") işle
  processCommand(subCommand);
  subCommand = strtok_r(NULL, ",", &restOfMainCommand);
}

commandIndex = 0;
memset(incomingCommand, 0, sizeof(incomingCommand));

}



void processCommand(char* command) {
  char* restOfSubCommand = command; // Alt komut için bağlam

  char* deviceNameStr = strtok_r(restOfSubCommand, "=", &restOfSubCommand);
  char* stateStr = strtok_r(NULL, "=", &restOfSubCommand);

  if (deviceNameStr != NULL && stateStr != NULL) {
    int targetState = atoi(stateStr); // Durum stringini sayıya çevir (0 veya 1)

    bool deviceFound = false; // Cihazın bulunup bulunmadığını takip etmek için
    for (int i = 0; i < DEVICE_MAP_SIZE; i++) {
      if (strcmp(deviceNameStr, deviceMap[i].deviceName) == 0) {
        // Cihaz bulundu, şimdi cihaz_durum'daki ilgili biti ayarla
        if (targetState == 1) {
          // Biti ayarla (SET)
          cihaz_durum |= (1 << deviceMap[i].bitPosition);
        } else {
          // Biti temizle (CLEAR)
          cihaz_durum &= ~(1 << deviceMap[i].bitPosition);
        }

        mySerial.println(deviceNameStr);
        mySerial.print(" durumu ayarlandi: ");
        mySerial.println(targetState);
        deviceFound = true;

        // Cihaz durumu güncellendikten sonra 74HC595'e gönder
        //updateShiftRegister(cihaz_durum);
        mySerial.println(cihaz_durum,BIN);
        break; // Cihaz bulunduğunda döngüyü sonlandır
      }
    }

    if (!deviceFound) {
      mySerial.println("Bilinmeyen cihaz adi veya komut gecersiz: ");
      mySerial.println(deviceNameStr);
    }
  } else {
    mySerial.println("Gecersiz komut formati: ");
    mySerial.println(command);
  }
}

void seriHaberlesmeIsleyici() {
  String komut="";
  String gelenVeri = Serial.readStringUntil('\n');
  gelenVeri.trim();

  if (gelenVeri == "guvenlik_modu"){
    mySerial.println(gelenVeri);
      return;
  }

  if (gelenVeri == "resume"){
    mySerial.println(gelenVeri);
      return;
  }

  static bool veriBekleniyor = false;

  if (gelenVeri == "REQ_WRITE") {
    Serial.println("READY");
    veriBekleniyor = true;
  } 
  else if (veriBekleniyor && gelenVeri.startsWith("DATA:")) {
    komut = gelenVeri.substring(5);
    komut.trim();
    mySerial.print("komut:  ");
    mySerial.println(komut);
    if (komut.length() > 0) {
      Serial.println("ACK");
      delay(50);  // Gerekirse azaltılabilir
      ack_flag=true;
      
    } else {
      Serial.println("NACK");
    }
    veriBekleniyor = false;
  } 
  else {
    Serial.println("NACK");
    veriBekleniyor = false;
  }
  if(ack_flag==true){
    mySerial.print("gelenveri: ");
    mySerial.println(gelenVeri);
    mySerial.println(komut);
    komut_isle(komut);  // Asıl iş burada yapılır
    //ack_flag=false;
  }
}





// ==================  ANA DÖNGÜ ==============================

unsigned long son_sensor_zamani = 0;
//unsigned long sensor_gonderme_suresi = 0;
const unsigned long alarmli_interval = 5000;  // 10 saniye
const unsigned long norm_interval   = 10000;  // 30 saniye
unsigned long sensor_gonderme_suresi = 0;
unsigned long buton_kontrol_suresi = 0;

void loop() {
  int saybekle=0;
  unsigned long suan = millis();

  if (Serial.available()) {
    seriHaberlesmeIsleyici();  // Seri veriyi işle
  }


  if (suan - buton_kontrol_suresi >= 500) {  // 200 ms
    buton_kontrol_suresi = suan;
    
    sensoroku();    // butonlar burada okunur
    //mySerial.println(suan);

    outputs();      // yeni veriye göre tepki verir
  }

  
  
  //outputs();  // Butonlara anlık tepki ver

  // Güvenlik modu kontrolü
  if (komut == "guvenlik_modu") {
    saybekle = 1;
    ack_flag = false;
  }

  if (komut == "resume") {
    saybekle = 0;
    sayzaman = 0;
    delay(1000);  // Çok kısa bekleme
  }

  // Python'a hazır olduğumuzu bildir
  if (ack_flag == true) {
    ack_flag = false;
    outputs();  // Cihazların son durumu
    String cihazlar = "cihaz," + String(mut_ayd) + "," + String(mis_ayd) + "," +
                      String(ot_ayd) + "," + String(ba_ayd) + "," + String(ko_ayd) + "," +
                      String(ya_ayd) + "," + String(wc_ayd) + "," + String(ot_ac) + "," +
                      String(ya_ac) + "," + String(ba_fan) + "," + String(kombi) + "," +
                      String(ot_tv);
    //Serial.println(cihazlar);
  }

  // Sensör veri gönderme zamanı geldi mi?
  //unsigned long suan = millis();

  if (saybekle == 0) {
    unsigned long hedef_sure = (alarm == 1) ? alarmli_interval : norm_interval;

    if (suan - sensor_gonderme_suresi >= hedef_sure) {
      sensor_gonderme_suresi = suan;

      // Sensörleri oku ve gönder
      //sensoroku();
      
      if (alarm == 1) {
        String sensors = "ALARM," + String(mut_duman) + "," + String(mis_duman) + "," + String(ot_duman) + "," +
                         String(ya_duman) + "," + String(mut_su) + "," + String(mis_su) + "," + String(ot_su) + "," +
                         String(ya_su) + "," + String(ba_su) + "," + String(ko_su) + "," + String(wc_su) + "," +
                         String(zil_b) + "," + String(kapi_ses) + "," + String(mut_gaz) + "," +
                         String(mut_temp) + "," + String(mis_temp) + "," + String(ot_temp) + "," +
                         String(ba_temp) + "," + String(ko_temp) + "," + String(ya_temp) + "," +
                         String(kapi_mes)+"," + String(25);
        Serial.println(sensors);
      } else if (hareket_var == 1) {
        String sensors = "DiKKAT," + String(mut_duman) + "," + String(mis_duman) + "," + String(ot_duman) + "," +
                         String(ya_duman) + "," + String(mut_su) + "," + String(mis_su) + "," + String(ot_su) + "," +
                         String(ya_su) + "," + String(ba_su) + "," + String(ko_su) + "," + String(wc_su) + "," +
                         String(zil_b) + "," + String(kapi_ses) + "," + String(mut_gaz) + "," +
                         String(mut_temp) + "," + String(mis_temp) + "," + String(ot_temp) + "," +
                         String(ba_temp) + "," + String(ko_temp) + "," + String(ya_temp) + "," +
                         String(kapi_mes)+"," + String(25) ;
        Serial.println(sensors);
      }else {
        String sensors = String(mut_duman) + "," + String(mis_duman) + "," + String(ot_duman) + "," +
                         String(ya_duman) + "," + String(mut_su) + "," + String(mis_su) + "," + String(ot_su) + "," +
                         String(ya_su) + "," + String(ba_su) + "," + String(ko_su) + "," + String(wc_su) + "," +
                         String(zil_b) + "," + String(kapi_ses) + "," + String(mut_gaz) + "," +
                         String(mut_temp) + "," + String(mis_temp) + "," + String(ot_temp) + "," +
                         String(ba_temp) + "," + String(ko_temp) + "," + String(ya_temp) + "," +
                         String(kapi_mes)+"," + String(25);
        Serial.println(sensors);
      }

      delay(50);  // Seri port taşmasını önlemek için

      // Cihaz durumu gönder
      String cihazlar = "cihaz," + String(mut_ayd) + "," + String(mis_ayd) + "," +
                        String(ot_ayd) + "," + String(ba_ayd) + "," + String(ko_ayd) + "," +
                        String(ya_ayd) + "," + String(wc_ayd) + "," + String(ot_ac) + "," +
                        String(ya_ac) + "," + String(ba_fan) + "," + String(kombi) + "," +
                        String(ot_tv);
      Serial.println(cihazlar);
    }
  }

  // loop sonunda çok kısa bir delay
  delay(10);
}

/*
void loop() { 
  int saybekle=0;
  
  if (Serial.available()) {
    seriHaberlesmeIsleyici();  // Tüm haberleşme ve işleme bu fonksiyonda
  }

  // Diğer görevler (örnek: sensör okumak, çıkış kontrolü vs.)



  outputs();

  // güvenlik modu kelimesi geldiğinde arduino bilgi göndermeyi kesecek. şayet resume gelirse tekrar göndermeye başlayacak. 

  if (komut=="guvenlik_modu"){
      saybekle=1;
      ack_flag=false;
  }
  
  if (komut=="resume"){
      saybekle=0;
      sayzaman=0;
      //ack_flag=true;
      //delay(1000);
  }
  
  if (ack_flag==true){
    ack_flag=false;
    outputs();
    //Serial.println("cihaz,0,0,1,0,0,0,0,0,0,0,0,0");
    String cihazlar=("cihaz,"+String(mut_ayd)+","+String(mis_ayd)+","+String(ot_ayd)+","+String(ba_ayd)+","+String(ko_ayd)+","+String(ya_ayd)+","+String(wc_ayd)+","+String(ot_ac)+","+String(ya_ac)+","+String(ba_fan)+","+String(kombi)+","+String(ot_tv));
    Serial.println(cihazlar);
  }
  sensoroku();
  sayzaman ++;
  if (sayzaman >=3 & alarm==1& saybekle==0){
    sayzaman=0;
    sensoroku();
    String sensors=("ALARM,"+String(mut_duman)+","+String(mis_duman)+","+String(ot_duman)+","+String(ya_duman)+","+String(mut_su)+","+String(mis_su)+","+String(ot_su)+","+String(ya_su)+","+String(ba_su)+","+String(ko_su)+","+String(wc_su)+","+String(zil_b)+","+String(kapi_ses)+","+String(mut_gaz)+","+String(mut_temp)+","+String(mis_temp)+","+String(ot_temp)+","+String(ba_temp)+","+String(ko_temp)+","+String(ya_temp)+","+String(kapi_mes)+","+"25.00");
    Serial.println(sensors);
    delay(100);
    String cihazlar=("cihaz,"+String(mut_ayd)+","+String(mis_ayd)+","+String(ot_ayd)+","+String(ba_ayd)+","+String(ko_ayd)+","+String(ya_ayd)+","+String(wc_ayd)+","+String(ot_ac)+","+String(ya_ac)+","+String(ba_fan)+","+String(kombi)+","+String(ot_tv));
    Serial.println(cihazlar);
  }  
  if (sayzaman >= 3 & alarm==0 & saybekle==0){
    sayzaman=0;
    sensoroku();
    String sensors=(String(mut_duman)+","+String(mis_duman)+","+String(ot_duman)+","+String(ya_duman)+","+String(mut_su)+","+String(mis_su)+","+String(ot_su)+","+String(ya_su)+","+String(ba_su)+","+String(ko_su)+","+String(wc_su)+","+String(zil_b)+","+String(kapi_ses)+","+String(mut_gaz)+","+String(mut_temp)+","+String(mis_temp)+","+String(ot_temp)+","+String(ba_temp)+","+String(ko_temp)+","+String(ya_temp)+","+String(kapi_mes)+","+"25.00");
    Serial.println(sensors);
    delay(100);
    String cihazlar=("cihaz,"+String(mut_ayd)+","+String(mis_ayd)+","+String(ot_ayd)+","+String(ba_ayd)+","+String(ko_ayd)+","+String(ya_ayd)+","+String(wc_ayd)+","+String(ot_ac)+","+String(ya_ac)+","+String(ba_fan)+","+String(kombi)+","+String(ot_tv));
    Serial.println(cihazlar);
    
  }
      
  delay(100);

}*/
