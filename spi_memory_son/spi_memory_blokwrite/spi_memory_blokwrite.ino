#include <SPI.h>
 int addr=0;
 int sil=0x0080;
 uint8_t yaz=0;
 #define Buton 2
 #define Buton1 3
void setup (void)
{
  pinMode(Buton, INPUT);
  pinMode(Buton1, INPUT);
  
  Serial.begin(9600);
  digitalWrite(SS, HIGH);  
  SPI.begin ();
  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
   

 
 digitalWrite(SS, LOW); //  Status write . write protect yazılımsal kaldırma. kod=1
  SPI.transfer (1);
  SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(1000);

  digitalWrite(SS, LOW);  
  SPI.transfer (171);  // read ID  bu entegre için 29 okunacak. komut kodu= 0xAB
  SPI.transfer(0);
  SPI.transfer(0);
  SPI.transfer(0);
  uint16_t jedecid = SPI.transfer(0) ;
 digitalWrite(SS, HIGH); 
 Serial.print(" ID NO : ");Serial.println(jedecid,HEX);

 digitalWrite(SS, LOW); //  SLEEP (Deep Power-Down mode)proteusta etkisiz. gerçek devrede son komut bu olur uyur ve read ID komutuyla uyandırılır. kod=185
  SPI.transfer (185);   // datasheete bakın. 0xB9
  SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(1000);


 
} 

void pageerase(){
  Serial.println( "page erase basladi");
digitalWrite(SS, LOW);  
  SPI.transfer (6);      // write enable latch (enable write operations) kod=6
  digitalWrite(SS, HIGH); 
 delay(10);
 
digitalWrite(SS, LOW);  // 25lc512 için kod. kod =0x42
  SPI.transfer (0x42);
  SPI.transfer(sil >> 16);
    SPI.transfer(sil >> 8);
    SPI.transfer(sil);
 digitalWrite(SS, HIGH); 
  Serial.println( "page erase bitti");
 delay(2000);
sil=0x000000;
 digitalWrite(SS, LOW);  
  SPI.transfer (6);      // write enable latch (enable write operations) kod=6
  digitalWrite(SS, HIGH); 
 delay(10);
 
digitalWrite(SS, LOW);  // AT25F512A için sector silme komutu kod =0x52 bu entegrede page erase yok. sector silinmesi gerek. 32K lık 2 sector var.
  SPI.transfer (0x52);
  SPI.transfer(sil >> 16);
    SPI.transfer(sil >> 8);
    SPI.transfer(sil);
 digitalWrite(SS, HIGH); 
  Serial.println( "sector erase bitti");
 delay(2000);
  
}


 void chiperase(){

 digitalWrite(SS, LOW);  // 25lc512 için kod. kod =199
  SPI.transfer (199);
 digitalWrite(SS, HIGH); 
 delay(2000);

 digitalWrite(SS, LOW);  // AT25F512A  için kod. kod=90
  SPI.transfer (98);
 digitalWrite(SS, HIGH); 
 delay(2000);
  
 }
 
 void yazdir(){   // YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
/* digitalWrite(SS, LOW);  
  SPI.transfer (5);			// status read kod=5
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);
*/


digitalWrite(SS, LOW);  
  SPI.transfer (6);			// write enable latch (enable write operations) kod=6
  digitalWrite(SS, HIGH); 
 
 delay(10);
/*
 digitalWrite(SS, LOW);  
  SPI.transfer (5);			// status read kod=5
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);
*/
 yaz++; 
   digitalWrite(SS, LOW);   
 
    SPI.transfer (2);			// write komutu 1-128byte yazabilirsiniz. 
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
    SPI.transfer(yaz+1);
  digitalWrite(SS, HIGH);
  Serial.println(addr >> 16,HEX);  // seri monitörde kaydırma sonuçlarını gösterir. en sağdaki byte geçerli olacaktır. 
  Serial.println(addr >> 8,HEX);   // gerçek sayı 0x010375 ise 16 bit kayınca 01 rakamı en düşük byte kısmına kayar ve değer bu olur. 
  Serial.println(addr ,HEX);        // 8 bit kayınca en düşük byte 03 olacaktır. en son addr yazılıyor normalde 3 byte tır fakat sadece en düşük byte yazdırılacaktır.
 delay (10);                        // çünkü 1 byte bilgi transfer edilmektedir. 

  
 }

void okuma(){
/*  delay(10);
 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
*/  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);			// read byte komutu kod=3
    SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  uint8_t result1 = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.print(result,HEX);Serial.print(" , ");Serial.println(result1,HEX);
 delay (10); 
 
 
  
  addr=addr+2;
}

void loop (void)
{
 
  yazdir();
 okuma();
  if (digitalRead(Buton) == 0){
    chiperase();
    Serial.println( " buton basildi ");
    addr=0;
    yaz=0;
  }
  if (digitalRead(Buton1) == 0){
    pageerase();
    Serial.println( " page erase yapildi ");
    
  }
 


} 
