#include <SPI.h>
#include <Wire.h> // RTC için gerekli

// --- PIN TANIMLAMALARI ---
const int chipSelectPin = 10;
const int resetPin      = 3;
const int PN532_IRQ     = 2; 
String isimsoy = "";
String sirket="";
String kapibitmask = "";

// --- GLOBAL DEĞİŞKENLER ---
unsigned long RTCunixTime = 0; // RTC'den gelen canlı zaman

// --- PROTOKOL SABİTLERİ ---
#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 
#define PN532_COMMAND_INCOMMUNICATETHRU 0x42 

// ===============  RTC UNIXTIME FONKSİYONLARI ========================

// RTC yıl, ay, gün, saat, dakika -> Unix timestamp (saniye)
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
  RTCunixTime = days*86400UL + hour*3600UL + min*60UL;
  return RTCunixTime;
}

void rtcZamanPlusDakika()
{
  Wire.beginTransmission(0x68);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7);

  if (Wire.available()) {
    uint8_t s  = Wire.read() & 0x7F;
    uint8_t m  = Wire.read();
    uint8_t h  = Wire.read();
    Wire.read(); // Haftanın günü pas geçiliyor
    uint8_t d  = Wire.read();
    uint8_t mo = Wire.read();
    uint8_t y  = Wire.read();

    m  = (m>>4)*10 + (m&0x0F);
    h  = (h>>4)*10 + (h&0x0F);
    d  = (d>>4)*10 + (d&0x0F);
    mo = (mo>>4)*10 + (mo&0x0F);
    y  = (y>>4)*10 + (y&0x0F);

    int yy = y + 2000;
    rtcToUnix(yy, mo, d, h, m);
  }
}

// --- TEMEL PN532 FONKSİYONLARI ---
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

