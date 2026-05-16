#include <SPI.h>
#include <Wire.h>

unsigned long RTCunixTime = 0;
const int chipSelectPin = 10;
const int resetPin = 3;
#define BUZZER_PIN 4

#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 

// -------------------------------
// Bit reverse (KULLANILACAK)
// -------------------------------
uint8_t reverseABit(uint8_t x) {
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
  x = ((x & 0x0F) << 4) | ((x & 0xF0) >> 4);
  return x;
}

// -------------------------------
// READY kontrol (datasheet uygun)
// -------------------------------
bool pn532_ready() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_STATREAD);
  uint8_t r = reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);
  return (r == 0x01);
}

// -------------------------------
// READY bekle
// -------------------------------
bool pn532_waitReady(uint16_t timeout) {
  uint32_t t = millis();
  while (millis() - t < timeout) {
    if (pn532_ready()) return true;
    delay(1);
  }
  return false;
}

// -------------------------------
// ACK oku (6 byte)
// -------------------------------
void pn532_readAck() {
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  for (int i = 0; i < 6; i++) {
    reverseABit(SPI.transfer(0x00));
  }

  digitalWrite(chipSelectPin, HIGH);
}

// -------------------------------
// Frame gönder
// -------------------------------
void pn532_writeFrame(uint8_t *data, uint8_t len) {

  uint8_t sum = 0;
  for (int i = 0; i < len; i++) sum += data[i];
  uint8_t dcs = 0x100 - sum;

  digitalWrite(chipSelectPin, LOW);

  SPI.transfer(PN532_SPI_DATAWRITE);

  // PREAMBLE
  SPI.transfer(reverseABit(0x00));
  SPI.transfer(reverseABit(0x00));
  SPI.transfer(reverseABit(0xFF));

  // LEN + LCS
  SPI.transfer(reverseABit(len));
  SPI.transfer(reverseABit(0x100 - len));

  // DATA
  for (int i = 0; i < len; i++) {
    SPI.transfer(reverseABit(data[i]));
  }

  // DCS + POST
  SPI.transfer(reverseABit(dcs));
  SPI.transfer(reverseABit(0x00));

  digitalWrite(chipSelectPin, HIGH);
}

