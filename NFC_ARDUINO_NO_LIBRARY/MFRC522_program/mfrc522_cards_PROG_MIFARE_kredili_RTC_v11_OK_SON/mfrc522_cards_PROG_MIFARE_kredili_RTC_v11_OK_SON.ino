// KREDİLİ SİSTEM - STABİL VERSİON v10
// Okuma ve Yazma işlemleri seri port kesmesi olmadan hızlıca yapılır.
// SPI hızı 200kHz sabitlendi.
//*********** yapılacak iş seri monitör çıktılarına tüm gelen bilgi ve yazılan bilgiler eklenecek seri monitörden olayı tamamen göreceğiz
// eproma kayıt sadece pc ye yazılmadığında yapılacak. 
// **************  bu düzeltmeyi de yap. 


#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>

#define SS_PIN   10
#define RST_PIN  9
#define BUZZER_PIN 6
const String OKUYUCU_KIMLIK = "izbb";

// MFRC522 Register Tanımları
#define CommandReg      0x01
#define ComIEnReg       0x02
#define ComIrqReg       0x04
#define DivIrqReg       0x05
#define ErrorReg        0x06
#define FIFODataReg     0x09
#define FIFOLevelReg    0x0A
#define ControlReg      0x0C
#define BitFramingReg   0x0D
#define ModeReg         0x11
#define TxModeReg       0x12
#define TxControlReg    0x14
#define TxASKReg        0x15
#define CRCResultRegM   0x21
#define CRCResultRegL   0x22
#define TModeReg        0x2A
#define TPrescalerReg   0x2B
#define TReloadRegH     0x2C
#define TReloadRegL     0x2D
#define VersionReg      0x37
#define Status2Reg      0x08

#define PCD_IDLE        0x00
#define PCD_TRANSCEIVE  0x0C
#define PCD_CALCCRC     0x03
#define PCD_AUTHENT     0x0E
#define PCD_RESET       0x0F

#define PICC_REQIDL     0x26
#define PICC_SELECTTAG  0x93
#define PICC_AUTH_KEY_B 0x61
#define PICC_READ       0x30
#define PICC_WRITE      0xA0

#define MAX_LEN         18

// Değişkenler
byte uid[7];
byte uidSize = 4;
byte defaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned long RTCunixTime = 0;

SoftwareSerial BTSerial(7, 8); // RX, TX
const unsigned long BT_BAUD = 9600;

// EEPROM LOG Ayarları

#define EEPROM_SIZE 1024
#define MAXLOG ((EEPROM_SIZE-EEPROM_START)/LOGSIZE)
#define ACK_TIMEOUT 300
#define LOGSIZE 20  // 19 yerine 20 yapmak her zaman daha güvenlidir
#define EEPROM_START 2

