#include <SPI.h>
 uint16_t addr=0xFF80;
 uint16_t bak=0;
 uint8_t yaz=10;
uint8_t result;


void setup (void)
{
  pinMode(2, INPUT);
  //digitalWrite(2, HIGH);// status için wp ucu kontrol
  Serial.begin(9600);
   
  digitalWrite(SS, HIGH);  
  SPI.begin ();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

digitalWrite(SS, LOW);  // reset
  SPI.transfer (4);
  //SPI.transfer (0);
  digitalWrite(SS, HIGH); 
  delay(1000);

  
  digitalWrite(SS, LOW);  // Chip erase: tüm hafıza temizlenir.  
  SPI.transfer (0xC7);
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
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 delay(300);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (300); 

  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);
 delay (300); 
yaz=yaz-1;
}

Serial.println( "    onceki bilgiler silinecek  ");
delay (1000);
//  önceki yazılanlar silinecek. PAGE ERASE sadece verilen adresten itibaren 128 byte sıfırlar. 
digitalWrite(SS, LOW);  
  SPI.transfer (6);
  digitalWrite(SS, HIGH);
  delay(300);
  
  digitalWrite(SS, LOW);  // PAGE ERASE
  SPI.transfer (0x42);
  SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  digitalWrite(SS, HIGH); 
  delay(300);
// ****************     PE   sonu 

for ( i =0; i <= 5; i++) {
Serial.print(" yukari sayma butona basin ") ;Serial.print(" yazilacak deger ");Serial.print(yaz);
while (digitalRead(2) == HIGH) {

  }

 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(300);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (300); 

  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (300); 
yaz=yaz+1;

   }
  
}


void yazma(){

  // yazma işleminin tümü bu altprogramda yapılabilir. bunun için yazılacak değer buraya aktarılır 
  // ve yazma işlemi yapılır.Tabii ki yazma satırlarının da burada yer alması gerekir. Değişkene göre yazabilecek şekilde.  
/* digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);
*/
digitalWrite(SS, LOW);  // yazma korumayı kaldırır. Bundan sonra yazma işlemi gelir. 
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH); 
 delay(10);
/*
 digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000);
 */
 
  
}


void okuma(){
/*
digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
 */ 
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    
   result = SPI.transfer(0);
  //uint8_t result1 = SPI.transfer(0);  // arka arkaya 2 veri almak istenirse. Veri okumak için saat palsi devam etmeli yolu da budur.
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (300); 
  
}

void pageerase(){  // 25lc512 için 128 byte lık bir sayfa düzeni vardır. saydfaya yazdıktan sonra 
                    // tekrar yazmak için sayfayı silmeniz gerekir. Proteus denemelerinde yazdıktan sonra 1 kez daha değiştirme hakkı veriyor 
                    // fakat 2. kez yazdırmıyor. bundan dolayı eski bilgileri okuyup üzerinde değişiklik yapıp sonrasında page erase ile temizleyip ,
                    // 128 byte ın tamamını tekrar yazdırmanız gerekebilir. 
                    // normalde tek tek yazarken sorun yok. fakat üzerine yazmak istediğinizde sorun çıkıyor. silme işlemi o zaman kullanılıyor. 
                    
Serial.print("PAGE ERASE BASLADI ");
digitalWrite(SS, LOW);  
  SPI.transfer (6);
  digitalWrite(SS, HIGH);
  
  delay(300);
  digitalWrite(SS, LOW);  // erase 
  SPI.transfer (0x42);
  SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  digitalWrite(SS, HIGH); 
  delay(300);
  
}

void loop ()//***************************************************
{
  char c;
 //yazma();
 addr=0;
 pageerase();
 yazma();
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr>> 16 );
    SPI.transfer(addr>> 8 );
    SPI.transfer(addr);
for (const char * p = "123456789098765432101234567890987654321012345678909876543210123456789098765432101234567890987654321012345678909876543210Merhaba!" ; c = *p; p++)
   SPI.transfer (c);
  digitalWrite(SS, HIGH);
 delay (300); 
okuma();
delay(5000);
//***********************************************************************

pageerase();

 yazma();
 
  digitalWrite(SS, LOW);   // write byte
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0xFE);
  digitalWrite(SS, HIGH);
 
 delay (1000); 

okuma(); 


yazma();

  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0xAA);
  digitalWrite(SS, HIGH);
 delay (1000); 

 okuma();
  

yazma();

  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(0xAB);
  digitalWrite(SS, HIGH);
 delay (1000); 


okuma();

delay(3000);

}



