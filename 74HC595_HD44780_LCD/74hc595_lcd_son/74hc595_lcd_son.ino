/*

UNO ve 74HC595 ile kontrol edilen 2 ayrı çalışma şekilli LCD kontrol programı
*/
//UNO pin kullanımı
int RS = 8; 
int RW = 9;  
int EN = 10;

// PORT D data için kullanılıyor. 
int RSS=0;
byte temp1=0;
byte temp2=0;
byte temp3=0;
int say=0;
int LED=0;
int timesay=0;
String AKTAR="";

//Pin SH_CP of 74HC595 
int CLOCK = 13; 
//Pin ST_CP of 74HC595 
int LATCH = 11; 
//Pin DS of 74HC595 
int DATA = 12;




void setup() {
  Serial.begin(9600);
  
//UNO pim dağılımı  
pinMode(RS, OUTPUT); 
pinMode(RW, OUTPUT); 
pinMode(EN, OUTPUT); 
// 74HC595 pimleri
pinMode(CLOCK, OUTPUT); 
pinMode(LATCH, OUTPUT); 
pinMode(DATA, OUTPUT);

Serial.println("START");
delay(1000);
DDRD=B11111101;// UNO port giriş ve çıkışları ayarlanıyor. Özellikle d4 d5 d6 d7 için birlikte kullanılıyor.
delay(100);
// INITIALIZE Başlangıcı
temp1=0x30;timesay=5000;sendcode(0);
temp1=0x30;timesay=200;sendcode(0);
temp1=0x30;timesay=200;sendcode(0);
temp1=0x20;timesay=200;sendcode(0);
temp1=0x28;timesay=200;sendcode(1);
temp1=0x08;timesay=200;sendcode(1);
temp1=0x01;timesay=200;sendcode(1);
temp1=0x06;timesay=200;sendcode(1);
temp1=0x0F;timesay=200;sendcode(1);

}

void LEDONOFF(int ledon){
  LED=ledon;
  Serial.print("LED   : "+String(LED));
  if (ledon==1){
    temp2=B00001000;
    PORTD=B00001000;
    //delay(1000);
    ;PORTD=PORTD;
  }else{
    temp2=B00000000;
    PORTD=B00000000;
    //delay(1000);
  }
  digitalWrite(LATCH, LOW); 
  shiftOut(DATA, CLOCK, MSBFIRST, temp2);//RS,RW=0  E=1 
  digitalWrite(LATCH, HIGH); 
  delayMicroseconds(200);
  delay(500);
}
void SENDER(){
 if (LED==1){
  PORTD|B00001000;
  temp2=temp2|B00001000;
}else{
  PORTD&B11110111;
  temp2=temp2&B11110111;
} 
   digitalWrite(RS, RSS); 
   delayMicroseconds(200);
   digitalWrite(RW, LOW); 
   delayMicroseconds(200);
   digitalWrite(EN, HIGH); 
   delayMicroseconds(200);
   PORTD=temp2;
   digitalWrite(EN, LOW);
   delayMicroseconds(timesay);
}
void SENDER1(){
if (LED==1){
  temp2=temp2|B00001000;
}else{
  temp2=temp2&B11110111;
}
// 74HC595 komutları

  digitalWrite(LATCH, LOW); 
  shiftOut(DATA, CLOCK, MSBFIRST, temp2);//RS,RW=0  E=1 
  digitalWrite(LATCH, HIGH); 
  delayMicroseconds(200);
  temp2=temp2&B11111011;// E=0
  digitalWrite(LATCH, LOW); 
  shiftOut(DATA, CLOCK, MSBFIRST, temp2); 
  digitalWrite(LATCH, HIGH); 
  delayMicroseconds(timesay); 
}

void writechar(){
Serial.println(" writechar ");
    temp2=temp1&B11110000;
    temp3=temp1&B00001111;
    temp3=temp3<<4;
Serial.println ("temp1: "+String(temp1,HEX));
Serial.println ("temp2: "+String(temp2,HEX));
Serial.println ("temp3: "+String(temp3,HEX));
    RSS=1;
    SENDER();
    byte temp4=temp2;
    temp2=temp3;
    SENDER();
    temp2=temp4;

 // 74HC595 komutları
    temp2=temp2&B11111100;//RS ve RW=0
    temp2=temp2|B00000101;//E=1 RS=1 sadece karakter datasında
    temp3=temp3&B11111100;//RS ve RW=0
    temp3=temp3|B00000101;//E=1  RS=1 sadece karakter datasında
//int temp4=temp2;

SENDER1();
    temp2=temp3;

SENDER1();

}

void sendcode(int kont){
  Serial.println(" sendcode ");
  temp2=temp1&B11110000;
  temp3=temp1&B00001111;
  temp3=temp3<<4;
Serial.println ("temp1: "+String(temp1,HEX));
Serial.println ("temp2: "+String(temp2,HEX));
Serial.println ("temp3: "+String(temp3,HEX));
 RSS=0;
 
 SENDER();
 byte temp4=temp2;
 
 if (kont==1){
 temp2=temp3;
 
 SENDER();
 temp2=temp4;
 }

// 74HC595 komutları
   temp2=temp2&B11111100;//RS ve RW=0
   temp2=temp2|B00000100;//E=1
   temp3=temp3&B11111100;//RS ve RW=0
   temp3=temp3|B00000100;//E=1
    SENDER1();
    //temp4=temp2;
    if (kont==1){
      temp2=temp3;
      SENDER1();
     }

}