struct __attribute__((packed)) LOG {
  uint32_t time;      // 4 byte - RTC zamanı
  uint8_t  uidSize1;  // 1 byte - UID uzunluğu
  uint8_t  uid[7];    // 7 byte - Kart ID
  uint8_t  gate;      // 1 byte - Okuyucu No (Senin istediğin gibi 1 byte)
  uint32_t kredi;     // 4 byte - Kalan Kredi
  uint16_t result;    // 2 byte - Durum / İndirim Bilgisi
  uint8_t  reserved;  // 1 byte - Boş yer (Hizalama için ekledik, toplam 20 oldu)
};
// ============ EEPROM KAYIT FONK. ========================
// Fonksiyon: log gönder ve EEPROM backup
void logGonder(LOG &log) {
  uint16_t pointer;

  

  EEPROM.get(0, pointer);
  if(pointer >= MAXLOG) pointer = 0;

  // Logu binary olarak SoftSerial'e gönder
  BTSerial.write(0xAA); // header
  BTSerial.write((uint8_t*)&log, sizeof(LOG));

  unsigned long t0 = millis();
  bool ack = false;

  // ACK bekle
  while(millis() - t0 < ACK_TIMEOUT) {
    if(BTSerial.available()) {
      String r = BTSerial.readStringUntil('\n');
      r.trim();
      if(r == "ACK") {
        ack = true;
        break;
      }
    }
  }
  
  if(ack) {
    // EEPROM dump
    for(int i = 0; i < pointer; i++) {
      int addr = EEPROM_START + (i * LOGSIZE);
      LOG tmp;
      EEPROM.get(addr, tmp);

      // Dumpu SoftSerial ile gönder (binary)
      BTSerial.write(0xAA); // header
      BTSerial.write((uint8_t*)&tmp, sizeof(LOG));
      delay(5); // hafif gecikme
    }

    // pointer reset
    pointer = 0;
    EEPROM.put(0, pointer);
  } else {
    // EEPROM'a yedekle
    int addr = EEPROM_START + (pointer * LOGSIZE);
    EEPROM.put(addr, log);
    pointer++;
    EEPROM.put(0, pointer);
  }

  // =========================
  // TEST AMAÇLI EEPROM OKUMA
  // =========================

  Serial.println("EEPROM TEST READ");

  uint16_t p;
  EEPROM.get(0, p);

  Serial.print("Pointer: ");
  Serial.println(p);

  for(int i = 0; i < p; i++) {

    int addr = EEPROM_START + (i * LOGSIZE);

    LOG tmp;
    EEPROM.get(addr, tmp);

    uint8_t *raw = (uint8_t*)&tmp;

    Serial.print("LOG ");
    Serial.print(i);
    Serial.print(" : ");

    for(int j = 0; j < sizeof(LOG); j++) {

      if(raw[j] < 16) Serial.print("0");

      Serial.print(raw[j], HEX);
      Serial.print(" ");
    }

    Serial.println();
  }

  
}









// --- RC522 Low Level (Hız Sabitlendi) ---
void rcWrite(byte reg, byte val) {
  SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE0));
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((reg << 1) & 0x7E);
  SPI.transfer(val);
  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();
}

byte rcRead(byte reg) {
  SPI.beginTransaction(SPISettings(200000, MSBFIRST, SPI_MODE0));
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(((reg << 1) & 0x7E) | 0x80);
  byte val = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
  SPI.endTransaction();
  return val;
}

void rcSetBitMask(byte reg, byte mask) { rcWrite(reg, rcRead(reg) | mask); }
void rcClearBitMask(byte reg, byte mask) { rcWrite(reg, rcRead(reg) & (~mask)); }

void pcdInit() {
  rcWrite(CommandReg, PCD_RESET);
  delay(50);
  rcWrite(TModeReg, 0x8D);
  rcWrite(TPrescalerReg, 0x3E);
  rcWrite(TReloadRegL, 30);
  rcWrite(TReloadRegH, 0x00);
  rcWrite(TxASKReg, 0x40);
  rcWrite(ModeReg, 0x3D);
  byte v = rcRead(TxControlReg);
  if ((v & 0x03) != 0x03) rcWrite(TxControlReg, v | 0x03);
}

bool pcdCalculateCRC(byte *data, byte len, byte *result) {
  rcWrite(FIFOLevelReg, 0x80);
  for (byte i = 0; i < len; i++) rcWrite(FIFODataReg, data[i]);
  rcWrite(CommandReg, PCD_CALCCRC);
  unsigned long t = millis();
  while (true) {
    byte n = rcRead(DivIrqReg);
    if (n & 0x04) break;
    if (millis() - t > 50) return false;
  }
  result[0] = rcRead(CRCResultRegL);
  result[1] = rcRead(CRCResultRegM);
  return true;
}

bool pcdTransceive(byte *send, byte sendLen, byte *back, byte &backLen, unsigned int waitMS = 200) {
  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80);
  rcWrite(ComIrqReg, 0x7F);
  for (byte i = 0; i < sendLen; i++) rcWrite(FIFODataReg, send[i]);
  rcWrite(CommandReg, PCD_TRANSCEIVE);
  rcSetBitMask(BitFramingReg, 0x80);
  unsigned long start = millis();
  while (true) {
    byte irq = rcRead(ComIrqReg);
    if (irq & 0x20) break;
    if (irq & 0x01) return false;
    if (millis() - start > waitMS) return false;
  }
  rcClearBitMask(BitFramingReg, 0x80);
  if (rcRead(ErrorReg) & 0x13) return false;
  byte n = rcRead(FIFOLevelReg);
  if (n == 0 || n > MAX_LEN) return false;
  backLen = n;
  for (byte i = 0; i < n; i++) back[i] = rcRead(FIFODataReg);
  return true;
}

