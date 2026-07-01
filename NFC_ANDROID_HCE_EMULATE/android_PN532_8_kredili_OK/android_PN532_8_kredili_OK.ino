#include <SPI.h>
#include <Wire.h>

const int chipSelectPin = 10;
const int resetPin = 3;
#define PN532_IRQ 2     // Arduino D2 pini
#define BUZZER_PIN 4

#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 

// --- 🏢 TERMİNAL DONANIM KİMLİK TANIMLAMALARI ---
const char* TERMINAL_SIRKET = "izbb";  // Cihazın ait olduğu yetkili şirket ismi
const int   TERMINAL_KAPI   = 2;       // Bu okuyucunun monte edildiği fiziksel kapı numarası (1-16 arası)
unsigned long RTCunixTime = 0;

// -------------------------------
// Sizin Bit Reverse Fonksiyonunuz (Aynen Korundu)
// -------------------------------
uint8_t reverseABit(uint8_t x) {
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
  x = ((x & 0x0F) << 4) | ((x & 0xF0) >> 4);
  return x;
}

// -------------------------------
// Sizin Ready ve Wait Kontrolleriniz (Aynen Korundu)
// -------------------------------
bool pn532_ready() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_STATREAD);
  uint8_t r = reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);
  return (r == 0x01);
}

bool pn532_waitReady(uint16_t timeout) {
  uint32_t t = millis();
  while (millis() - t < timeout) {
    if (pn532_ready()) return true;
    delay(1);
  }
  return false;
}

void pn532_readAck() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  for (int i = 0; i < 6; i++) {
    reverseABit(SPI.transfer(0x00));
  }
  digitalWrite(chipSelectPin, HIGH);
}

void pn532_writeFrame(uint8_t *data, uint8_t len) {
  uint8_t sum = 0;
  for (int i = 0; i < len; i++) sum += data[i];
  uint8_t dcs = 0x100 - sum;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAWRITE);

  SPI.transfer(reverseABit(0x00)); // PREAMBLE
  SPI.transfer(reverseABit(0x00));
  SPI.transfer(reverseABit(0xFF));

  SPI.transfer(reverseABit(len)); // LEN + LCS
  SPI.transfer(reverseABit(0x100 - len));
  for (int i = 0; i < len; i++) { // DATA
    SPI.transfer(reverseABit(data[i]));
  }

  SPI.transfer(reverseABit(dcs));
  SPI.transfer(reverseABit(0x00)); // POSTAMBLE

  digitalWrite(chipSelectPin, HIGH);
}

