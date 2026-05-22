// BU PROGRAM NTAG213 ETİKETLERİNE ŞİFRE KOYMAK İÇİNDİR. 
// ŞİFRE İSE SAFK DIR BUNUN ASCİİ OLARAK GÖRÜNMESİ İÇİN BYTE OLARAK GÖRÜNÜR. 
// NFCTOOLS BUNU OKUMAZ. 



#include <SPI.h>

// --- PIN TANIMLAMALARI ---
const int chipSelectPin = 10;
const int resetPin      = 3;
const int PN532_IRQ     = 2; // IRQ pini burada tanımlı

// --- PROTOKOL SABİTLERİ ---
#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 

uint8_t reverseABit(uint8_t x) {
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
  x = ((x & 0x0F) << 4) | ((x & 0xF0) >> 4);
  return x;
}

bool pn532_ready() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_STATREAD);
  uint8_t r = reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);
  return (r == 0x01);
}

// Donanımsal IRQ ve Yazılımsal Timeout'u birleştiren bekleme
bool pn532_waitReady(uint16_t timeout) {
  uint32_t t = millis();
  while (millis() - t < timeout) {
    // Önce fiziksel pini kontrol et (LOW olması verinin hazır olduğunu gösterir)
    if (digitalRead(PN532_IRQ) == LOW) {
      if (pn532_ready()) return true;
    }
    delay(1);
  }
  return false;
}

void pn532_readAck() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  for (int i = 0; i < 6; i++) reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);
}

void pn532_writeFrame(uint8_t *data, uint8_t len) {
  uint8_t sum = 0;
  for (int i = 0; i < len; i++) sum += data[i];
  uint8_t dcs = 0x100 - sum;
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAWRITE);
  SPI.transfer(reverseABit(0x00)); SPI.transfer(reverseABit(0x00)); SPI.transfer(reverseABit(0xFF));
  SPI.transfer(reverseABit(len)); SPI.transfer(reverseABit(0x100 - len));
  for (int i = 0; i < len; i++) SPI.transfer(reverseABit(data[i]));
  SPI.transfer(reverseABit(dcs)); SPI.transfer(reverseABit(0x00));
  digitalWrite(chipSelectPin, HIGH);
}

bool pn532_readUID(uint8_t *uid, uint8_t &uidLen) {
  uint8_t cmd[] = {0xD4, 0x4A, 0x01, 0x00};
  pn532_writeFrame(cmd, 4);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(300)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  bool found = false;
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5 && reverseABit(SPI.transfer(0x00)) == 0x4B) {
      found = true;
      for (int j = 0; j < 5; j++) reverseABit(SPI.transfer(0x00));
      uidLen = reverseABit(SPI.transfer(0x00));
      for (int k = 0; k < uidLen; k++) uid[k] = reverseABit(SPI.transfer(0x00));
      break;
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return found;
}