bool mifareRequest(byte *atqa, byte &atqaLen) {
  byte cmd = PICC_REQIDL;
  rcWrite(BitFramingReg, 0x07);
  return pcdTransceive(&cmd, 1, atqa, atqaLen, 100);
}

bool mifareAnticoll(byte *uid, byte &uidSize) {
  byte ser[2]; byte back[MAX_LEN]; byte backLen = 0;
  rcWrite(BitFramingReg, 0x00);
  ser[0] = 0x93; ser[1] = 0x20;
  if (!pcdTransceive(ser, 2, back, backLen, 100)) return false;
  byte bcc = back[0]^back[1]^back[2]^back[3];
  if (bcc != back[4]) return false;
  for(byte i=0; i<4; i++) uid[i] = back[i];
  uidSize = 4;
  return true;
}

bool mifareSelect(byte *uid4) {
  byte buf[9]; byte back[10]; byte backLen = 0;
  buf[0]=0x93; buf[1]=0x70;
  for(int i=0; i<4; i++) buf[2+i] = uid4[i];
  buf[6] = uid4[0]^uid4[1]^uid4[2]^uid4[3];
  byte crc[2];
  if (!pcdCalculateCRC(buf,7,crc)) return false;
  buf[7]=crc[0]; buf[8]=crc[1];
  if (!pcdTransceive(buf,9,back,backLen,100)) return false;
  return (backLen > 0);
}

bool mifareAuthenticate(byte keyType, byte blockAddr, byte *key, byte *uid4) {
  byte buff[12];
  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80);
  buff[0]=keyType; buff[1]=blockAddr;
  for (byte i=0;i<6;i++) buff[2+i]=key[i];
  for (byte i=0;i<4;i++) buff[8+i]=uid4[i];
  for (byte i=0;i<12;i++) rcWrite(FIFODataReg, buff[i]);
  rcWrite(CommandReg, PCD_AUTHENT);
  unsigned long t0 = millis();
  while (millis() - t0 < 100) {
    if (rcRead(Status2Reg) & 0x08) return true;
  }
  return false;
}

bool mifareRead(byte blockAddr, byte *buffer) {
  byte cmd[4]; byte back[MAX_LEN]; byte backLen = 0;
  cmd[0]=PICC_READ; cmd[1]=blockAddr;
  byte crc[2];
  if (!pcdCalculateCRC(cmd,2,crc)) return false;
  cmd[2]=crc[0]; cmd[3]=crc[1];
  if (!pcdTransceive(cmd,4,back,backLen,100)) return false;
  if (backLen < 16) return false;
  for (byte i=0;i<16;i++) buffer[i]=back[i];
  return true;
}

bool mifareWrite(byte blockAddr, byte *data16) {
  byte cmd[4], back[MAX_LEN], backLen=0, crc[2];
  cmd[0]=PICC_WRITE; cmd[1]=blockAddr;
  if (!pcdCalculateCRC(cmd,2,crc)) return false;
  cmd[2]=crc[0]; cmd[3]=crc[1];
  if (!pcdTransceive(cmd,4,back,backLen,100)) return false;
  byte pkt[18];
  for (byte i=0;i<16;i++) pkt[i]=data16[i];
  if (!pcdCalculateCRC(pkt,16,crc)) return false;
  pkt[16]=crc[0]; pkt[17]=crc[1];
  return pcdTransceive(pkt,18,back,backLen,100);
}

void mifareStopCrypto() {
  rcClearBitMask(Status2Reg, 0x08);
  rcWrite(CommandReg, PCD_IDLE);
}

void bipTek() {
  digitalWrite(BUZZER_PIN, HIGH); delay(120);
  digitalWrite(BUZZER_PIN, LOW);
}

void bipHata() {
  for(int i=0; i<3; i++) {
    digitalWrite(BUZZER_PIN, HIGH); delay(80);
    digitalWrite(BUZZER_PIN, LOW); delay(80);
  }
}

