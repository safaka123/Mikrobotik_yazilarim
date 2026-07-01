#include <SPI.h>

const int chipSelectPin = 10;
const int resetPin = 3;
#define PN532_IRQ 2     // Arduino D2 pini
#define BUZZER_PIN 4

#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 

// --- 🏢 TERMİNAL DONANIM KİMLİK TANIMLAMALARI ---
const char* TERMINAL_SIRKET = "izbb";
// Cihazın ait olduğu yetkili şirket ismi
const int   TERMINAL_KAPI   = 2;
// Bu okuyucunun monte edildiği fiziksel kapı numarası (1-16 arası)

// -------------------------------
// Sizin Bit Reverse Fonksiyonunuz (Aynen Korundu)
// -------------------------------
uint8_t reverseABit(uint8_t x) {
  x = ((x & 0x55) << 1) |
((x & 0xAA) >> 1);
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

  SPI.transfer(reverseABit(dcs)); // 🌟 BURASI ORİJİNAL HALİNE GETİRİLDİ (Haberleşme hatası çözüldü)
  SPI.transfer(reverseABit(0x00));
// POSTAMBLE

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
        Serial.print(sw1, HEX); Serial.print(" ");
        Serial.println(sw2, HEX);
        
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
        Serial.print(sw1, HEX); Serial.print(" ");
        Serial.println(sw2, HEX);
        
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

// --- SETUP ---
void setup() {
  Serial.begin(115200);
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

  pn532_samConfig();
  // Sizin uyanmayı garantiye alan sihirli dokunuşunuz
  Serial.println("Waiting for an ISO14443A Card or Phone (HCE) ...");
}

// --- LOOP ---
void loop() {
  int myDoor = 2;
  // Sizin sabit terminal kapı numaranız
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
        if (sak == 0x20) { phoneFound = true; break;
        }
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
          
          char isim[17] = {0};
          char sirket[17] = {0};       
          uint8_t kapiMaskesi[2];      
          char kredi[5] = {0};         
          char zamanDamgasi[11] = {0}; 
          uint8_t durumMetot = 0;
          uint8_t durumProfil = 0;     

          // Ayrıştırma İşlemleri
          memcpy(isim, &phoneData[9], 16);
          for(int i = 15; i >= 0; i--) { if(isim[i] == ' ') i = '\0'; else break;
          }

          memcpy(sirket, &phoneData[25], 16);
          for(int i = 15; i >= 0; i--) { if(sirket[i] == ' ') sirket[i] = '\0'; else break;
          }

          // -----------------------------------------------------------------
          // 🚪 GERÇEK HAM BINARY KAPI MASKESİ BİRLEŞTİRME (Endianness Düzeltildi)
          // -----------------------------------------------------------------
          // Sizin tespitiniz doğrultusunda alt ve üst byte dizilim sıralaması tam olması gerektiği gibi yer değiştirildi:
          uint8_t maskeAltByte = phoneData[41]; // Telefondan gelen b1 (Kapı 1-8 alt byte'ı)
          uint8_t maskeUstByte = phoneData[42]; // Telefondan gelen b2 (Kapı 9-16 üst byte'ı)

          // Üst byte 8 bit sola kaydırılır ve alt byte ile birleştirilerek kusursuz 16-bit oluşturulur
          uint16_t gercekBitmask = ((uint16_t)maskeUstByte << 8) | maskeAltByte;

          memcpy(kredi, &phoneData[43], 4);
          memcpy(zamanDamgasi, &phoneData[47], 10);
          durumMetot = phoneData[57];
          durumProfil = phoneData[58];
          // Kurumsal Rapor Çıktısı (Seri Monitör)
          Serial.println("\n======= 💳 İZBB TERMİNAL SİSTEMİ =======");
          Serial.print("👤 Kullanıcı:     "); Serial.println(isim);
          Serial.print("🏢 Şirket:        "); Serial.println(sirket);
          // Ham maskeyi kurumsal Hex formatında basıyoruz (Örn: 0x00C3)
          Serial.print("🚪 Kapı Yetki M.: ");
          if (gercekBitmask < 0x0010) Serial.print("000");
          else if (gercekBitmask < 0x0100) Serial.print("00");
          else if (gercekBitmask < 0x1000) Serial.print("0");
          Serial.println(gercekBitmask, HEX);
          // KULLANICIYA ANLAŞILIR KAPI NUMARALARINI BASMA (Binary'den String'e Çevrim)
          Serial.print("🚪 Yetkili Kapılar: ");
          bool ilkKapi = true;
          for (int i = 1; i <= 16; i++) {
            if ((gercekBitmask & (1 << (i - 1))) != 0) {
              if (!ilkKapi) Serial.print(", ");
              Serial.print(i);
              ilkKapi = false;
            }
          }
          if (ilkKapi) Serial.print("Hiçbir kapıya yetki yok!");
          Serial.println();

          Serial.print("💰 Güncel Kredi:  "); Serial.println(kredi);
          Serial.print("⏰ RTC/Epoch Z.:  "); Serial.println(zamanDamgasi);
          Serial.print("🔄 90 Dk Metodu:  "); Serial.println(durumMetot);
          Serial.print("📊 Kart Profili:  "); 
          switch(durumProfil) {
            case 0: Serial.println("0 (Tam Kart)");
              break;
            case 1: Serial.println("1 (Engelli Ücretsiz)"); break;
            case 2: Serial.println("2 (Öğretmen)"); break;
            case 3: Serial.println("3 (Öğrenci)"); break;
            default: Serial.print(durumProfil);
              Serial.println(" (Özel Profil)"); break;
          }
          Serial.println("========================================\n");
          // -----------------------------------------------------------------
          // 🛑 ADIM 1: PARAMETRİK BİT SEVİYESİNDE YETKİLENDİRME 🛑
          // -----------------------------------------------------------------
          
          // 1. Şirket Doğrulaması (TERMINAL_SIRKET ile kıyaslanır)
          bool companyOK = (strcmp(sirket, TERMINAL_SIRKET) == 0);
          // 2. Saf Bitwise Kontrolü (Sizin eski mantıkla birebir aynı)
          // TERMINAL_KAPI = 2 ise -> (1 << 1) -> 0x0002.
          // gercekBitmask ile AND'lenir.
          bool doorOK = ((gercekBitmask & (1 << (TERMINAL_KAPI - 1))) != 0);
          // 3. Karar ve Ayrıntılı Loglama Mekanizması
          if (companyOK && doorOK) {
            Serial.print("📝 LOG: [YETKİLİ] -> ");
            Serial.print(isim);
            Serial.print(" isimli personelin karti ");
            Serial.print(zamanDamgasi);
            Serial.print(" RTC zaman damgasinda ");
            Serial.print(TERMINAL_SIRKET);
            Serial.print(" bünyesindeki ");
            Serial.print(TERMINAL_KAPI);
            Serial.println(" nolu kapidan basariyla gecmistir.");
            
            BIP(); // Başarılı Geçiş Sesi
          } 
          else {
            Serial.print("⚠️ LOG: [RED] -> ");
            Serial.print(isim);
            Serial.print(" isimli sahis ");
            Serial.print(zamanDamgasi);
            Serial.print(" zaman damgasinda ");
            Serial.print(TERMINAL_KAPI);
            Serial.print(" nolu kapiyi zorladi. ");
            if (!companyOK) {
              Serial.print("NEDEN: YETKİSİZ ŞİRKET (Gelen: '");
              Serial.print(sirket);
              Serial.print("', Beklenen: '");
              Serial.print(TERMINAL_SIRKET);
              Serial.println("')");
            }
            else if (!doorOK) {
              Serial.print("NEDEN: YETKİSİZ KAPI (Sahsin bu kapiya [Kapı ");
              Serial.print(TERMINAL_KAPI);
              Serial.println("] geçiş izni tanımlı değil!)");
            }
            
            BIP_BIP();
            // Başarısız Geçiş Sesi
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
    delay(2500); 
  } 
  delay(100);
}