bool pn532_getFirmware(uint8_t &ver, uint8_t &rev) {
  uint8_t cmd[] = {0xD4, 0x02};
  pn532_writeFrame(cmd, 2);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();

  if (!pn532_waitReady(100)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  for (int i = 0; i < 30; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x03) {
        reverseABit(SPI.transfer(0x00));
        ver = reverseABit(SPI.transfer(0x00));
        rev = reverseABit(SPI.transfer(0x00));
        digitalWrite(chipSelectPin, HIGH);
        return true;
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return false;
}

void pn532_samConfig() {
  uint8_t cmd[] = {0xD4,0x14,0x01,0x14,0x01};
  pn532_writeFrame(cmd, 5);
  pn532_waitReady(100);
  pn532_readAck();
  pn532_waitReady(100);
}

// --- BUZZER SİNYALLERİ ---
void BIP() {
  digitalWrite(BUZZER_PIN, HIGH); delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void BIP_BIP() {
  for(int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH); delay(100);
    digitalWrite(BUZZER_PIN, LOW);  delay(100);
  }
}

// --- HCE FONKSİYONLARI (Kusursuz Çalışan APDU Zinciri) ---
bool HCE_selectAID(uint8_t tgNumber) {
  uint8_t selectApdu[] = {
    0xD4, 0x40, tgNumber,                     
    0x00, 0xA4, 0x04, 0x00, 0x07,             
    0xD2, 0x76, 0x00, 0x00, 0x85, 0x01, 0x01  
  };
  Serial.println("\n🎯 TELEFON YAKALANDI. -> Adim 1: SELECT AID gönderiliyor...");
  pn532_writeFrame(selectApdu, sizeof(selectApdu));
  if (!pn532_waitReady(150)) return false;
  pn532_readAck();
  
  while (digitalRead(PN532_IRQ) == HIGH);

  digitalWrite(chipSelectPin, LOW); 
  SPI.transfer(PN532_SPI_DATAREAD);
  
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) {
        uint8_t status = reverseABit(SPI.transfer(0x00));
        uint8_t sw1 = reverseABit(SPI.transfer(0x00));
        uint8_t sw2 = reverseABit(SPI.transfer(0x00));
        
        Serial.print("➡️ Adim 1 Gelen SW Kodlari: ");
        Serial.print(sw1, HEX); Serial.print(" "); Serial.println(sw2, HEX);
        
        digitalWrite(chipSelectPin, HIGH);
        return (sw1 == 0x90 && sw2 == 0x00);
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return false;
}

bool HCE_selectNdefFile(uint8_t tgNumber) {
  uint8_t apduSelectNdefFile[] = {
    0xD4, 0x40, tgNumber,         
    0x00, 0xA4, 0x00, 0x01, 0x02, 
    0xE1, 0x04                   
  };
  Serial.println("📂 Adim 2: NDEF File secim APDU'su gönderiliyor...");
  pn532_writeFrame(apduSelectNdefFile, sizeof(apduSelectNdefFile));
  if (!pn532_waitReady(150)) return false;
  pn532_readAck();
  
  while (digitalRead(PN532_IRQ) == HIGH);

  digitalWrite(chipSelectPin, LOW); 
  SPI.transfer(PN532_SPI_DATAREAD);
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) {
        uint8_t status = reverseABit(SPI.transfer(0x00));
        uint8_t sw1 = reverseABit(SPI.transfer(0x00));
        uint8_t sw2 = reverseABit(SPI.transfer(0x00));
        
        Serial.print("➡️ Adim 2 Gelen SW Kodlari: ");
        Serial.print(sw1, HEX); Serial.print(" "); Serial.println(sw2, HEX);
        
        digitalWrite(chipSelectPin, HIGH);
        return (sw1 == 0x90 && sw2 == 0x00);
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return false;
}

bool HCE_readBinary(uint8_t tgNumber, uint8_t *dataBuffer, uint8_t readLen) {
  uint8_t apduReadBinary[] = {
    0xD4, 0x40, tgNumber, 
    0x00, 0xB0,           
    0x00, 0x00,           
    readLen               
  };
  Serial.println("📥 Adim 3: READ BINARY ile veriler talep ediliyor...");
  pn532_writeFrame(apduReadBinary, sizeof(apduReadBinary));
  if (!pn532_waitReady(150)) return false;
  pn532_readAck();
  while (digitalRead(PN532_IRQ) == HIGH);

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  bool dataStarted = false;
  int bufferIndex = 0;
  bool success = false;

  for (int i = 0; i < (readLen + 40); i++) {
    uint8_t r = reverseABit(SPI.transfer(0x00));
    if (r == 0xD5) {
      dataStarted = true;
      reverseABit(SPI.transfer(0x00)); 
      reverseABit(SPI.transfer(0x00)); 
      i += 2;
      continue;
    }
    if (dataStarted) {
      if (bufferIndex < readLen) {
        dataBuffer[bufferIndex] = r;
        bufferIndex++;
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  if (bufferIndex >= readLen) success = true;
  return success;
}

// =================================================================
// 🧮 1. FONKSİYON: İZMİR 90 DAKİKA KREDİ VE AKTARMA HESAPLAMA MODÜLÜ
// =================================================================
void hesapla90Dakika(uint8_t* data, uint32_t rtcZamani) {
  // 1. Karttan Mevcut Ham ASCII String Bilgileri Geçici Dizilere Çekme
  char eskiKrediStr[5] = {0};
  char eskiZamanStr[11] = {0};
  
  memcpy(eskiKrediStr, &data[43], 4);
  memcpy(eskiZamanStr, &data[47], 10);
  
  uint8_t durumMetot = data[57];  // 1. Durum Byte (Aktarım Fazı: 0 veya 1)
  uint8_t durumProfil = data[58]; // 2. Durum Byte (Profil: 0=Tam, 1=Öğrenci, 2=Şehit Yakını, 3=engelli, 4=özel durum)

  // ASCII karakterleri matematiksel sayılara çeviriyoruz
  long eskiKredi = 0;
  for(int i = 0; i < 4; i++) {
    if(eskiKrediStr[i] >= '0' && eskiKrediStr[i] <= '9') {
      eskiKredi = eskiKredi * 10 + (eskiKrediStr[i] - '0');
    }
  }

  uint32_t eskiZaman = (uint32_t)strtoul(eskiZamanStr, NULL, 10);

  // 2. Zaman Farkı Hesaplama (Dakika Cinsinden)
  long deltaSaniye = (long)rtcZamani - (long)eskiZaman;
  long deltaDakika = deltaSaniye / 60;

  // Hesaplanan yeni değerleri tutacak değişkenler (Varsayılan olarak eskileri korur)
  long yeniKredi = eskiKredi;
  uint8_t yeniDurumMetot = durumMetot;
  uint32_t yeniZaman = eskiZaman; 
  int dusenKredi = 0;

  // 3. İZMİR 90 DK LOJİK MATRİSİNİN İŞLETİLMESİ
  if (deltaDakika > 90 || eskiZaman == 0) {
    // --- SENARYO 1: 90 DK SÜRE AŞILMIŞ VEYA İLK BİNİŞ ---
    yeniDurumMetot = 0;      // Zincir sıfırlanır (0 yapılır)
    yeniZaman = rtcZamani;   // Zaman damgası cihazın şimdiki RTC'siyle güncellenir
    
    // Profile göre ana tarife kredi düşümü
    if (durumProfil == 0)      dusenKredi = 30; // Tam Kart
    else if (durumProfil == 2) dusenKredi = 30; // Şehit yakını
    else if (durumProfil == 1) dusenKredi = 15; // Öğrenci
    else if (durumProfil == 3) dusenKredi = 0;  // Engelli 
    else if (durumProfil == 4) dusenKredi = 0;  // Özel Durum
  } 
  else {
    // --- 90 DAKİKA SÜRE DAHİLİNDEYİZ ---
    if (durumMetot == 0) {
      // --- SENARYO 2: 1. AKTARMA (İndirimli) ---
      yeniDurumMetot = 1;    // 1. Aktarma yapıldı olarak işaretlenir
      // DİKKAT: yeniZaman = eskiZaman kalır, GÜNCELLENMEZ!

      // Profile göre 1. Aktarma tarifesi
      if (durumProfil == 0)      dusenKredi = 15; // Tam Kart
      else if (durumProfil == 2) dusenKredi = 0; // Şehit yakını
      else if (durumProfil == 1) dusenKredi = 5; // Öğrenci
      else if (durumProfil == 3) dusenKredi = 0;  // Engelli 
      else if (durumProfil == 4) dusenKredi = 0;  // Özel Durum
    } 
    else if (durumMetot == 1) {
      // --- SENARYO 3: SONRAKİ AKTARMALAR (Tamamen Ücretsiz binişler) ---
      yeniDurumMetot = 1;    // Durum 1 olarak kilitli kalır
      dusenKredi = 0;        // Profil ne olursa olsun 0 Kredi düşer!
      // DİKKAT: yeniZaman = eskiZaman kalır, GÜNCELLENMEZ!
    }
  }

  // Yeni krediyi hesapla ve koruma koy
  yeniKredi = eskiKredi - dusenKredi;
  if (yeniKredi < 0) yeniKredi = 0; 

  // 4. HESAPLANAN VERİLERİ ASCII STRING FORMATINA ÇEVİRİP HAM `phoneData` DİZİSİNE GÖMME
  char yeniKrediStr[5];
  sprintf(yeniKrediStr, "%04ld", yeniKredi);
  memcpy(&data[43], yeniKrediStr, 4);

  char yeniZamanStr[11];
  sprintf(yeniZamanStr, "%010lu", yeniZaman);
  memcpy(&data[47], yeniZamanStr, 10);

  data[57] = yeniDurumMetot; // 1. Durum Byte güncellendi

  // 5. SERİ MONİTÖR DETAYLI RAPORLAMA ÇIKTISI
  Serial.println(F("\n========================================"));
  Serial.println(F("📊  90 DK AKTARMA METODU HESAPLAMA RAPORU"));
  Serial.println(F("========================================"));
  Serial.print(F(" Kart Profili   : "));
  switch(durumProfil) {
    case 0: Serial.println(F("TAM KART")); break;
    case 1: Serial.println(F("ÖĞRENCİ")); break;
    
    case 2: Serial.println(F(" ŞEHİT YAKINI (Ücretsiz)")); break;
    
    case 3: Serial.println(F(" ENGELLİ (Ücretsiz)")); break;
    case 4: Serial.println(F(" ÖZEL DURUM (Ücretsiz)")); break;
  }
  Serial.print(F(" Zaman Durumu   : "));
  if (deltaDakika > 90 || eskiZaman == 0) {
    Serial.print(F("Süre Aşımı / İlk Geçiş (Fark: ")); Serial.print(deltaDakika); Serial.println(F(" dk)"));
  } else {
    Serial.print(F("90 Dk Süre Dahilinde (Fark: ")); Serial.print(deltaDakika); Serial.println(F(" dk)"));
  }
  
  Serial.println(F("----------------------------------------"));
  Serial.print(F(" 💰 ESKİ KREDİ  : ")); Serial.println(eskiKrediStr);
  Serial.print(F(" 💰 YENİ KREDİ  : ")); Serial.println(yeniKrediStr);
  Serial.print(F(" 📉 DÜŞEN KREDİ : ")); Serial.println(dusenKredi);
  Serial.println(F("----------------------------------------"));
  Serial.print(F(" 🔄 METOT FAZI  : ")); Serial.print(durumMetot); Serial.print(F("  ==>  ")); Serial.println(yeniDurumMetot);
  Serial.print(F(" ⏰ ZAMAN DAMGASI: ")); Serial.print(eskiZamanStr); Serial.print(F("  ==>  ")); Serial.println(yeniZamanStr);
  Serial.println(F("========================================\n"));
}


// =================================================================
// 💾 2. FONKSİYON: TELEFONA GÜNCEL VERİLERİ BASMA (WRITE BINARY APDU)
// =================================================================
// =================================================================
// 💾 GÜNCELLENMISHED VE STANDARDA UYGUN WRITE BINARY (Lc BYTE DESTEKLİ)
// =================================================================
// =================================================================
// 💾 TAM UYUMLU VE KAYMASIZ WRITE BINARY (APDU PAKET DOĞRULAMA)
// =================================================================
bool HCE_writeBinary(uint8_t tgNumber, uint8_t* dataToWrite, uint8_t dataLen) {
  
  // 8 Byte Tam APDU Başlığı (Boşluk bırakmadan, tam doldurarak):
  // CLA(00) - INS(D6) - P1(00) - P2(00) - Lc(96 Byte -> 0x60)
  uint8_t writeHeader[8] = {
    0xD4,        // PN532 Komutu
    0x40,        // InDataExchange
    tgNumber,    // Telefon Hedef Numarası
    0x00,        // CLA (ISO 7816)
    0xD6,        // INS (WRITE BINARY)
    0x00,        // P1 (Ofset Yüksek)
    0x00,        // P2 (Ofset Düşük)
    dataLen      // Lc (Veri Uzunluğu - 96 Byte için 0x60)
  }; 
  
  // Toplam Paket Boyutu: 8 byte başlık + 96 byte veri = 104 byte
  uint8_t fullPacket[8 + dataLen];
  
  memcpy(fullPacket, writeHeader, 8);           // Başlığı kopyala
  memcpy(&fullPacket[8], dataToWrite, dataLen); // Veriyi tam 8. indisten itibaren başlat

  // Çerçeveyi telefona uçuruyoruz
  pn532_writeFrame(fullPacket, 8 + dataLen);
  if (!pn532_waitReady(150)) return false;
  pn532_readAck();

  uint32_t irqStart = millis();
  while (digitalRead(PN532_IRQ) == HIGH && (millis() - irqStart < 250));

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  
  bool success = false;
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) { 
        uint8_t status = reverseABit(SPI.transfer(0x00));
        if (status == 0x00) { 
          uint8_t sw1 = reverseABit(SPI.transfer(0x00));
          uint8_t sw2 = reverseABit(SPI.transfer(0x00));
          
          if (sw1 == 0x90 && sw2 == 0x00) {
            success = true;
          }
        }
      }
      break;
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return success;
}


// =================================================================
// 🕒 3. FONKSİYON: RTC MOCK/PROTOTİP FONKSİYONU
// =================================================================
uint32_t getTerminalRTC() {
  //uint32_t getTerminalRTC() {
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7);

  if (Wire.available() >= 7) {
    uint8_t s  = Wire.read() & 0x7F; // Saniye (Kullanmıyoruz ama hattan çekiyoruz)
    uint8_t m  = Wire.read();        // Dakika
    uint8_t h  = Wire.read();        // Saat
    Wire.read();                     // Haftanın günü (Gereksiz, boşa okuyoruz)
    uint8_t d  = Wire.read();        // Gün
    uint8_t mo = Wire.read();        // Ay
    uint8_t y  = Wire.read();        // Yıl (00-99)

    // BCD → DECIMAL ÇEVRİMİ
    m  = (m >> 4) * 10 + (m & 0x0F);
    h  = (h >> 4) * 10 + (h & 0x0F);
    d  = (d >> 4) * 10 + (d & 0x0F);
    mo = (mo >> 4) * 10 + (mo & 0x0F);
    y  = (y >> 4) * 10 + (y & 0x0F);

    int yy = y + 2000;

    // Sizin matematiksel Unix dönüştürücüye parametreleri paslıyoruz
    RTCunixTime = rtcToUnix(yy, mo, d, h, m);
    return RTCunixTime;
  }
  
  // Eğer I2C hattından veri okunamazsa koruma amaçlı 0 dönmesin, son bilineni veya tabanı dönsün
  return RTCunixTime; 
}



// =================================================================
// ⏳ SİZİN MATEMATİKSEL RTC TO UNIX DÖNÜŞTÜRÜCÜNÜZ (Aynen Korundu)
// =================================================================
unsigned long rtcToUnix(int yr, int mn, int day, int hour, int min) {
  const uint8_t dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  unsigned long days = 0;

  for(int y=1970; y<yr; y++) {
    days += 365;
    if((y % 4) == 0) days++;
  }

  for(int m=1; m<mn; m++) {
    days += dim[m-1];
    if(m==2 && (yr % 4)==0) days++;
  }

  days += day - 1;

  return days*86400UL + hour*3600UL + min*60UL;
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  Wire.begin(); // I2C haberleşme hattını master olarak başlatır
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, HIGH);

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW); delay(100);
  digitalWrite(resetPin, HIGH); delay(100);

  SPI.begin();
  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE0));
  Serial.println("Looking for PN532...");

  uint8_t v, r;
  if (pn532_getFirmware(v, r)) {
    Serial.print("PN532 bulundu - Firmware: ");
    Serial.print(v); Serial.print("."); Serial.println(r);
  } else {
    Serial.println("PN532 bulunamadi!");
  }

  pn532_samConfig(); // Sizin uyanmayı garantiye alan sihirli dokunuşunuz
  Serial.println("Waiting for an ISO14443A Card or Phone (HCE) ...");
}