// --- KART OKU VE KREDİ DÜŞ (GÜNCELLENDİ) ---
// Global değişken olarak hangi sektörde olduğumuzu tutalım
int okumaAsamasi = 1; 



void kartOku() {
  byte atqa[2]; byte atqaLen=0;
  if (!mifareRequest(atqa, atqaLen)) return;
  if (!mifareAnticoll(uid, uidSize)) return;
  if (!mifareSelect(uid)) return;

  // Değişkenler her zaman hazır
  static byte b4[16], b5[16], b6[16], b8[16], b9[16], b10[16];

  if (okumaAsamasi == 1) {
    // --- 1. ADIM: SEKTÖR 1 ---
    if (mifareAuthenticate(PICC_AUTH_KEY_B, 4, defaultKey, uid)) {
      mifareRead(4, b4);
      mifareRead(5, b5);
      mifareRead(6, b6);
      //Serial.println(F("-> 1. Sektor Tamam. Simdi 2. Sektore Geciliyor..."));
      okumaAsamasi = 2; // Bir sonraki okumada 2. sektöre bak
    }
  } 
  else if (okumaAsamasi == 2) {
    // --- 2. ADIM: SEKTÖR 2 ---
    if (mifareAuthenticate(PICC_AUTH_KEY_B, 8, defaultKey, uid)) {
      mifareRead(8, b8);
      mifareRead(9, b9);
      mifareRead(10, b10);
      //Serial.println(F("-> 2. Sektor Tamam. Hesaplama Yapiliyor..."));
      // HESAPLA VE YAZA GİDİYORUZ
      hesapla_yaz(b4, b5, b8, b9, b10);
      // Veriler hazır, işlemi bitir ve 1. aşamaya dön
      //islemYap(b4, b5, b6, b8, b9, b10);
      okumaAsamasi = 1; 
      delay(3000); // İşlem bitti, kartı çekmesi için bekle
    } else {
      Serial.println(F("2. Sektor Auth Hatasi! (Tekrar Deneniyor)"));
    }
  }

  mifareStopCrypto(); // Her seferinde kartı temizce bırak
}

void islemYap(byte* b4, byte* b5, byte* b6, byte* b8, byte* b9, byte* b10) {
  
    
      
      Serial.println(F("\n--- ISLEM BASARILI (SEKTOR 2) ---"));
      Serial.print(F("ISIM : ")); Serial.write(b4, 16); Serial.println();
      Serial.print(F("FIRMA : ")); Serial.write(b5, 16); Serial.println();
      delay(2000);
     
  
}

