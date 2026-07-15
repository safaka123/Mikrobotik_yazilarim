#include <SoftwareSerial.h>

SoftwareSerial ekranaBas(9, 10); // Verileri ekranda gözlemlemek için kullanılan sanal port [cite: 22]

#define MAX_BUFFER 200 // [cite: 22]

unsigned long paralelBaslangic = 0; // [cite: 22]
unsigned long paralelBitis = 0; // [cite: 23]
volatile bool paralelBitti = false; // [cite: 23]
int paralelIndex = 0; // [cite: 23]
char paralelCumlesi[MAX_BUFFER]; // [cite: 23]

void setup() {
  ekranaBas.begin(9600); // [cite: 24]
  
  DDRD = B00000000;   // PORTD (D0 - D7) tamamen Giriş (Paralel veri yolu) [cite: 25]
  
  DDRC |= B00000001;  // A0 ACK çıkış pini (PORTC0) 
  DDRC &= B11111101;  // A1 STROBE giriş pini (PORTC1) 
  
  PORTC &= B11111110; // ACK başlangıçta LOW [cite: 26, 27]
  
  ekranaBas.println("--- MULTI-SLAVE PARALEL PORT ALICISI ---");
  ekranaBas.println("Sinyal bekleniyor...\n");
}

void loop() {
  if (!paralelBitti) {
    // 1. Verici STROBE (A1 - PORTC1) sinyalini HIGH yaptı mı? [cite: 28, 29]
    if (PINC & B00000010) { // [cite: 29]
      
      // İlk karakter geldiğinde süreyi başlat
      if (paralelIndex == 0) { // [cite: 29]
        paralelBaslangic = micros(); // [cite: 29]
      }
      
      // PORTD register'ı üzerinden 8-bitlik veriyi tek bir çevrimde içeri al
      char gelenKarakter = PIND; // [cite: 30]
      
      // NULL karakteri geldiyse veri aktarımı bitti demektir
      if (gelenKarakter == '\0') { // [cite: 31]
        paralelBitis = micros(); // [cite: 31]
        paralelCumlesi[paralelIndex] = '\0'; // [cite: 31]
        paralelBitti = true; // [cite: 32]
      } 
      else if (paralelIndex < MAX_BUFFER - 1) { // [cite: 32]
        paralelCumlesi[paralelIndex++] = gelenKarakter; // [cite: 32]
      }
      
      // 2. Karakter okuma işi bitti! ACK (A0 - PORTC0) HIGH yapıp vericiye bildir [cite: 33, 34]
      PORTC |= B00000001; // [cite: 34]
      
      // 3. Verici bizim ACK sinyalimizi görene ve STROBE'u LOW yapana kadar burada KİLİTLEN [cite: 35]
      while (PINC & B00000010) {} // [cite: 35]
      
      // 4. Verici STROBE'u kapattı! Biz de kendi ACK sinyalimizi LOW yapıp döngüyü tamamlıyoruz [cite: 36]
      PORTC &= B11111110; // [cite: 36]
    }
  }
  else {
    // Paralel veri alımı bittiyse sonuçları hemen ekrana yazdır ve sistemi kilitle
    sonuclariYazdir();
  }
}

void sonuclariYazdir() {
  unsigned long paralelToplamSure = paralelBitis - paralelBaslangic; // [cite: 41]
  
  ekranaBas.println("============= VERI ALINDI ============="); // [cite: 42]
  ekranaBas.print("Aktarilan Toplam Karakter: ");  // [cite: 42]
  ekranaBas.println(paralelIndex); // [cite: 42]
  ekranaBas.println("---------------------------------------"); // [cite: 42]
  
  ekranaBas.println("[GELEN CUMLE]:"); // [cite: 43]
  ekranaBas.print("-> \""); // [cite: 43]
  
  int satirSayaci = 0; // [cite: 43]
  for (int i = 0; i < paralelIndex; i++) { // [cite: 43]
    ekranaBas.print(paralelCumlesi[i]); // [cite: 43]
    satirSayaci++; // [cite: 43]
    if (satirSayaci >= 45 && paralelCumlesi[i] == ' ') { // [cite: 43]
      ekranaBas.println(); // [cite: 43]
      ekranaBas.print("    ");  // [cite: 43]
      satirSayaci = 0; // [cite: 43]
    }
  }
  ekranaBas.println("\""); // [cite: 43]
  
  ekranaBas.println("---------------------------------------"); // [cite: 44]
  ekranaBas.print("Sure: ");  // [cite: 44]
  ekranaBas.print(paralelToplamSure);  // [cite: 44]
  ekranaBas.println(" mikrosaniye."); // [cite: 44]
  ekranaBas.println("======================================="); // [cite: 48]
  
  // Yeni bir veri paketi gelene kadar alıcıyı uyutuyoruz
  while(1);
}
