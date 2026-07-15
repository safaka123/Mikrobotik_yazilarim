#define LATCH_PIN 10

// Cümlelerimiz
const char cumle1[] = "1. Arduino: Mikrobotik ile kesintisiz ve yuksek hizli paralel veri aktarimi basariyla tamamlandi.1";
const char cumle2[] = "2. Arduino: Donanimsal multiplexer ve demultiplexer adresleme mimarisini test ediyoruz.2";
const char cumle3[] = "3. Arduino: Kutuphanesiz saf C++ ve register seviyesinde port manipulasyonu canavardir.3";
const char cumle4[] = "4. Arduino: Pick-and-place endustriyel makine mantigi Proteus uzerinde simule edildi.4";

const char* cumleler[] = {cumle1, cumle2, cumle3, cumle4};

void setup() {
  pinMode(11, OUTPUT); // MOSI
  pinMode(13, OUTPUT); // SCK
  pinMode(LATCH_PIN, OUTPUT); // SS (LATCH)
  
  // Donanımsal SPI Ayarı (8 MHz)
  SPCR = (1 << SPE) | (1 << MSTR);
  SPSR |= (1 << SPI2X);

  // Adresleme Pinleri (PD5, PD6, PD7 çıkış yapılıyor)
  DDRD |= B11100000; 

  pinMode(8, OUTPUT); // STROBE (PORTB0)
  pinMode(A1, INPUT); // ACK (PINC1)
  
  PORTB &= B11111110; // STROBE = LOW (Başlangıçta kapılar kesinlikle kapalı!)
  PORTD = (PORTD & B00011111) | B00000000; // Adres = 000 (Park konumu)

  delay(500); // Simülasyonun oturması için bekleme
  
  tumAlicilaraGonder();
}

void loop() {
  // Tek çevrim çalışacak
}

void tumAlicilaraGonder() {
  for (byte cihazID = 1; cihazID <= 4; cihazID++) {
    int cumleUzunlugu = strlen(cumleler[cihazID - 1]);
    
    for (int i = 0; i < cumleUzunlugu; i++) {
      paralelKarakterGonder(cumleler[cihazID - 1][i], cihazID);
    }
    
    // NULL sonlandırıcı karakterini gönder
    paralelKarakterGonder('\0', cihazID);
    
    // Alıcı geçişinde hattı tamamen park konumuna çekip dinlendiriyoruz
    PORTD = (PORTD & B00011111) | B00000000; // 000 Park konumu
    delay(50); // Cümleler arası geçiş için Proteus'a çok kısa bir es (İsteğe göre daha da düşürülebilir)
  }
}

void paralelKarakterGonder(char c, byte cihazID) {
  // === ADIM 1: YENİ VERİYİ HAZIRLA ===
  PORTB &= B11111011;
  SPDR = c;
  while (!(SPSR & (1 << SPIF))) {}
  PORTB |= B00000100; // LATCH kaldır, veri çıkış bacaklarında hazır.

  // === ADIM 2: ADRESİ SEÇ ===
  byte korunanPinler = PORTD & B00011111; 
  switch(cihazID) {
    case 1: PORTD = korunanPinler | B00100000; break; 
    case 2: PORTD = korunanPinler | B01000000; break; 
    case 3: PORTD = korunanPinler | B01100000; break; 
    case 4: PORTD = korunanPinler | B10000000; break; 
  }
  
  // Entegre kapılarının oturması için minimum süre (Gerçek dünyada gerekebilir, Proteus'ta gerekirse silinebilir)
  delayMicroseconds(5); 

  // === ADIM 3: KAPILARI AÇ (STROBE HIGH!) ===
  PORTB |= B00000001; // STROBE = HIGH

  // === ADIM 4: ALICIDAN ACK HIGH BEKLE ===
  while ( !(PINC & B00000010) ) {}
  
  // === ADIM 5: STROBE KAPAT ===
  PORTB &= B11111110; // STROBE = LOW
  
  // === ADIM 6: ALICININ ACK SİNYALİNİ DÜŞÜRMESİNİ BEKLE ===
  while (PINC & B00000010) {}
  
  // === ADIM 7: PARK KONUMUNA GÜVENLİ GEÇİŞ ===
  PORTD = (PORTD & B00011111) | B00000000; // Adres = 000 (Park)
  delayMicroseconds(2); 
}