void stringsend(int sata,int sutb){
    int sat=sata;
    int sut=sutb;
Serial.println(String(sata)+String(sutb));
    int startsat=80;
    if (sat==1){startsat=0x80;}// bu değerler 20*2 ve 20*4 için geçerli
    if (sat==2){startsat=0xC0;}
    if (sat==3){startsat=0x94;}
    if (sat==4){startsat=0xD4;}
Serial.println(String(startsat,HEX));
    temp1=startsat+sut-1;timesay=200;sendcode(1);
    String stdata="";
    stdata=AKTAR;
    stdata.toUpperCase();//HEX sayıları yazarken büyük harf yazsın diye komut eklendi. Fakat tüm karakterler büyük harf yazacağından kaldırılabilir.
    int stringsize=stdata.length();
    for (int b = 0; b < stringsize ; b++) 
     {
    String temp4=(stdata.substring(b,b+1));

    byte buf[1];// 1 karakterlik yer ayırır
    temp4.getBytes(buf, 2);// ASCII değerini byte olarak alıyor. 
    temp1=buf[0];// 1 karakterlik yer array de 0 dan başlar. 
          writechar();
     } 
    delay (2000);

}
void NEWCHAR(int cgramadd,byte L1,byte L2,byte L3,byte L4,byte L5,byte L6,byte L7,byte L8){
byte newchararray[8]={};
newchararray[0]=L1;
newchararray[1]=L2;
newchararray[2]=L3;
newchararray[3]=L4;
newchararray[4]=L5;
newchararray[5]=L6;
newchararray[6]=L7;
newchararray[7]=L8;
delay(1000);
temp1=0x40+(cgramadd*8);timesay=200;sendcode(1);
for (int i=0;i<8;i++){
temp1=newchararray[i];timesay=200;writechar();
}

 
}

void animasyon(){
  LEDONOFF(1);
    delay (500);
    
temp1=65;timesay=200;writechar();// sat=1 sut=1 Çünkü cursor neredeyse oraya yazar.
temp1=66;timesay=200;writechar();// sat=1 sut=2 Çünkü cursor 1 karakter yazınca sağa kayar.
temp1=0x85;timesay=200;sendcode(1);// cursor sat1 sut 6 cursor yerleştirme 1. satır 80h tan başlar 85 ise 6. sütundur.
temp1=66;timesay=200;writechar();// sat=1 sut=6 bir öncekinde cursor poz. ayarlanmıştı
temp1=0xC5;timesay=200;sendcode(1);// sat=2 sut=6 2. satır C0h ile başlar C5=6. sütun
temp1=67;timesay=200;writechar();// sat=2 sut=6 öncekinde cursor yeri ayarlanmıştı
int deg=100;temp1=100;AKTAR="den HEX:"+String(deg,HEX)+" "+String(temp1,BIN)+" C";timesay=1000;stringsend(3,1);
for (int b = 0; b <20 ; b++){
    temp1=0x18;timesay=200;sendcode(1);// display left shift
    delay(100);
   }
    delay (1000);
for (int b = 0; b <20 ; b++){
    temp1=0x1C;timesay=200;sendcode(1);// display left shift
    delay(100);
   }
    delay (1000);
    temp1=0x02;timesay=200;sendcode(1);//return home
    delay (3000);
    temp1=0x01;timesay=200;sendcode(1);//clear
    delay (500);
    AKTAR="12345678901234567890";timesay=200;stringsend(1,1);
     Serial.println("decrement and disp shift OFF    4");  
    temp1=0x04;timesay=200;sendcode(1);delay(500);
    AKTAR="DENEME TERS";timesay=200;stringsend(2,16);
    delay(3000);
    temp1=0x01;timesay=200;sendcode(1);//clear
    delay (500);
    Serial.println("decrement and disp shift ON   5");
    temp1=0x05;timesay=200;sendcode(1);delay(500);
    AKTAR="TERS KAYDIR";timesay=200;stringsend(4,20);
    delay(3000);
    temp1=0x01;timesay=200;sendcode(1);//clear
    delay (500);
    
    Serial.println("increment and disp shift ON   7");
    temp1=0x07;timesay=200;sendcode(1);delay(500);
    AKTAR="DUZ KAYDIR";timesay=200;stringsend(2,16);
    delay(3000);
    temp1=0x06;timesay=200;sendcode(1);delay(500);
    temp1=0x01;timesay=200;sendcode(1);delay(500);
    temp1=0x02;timesay=200;sendcode(1);//return home
    delay (500);
AKTAR="NORMAL YAZI";timesay=200;stringsend(4,4);
    delay(3000);
    

NEWCHAR(1,12,18,18,12,0,0,0,0);// karakter no ve yeni karakter bilgisi yazılır.1=yeni karakter no. 0-7 arası olabilir.
temp1=0xC9;timesay=200;sendcode(1);
temp1=0x01;timesay=200;writechar();
delay(3000);
temp1=67;timesay=200;writechar();
delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (1000);
temp1=0x0C;timesay=200;sendcode(1);//CURSOR HIDDEN
    delay (5000);
temp1=0x0E;timesay=200;sendcode(1);//CURSOR UNDERLINE
    delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x10;timesay=200;sendcode(1);//CURSOR LEFT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (1000);
temp1=0x14;timesay=200;sendcode(1);//CURSOR RIGHT
    delay (3000);
temp1=0x0F;timesay=200;sendcode(1);//CURSOR BLINK ve Kutu Display ON
    delay (1000);
temp1=0x0B;timesay=200;sendcode(1);//DISPLAY OFF
    delay (3000);
temp1=0x0F;timesay=200;sendcode(1);//CURSOR BLINK ve Kutu Display ON
    delay (3000);
temp1=0x01;timesay=200;sendcode(1);//clear
    delay (3000);
    LEDONOFF(0);
}

void loop() {
 
  animasyon();
 delay(5000);
}
