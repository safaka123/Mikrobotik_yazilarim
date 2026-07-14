// 74HC595 LATCH Pini Donanımsal SS (D10) yapıldı
#define LATCH_PIN 10 

const char testCumlesi[] = "Mikrobotik Elektronik Platformu ile donanim ve yazilim mantigini kutuphanesiz ogreniyoruz. Bu deney paralel ve seri haberlesme hiz farkini gosterir.";

void setup() {
  // SPI Pinlerinin Yön Ayarları (D11 ve D13 otomatik çıkış olur ama D10'u biz yapmalıyız)
  
   // PROTEUS İÇİN KRİTİK ADIM: SPI fiziksel pinlerini açıkça ÇIKIŞ yapıyoruz
  pinMode(11, OUTPUT); // MOSI (74HC595 DS/DATA pinine giden bacak)
  pinMode(13, OUTPUT); // SCK  (74HC595 SH_CP/CLOCK pinine giden bacak)
  pinMode(LATCH_PIN, OUTPUT); // SS (D10 - LATCH)
  
  // KÜTÜPHANESİZ DONANIMSAL SPI AYARI (Direct Register)
  // SPCR = SPI Control Register
  // SPE (SPI Enable) = 1, MSTR (Master Mode) = 1, SPR0/SPR1 ile Hız = Fosc/4 (4 MHz)
  SPCR = (1 << SPE) | (1 << MSTR); 
  // SPI hızını maksimuma katlamak için SPSR (SPI Status Register) Double Speed bitini açıyoruz (8 MHz!)
  SPSR |= (1 << SPI2X); 

  pinMode(8, OUTPUT); // STROBE Pini (PORTB0)
  pinMode(A1, INPUT); // ACK Giriş Pini (PINC1)
  
  PORTB &= B11111110; // STROBE = LOW
  
  Serial.begin(115200);
  delay(2000); 
  yarisiBaslat();
}

void loop() {
  // Yarış bir kez çalışıp duracak
}

void yarisiBaslat() {
  int cumleUzunlugu = sizeof(testCumlesi) - 1; 
  
  // ----------------------------------------------------
  // ETAP 1: PARALEL VERİYOLU YARIŞI (SPI DESTEKLİ)
  // ----------------------------------------------------
  for (int i = 0; i < cumleUzunlugu; i++) {
    paralelKarakterGonder(testCumlesi[i]);
  }
  paralelKarakterGonder('\0'); 
  
  entegreyeTemizlikBas(0xFF); 
  delay(100); 
  
  // ----------------------------------------------------
  // ETAP 2: SERİ HABERLEŞME YARIŞI (115200 Baud)
  // ----------------------------------------------------
  for (int i = 0; i < cumleUzunlugu; i++) {
    Serial.write(testCumlesi[i]);
  }
  Serial.write('\n'); 
}

void paralelKarakterGonder(char c) {
  // 1. Latch kilidini indir (PORTB'nin 2. biti - D10 Pini)
  PORTB &= B11111011; 

  // 2. KÜTÜPHANESİZ DONANIMSAL SPI YAZIMI
  // Karakteri doğrudan SPI Data Register (SPDR) içine fırlatıyoruz. 
  // Donanım bunu 8 MHz hızında (1 mikrosaniyede) 74HC595'e gönderir!
  SPDR = c; 
  
  // Donanım bitleri hattan eritmeyi bitirene kadar (SPIF bayrağı 1 olana kadar) bekle
  while (!(SPSR & (1 << SPIF))) {}

  // 3. Latch kilidini kaldır, veri artık 74HC595 çıkışlarında kararlı (D10 HIGH)
  PORTB |= B00000100; 

  // 4. Alıcıya "Veri hazır" de: STROBE (D8 - PORTB0) HIGH yap ve öyle bırak!
  PORTB |= B00000001;  
  
  // 5. Alıcı işini bitirip ACK (A1 - PINC1) sinyalini HIGH yapana kadar KİLİTLEN
  while ( !(PINC & B00000010) ) {}
  
  // 6. STROBE sinyalini kapatıyoruz: LOW
  PORTB &= B11111110;  
  
  // 7. Alıcı kendi ACK sinyalini LOW yapana kadar KİLİTLEN
  while (PINC & B00000010) {}
}

void entegreyeTemizlikBas(byte veri) {// bu 74hc595 entegresinin işi bittiğinde tüm bitlerinin HIGH seviyesinde kalmasını sağlar. 
                                      // Alıcı arduino RX girişinde çakışma olmasın paralel ve seri çalışmada sorunsuz çalışsın,
                                      // diye diyotlar konulmuştur. pull up direnç konulmuştur. 
  PORTB &= B11111011; // Latch LOW
  SPDR = veri;
  while (!(SPSR & (1 << SPIF))) {}
  PORTB |= B00000100; // Latch HIGH
}
