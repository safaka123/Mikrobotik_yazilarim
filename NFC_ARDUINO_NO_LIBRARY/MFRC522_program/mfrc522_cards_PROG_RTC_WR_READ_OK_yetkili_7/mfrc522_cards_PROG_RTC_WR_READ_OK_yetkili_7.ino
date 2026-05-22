// Program hem kart yazma(admin buton) hem de okuma OK 
// Eproma log yazma OK, Seri port/Bluetooth üzerinden gönderme OK
// SPI hızı ve senkronizasyon ayarları yapıldı.





#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>

#define SS_PIN   10
#define RST_PIN  9
#define ADMIN_BUTTON 2
#define BUZZER_PIN  6

// Hatalı kart değişkenleri
int hataliDenemeSayisi = 0;
bool sistemKilitli = false;
unsigned long kilitBaslangicZamani = 0;
const unsigned long KILIT_SURESI = 2000; // 2 Dakika
const int MAKS_HATALI_DENEME = 15;
unsigned long RTCunixTime = 0;

// Kapı Tanımı

const uint8_t aktifKapiNo = 2; 

// Kopya kart değişkenleri
byte sonUID[4];
byte sonUIDLen = 0;
unsigned long sonOkumaZamani = 0;
byte ardArdaAyniOkumaSayisi = 0;
bool kopyaKartTespitEdildi = false;
const unsigned long KOPYA_ESIK_SURE = 3000;
const byte KOPYA_TETIK_SAYISI = 3;
byte Nuid = 0;
byte uid[7];
byte uidSize = 4;

// Bluetooth
SoftwareSerial BTSerial(7, 8); 
const unsigned long BT_BAUD = 9600;

// RC522 Register Tanımları
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

#define MAX_LEN  18
#define RES_RED            0
#define RES_OK             1
#define RES_YETKISIZ       2
#define RES_HATALI_KART    3

// EEPROM LOG Ayarları
#define LOGSIZE 16
#define EEPROM_START 2
#define EEPROM_SIZE 1024
#define MAXLOG ((EEPROM_SIZE-EEPROM_START)/LOGSIZE)
#define ACK_TIMEOUT 300

struct LOG {
  uint32_t time;
  uint8_t uidSize1;
  uint8_t uid[7];
  uint8_t gate;
  uint16_t kredi;
  uint8_t result;
};

// Admin Modları
enum SistemModu { NORMAL_MOD, AD_VERI_HAZIR, AD_KART_YAZMA };
SistemModu aktifMod = NORMAL_MOD;
unsigned long AD_sonIslemZamani = 0;
const unsigned long AD_timeout = 120000;
byte AD_bekleyenBlok[3][16];
byte defaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// --- RC522 Low Level ---
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

// --- Yardımcı Fonksiyonlar ---
void printHex(byte *buffer, byte len) {
  for (byte i=0;i<len;i++) {
    if (buffer[i] < 0x10) Serial.print('0');
    Serial.print(buffer[i], HEX); Serial.print(' ');
  }
  Serial.println();
}

void bipTek() {
  digitalWrite(BUZZER_PIN, HIGH); delay(120);
  digitalWrite(BUZZER_PIN, LOW); Serial.println(F("BIP"));
}

void HataliDenemeArtir() {
  hataliDenemeSayisi++;
  Serial.print(F("HATALI DENEME: ")); Serial.println(hataliDenemeSayisi);
  if (hataliDenemeSayisi >= 5) {
    sistemKilitli = true;
    kilitBaslangicZamani = millis();
    Serial.println(F("❌ SISTEM KILITLENDI"));
    kopyaKartTespitEdildi = false;
  }
}

