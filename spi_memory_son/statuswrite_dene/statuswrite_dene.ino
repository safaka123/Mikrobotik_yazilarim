#include <SPI.h>
 uint16_t addr=0;
 uint16_t bak=0;
 uint8_t yaz=10;

void setup (void)
{
  pinMode(2, INPUT);
  //digitalWrite(2, HIGH);// status için wp ucu kontrol
  Serial.begin(9600);
   
  digitalWrite(SS, HIGH);  
  SPI.begin ();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  
  digitalWrite(SS, LOW);  // erase 
  SPI.transfer (0xC7);
  //SPI.transfer (0x00);
  //SPI.transfer (0x01);
  //SPI.transfer (0x02);
  digitalWrite(SS, HIGH); 
  delay(1000);

  digitalWrite(SS, LOW);  // read ID (MAC) burayı tekrar düzenle. ***********************
  SPI.transfer (0x4B);
  SPI.transfer (0);
  SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(1000);

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);

 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //  SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);


 digitalWrite(SS, LOW);  // status write
  SPI.transfer (1);
  //SPI.transfer (0);
  digitalWrite(SS, HIGH); 
  delay(1000);
 // buton();
} 

void buton(){
int i=0;
for ( i =0; i <= 5; i++) {
    
 
Serial.print(" Asagi sayma  butona basin ") ;Serial.print(" yazilacak deger ");Serial.print(yaz);
while (digitalRead(2) == HIGH) {

  }

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);
 //addr=7;
 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(1000);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (1000); 

 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);
 delay (1000); 
yaz=yaz-1;
}

Serial.print( "    onceki bilgiler silinecek  ");
delay (5000);
//  önceki yazılanlar silinecek. PAGE ERASE sadece verilen adresten itibaren 128 byte sıfırlar. 
digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH);
  delay(1000);
  
  digitalWrite(SS, LOW);  // PAGE ERASE
  SPI.transfer (0x42);
  SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  digitalWrite(SS, HIGH); 
  delay(3000);
// ****************     PE   sonu 

for ( i =0; i <= 5; i++) {
Serial.print(" yukari sayma butona basin ") ;Serial.print(" yazilacak deger ");Serial.print(yaz);
while (digitalRead(2) == HIGH) {

  }

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);
 //addr=7;
 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(1000);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (1000); 

 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (1000); 
yaz=yaz+1;

   }
  
}


 
void loop (void)//***************************************************
{
  char c;
  digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);

digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH); 
 
 delay(10);

 digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);
 
 addr=0xFF80;
  digitalWrite(SS, LOW);   // write byte
 yaz=9; 
    SPI.transfer (2);
    SPI.transfer (0);
    //SPI.transfer(addr>> 16 );
    SPI.transfer(addr>> 8 );
    SPI.transfer(addr);
    //SPI.transfer (0);
for (const char * p = "123456789098765432101234567890987654321012345678909876543210123456789098765432101234567890987654321012345678909876543210Merhaba!" ; c = *p; p++)
   SPI.transfer (c);
  digitalWrite(SS, HIGH);
 delay (3000); 

 
digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr+1);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (1000); 


 
//***********************************************************************

  Serial.print("PAGE ERASE BASLADI ");
digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH);
  
  delay(3000);
  digitalWrite(SS, LOW);  // erase 
  SPI.transfer (0x42);
  SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  digitalWrite(SS, HIGH); 
  delay(1000);

  
digitalWrite(SS, LOW);  // reset
  SPI.transfer (4);
  //SPI.transfer (0);
  digitalWrite(SS, HIGH); 
  delay(5000);


digitalWrite(SS, LOW);  // status write
  SPI.transfer (1);
  digitalWrite(SS, HIGH); 
  delay(1000);



  
 
 digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);
 //addr=7;
 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(1000);
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0xFE);
  digitalWrite(SS, HIGH);
 
 delay (3000); 
//DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDdd
digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    
   result = SPI.transfer(0);
  //uint8_t result1 = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (1000); 


digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);

digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH); 
 
 delay(10);

 digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);

  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0xAA);
//for (const char * p = "Merhaba!\n" ; c = *p; p++)
//   SPI.transfer (c);

  digitalWrite(SS, HIGH);
 //Serial.print(" write modulu : ");Serial.println(resultw,HEX);
 delay (3000); 

//DdDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD

 

//************** tek adres değiştirme  : ilk önce değeri oku. sonra FF den çıkararak FFye ulaşması için gereken sayı ortaya çıksın
// sonrasında okunan deger+fark değer+verilecek değer olarak yazarak koy. 
Serial.println(" degistirme bolumu ");

 delay(3000);
 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(100);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
   result = SPI.transfer(0);
  //uint8_t result1 = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);
 delay (100); 
  

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);

digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH); 
 
 delay(1000);

 digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);

  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr+1);
    SPI.transfer(0xAB);
  digitalWrite(SS, HIGH);
 delay (3000); 
digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(100);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr+1);
    
   result = SPI.transfer(0);
  //uint8_t result1 = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);
 delay (1000); 

}