void hesapla_yaz(byte* b4, byte* b5, byte* b8, byte* b9, byte* b10) {
  Serial.println(F("\n---- KREDI SISTEMI HESAPLAMA ----"));

  // 1. ADIM: ASCII VERİLERİ SAYISAL DEĞERLERE DÖNÜŞTÜR
  String krediStr = "";
  for(int i=0; i<16; i++) { if(b8[i] >= '0' && b8[i] <= '9') krediStr += (char)b8[i]; }
  long mevcutKredi = krediStr.toInt();

  String zamanStr = "";
  for(int i=0; i<16; i++) { if(b9[i] >= '0' && b9[i] <= '9') zamanStr += (char)b9[i]; }
  uint32_t kayitliZaman = strtoul(zamanStr.c_str(), NULL, 10);

  // KART TİPİ VE DURUMU AYRIŞTIRMA
  int mevcutDurum = (b10[0] - '0');  // b10'un 1. karakteri (Aktarma)
  int kartTipi    = (b10[1] - '0');  // b10'un 2. karakteri (0:Tam, 1:Öğr, 2-4:Ücretsiz)
  
  uint32_t suAnkiUnix = getUnixTime();
  
  // 3. ADIM: FİRMA KONTROLÜ
  char firmaBuf[17]; memcpy(firmaBuf, b5, 16); firmaBuf[16] = '\0';
  String firmaStr = String(firmaBuf);
  firmaStr.trim(); 
  
  if (!firmaStr.startsWith(OKUYUCU_KIMLIK)) {
    Serial.print(F("❌ GECERSIZ SEHIR! Kart: ")); Serial.print(firmaStr);
    bipHata(); 
    return;
  }
  
  // 4. ADIM: 90 DAKİKA VE ÜCRET HESABI
  long farkSaniye = suAnkiUnix - kayitliZaman;
  long farkDakika = farkSaniye / 60;
  if (farkSaniye < 0) farkDakika = 100; 

  int dusulecekKredi = 0;
  int yeniDurum = mevcutDurum;
  bool zamanGuncelle = false;

  Serial.print(F("Kart Tipi : ")); Serial.println(kartTipi);
  Serial.print(F("Mevcut Durum : ")); Serial.println(mevcutDurum);
  Serial.print(F("Fark Dakika : ")); Serial.println(farkDakika);

  // --- ÜCRET VE AKTARMA MANTIĞI ---
  if (kartTipi >= 2 && kartTipi <= 4) {
    // Şehit Yakını, Engelli, Özel Durum -> Daima Ücretsiz
    Serial.println(F("✨ OZEL KART: UCRETSIZ GECIS"));
    dusulecekKredi = 0;
    zamanGuncelle = false;
  } 
  else if (farkDakika <= 90) {
    // 90 DAKİKA İÇİNDEYSE (AKTARMA)
    if (mevcutDurum == 1) {
      Serial.println(F("🔄 2. AKTARMA VE SONRASI: UCRETSIZ"));
      dusulecekKredi = 0;
    } else {
      // İLK AKTARMA
      if (kartTipi == 1) { // Öğrenci
        Serial.println(F("🎓 OGRENCI ILK AKTARMA: 2 KREDI"));
        dusulecekKredi = 2;
      } else { // Tam (kartTipi == 0)
        Serial.println(F("🎫 TAM ILK AKTARMA: 5 KREDI"));
        dusulecekKredi = 5;
      }
      yeniDurum = 1;
    }
  } 
  else {
    // 90 DAKİKA DOLMUŞ VEYA İLK BİNİŞ
    if (kartTipi == 1) { // Öğrenci
      Serial.println(F("🎓 OGRENCI ILK BINIS: 15 KREDI"));
      dusulecekKredi = 15;
    } else { // Tam (kartTipi == 0)
      Serial.println(F("🎫 TAM ILK BINIS: 30 KREDI"));
      dusulecekKredi = 30;
    }
    yeniDurum = 0;
    zamanGuncelle = true;
  }

  // 5. ADIM: KARAR VE YAZMA KONTROLÜ
  if (dusulecekKredi == 0) {
    bipTek();
    Serial.println(F("✅ UCRETSIZ GECIS ONAYLANDI (YAZMA YAPILMADI)"));
    // Ücretsiz olsa da log tutmak için log kısmına düşüyoruz ama karta yazmıyoruz.
  } else {
    if (mevcutKredi < dusulecekKredi) {
      bipHata();
      Serial.println(F("❌ YETERSIZ BAKIYE"));
      return;
    }

    // 6. ADIM: KART GÜNCELLEME (SADECE ÜCRETLİ DURUMLARDA)
    long yeniKredi = mevcutKredi - dusulecekKredi;
    byte yeniB8[16], yeniB9[16], yeniB10[16];
    memcpy(yeniB8, b8, 16); memcpy(yeniB9, b9, 16); memcpy(yeniB10, b10, 16);

    memset(yeniB8, 0x20, 16);
    String(yeniKredi).getBytes(yeniB8, 16);

    yeniB10[0] = yeniDurum + '0';
    // yeniB10[1] (kartTipi) zaten kartta var, değiştirmiyoruz.

    bool yazmaBasarili = true;
    yazmaBasarili &= mifareWrite(8, yeniB8);
    yazmaBasarili &= mifareWrite(10, yeniB10);

    if (zamanGuncelle) {
      memset(yeniB9, 0x20, 16);
      String(suAnkiUnix).getBytes(yeniB9, 11);
      yazmaBasarili &= mifareWrite(9, yeniB9);
      Serial.println(F("📅 Zaman Damgasi Guncellendi."));
    }

    if (yazmaBasarili) {
      bipTek();
      Serial.print(F("✅ ISLEM BASARILI. Dusulen: ")); Serial.println(dusulecekKredi);
    } else {
      Serial.println(F("❌ YAZMA HATASI!"));
      return;
    }
  }

  // 7. ADIM: LOGLAMA (Hem ücretli hem ücretsiz geçişler için)
  long sonKredi = (dusulecekKredi == 0) ? mevcutKredi : (mevcutKredi - dusulecekKredi);
  
  /*LOG yeniLog;
  yeniLog.time = suAnkiUnix;
  yeniLog.uidSize1 = uidSize;
  memset(yeniLog.uid, 0, 7);
  memcpy(yeniLog.uid, uid, uidSize);
  yeniLog.gate = 5;// burada okuyucunun kapı numarası ya da okuyucu numarası olarak yazıyor. yetkili sistem olsa gerçek kapı no olacaktı.
  yeniLog.kredi = (uint32_t)sonKredi;
  // Result kısmına hem tipi hem durumu kaydedebilirsiniz (Örn: kartTipi*10 + yeniDurum)
  yeniLog.result = (uint16_t)dusulecekKredi; 
  yeniLog.reserved = 0;

  logGonder(yeniLog);*/

  LOG yeniLog;
    yeniLog.time = suAnkiUnix;
    yeniLog.uidSize1 = uidSize;
    
    memset(yeniLog.uid, 0, 7);
    memcpy(yeniLog.uid, uid, uidSize);
    
    yeniLog.gate = 5; 
    yeniLog.kredi = (uint32_t)sonKredi; // Kartta kalan bakiye (4 byte)

    // --- HATALI KISMIN DÜZELTİLMESİ (BİT PAKETLEME) ---
    // 2. byte'a (Üst byte) durum ve kart tipini sıkıştırıyoruz. 
    // Örn: yeniDurum (0 veya 1) ve kartTipi (0-4 arası). 
    // Bilgisayarda kolayca ayırmak için: (kartTipi * 10) + yeniDurum formülünü kullanabiliriz.
    uint8_t durumPaketi = (kartTipi * 10) + yeniDurum; 

    // result değişkeninin alt byte'ına düşülen krediyi, üst byte'ına ise durum paketini koyuyoruz
    yeniLog.result = (uint16_t)((durumPaketi << 8) | (dusulecekKredi & 0xFF));
    
    yeniLog.reserved = 0; // Hizalama byte'ı

    logGonder(yeniLog);


  
}