// --- OKUMA FONKSIYONU (GÜNCELLENDİ) ---
void kartOku() {
  byte atqa[2]; byte atqaLen=0;
  if (!mifareRequest(atqa, atqaLen)) return; 
  
  if (!mifareAnticoll(uid, uidSize)) { HataliDenemeArtir(); return; }
  if (!mifareSelect(uid)) { HataliDenemeArtir(); return; }

  // Sektör 1 için bir kez Auth yapıp 3 bloğu hızla okuyoruz
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, 4, defaultKey, uid)) {
    mifareStopCrypto(); HataliDenemeArtir(); return;
  }

  byte b4[16], b5[16], b6[16];
  bool r4 = mifareRead(4, b4);
  bool r5 = mifareRead(5, b5);
  bool r6 = mifareRead(6, b6);
  mifareStopCrypto(); // Kartla iş bitti
  
  if(!r4 || !r5 || !r6) { HataliDenemeArtir(); return; }

  // Veri işleme
  char isimBuf[17]; memcpy(isimBuf, b4, 16); isimBuf[16]=0;
  String kartIsmi = String(isimBuf); kartIsmi.trim();
  char firmaBuf[17]; memcpy(firmaBuf, b5, 16); firmaBuf[16]=0;
  String firmaAdi = String(firmaBuf); firmaAdi.trim();
  uint16_t kartBitmask = ((uint16_t)b6[1] << 8) | (uint16_t)b6[0];

  Serial.print(F("Okunan ISIM: ")); Serial.println(kartIsmi);
  Serial.print(F("Okunan FIRMA: ")); Serial.println(firmaAdi);
  Serial.print(F("Okunan BITMASK: ")); Serial.println(kartBitmask);

  KopyaKartKontrolFonksiyonu(uid, 4);
  //kopyaKartTespitEdildi=false;
  if (!kopyaKartTespitEdildi && !sistemKilitli) {
    yetkiKontrolVeKayitUret(uid, kartIsmi, firmaAdi, aktifKapiNo, kartBitmask);
  }
  delay(2000);
}

// --- ADMIN FONKSIYONLARI ---
void prepareBlock(byte *dest, String s) {
  s.trim();
  if (s.length() > 16) s = s.substring(0, 16);
  while (s.length() < 16) s += ' ';
  for (byte i=0; i<16; i++) dest[i] = (byte)s[i];
}

void createBitmask(byte *dest, String doorList) {
  unsigned int mask = 0; int start = 0;
  while (true) {
    int dot = doorList.indexOf('.', start);
    String doorStr = (dot == -1) ? doorList.substring(start) : doorList.substring(start, dot);
    int doorNo = doorStr.toInt();
    if (doorNo >= 1 && doorNo <= 16) mask |= (1 << (doorNo - 1));
    if (dot == -1) break;
    start = dot + 1;
  }
  dest[0] = mask & 0xFF;
  dest[1] = (mask >> 8) & 0xFF;
  for (int i=2; i<16; i++) dest[i] = ' ';
}

void AD_VeriGeldi(String s) {
  s.trim(); Serial.println("AD: Gelen: " + s);
  int p1 = s.indexOf(','); int p2 = s.indexOf(',', p1 + 1);
  if (p1 < 0 || p2 < 0) return;
  prepareBlock(AD_bekleyenBlok[0], s.substring(0, p1));
  prepareBlock(AD_bekleyenBlok[1], s.substring(p1 + 1, p2));
  createBitmask(AD_bekleyenBlok[2], s.substring(p2 + 1));
  aktifMod = AD_VERI_HAZIR;
  AD_sonIslemZamani = millis();
}

void AD_KartProgramla() {
  byte atqa[2], atLen=0;
  if (!mifareRequest(atqa, atLen)) return;
  if (!mifareAnticoll(uid, uidSize)) return;
  if (!mifareSelect(uid)) return;

  if (mifareAuthenticate(PICC_AUTH_KEY_B, 4, defaultKey, uid)) {
    for (byte i=0; i<3; i++) mifareWrite(4+i, AD_bekleyenBlok[i]);
    Serial.println(F("AD: Yazma OK."));
    bipTek();
  }
  mifareStopCrypto();
  aktifMod = AD_VERI_HAZIR;
}

// --- LOG & YETKI ---
void logGonder(LOG &log) {
  uint16_t pointer;
  if (Nuid == 1) return;
  EEPROM.get(0, pointer);
  if(pointer >= MAXLOG) pointer = 0;
  BTSerial.write(0xAA);
  BTSerial.write((uint8_t*)&log, sizeof(LOG));
  // Basitlik için ACK bekleme kısmı orijinalde olduğu gibi kalabilir 
  // veya EEPROM'a direkt yedeklenebilir.
  int addr = EEPROM_START + (pointer * LOGSIZE);
  EEPROM.put(addr, log);
  pointer++;
  EEPROM.put(0, pointer);
}