bool pn532_waitReady(uint16_t timeout) {
  uint32_t t = millis();
  while (millis() - t < timeout) {
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

bool ntag213_authenticate_tunnel(uint8_t *pwd) {
  uint8_t cmd[7] = {0xD4, 0x42, 0x1B, pwd[0], pwd[1], pwd[2], pwd[3]};
  pn532_writeFrame(cmd, 7);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(200)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  uint8_t res[20];
  for (int i = 0; i < 20; i++) res[i] = reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);

  for (int i = 0; i < 12; i++) {
    if (res[i] == 0xD5 && res[i+1] == 0x43) {
      if (res[i+2] == 0x00) return true;
    }
  }
  return false;
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

bool pn532_ntag_writePage(uint8_t pageAddr, uint8_t *data4Bytes) {
  uint8_t cmd[9] = {0xD4, 0x40, 0x01, 0xA2, pageAddr, 
                    data4Bytes[0], data4Bytes[1], data4Bytes[2], data4Bytes[3]};
  pn532_writeFrame(cmd, 9);
  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

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
  uint8_t lenToWrite = (totalLen > maxLen) ? maxLen : totalLen;
  int pageNeeded = (maxLen + 3) / 4; 
  for (int p = 0; p < pageNeeded; p++) {
    for (int b = 0; b < 4; b++) {
      int idx = (p * 4) + b;
      temp[b] = (idx < lenToWrite) ? data[idx] : 0x00;
    }
    if (!pn532_ntag_writePage(startPage + p, temp)) return false;
    delay(10);
  }
  return true;
}

bool yetkiKontrolu(uint8_t *buffer, int hedefKapi) {
    int kapiIndex = hedefKapi - 1; 
    int byteIdx = kapiIndex / 8;
    int bitIdx = kapiIndex % 8;
    return (buffer[byteIdx] & (1 << bitIdx));
}

// --- ANA OKUMA FONKSİYONU (GELİŞTİRİLMİŞ) ---
void ntag_kredili_oku_detayli() {
  uint8_t buf[16];
  isimsoy = ""; // Temizlik
  Serial.println("\n--- NTAG213 KONTROL PANELI ---");

  // 1. ISIM SOYAD
  if (pn532_ntag_readPage(4, buf)) {
    Serial.print("ISIM SOYAD: ");
    for(int i=0; i<16; i++) {
      if(buf[i] == 0x00) break;
      isimsoy += (char)buf[i];
    }
    Serial.println(isimsoy);
  }

  // 2. SIRKET KONTROL
const String sirketkontrol = "izbb";
bool sirketDogrulandi = false;
sirket = "";

if (pn532_ntag_readPage(8, buf)) {
    for(int i=0; i<16; i++) {
        if(buf[i] == 0x00) break; // Null karakter gördüğünde döngüden çık
        sirket += (char)buf[i];
    }
    
    Serial.print("SIRKET: "); Serial.println(sirket);

    // '==' yerine 'startsWith' kullanarak 16 byte içindeki fazlalıkları eliyoruz
    if (sirket.startsWith(sirketkontrol)) { 
        sirketDogrulandi = true;
        Serial.println(">>> [OK] Sirket Onaylandi.");
    } else {
        Serial.println(">>> [HATA] Gecersiz Sirket!");
    }
}
  // 3. ZAMAN KONTROLÜ (Sayfa 15 - 10 Byte)
  bool zamanGecerli = false;
  if (pn532_ntag_readPage(15, buf)) {
    String zamanStr = "";
    for(int i=0; i<10; i++) {
        if(buf[i] == 0x00) break;
        zamanStr += (char)buf[i];
    }
    unsigned long kartZamanUnix = strtoul(zamanStr.c_str(), NULL, 10);
    
    Serial.print("KART SON TARIH (Unix): "); Serial.println(kartZamanUnix);
    Serial.print("CIHAZ TARIH (Unix):    "); Serial.println(RTCunixTime);

    if (RTCunixTime <= kartZamanUnix) {
        zamanGecerli = true;
        Serial.println(">>> [OK] Kart Suresi Gecerli.");
    } else {
        Serial.println(">>> [HATA] KART SURESİ DOLMUS!");
    }
  }

  // 4. BITMASK & FINAL ERISIM
  const int CIHAZ_KAPI_NO = 2; 
  if (pn532_ntag_readPage(12, buf)) {
    Serial.print("BITMASK (BIN): ");
    for (int i = 1; i >= 0; i--) {
      for (int bit = 7; bit >= 0; bit--) {
          Serial.print((buf[i] & (1 << bit)) ? "1" : "0");
      }
      Serial.print(" ");
    }
    Serial.println("");

    // TÜM ŞARTLAR: Şirket + Zaman + Kapı Yetkisi
    if (sirketDogrulandi && zamanGecerli) {
        if (yetkiKontrolu(buf, CIHAZ_KAPI_NO)) {
            Serial.println(">>>>>> ERISIM ONAYLANDI: Kapi Aciliyor... <<<<<<");
        } else {
            Serial.println(">>> [HATA] Bu Kapi Icin Yetki Yok!");
        }
    } else {
        Serial.println(">>> ERISIM REDDEDILDI: Guvenlik Sartlari Saglanamadi.");
    }
  }
}

// --- SETUP & LOOP ---
void setup() {
  Serial.begin(115200);
  Wire.begin(); // I2C Başlat (RTC için)
  
  pinMode(PN532_IRQ, INPUT_PULLUP);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW); delay(50); digitalWrite(resetPin, HIGH); delay(50);

  SPI.begin();
  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE0));

  uint8_t samCmd[] = {0xD4, 0x14, 0x01, 0x14, 0x01};
  pn532_writeFrame(samCmd, 5);
  pn532_waitReady(100); pn532_readAck();

  Serial.println("Sistem Hazir. RTC ve NTAG Bekleniyor...");
}

void loop() {
  // Her döngüde güncel saati RTC'den alalım
  rtcZamanPlusDakika();

  uint8_t uid[10], uidLen;
  if (pn532_readUID(uid, uidLen)) {
    Serial.print("\nUID: ");
    for (int i = 0; i < uidLen; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i], HEX); Serial.print(" ");
    }
    Serial.println();

    uint8_t password[4] = {'S', 'A', 'F', 'K'};
    if (ntag213_authenticate_tunnel(password)) {
      Serial.println(">>> SIFRE DOGRU!");
      ntag_kredili_oku_detayli();
    } else {
      Serial.println(">>> HATA: Sifre Yanlis!");
    }
    
    Serial.println("\nKarti cekin...");
    delay(3000);
  }
}