// --- RTC ---
uint32_t getUnixTime() {
  Wire.beginTransmission(0x68); Wire.write(0x00); Wire.endTransmission();
  Wire.requestFrom(0x68, 7);
  if (Wire.available() < 7) return 0;
  uint8_t s = Wire.read(); uint8_t m = Wire.read(); uint8_t h = Wire.read();
  Wire.read(); // day of week
  uint8_t d = Wire.read(); uint8_t mo = Wire.read(); uint8_t y = Wire.read();

  auto bcd2dec = [](uint8_t val) { return (val >> 4) * 10 + (val & 0x0F); };
  int second = bcd2dec(s); int minute = bcd2dec(m); int hour = bcd2dec(h);
  int day = bcd2dec(d); int month = bcd2dec(mo); int year = bcd2dec(y) + 2000;

  const uint8_t dim[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  uint32_t days = 0;
  for (int i = 1970; i < year; i++) { days += 365; if (i % 4 == 0) days++; }
  for (int i = 1; i < month; i++) { days += dim[i - 1]; if (i == 2 && year % 4 == 0) days++; }
  days += day - 1;
  return days * 86400UL + hour * 3600UL + minute * 60UL + second;
}

// --- SETUP & LOOP ---
void setup() {
  Serial.begin(115200);
  BTSerial.begin(BT_BAUD);
  Wire.begin();
  SPI.begin();
  //EEPROM.put(0, (uint16_t)0); // Pointer'ı sıfıra çek (Sadece 1 kere çalıştırılacak)
  pinMode(SS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(RST_PIN, HIGH);
  pcdInit();

  Serial.print(F("MFRC522 Version: 0x"));
  Serial.println(rcRead(VersionReg), HEX);
  Serial.println(F("Kredili Sistem Hazir."));
}

void loop() {
  kartOku();
  delay(10);
  
  }