void yetkiKontrolVeKayitUret(byte *uid, const String &kartKimligi, const String &firmaAdi, uint8_t kapiNo, uint16_t kartYetkisi) {
  bool yetkili = (kartYetkisi & (1 << (kapiNo - 1))) != 0;
  rtcZamanPlusDakika();
  
  if (yetkili) {
    Serial.println(F("✅ ONAYLANDI")); bipTek();
    
    hataliDenemeSayisi = 0;
    LOG yeniLog = {RTCunixTime, 4, {0}, 2, 0, RES_OK};
    memcpy(yeniLog.uid, uid, 4);
    logGonder(yeniLog);
  } else {
    Serial.println(F("❌ YETKISIZ")); HataliDenemeArtir();
    LOG yeniLog = {RTCunixTime, 4, {0}, 2, 0, RES_YETKISIZ};
    memcpy(yeniLog.uid, uid, 4);
    logGonder(yeniLog);
  }
}

// --- RTC ---
void rtcZamanPlusDakika() {
  Wire.beginTransmission(0x68); Wire.write(0x00); Wire.endTransmission();
  Wire.requestFrom(0x68, 7);
  Wire.read(); // sn
  uint8_t m = Wire.read(); uint8_t h = Wire.read(); Wire.read();
  uint8_t d = Wire.read(); uint8_t mo = Wire.read(); uint8_t y = Wire.read();
  m = (m>>4)*10 + (m&0x0F); h = (h>>4)*10 + (h&0x0F);
  d = (d>>4)*10 + (d&0x0F); mo = (mo>>4)*10 + (mo&0x0F);
  int yy = (y>>4)*10 + (y&0x0F) + 2000;
  
  const uint8_t dim[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  unsigned long days = 0;
  for(int i=1970; i<yy; i++) { days += 365; if(i%4==0) days++; }
  for(int i=1; i<mo; i++) { days += dim[i-1]; if(i==2 && yy%4==0) days++; }
  days += d - 1;
  RTCunixTime = days*86400UL + h*3600UL + m*60UL;
}

// --- LOOP & SETUP ---
void setup() {
  Serial.begin(115200); BTSerial.begin(9600); Wire.begin(); SPI.begin();
  pinMode(SS_PIN, OUTPUT); pinMode(RST_PIN, OUTPUT);
  pinMode(ADMIN_BUTTON, INPUT_PULLUP); pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH); pcdInit();
  Serial.println(F("Sistem Hazir."));
}

String btBuffer = "";
void loop() {
  
  if (sistemKilitli) {
    if (millis() - kilitBaslangicZamani >= KILIT_SURESI) {
      sistemKilitli = false; hataliDenemeSayisi = 0;
      Serial.println(F("SISTEM OTOMATIK ACILDI ✅"));
      kopyaKartTespitEdildi = false;
    } else return;
  }

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') { AD_VeriGeldi(btBuffer); btBuffer = ""; }
    else if (c != '\r') btBuffer += c;
  }

  // Admin Buton Basit Kontrol
  if (digitalRead(ADMIN_BUTTON) == LOW) {
    delay(50); // debounce
    if (aktifMod == AD_VERI_HAZIR) aktifMod = AD_KART_YAZMA;
  }

  if (aktifMod == NORMAL_MOD) kartOku();
  else if (aktifMod == AD_KART_YAZMA) AD_KartProgramla();
  
  if (aktifMod != NORMAL_MOD && millis() - AD_sonIslemZamani > AD_timeout) aktifMod = NORMAL_MOD;
}

void KopyaKartKontrolFonksiyonu(byte *uid, byte uidLen) {
  unsigned long simdi = millis();
  if (sonUIDLen == uidLen && memcmp(uid, sonUID, uidLen) == 0) {
    if (simdi - sonOkumaZamani < KOPYA_ESIK_SURE) ardArdaAyniOkumaSayisi++;
    Nuid = 1;
  } else {
    memcpy(sonUID, uid, uidLen); sonUIDLen = uidLen; ardArdaAyniOkumaSayisi = 1; Nuid = 0;
  }
  sonOkumaZamani = simdi;
  if (ardArdaAyniOkumaSayisi >= KOPYA_TETIK_SAYISI) {
    Serial.println(" kopya kart");
    kopyaKartTespitEdildi = true; HataliDenemeArtir();
  }
}