// --- LOOP ---
void loop() {
  uint8_t cmd[] = {0xD4, 0x4A, 0x01, 0x00}; 
  
  pn532_writeFrame(cmd, 4);
  if (!pn532_waitReady(100)) return;
  pn532_readAck();

  uint32_t irqStart = millis();
  while (digitalRead(PN532_IRQ) == HIGH && (millis() - irqStart < 200));

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  bool phoneFound = false;
  uint8_t tgNumber = 0x01;

  for (int i = 0; i < 50; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x4B) { 
        reverseABit(SPI.transfer(0x00)); 
        tgNumber = reverseABit(SPI.transfer(0x00)); 
        reverseABit(SPI.transfer(0x00)); 
        reverseABit(SPI.transfer(0x00)); 
        uint8_t sak = reverseABit(SPI.transfer(0x00));
        if (sak == 0x20) { phoneFound = true; break; }
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);

  if (phoneFound) {
    delay(10); 

    // 1. ADIM: AID SEÇİMİ
    if (HCE_selectAID(tgNumber)) {
      delay(15);
      // 2. ADIM: NDEF DOSYA SEÇİMİ
      if (HCE_selectNdefFile(tgNumber)) {
        delay(15);
        // 3. ADIM: VERİ OKUMA (96 Byte)
        uint8_t phoneData[96];
        if (HCE_readBinary(tgNumber, phoneData, 96)) {
          
          char sirket[17] = {0};       
          
          // Şirket bilgisini ham veriden (25. indistten itibaren) ayıklıyoruz
          memcpy(sirket, &phoneData[25], 16);
          for(int i = 15; i >= 0; i--) { if(sirket[i] == ' ') sirket[i] = '\0'; else break; }

          // -----------------------------------------------------------------
          // 🏢 ŞİRKET DOĞRULAMA KONTROLÜ
          // -----------------------------------------------------------------
          if (strcmp(sirket, TERMINAL_SIRKET) == 0) {
            
            // 1. İşlem: RTC modülünden şimdiki Unix/Epoch zamanını alıyoruz
            uint32_t rtcSimdi = getTerminalRTC();

            // 2. İşlem: Hesaplama fonksiyonuna paslayıp, bakiye/zaman/metot güncellemelerini RAM'de tamamlıyoruz
            // Bu fonksiyon seri monitöre eski ve yeni tüm durum dökümlerini yazdıracaktır.
            hesapla90Dakika(phoneData, rtcSimdi);

            // loop() içinde HCE_writeBinary çağrılmadan hemen önce:
            // 57. indisten sonraki (durum byte'ları hariç) kalan tüm boşlukları 0x00 yapıyoruz
            for (int i = 59; i < 96; i++) {
              phoneData[i] = 0x00; 
            }

            // 3. İşlem: RAM üzerinde güncellenen phoneData paketini telefona geri yazıyoruz (WRITE BINARY)
            Serial.println("💾 Hesaplamalar doğru gerçekleşti. Güncel veriler telefona yazılıyor...");
            
             
            
            if (HCE_writeBinary(tgNumber, phoneData, 96)) {
              Serial.println("✅ [İŞLEM BAŞARILI] - Telefon başarıyla güncellendi ve geçiş onaylandı.");
              BIP(); // Başarılı terminal geçiş sesi
            } else {
              Serial.println("❌ [YAZMA HATASI] - Telefona WRITE BINARY komutu gönderildi fakat telefon reddetti!");
              BIP_BIP(); // Başarısız terminal sesi
            }

          } else {
            // ŞİRKET BİLGİSİ YETKİSİZ İSE
            Serial.print("⚠️ LOG: [RED] -> Geçersiz Şirket Kartı! Gelen: '");
            Serial.print(sirket);
            Serial.print("', Beklenen Yetkili Şirket: '");
            Serial.print(TERMINAL_SIRKET);
            Serial.println("'. İşlem iptal edildi.");
            BIP_BIP(); // Başarısız terminal sesi
          }
          // -----------------------------------------------------------------

        } else {
          Serial.println("❌ Adim 3 Hata: Veri Okunamadi.");
        } 
      } else {
        Serial.println("❌ Adim 2 Hata: NDEF Dosyasi Secilemedi.");
      } 
    } else {
      Serial.println("❌ Adim 1 Hata: AID Secimi Reddedildi.");
    } 
    delay(2500); // Üst üste mükerrer okumayı engellemek için bekleme payı
  } 
  delay(100);
}
