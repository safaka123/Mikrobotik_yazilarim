#include <SPI.h>
 uint16_t addr=0x0000;
 uint16_t bak=0;
 uint8_t yaz=20;
uint8_t result;


void setup (void)
{
  pinMode(2, INPUT);
  //digitalWrite(2, HIGH);// status için wp ucu kontrol
  Serial.begin(9600);
   
  digitalWrite(SS, HIGH);  
  SPI.begin ();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));//16mhz clock div 8 yapılarak 2 mhz frekansında çalışıldı. 25lc640 max 2mhz

digitalWrite(SS, LOW);  // reset
  SPI.transfer (4);
  //SPI.transfer (0);
  digitalWrite(SS, HIGH); 
  delay(100);

  
 

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(100);

 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //  SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(100);


 digitalWrite(SS, LOW);  // status write
  SPI.transfer (1);
  digitalWrite(SS, HIGH); 
  delay(100);
  buton();
 
} 

void buton(){
int i=0;
for ( i =0; i <= 5; i++) {
    
 
Serial.print(" Asagi sayma  butona basin ") ;Serial.print(" yazilacak deger HEX : ");Serial.println(yaz,HEX);
while (digitalRead(2) == HIGH) {  // buton çift basmasın diye basılasıya kadar bekler. 

  }
  while (digitalRead(2) == LOW) {// buton çift basmasın diye bırakılasıya kadar bekler. 

  }

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);
  digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(10);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
   // SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (10); 

 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW); 
 
    SPI.transfer (3);      // read byte komutu kod=3
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
   
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);
 delay (10); 
 
yaz=yaz-1;
}



for ( i =0; i <= 5; i++) {
Serial.print(" yukari sayma butona basin ") ;Serial.print(" yazilacak deger HEX : ");Serial.println(yaz,HEX);
while (digitalRead(2) == HIGH) {

  }

digitalWrite(SS, LOW);  
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(10);
 //addr=7;
 digitalWrite(SS, LOW);  
  SPI.transfer (6);
 digitalWrite(SS, HIGH); 
 
 delay(10);
 addr=yaz;
  digitalWrite(SS, LOW);   // write byte
  
    SPI.transfer (2);
   // SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(yaz);
  digitalWrite(SS, HIGH);
 
 delay (10); 

 digitalWrite(SS, LOW);  
  SPI.transfer (0x05);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
  delay(10);
  
  digitalWrite(SS, LOW);  
    SPI.transfer (3);      // read byte komutu kod=3
   // SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
  uint8_t result = SPI.transfer(0);
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.println(result,HEX);//Serial.print(" , ");Serial.println(result1,HEX);
 delay (10); 
yaz=yaz+1;

   }
  
}

// YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
void yazma(){
 
// bu sadece yazma kilidini kaldırır. 
digitalWrite(SS, LOW);  
  SPI.transfer (6);
 //delay(100);
 digitalWrite(SS, HIGH); 
 
 delay(10);
/*
 digitalWrite(SS, LOW);  // Status registerini okur. 
  SPI.transfer (5);
   SPI.transfer (0);
 digitalWrite(SS, HIGH); 
 delay(1000); 
 */
}

// OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
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
   // SPI.transfer(addr >> 16);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    
   result = SPI.transfer(0);
  uint8_t result1 = SPI.transfer(0); //Aynı anda 2 değer okunacaksa bu şekilde okunur. 
                                      //Her okunacak değer için saat palsi devam ettirilmesi için bu şekilde okunur. 
  digitalWrite(SS, HIGH);
  Serial.print(" okunan deger  : ");Serial.print(result,HEX);Serial.print(" , ");Serial.println(result1,HEX);
 delay (100); 
  
}


void loop ()//***************************************************
{
  addr=0x0020;
  char c;
 yazma();
 
  digitalWrite(SS, LOW);   // write byte
    SPI.transfer (2);
    SPI.transfer(addr>> 8 );
    SPI.transfer(addr);
for (const char * p = "12345678909876543210Merhaba!1234" ; c = *p; p++)
   SPI.transfer (c);
  digitalWrite(SS, HIGH);
 delay (3000); 
Serial.println( "sayma basladi");
for ( int say =0; say <= 10; say++) {

yazma();
 
  digitalWrite(SS, LOW);   // write byte
    SPI.transfer (2);
    SPI.transfer(addr >> 8);
    SPI.transfer(addr);
    SPI.transfer(say);
  digitalWrite(SS, HIGH);
 Serial.print( "yazilan deger : ");Serial.println( say);
 delay (100); 

okuma(); 

}

}