bool pn532_ntag_readPage(uint8_t pageAddr, uint8_t *buffer) {
  uint8_t cmd[] = {0xD4, 0x40, 0x01, 0x30, pageAddr};
  pn532_writeFrame(cmd, 5);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  bool success = false;
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5 && reverseABit(SPI.transfer(0x00)) == 0x41) {
      if (reverseABit(SPI.transfer(0x00)) == 0x00) {
        for (int b = 0; b < 16; b++) buffer[b] = reverseABit(SPI.transfer(0x00));
        success = true;
        break;
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return success;
}

void ntag_kredili_oku(uint8_t *uid, uint8_t uidLen) {
  uint8_t buf[16];
  
  Serial.println("\n--- NTAG213 KREDILI SISTEM OKUMA (TEMIZ) ---");

  // 1. ISIM SOYAD (Sayfa 4-7)
  if (pn532_ntag_readPage(4, buf)) {
    Serial.print("Isim Soyad (HEX): ");
    for(int i=0; i<16; i++) {
      if(buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX); Serial.print(" ");
    }
    Serial.println();
  }

  // 2. SIRKET ISMI (Sayfa 8-11)
  if (pn532_ntag_readPage(8, buf)) {
    Serial.print("Sirket (HEX):     ");
    for(int i=0; i<16; i++) {
      if(buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX); Serial.print(" ");
    }
    Serial.println();
  }

  // 3. BITMASK & KREDI (Sayfa 12-15)
  if (pn532_ntag_readPage(12, buf)) {
    Serial.print("Bitmask (4B):    ");
    for(int i=0; i<4; i++) {
      if(buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX); Serial.print(" ");
    }
    
    Serial.print("\nKredi (6B):      ");
    for(int i=4; i<10; i++) { // Sayfa 13 ve 14'ün bir kısmı
      if(buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX); Serial.print(" ");
    }
    Serial.println();
  }

  // 4. ZAMAN & DURUM (Sayfa 15-18)
  if (pn532_ntag_readPage(15, buf)) {
    Serial.print("Zaman (10B):     ");
    // Sayfa 15 (4 byte) + 16 (4 byte) + 17 (2 byte)
    for(int i=0; i<10; i++) {
      if(buf[i] < 0x10) Serial.print("0");
      Serial.print(buf[i], HEX); Serial.print(" ");
    }
    
    Serial.print("\nDurum (1B):      ");
    // Sayfa 18, bu okumada (15,16,17,18) 12. indekse düşer
    if(buf[12] < 0x10) Serial.print("0");
    Serial.println(buf[12], HEX);
  }
}


bool pn532_ntag_writePage(uint8_t pageAddr, uint8_t *data4Bytes) {
  // Komut: 0xD4, 0x40 (Exchange), 0x01 (Target), 0xA2 (Write), Sayfa, 4 Byte Veri
  uint8_t cmd[9] = {0xD4, 0x40, 0x01, 0xA2, pageAddr, 
                    data4Bytes[0], data4Bytes[1], data4Bytes[2], data4Bytes[3]};

  pn532_writeFrame(cmd, 9);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

  // Yanıtı kontrol et (Başarılıysa 00 döner)
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  bool success = false;
  for (int i = 0; i < 20; i++) {
    if (reverseABit(SPI.transfer(0x00)) == 0xD5 && reverseABit(SPI.transfer(0x00)) == 0x41) {
      if (reverseABit(SPI.transfer(0x00)) == 0x00) { success = true; break; }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return success;
}

bool ntag_blok_yaz(uint8_t startPage, uint8_t *data, uint8_t totalLen, uint8_t maxLen) {
  uint8_t temp[4];
  // Güvenlik: maxLen üzerinde veri yazma
  uint8_t lenToWrite = (totalLen > maxLen) ? maxLen : totalLen;
  
  int pageNeeded = (maxLen + 3) / 4; 

  for (int p = 0; p < pageNeeded; p++) {
    for (int b = 0; b < 4; b++) {
      int idx = (p * 4) + b;
      temp[b] = (idx < lenToWrite) ? data[idx] : 0x00; // Veri yoksa 0 bas (padding)
    }
    
    if (!pn532_ntag_writePage(startPage + p, temp)) return false;
    delay(10); // Eprom yazma hızı için kısa bekleme
  }
  return true;
}


void ntag_kredili_sistem_yaz() {
  Serial.println("\n--- YAZMA ISLEMI BASLIYOR ---");

  // 1. İsim Soyad (Maks 16 byte - "Mustafa Ozatayoglu" -> "Mustafa Ozatayog")
  char isim[] = "ilk programlama"; 
  if(ntag_blok_yaz(4, (uint8_t*)isim, strlen(isim), 16)) Serial.println("Isim Yazildi.");

  // 2. Şirket (Maks 16 byte)
  char sirket[] = "sirket ismi";
  if(ntag_blok_yaz(8, (uint8_t*)sirket, strlen(sirket), 16)) Serial.println("Sirket Yazildi.");

  // 3. Bitmask (2 Byte ama biz 4 byte yer ayırdık - Sayfa 12)
  // Verilen: 00000001 00010011 (Binary) -> 0x01 0x13
  uint8_t bitmask[4] = {0x01, 0x13, 0x00, 0x00}; 
  if(pn532_ntag_writePage(12, bitmask)) Serial.println("Bitmask Yazildi.");

  // 4. Kredi (1234 -> ASCII olarak "1234" - Sayfa 13 ve 14'ün bir kısmı)
  char kredi[] = "1234";
  if(ntag_blok_yaz(13, (uint8_t*)kredi, 4, 6)) Serial.println("Kredi Yazildi.");

  // 5. Zaman Damgası (1777515420 - 10 Byte - Sayfa 15'ten başlar)
  char zaman[] = "1777515420";
  if(ntag_blok_yaz(15, (uint8_t*)zaman, 10, 10)) Serial.println("Zaman Yazildi.");

  // 6. Durum (2 - Sayfa 18)
  uint8_t durum[4] = {'2', 0x00, 0x00, 0x00}; 
  if(pn532_ntag_writePage(18, durum)) Serial.println("Durum Yazildi.");

  Serial.println("--- YAZMA TAMAMLANDI ---\n");
}

// ************************************
//  ŞİFRE KİLİT KOYMA FONKSİYONU 1 kez çalıştır. 
// ŞİFRE SAFK bunların ascii karşılıkları byte olarak verilecek. 
//***********************************************

bool ntag213_kilit_vur() {
  // 1. Şifreyi Belirle (PWD - Sayfa 43)
  uint8_t pwd[4] = {'S', 'A', 'F', 'K'}; // ********************** şifre burada değiştir. 4 byte olacak. ***********************
  if (!pn532_ntag_writePage(43, pwd)) return false;

  // 2. Onay Kodunu Belirle (PACK - Sayfa 44)
  // İlk 2 byte PACK'tir, kalan 2 byte 0 kalabilir.
  uint8_t pack[4] = {0x12, 0x34, 0x00, 0x00}; 
  if (!pn532_ntag_writePage(44, pack)) return false;

  // 3. Koruma Başlangıç Sayfası (AUTH0 - Sayfa 41)
  // Buraya 0x04 yazarak 4. sayfadan itibaren her şeyi kilitliyoruz.
  uint8_t auth0[4] = {0x04, 0x00, 0x00, 0x00}; 
  if (!pn532_ntag_writePage(41, auth0)) return false;

  // 4. Erişim Türünü Belirle (ACCESS - Sayfa 42)
  // 0x80 -> PROT bitini 1 yapar (Hem Okuma Hem Yazma Koruması)
  uint8_t access[4] = {0x80, 0x00, 0x00, 0x00}; 
  if (!pn532_ntag_writePage(42, access)) return false;

  return true;
}




void setup() {
  Serial.begin(115200);
  pinMode(PN532_IRQ, INPUT_PULLUP); // IRQ pini mutlaka tanımlanmalı
  pinMode(chipSelectPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW); delay(50); digitalWrite(resetPin, HIGH); delay(50);

  SPI.begin();
  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE0));

  uint8_t samCmd[] = {0xD4, 0x14, 0x01, 0x14, 0x01};
  pn532_writeFrame(samCmd, 5);
  pn532_waitReady(100); pn532_readAck();


  Serial.println("IRQ Destekli NTAG213 Okuyucu Hazir...");
  
}

void loop() {
  uint8_t uid[10], uidLen, data[16];
  if (pn532_readUID(uid, uidLen)) {
    Serial.print("\nUID: ");
    for (int i = 0; i < uidLen; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i], HEX); Serial.print(" ");
    }
    ntag213_kilit_vur();
    Serial.println(" SIFRELEME TAMAM SIFRE SAFK ");
    Serial.println();

    if (pn532_ntag_readPage(4, data)) {
      Serial.println("Sayfa 4-7:");
      for (int i = 0; i < 16; i++) {
        if (i > 0 && i % 4 == 0) Serial.print("| ");
        if (data[i] < 0x10) Serial.print("0");
        Serial.print(data[i], HEX); Serial.print(" ");
      }
      Serial.println();
    }
    ntag_kredili_oku(uid, uidLen);

    ntag_kredili_sistem_yaz();
    
    delay(2000);
  }
}
