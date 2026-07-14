#include <SoftwareSerial.h>

SoftwareSerial ekranaBas(9, 10); 

#define MAX_BUFFER 200 

unsigned long paralelBaslangic = 0;
unsigned long paralelBitis = 0;
volatile bool paralelBitti = false;
int paralelIndex = 0;
char paralelCumlesi[MAX_BUFFER]; 

unsigned long seriBaslangic = 0;
unsigned long seriBitis = 0;
bool seriBasladi = false;
int seriIndex = 0;
char seriCumlesi[MAX_BUFFER]; 

void setup() {
  ekranaBas.begin(9600);
  pinMode(1, INPUT);
  
  DDRD = B00000000; // PORTD Giriş
  
  DDRC |= B00000001;  // A0 ACK çıkış
  DDRC &= B11111101;  // A1 STROBE giriş
  
  PORTC &= B11111110;  // ACK Başlangıçta LOW
  ekranaBas.println("--- MIKROBOTIK HABERLESME BENCHMARK TESTI ---");
  ekranaBas.println("Veriler bekleniyor...\n");
}

void loop() {
  // ----------------------------------------------------
  // ETAP 1: PARALEL VERİ AKTARIM TAKİBİ
  // ----------------------------------------------------
  if (!paralelBitti) {
    // 1. Verici STROBE (A1) sinyalini HIGH yaptı mı?
    if (PINC & B00000010) {
      
      if (paralelIndex == 0) {
        paralelBaslangic = micros();
      }
      
      // 8-bitlik paralel veriyi tek çevrimde oku
      char gelenKarakter = PIND; 
      
      if (gelenKarakter == '\0') {
        paralelBitis = micros();
        paralelCumlesi[paralelIndex] = '\0'; 
        Serial.begin(115200); 
        paralelBitti = true;
      } 
      else if (paralelIndex < MAX_BUFFER - 1) {
        paralelCumlesi[paralelIndex++] = gelenKarakter;
      }
      
      // 2. İş bitti! ACK (A0) sinyalini HIGH yap ve hatta öylece bırak!
      PORTC |= B00000001;  
      
      // 3. Verici bizim ACK'imizi görene ve STROBE'u LOW yapana kadar BURADA BEKLE
      while (PINC & B00000010) {}
      
      // 4. Verici STROBE'u kapattı! Biz de kendi ACK (A0) sinyalimizi kapatıyoruz.
      PORTC &= B11111110;  
    }
  }
  
  // ----------------------------------------------------
  // ETAP 2: SERİ HABERLEŞME TAKİBİ
  // ----------------------------------------------------
  if (paralelBitti && Serial.available() > 0) {
    char gelenSeri = Serial.read();
    
    if (!seriBasladi) {
      seriBaslangic = micros();
      seriBasladi = true;
    }
    
    if (gelenSeri == '\n') {
      seriBitis = micros();
      seriCumlesi[seriIndex] = '\0'; 
      yaristanSonraSonuclariYazdir();
    } 
    else if (seriIndex < MAX_BUFFER - 1) {
      seriCumlesi[seriIndex++] = gelenSeri;
    }
  }
}

void yaristanSonraSonuclariYazdir() {
  unsigned long paralelToplamSure = paralelBitis - paralelBaslangic;
  unsigned long seriToplamSure = seriBitis - seriBaslangic;
  
  ekranaBas.println("============= YARIS BITTI =============");
  ekranaBas.print("Aktarilan Toplam Karakter: "); ekranaBas.println(paralelIndex);
  ekranaBas.println("---------------------------------------");
  
  ekranaBas.println("[1] PARALEL HATLA GELEN CUMLE:");
  ekranaBas.print("-> \"");
  int satirSayaci = 0;
  for (int i = 0; i < paralelIndex; i++) {
    ekranaBas.print(paralelCumlesi[i]);
    satirSayaci++;
    if (satirSayaci >= 45 && paralelCumlesi[i] == ' ') {
      ekranaBas.println();
      ekranaBas.print("    "); 
      satirSayaci = 0;
    }
  }
  ekranaBas.println("\"");
  ekranaBas.print("Sure: "); ekranaBas.print(paralelToplamSure); ekranaBas.println(" mikrosaniye.");
  ekranaBas.println("---------------------------------------");
  
  ekranaBas.println("[2] SERI HATLA (115200) GELEN CUMLE:");
  ekranaBas.print("-> \"");
  satirSayaci = 0;
  for (int i = 0; i < seriIndex; i++) {
    ekranaBas.print(seriCumlesi[i]);
    satirSayaci++;
    if (satirSayaci >= 45 && seriCumlesi[i] == ' ') {
      ekranaBas.println();
      ekranaBas.print("    ");
      satirSayaci = 0;
    }
  }
  ekranaBas.println("\"");
  ekranaBas.print("Sure: "); ekranaBas.print(seriToplamSure); ekranaBas.println(" mikrosaniye.");
  ekranaBas.println("---------------------------------------");
  
  if (paralelToplamSure < seriToplamSure) {
    float kat = (float)seriToplamSure / paralelToplamSure;
    ekranaBas.print("KAZANAN: PARALEL VERIYOLU! ( ");
    ekranaBas.print(kat, 1);
    ekranaBas.println(" kat daha hizli! )");
  } else {
    ekranaBas.println("KAZANAN: SERI HABERLESME!");
  }
  ekranaBas.println("=======================================");
  while(1);
}