// -------------------------------
// Firmware oku (SAĞLAM)
// -------------------------------
bool pn532_getFirmware(uint8_t &ver, uint8_t &rev) {

  uint8_t cmd[] = {0xD4, 0x02};

  pn532_writeFrame(cmd, 2);

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();

  if (!pn532_waitReady(100)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  // frame başını yakala
  for (int i = 0; i < 30; i++) {

    uint8_t d = reverseABit(SPI.transfer(0x00));

    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x03) {

        reverseABit(SPI.transfer(0x00)); // IC

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

// -------------------------------
// SAM config
// -------------------------------
void pn532_samConfig() {

  uint8_t cmd[] = {0xD4,0x14,0x01,0x14,0x01};

  pn532_writeFrame(cmd, 5);

  pn532_waitReady(100);
  pn532_readAck();
  pn532_waitReady(100);
}

// -------------------------------
// UID oku (SAĞLAM VERSION)
// -------------------------------
bool pn532_readUID(uint8_t *uid, uint8_t &uidLen) {

  uint8_t cmd[] = {0xD4,0x4A,0x01,0x00};

  pn532_writeFrame(cmd, 4);

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();

  if (!pn532_waitReady(300)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  bool found = false;

  for (int i = 0; i < 40; i++) {

    uint8_t d = reverseABit(SPI.transfer(0x00));

    if (d == 0xD5) {

      if (reverseABit(SPI.transfer(0x00)) == 0x4B) {

        found = true;

        reverseABit(SPI.transfer(0x00)); // NbTg
        reverseABit(SPI.transfer(0x00)); // Tg
        reverseABit(SPI.transfer(0x00));
        reverseABit(SPI.transfer(0x00));
        reverseABit(SPI.transfer(0x00));

        uidLen = reverseABit(SPI.transfer(0x00));

        for (int i = 0; i < uidLen; i++) {
          uid[i] = reverseABit(SPI.transfer(0x00));
        }

        digitalWrite(chipSelectPin, HIGH);
        return true;
      }
    }
  }

  digitalWrite(chipSelectPin, HIGH);
  return false;
}

// -------------------------------
// Mifare Classic Authenticate (Data Exchange)
// -------------------------------
bool pn532_mifareAuthenticate(uint8_t *uid, uint8_t uidLen, uint8_t blockAddr, uint8_t keyType, uint8_t *key) {
  // Komut: 0x40 (InDataExchange), 0x01 (Target 1), 0x60 veya 0x61 (Auth Key A/B)
  // Devamı: BlockAddr, Key (6 byte), UID (4 byte)
  
  uint8_t cmd[20];
  cmd[0] = 0xD4;
  cmd[1] = 0x40; // InDataExchange
  cmd[2] = 0x01; // Target number
  cmd[3] = (keyType == 0) ? 0x60 : 0x61; // 0x60=KeyA, 0x61=KeyB
  cmd[4] = blockAddr;
  
  for (int i = 0; i < 6; i++) cmd[5 + i] = key[i];
  for (int i = 0; i < uidLen; i++) cmd[11 + i] = uid[i];

  pn532_writeFrame(cmd, 11 + uidLen);

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

  // Yanıt kontrolü (Response parse)
  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  
  bool success = false;
  for (int i = 0; i < 20; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) { // 0x41 = InDataExchange Response
        uint8_t status = reverseABit(SPI.transfer(0x00));
        if (status == 0x00) success = true; // Status 00 = OK
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return success;
}

// -------------------------------
// Mifare Classic Read Block
// -------------------------------
bool pn532_readBlock(uint8_t blockAddr, uint8_t *buffer) {
  uint8_t cmd[] = {0xD4, 0x40, 0x01, 0x30, blockAddr}; // 0x30 = Mifare Read

  pn532_writeFrame(cmd, 5);

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  bool found = false;
  for (int i = 0; i < 40; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) {
        if (reverseABit(SPI.transfer(0x00)) == 0x00) { // Status OK
          for (int b = 0; b < 16; b++) {
            buffer[b] = reverseABit(SPI.transfer(0x00));
          }
          found = true;
          break;
        }
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return found;
}




#define PN532_IRQ (2) // Arduino D2 pini



// -------------------------------
// Mifare Classic Write Block
// -------------------------------
bool pn532_writeBlock(uint8_t blockAddr, uint8_t *buffer) {
  uint8_t cmd[21]; // Tam olarak 21 byte
  cmd[0] = 0xD4;
  cmd[1] = 0x40; 
  cmd[2] = 0x01; 
  cmd[3] = 0xA0; // Mifare Write
  cmd[4] = blockAddr;
  
  for (int i = 0; i < 16; i++) {
    cmd[5 + i] = buffer[i];
  }

  // BURASI KRİTİK: len parametresi cmd dizisinin gerçek boyutu olmalı
  pn532_writeFrame(cmd, 21); 

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(150)) return false; // Yazma süresini biraz artırdık

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  bool success = false;
  // Yanıt çerçevesini tarayalım
  for (int i = 0; i < 25; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) {
        uint8_t status = reverseABit(SPI.transfer(0x00));
        if (status == 0x00) { 
          success = true;
          break;
        }
      }
    }
  }
  digitalWrite(chipSelectPin, HIGH);
  return success;
}

// -------------------------------
// BIP LER
// -------------------------------

void BIP() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
}

void BIP_BIP() {
  for(int i=0;i<2;i++){
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}

// -------------------------------
// BLOK TO STRING
// -------------------------------

String blockToString(uint8_t *data) {
  String s = "";
  for (int i = 0; i < 16; i++) {
    char c = (char)data[i];
    if (c == 0x00) break;
    if (c >= 32 && c <= 126) s += c;
  }
  s.trim();
  return s;
}

//=====================================
//      RTC  OKUMA
//=====================================

void rtcZamanPlusDakika()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7);

  uint8_t s  = Wire.read() & 0x7F;
  uint8_t m  = Wire.read();
  uint8_t h  = Wire.read();
  Wire.read();
  uint8_t d  = Wire.read();
  uint8_t mo = Wire.read();
  uint8_t y  = Wire.read();

  // BCD → DECIMAL
  m  = (m>>4)*10 + (m&0x0F);
  h  = (h>>4)*10 + (h&0x0F);
  d  = (d>>4)*10 + (d&0x0F);
  mo = (mo>>4)*10 + (mo&0x0F);
  y  = (y>>4)*10 + (y&0x0F);

  int yy = y + 2000;

  RTCunixTime = rtcToUnix(yy, mo, d, h, m);

  Serial.print("RTC Unix: ");
  Serial.println(RTCunixTime);
}
//=====================================
//      RTC TO UNIX
//=====================================
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


//=====================================
//    KREDİ VE YAZ CUSTOM krediyaz fonksiyonu yerine kullanılıyor. 
//=====================================
bool krediYazCustom(uint8_t *uid, uint8_t uidLen,
                    uint8_t *block8,
                    uint8_t *block9,
                    uint8_t *block10) {

  Serial.println("\n--- KREDI YAZMA (CUSTOM) ---");
  delay(150);

  uint8_t keyB[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

  uint8_t data8[16];
  uint8_t data9[16];
  uint8_t data10[16];

  // -------- 16 BYTE KOPYALA --------
  memset(data8, 0, 16);
  memset(data9, 0, 16);
  memset(data10, 0, 16);

  memcpy(data8,  block8,  16);
  memcpy(data9,  block9,  16);
  memcpy(data10, block10, 16);

  // DEBUG (okunabilir kontrol)
  Serial.print("B8: ");  Serial.println((char*)data8);
  Serial.print("B9: ");  Serial.println((char*)data9);
  Serial.print("B10: "); Serial.println((char*)data10);

  // -------- SEKTÖR AUTH (TEK KEZ) --------
  if (!pn532_mifareAuthenticate(uid, uidLen, 11, 1, keyB)) {
    Serial.println("AUTH FAIL (Sector 2)");
    return false;
  }

  uint8_t blocks[] = {8, 9, 10};
  uint8_t *datas[] = {data8, data9, data10};

  for (int i = 0; i < 3; i++) {

    delay(80);

    if (!pn532_writeBlock(blocks[i], datas[i])) {
      Serial.print("YAZMA HATA: Block ");
      Serial.println(blocks[i]);
      return false;
    }

    Serial.print("YAZILDI: Block ");
    Serial.println(blocks[i]);

    // IRQ stabilizasyon
    uint32_t t = millis();
    while (digitalRead(PN532_IRQ) == HIGH && millis() - t < 80);
  }

  Serial.println("--- KREDI YAZMA BITTI ---");
  return true;
}

//=====================================
//    hesaplama ve yazma
//=====================================

bool hesaplaVeYaz(uint8_t *uid, uint8_t uidLen,
                  uint8_t *block8,
                  uint8_t *block9,
                  uint8_t *block10) {

  Serial.println("\n--- HESAPLAMA BASLADI ---");

  // -------- OKUNAN VERILER --------
  int kredi = blockToString(block8).toInt();
  unsigned long kartZaman = strtoul(blockToString(block9).c_str(), NULL, 10);
  int durum = blockToString(block10).toInt();

  Serial.print("Kredi: "); Serial.println(kredi);
  Serial.print("Kart Zaman: "); Serial.println(kartZaman);
  Serial.print("Durum: "); Serial.println(durum);

  // -------- RTC --------
  rtcZamanPlusDakika();
  unsigned long simdi = RTCunixTime;

  long farkDakika = (simdi - kartZaman) / 60;
  if (farkDakika < 0) farkDakika = 100;

  Serial.print("Fark dk: "); Serial.println(farkDakika);

  int dusulecek = 0;
  bool zamanYaz = false;
  bool durumYaz = false;

  int yeniDurum = durum;

  // =========================
  // ANA LOGIC
  // =========================

  if (farkDakika > 90) {
    // ⏱ 90dk dışı = RESET + 30 kredi
    dusulecek = 30;
    zamanYaz = true;
    durumYaz = true;
    yeniDurum = 0;

    Serial.println(">> 90DK DISI -> 30 KREDI");

  } else {

    if (durum == 0) {
      // 🟡 süre içi ilk tekrar
      dusulecek = 5;
      durumYaz = true;
      yeniDurum = 1;

      Serial.println(">> 2. GECIS -> 5 KREDI");

    } else if (durum == 1) {
      // 🔵 ücretsiz
      Serial.println(">> UCRETSIZ GECIS");
      return false;
    }
  }

  // -------- BAKIYE --------
  if (kredi < dusulecek) {
    Serial.println(">> YETERSIZ BAKIYE");
    return false;
  }

  int yeniKredi = kredi - dusulecek;

  Serial.print("Yeni kredi: ");
  Serial.println(yeniKredi);

  // -------- VERI HAZIRLA --------
  uint8_t b8[16] = {0};
  uint8_t b9[16] = {0};
  uint8_t b10[16] = {0};

  String krediStr = String(yeniKredi);
  memcpy(b8, krediStr.c_str(), krediStr.length());

  if (zamanYaz) {
    char tbuf[11];
    sprintf(tbuf, "%lu", simdi);
    memcpy(b9, tbuf, strlen(tbuf));
  } else {
    memcpy(b9, block9, 16); // eskiyi koru
  }

  if (durumYaz) {
    String dStr = String(yeniDurum);
    memcpy(b10, dStr.c_str(), dStr.length());
  } else {
    memcpy(b10, block10, 16);
  }

  // -------- YAZ --------
  return krediYazCustom(uid, uidLen, b8, b9, b10);
}



// -------------------------------
// SETUP
// -------------------------------
void setup() {
  Wire.begin();
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
    Serial.print(v);
    Serial.print(".");
    Serial.println(r);
  } else {
    Serial.println("PN532 bulunamadi!");
  }

  pn532_samConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}

// -------------------------------
// LOOP
// -------------------------------
void loop() {

  uint8_t uid[10];
  uint8_t uidLen;

  uint8_t keyB[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

  uint8_t blocks[] = {4,5,6,8,9,10};
  uint8_t data[6][16];
  bool ok[6];

  if (pn532_readUID(uid, uidLen)) {

    Serial.println("\n--- KART OKUMA ---");

    // -------- TÜM BLOKLARI OKU --------
    for (int i = 0; i < 6; i++) {

      uint8_t block = blocks[i];
      uint8_t authGate = (block < 8) ? 6 : 10;

      ok[i] = false;

      delay(100); // KRİTİK

      if (pn532_mifareAuthenticate(uid, uidLen, authGate, 1, keyB)) {

        uint32_t t = millis();
        while (digitalRead(PN532_IRQ) == HIGH && millis() - t < 50);

        delay(5);

        if (pn532_readBlock(block, data[i])) {
          ok[i] = true;
          Serial.print("B"); Serial.print(block); Serial.print(":OK ");
        } else {
          Serial.print("B"); Serial.print(block); Serial.print(":RE ");
        }

      } else {
        Serial.print("B"); Serial.print(block); Serial.print(":AE ");
      }
    }

    // -------- OKUMA KONTROL --------
    bool allOK = true;
    for (int i = 0; i < 6; i++) {
      if (!ok[i]) allOK = false;
    }

    Serial.println("\n\n--- OKUMA SONUCU ---");

    for (int i = 0; i < 6; i++) {

      Serial.print("Block ");
      Serial.print(blocks[i]);
      Serial.print(": ");

      if (ok[i]) {

        for (int j = 0; j < 16; j++) {
          char c = (char)data[i][j];
          if (c >= 32 && c <= 126) Serial.print(c);
          else Serial.print(".");
        }

      } else {
        Serial.print("Hata");
      }

      Serial.println();
    }

    // -------- HATA VARSA DUR --------
    if (!allOK) {
      Serial.println(">>> OKUMA HATASI - ISLEM YAPILMAZ");
      delay(2000);
      return;
    }

    // -------- STRING DONUSUM --------
    String name    = blockToString(data[0]); // 4
    String company = blockToString(data[1]); // 5

    Serial.println("\n--- KONTROL ---");
    Serial.print("Isim: "); Serial.println(name);
    Serial.print("Sirket: "); Serial.println(company);

    // -------- SIRKET KONTROL --------
    if (company != "izbb") {

      Serial.println(">>> YETKISIZ (SIRKET HATALI)");
      delay(2000);
      return;
    }

    // -------- YAZMA --------
    Serial.println(">>> KART GECERLI - YAZMA BASLIYOR");

    
    hesaplaVeYaz(uid, uidLen, data[3], data[4], data[5]);
    delay(3000); // kartı çekme süresi
  }
}
