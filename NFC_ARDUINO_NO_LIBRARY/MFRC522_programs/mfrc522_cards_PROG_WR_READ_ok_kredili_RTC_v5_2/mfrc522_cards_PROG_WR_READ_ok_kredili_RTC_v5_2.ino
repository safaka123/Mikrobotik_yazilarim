//******* BU VERSİYON 5_2hatalar düzeltildi
// 5_3 te üzerine LOG sistemi kurulacak şekilde düzenlenecek. 


// kullanılmayan değişkenler silinecek


//*** dikkat gerçek blok3 kullanılmayuacak ve blok 7 kullanılmayacak bunlar 
// *** kart parametreleridir bozulursa kart okuma hatası verir. programda bu engellenmiştir
// ***  fakat programda başka bloklar kullanacaksanız onlarında kendine ait trailer şifre blokları vardır bundan dolayı çok dikkatli olun. 

//******************* ad verial kısmında ve admin yazma kısmında 8 9 10 spare yazıyor ama burada bilgiyi 4 5 6 8 10 blok bilgileri 
// **************** seri port üzerinden gelecek virgülle ayrılmış gelecek ve burada bloklara ayrılacak 4 5 6 blok ayırma tamam 
// ************* 8 9 10 spare yazıyor virgüllü gelen veriden dolum bilgisi alınacak spare yerine onlar yazılacak. 
// ************** ascii olarak yazılacak 16 byte kontrol yapılacak. 


// Tam Program: RC522 mini-driver + SoftSerial (HC-05/06) + Admin programlama (AD_ prefix)
// SPI: 11(MOSI),12(MISO),13(SCK)
// SS=10, RST=9
// SoftwareSerial: RX=7 (to BT TX), TX=8 (to BT RX)

#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SS_PIN   10
#define RST_PIN  9
#define BUZZER_PIN  6

// *********** hatalı kart değişkenleri **********
int hataliDenemeSayisi = 0;
bool sistemKilitli = false;
unsigned long kilitBaslangicZamani = 0;

const unsigned long KILIT_SURESI = 1000; // 2 dakika = 120.000 ms
const int MAKS_HATALI_DENEME = 15;

// Hangi kapı bu okuyucuya bağlı? (0..15)
const uint8_t aktifKapiNo = 2;  // test için 

// ************* kopya kart değişkenleri ***************
byte sonUID[4];
byte sonUIDUzunluk = 0;
byte sonUIDLen = 0;           // sonUID'nin uzunluğu (genelde 4)
unsigned long sonOkumaZamani = 0;
byte ardArdaAyniOkumaSayisi = 0;
bool kopyaKartTespitEdildi = false;

const unsigned long KOPYA_ESIK_SURE = 3000; // ms (0.8 saniye)
bool kopyaSuphesi = false;
const byte KOPYA_TETIK_SAYISI = 3;

unsigned long RTCunixTime=0;
//String sistemZamanDamgasi = "";
//bool zamanHazir = false;
//uint32_t baslangicDakika = 0;
//unsigned long zamanBaslangicMillis = 0;
//String zamanTarih;   // YYYYMMDD

// son uid kontrol et aynı kart ise ret et. 
const byte uidSize = 4;
byte esonUID[uidSize] = {0,0,0,0};  // Son başarılı kart UID'si
bool sonUIDVar = false;       // Henüz kart yok



// Bluetooth (SoftSerial)
SoftwareSerial BTSerial(7, 8); // RX, TX (HC-05 TX -> 7, HC-05 RX <- 8)
const unsigned long BT_BAUD = 9600;

// RC522 register defines (kısaltılmış)
#define CommandReg      0x01
#define ComIEnReg       0x02
#define DivIEnReg       0x03
#define ComIrqReg       0x04
#define DivIrqReg       0x05
#define ErrorReg        0x06
#define FIFODataReg     0x09
#define FIFOLevelReg    0x0A
#define ControlReg      0x0C
#define BitFramingReg   0x0D
#define ModeReg         0x11
#define TxModeReg       0x12
#define RxModeReg       0x13
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
#define PICC_ANTICOLL   0x93
#define PICC_SELECTTAG  0x93
#define PICC_AUTH_KEY_A 0x60
#define PICC_AUTH_KEY_B 0x61
#define PICC_READ       0x30
#define PICC_WRITE      0xA0

#define MAX_LEN  18

// ADMIN state machine
enum SistemModu { NORMAL_MOD, AD_VERI_HAZIR, AD_KART_YAZMA };
SistemModu aktifMod = NORMAL_MOD;

//unsigned long AD_sonIslemZamani = 0;
//const unsigned long AD_timeout = 120000; // 2 dakika


// default key
byte defaultKey[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
//byte defaultKey[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

// Forward RC522 low-level
void rcWrite(byte reg, byte val) {
  digitalWrite(SS_PIN, LOW);
  SPI.transfer((reg << 1) & 0x7E);
  SPI.transfer(val);
  digitalWrite(SS_PIN, HIGH);
}
byte rcRead(byte reg) {
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(((reg << 1) & 0x7E) | 0x80);
  byte val = SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
  return val;
}
void rcSetBitMask(byte reg, byte mask) {
  rcWrite(reg, rcRead(reg) | mask);
}
void rcClearBitMask(byte reg, byte mask) {
  rcWrite(reg, rcRead(reg) & (~mask));
}

// PCD init
void pcdInit() {
  rcWrite(CommandReg, PCD_RESET);
  delay(50);

  rcWrite(TModeReg, 0x8D);
  rcWrite(TPrescalerReg, 0x3E);
  rcWrite(TReloadRegL, 30);
  rcWrite(TReloadRegH, 0x00);
  rcWrite(TxASKReg, 0x40);
  rcWrite(ModeReg, 0x3D);
  rcWrite(0x26, 0x70); // RFCfgReg

  byte v = rcRead(TxControlReg);
  if ((v & 0x03) != 0x03) rcWrite(TxControlReg, v | 0x03);

  // Not: TxMode/RxMode CRC global açmıyoruz (pcdCalculateCRC kullanacağız)
}

// CRC hesaplama (chip)
bool pcdCalculateCRC(byte *data, byte len, byte *result) {
  rcWrite(FIFOLevelReg, 0x80); // flush
  for (byte i = 0; i < len; i++) rcWrite(FIFODataReg, data[i]);
  rcWrite(CommandReg, PCD_CALCCRC);

  unsigned long t = millis();
  while (true) {
    byte n = rcRead(DivIrqReg);
    if (n & 0x04) break; // CRC ready
    if (millis() - t > 50) return false;
  }
  result[0] = rcRead(CRCResultRegL);
  result[1] = rcRead(CRCResultRegM);
  return true;
}

// Transceive genel (irq tabanlı)
bool pcdTransceive(byte *send, byte sendLen, byte *back, byte &backLen, unsigned int waitMS = 200) {
  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80); // flush
  rcWrite(ComIrqReg, 0x7F);     // clear all

  for (byte i = 0; i < sendLen; i++) rcWrite(FIFODataReg, send[i]);

  rcWrite(CommandReg, PCD_TRANSCEIVE);
  rcSetBitMask(BitFramingReg, 0x80); // StartSend

  unsigned long start = millis();
  while (true) {
    byte irq = rcRead(ComIrqReg);
    if (irq & 0x20) break;   // RxIRq
    if (irq & 0x01) return false; // Timer
    if (millis() - start > waitMS) return false;
  }

  rcClearBitMask(BitFramingReg, 0x80);

  byte error = rcRead(ErrorReg);
  if (error & 0x13) return false;

  byte n = rcRead(FIFOLevelReg);
  if (n == 0) return false;
  if (n > MAX_LEN) n = MAX_LEN;
  backLen = n;
  for (byte i = 0; i < n; i++) back[i] = rcRead(FIFODataReg);
  return true;
}

// REQA
bool mifareRequest(byte *atqa, byte &atqaLen) {
  byte cmd = PICC_REQIDL;
  rcWrite(BitFramingReg, 0x07);  // 7 bit
  delay(300);
  return pcdTransceive(&cmd, 1, atqa, atqaLen, 200);
}

// Anticoll (4 byte + BCC)
bool mifareAnticoll(byte *uid4) {
  byte ser[2];
  byte back[MAX_LEN];
  byte backLen = 0;
  rcWrite(BitFramingReg, 0x00);
  ser[0] = 0x93; ser[1] = 0x20;
  if (!pcdTransceive(ser, 2, back, backLen, 200)) return false;
  if (backLen != 5) return false;
  byte bcc = back[0]^back[1]^back[2]^back[3];
  if (bcc != back[4]) return false;
  for (byte i=0;i<4;i++) uid4[i]=back[i];
  return true;
}

// Select (3 byte SAK+CRC veya 1 byte)
bool mifareSelect(byte *uid4) {
  rcWrite(BitFramingReg, 0x00);
  byte buf[9];
  byte back[10];
  byte backLen = 0;
  buf[0]=0x93; buf[1]=0x70;
  buf[2]=uid4[0]; buf[3]=uid4[1]; buf[4]=uid4[2]; buf[5]=uid4[3];
  buf[6]=uid4[0]^uid4[1]^uid4[2]^uid4[3];
  byte crc[2];
  if (!pcdCalculateCRC(buf,7,crc)) return false;
  buf[7]=crc[0]; buf[8]=crc[1];
  if (!pcdTransceive(buf,9,back,backLen,200)) return false;
  if (backLen < 1) return false;
  byte sak = back[0];
  Serial.print("SAK: "); Serial.println(sak, HEX);
  // accept typical MIFARE1K 0x08
  return true;
}

// Authenticate (checks Status2Reg MFCrypto1On)
bool mifareAuthenticate(byte keyType, byte blockAddr, byte *key, byte *uid4) {
  byte buff[12];
  byte back[MAX_LEN]; byte backLen=0;
  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80);
  buff[0]=keyType; buff[1]=blockAddr;
  for (byte i=0;i<6;i++) buff[2+i]=key[i];
  for (byte i=0;i<4;i++) buff[8+i]=uid4[i];
  for (byte i=0;i<12;i++) rcWrite(FIFODataReg, buff[i]);
  rcWrite(CommandReg, PCD_AUTHENT);
  unsigned long t0 = millis();
  while (true) {
    byte st2 = rcRead(Status2Reg);
    if (st2 & 0x08) return true;
    if (millis() - t0 > 200) break;
  }
  return false;
}

// Read block (uses pcdCalculateCRC + pcdTransceive)
bool mifareRead(byte blockAddr, byte *buffer) {
  byte cmd[4];
  byte back[MAX_LEN];
  byte backLen = 0;
  cmd[0]=PICC_READ; cmd[1]=blockAddr;
  byte crc[2];
  if (!pcdCalculateCRC(cmd,2,crc)) return false;
  cmd[2]=crc[0]; cmd[3]=crc[1];
  if (!pcdTransceive(cmd,4,back,backLen,300)) return false;
  if (backLen < 16) return false;
  for (byte i=0;i<16;i++) buffer[i]=back[i];
  return true;
}

// Write block (two-step)
bool mifareWrite(byte blockAddr, byte *data16) {
  byte cmd[4], back[MAX_LEN]; byte backLen=0;
  cmd[0]=PICC_WRITE; cmd[1]=blockAddr;
  byte crc[2];
  if (!pcdCalculateCRC(cmd,2,crc)) return false;
  cmd[2]=crc[0]; cmd[3]=crc[1];
  if (!pcdTransceive(cmd,4,back,backLen,300)) return false;
  if (backLen==0) return false;
  // prepare 16 bytes packet + crc
  byte pkt[18];
  for (byte i=0;i<16;i++) pkt[i]=data16[i];
  if (!pcdCalculateCRC(pkt,16,crc)) return false;
  pkt[16]=crc[0]; pkt[17]=crc[1];
  if (!pcdTransceive(pkt,18,back,backLen,300)) return false;
  if (backLen==0) return false;
  return true;
}

void mifareStopCrypto() {
  rcClearBitMask(Status2Reg, 0x08);
  rcWrite(CommandReg, PCD_IDLE);
}

// Helper
void printHex(byte *buffer, byte len) {
  for (byte i=0;i<len;i++) {
    if (buffer[i] < 0x10) Serial.print('0');
    Serial.print(buffer[i], HEX);
    Serial.print(' ');
  }
  Serial.println();
}



// ---------------- NORMAL USER FUNCTIONS ----------------

void kartOku() {
  byte atqa[2]; byte atqaLen=0;
  if (!mifareRequest(atqa, atqaLen)) { delay(200); return; }
  Serial.print("ATQA: "); printHex(atqa, atqaLen);
  byte uid[4];
  if (!mifareAnticoll(uid)) { Serial.println(F("Anticoll FAIL")); delay(200); HataliDenemeArtir(); return; }
  Serial.print("UID: "); printHex(uid,4);
  

  if (!mifareSelect(uid)) { Serial.println(F("Select FAIL")); delay(200); HataliDenemeArtir(); return; }
  Serial.println(F("Select OK"));

  Serial.print("son UID: "); printHex(esonUID,4);
  
  if (ayniKartMi(uid, uidSize)) {
  Serial.println(F("AYNI KART! Lutfen tekrar gecirmeyin."));
  // Burada bip veya hata sesi çalabiliriz
  // Kredi düşme fonksiyonuna girme
  return;  // Döngüyü kır veya atla
  }
  delay(1000);

  // --- Burada artık SEKTOR 1'in bloklarını okuyoruz: 4,5,6 ---
  byte buf[16];

  // Auth + Read Block 4 (isim)
  byte block = 4;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL (block 4)")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 4")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }
  char isimBuf[17]; memcpy(isimBuf, buf, 16); isimBuf[16]=0;
  String kartIsmi = String(isimBuf);
  //bipTek();

  // Auth + Read Block 5 (firma)
  block = 5;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL (block 5)")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 5")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }
  char firmaBuf[17]; memcpy(firmaBuf, buf, 16); firmaBuf[16]=0;
  String firmaAdi = String(firmaBuf);

  // Auth + Read Block 6 (bitmask vb.)
  block = 6;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL (block 6)")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 6")); mifareStopCrypto(); delay(200); HataliDenemeArtir(); return;
  }

  // Bitmask -> biz MSB: buf[0], LSB: buf[1] şeklinde bekliyoruz
  uint16_t kartBitmask = ((uint16_t)buf[0] << 8) | (uint16_t)buf[1];

    // -------- BLOK 8 : KREDI --------
  block = 8;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL block 8")); mifareStopCrypto(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 8")); mifareStopCrypto(); return;
  }
  char krediBuf[17];
  memcpy(krediBuf, buf, 16);
  krediBuf[16] = 0;

  String krediStr = String(krediBuf);
  krediStr.trim();

  int kredi = krediStr.toInt();

  Serial.print(F("KREDI: "));
  Serial.println(kredi);
  
  //int kredi = ((uint16_t)buf[0] << 8) | buf[1];

  // -------- BLOK 9 : SON SAAT --------
  block = 9;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL block 9")); mifareStopCrypto(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 9")); mifareStopCrypto(); return;
  }

  // ilk 10 byte unix zaman
  char unixBuf[11];
  memcpy(unixBuf, buf, 10);
  unixBuf[10] = 0;

  // sayıya çevir
  unsigned long kayitSaat = strtoul(unixBuf, NULL, 10);

  Serial.print("Kart Unix Zaman: ");
  Serial.println(kayitSaat);
    
  //uint16_t kayitSaat = ((uint16_t)buf[0] << 8) | buf[1];

  // -------- BLOK 10 : DURUM --------
  block = 10;
  if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
    Serial.println(F("Auth FAIL block 10")); mifareStopCrypto(); return;
  }
  if (!mifareRead(block, buf)) {
    Serial.println(F("Read FAIL block 10")); mifareStopCrypto(); return;
  }
  char durumChar = buf[0];
  byte durum = durumChar - '0';
  
  
  
  
  //byte durum = buf[0];

  //Serial.print(F("KREDI: "));
  //Serial.println(kredi);

  //Serial.print(F("SON SAAT: "));
  //Serial.println(kayitSaat);

  Serial.print(F("DURUM: "));
  Serial.println(durum);

  // Log ve yetki kontrolü
  // UID string oluştur
  String uidString = "";
  for (byte i = 0; i < 4; i++) {
    if (uid[i] < 0x10) uidString += "0";
    uidString += String(uid[i], HEX);
  }
  uidString.toUpperCase();

  Serial.print(F("Okunan ISIM: ")); Serial.println(kartIsmi);
  Serial.print(F("Okunan FIRMA: ")); Serial.println(firmaAdi);

  // Kopya kart kontrol (aynı uid ardışık okuma vs.)
  //KopyaKartKontrolFonksiyonu(uid, 4);

  // Eğer kopya değil ve sistem kilitli değilse yetki kontrolüne gönder
  //if (!kopyaKartTespitEdildi && !sistemKilitli) {
  //  yetkiKontrolVeKayitUret(uidString, kartIsmi, firmaAdi, aktifKapiNo, kartBitmask);
  //}


  krediliSistem(uid, kartIsmi, firmaAdi, kredi, kayitSaat, durum);
  
  mifareStopCrypto();
  
  delay(2000);
}

// ****************  KREDİLİ SİSTEM HESAPLAMA **************************

bool ayniKartMi(byte *uid, byte uidSize)
{
  if (!sonUIDVar) return false;

  for (byte i=0; i<uidSize; i++)
  {
    if (uid[i] != esonUID[i]) return false;
  }
  return true; // tüm byte’lar aynı ise aynı kart
}

//***************  KREDİLİ SİSTEM HESAPLAMA ************************

void krediliSistem(byte *uid, String isim, String firma, int kredi, unsigned long kayitSaat, byte durum) {

  Serial.println(F("---- KREDI SISTEMI ----"));

  if (durum == 5) {
    Serial.println(F("UCRETSIZ GECIS OZEL DURUM"));
    for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;
    return;
  }
  String firmaismi = String(firma);
    firmaismi.trim();
  if (firmaismi != "izbb") {
    Serial.println(F("BU KART BU SEHRIN DEGIL"));
    for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;
    return;
  }


// ============   KARTTAKİ UNİXTIME OKUYUP FARK ALMA DURUMU BURADA OLACAK. ======================

  //unsigned long kartUnix=1773406620;// ************** buraya karttan okunan gerçek unixtime konulacak. *****************
  rtcZamanPlusDakika();
  Serial.print(" RTC_UNIXTIME  ");
  Serial.println(RTCunixTime);
  long farkSaniye = RTCunixTime - kayitSaat; // 5400 saniye
  long farkDakika = farkSaniye / 60;    // 90 dakika
  //Serial.println(" fark saniye : "+farkSaniye);
  //Serial.println(" fark dakika : "+farkDakika);

  if(farkDakika<0){
    farkDakika=100;
  }
  Serial.print("fark saniye :  "); Serial.println(farkSaniye);
   Serial.print("fark dakika :  "); Serial.println(farkDakika);
   

//  ========================  UNIXTIME SONU ====================================================

  int dusulecek = 0;

  if (farkDakika <= 90) {

    if (durum == 1) {
      Serial.println(F("UCRETSIZ GECIS"));
      for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;
      return;
    }

    if (durum == 0) {
      dusulecek = 5;
      Serial.println(F("5 KREDI DUSULECEK"));
      for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;durum=1;
    }

  } else {

    dusulecek = 30;
    Serial.println(F("30 KREDI DUSULECEK"));
    for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;durum=0;

  }

  if (kredi < dusulecek) {
    Serial.println(F("YETERSIZ BAKIYE"));
    for (byte i=0; i<uidSize; i++) esonUID[i] = uid[i];
      sonUIDVar = true;
    return;
  }

  int yeniKredi = kredi - dusulecek;

  Serial.print(F("YENI KREDI: "));
  Serial.println(yeniKredi);

  char zamanDamga[11];
  sprintf(zamanDamga, "%lu", RTCunixTime);

   K_kart_yaz(uid, yeniKredi, zamanDamga, durum,dusulecek);

  

}

// *************  KREDİLİ SİSTEM YAZMA FONKSİYONU **************

void hazirlaBlok(String veri, byte *buf)
{
  veri.trim();

  if (veri.length() > 16)
    veri = veri.substring(0,16);

  for(byte i=0;i<16;i++)
  {
    if(i < veri.length())
      buf[i] = veri[i];
    else
      buf[i] = 0x00;
  }
}


void K_kart_yaz(byte *uid, int kredi, String zamanDamgasi, byte durum,int dusulen)
{
  Serial.println(F("KART YAZMA BASLADI"));

  byte buf[16];

  String krediStr = String(kredi);
  String durumStr = String(durum);

  byte blockList[3] = {8,9,10};

  for(byte i=0;i<3;i++)
  {
    byte block = blockList[i];

    if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid))
    {
      Serial.print(F("Auth FAIL block "));
      Serial.println(block);
      mifareStopCrypto();
      return;
    }

    if(block == 8){
      hazirlaBlok(krediStr, buf);
    }
    
    if(block == 9){
      if (dusulen<20){
        continue;
      }
      hazirlaBlok(zamanDamgasi, buf);
    }

    if(block == 10){
      hazirlaBlok(durumStr, buf);
    }
    
    if (!mifareWrite(block, buf))
    {
      Serial.print(F("WRITE FAIL block "));
      Serial.println(block);
      mifareStopCrypto();
      return;
    }

    //Serial.print(F("YAZILDI block "));
    //Serial.println(block);
  }

  mifareStopCrypto();

  Serial.println(F("KART BASARIYLA GUNCELLENDI"));
  
  bipTek();
  delay(1000);

  aktifMod = NORMAL_MOD;
}


// ------------- BUZZER BİP SESİ ------------
void bipTek() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  Serial.println(F("BIP"));
  delay(200);
}

void bipiki() {
  for (byte i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
  Serial.println(F("BIP BIP"));
  
  delay(200);
}
void bipUc() {
  for (byte i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
  Serial.println(F("BIP BIP BIP"));
  delay(200);
}

//---------------- hatalı kart deneme sayısı arttırma -------------
void HataliDenemeArtir() {
  hataliDenemeSayisi++;

  Serial.print(F("HATALI DENEME: "));
  Serial.println(hataliDenemeSayisi);
  bipiki();
  

  if (hataliDenemeSayisi >= 5) {
    sistemKilitli = true;
    kilitBaslangicZamani = millis();
    Serial.println(F("❌❌❌ SISTEM 2 DAKIKA KILITLENDI ❌❌❌"));
  }
}

// -------------- kopya kart bulma fonksiyon ------------------

// uid -> okunan uid pointer (ör. uid array), uidLen -> genelde 4
void KopyaKartKontrolFonksiyonu(byte *uid, byte uidLen) {
  unsigned long simdi = millis();
  bool ayniKart = false;

  // eğer daha önce UID yoksa doğrudan kaydet
  if (sonUIDLen == uidLen) {
    if (memcmp(uid, sonUID, uidLen) == 0) ayniKart = true;
  }

  if (ayniKart) {
    // aynı UID, sürenin kısa olup olmadığına bak
    if (simdi - sonOkumaZamani < KOPYA_ESIK_SURE) {
      ardArdaAyniOkumaSayisi++;
    } else {
      // fakat aradaki süre uzunsa tekrar sayısını resetle
      ardArdaAyniOkumaSayisi = 1;
    }
  } else {
    // farklı UID: geçmiş UID'i güncelle ve sayacı 1 yap
    memcpy(sonUID, uid, uidLen);
    sonUIDLen = uidLen;
    ardArdaAyniOkumaSayisi = 1;
  }

  sonOkumaZamani = simdi;

  // şüphe kontrolü
  if (ardArdaAyniOkumaSayisi >= KOPYA_TETIK_SAYISI) {
    Serial.println(F("⚠️ KOPYA KART ŞÜPHESİ!"));
    Serial.print(F("KOPYA SUPHESI SAYISI: "));
    Serial.println(ardArdaAyniOkumaSayisi);
    hataliDenemeSayisi = MAKS_HATALI_DENEME;
    kopyaKartTespitEdildi = true;

    // buraya istersen hata artırma veya kilit fonksiyonu çağır
    HataliDenemeArtir(); // kopya şüphesini hatalı deneme sayacına dahil etmek istersen
    // veya doğrudan kilitle:
    // sistemKilitli = true; kilitBaslangicZamani = millis();

    // sayaçları temizle/başlat (opsiyonel, tercihe bağlı)
    ardArdaAyniOkumaSayisi = 0;
  }
}

// ************* kapı yetkilendirme fonksiyonları *****************
// kartYetki: 16-bit bitmask (ör. 0b0000000000001011)
// kapiNo: 0-based index (0..15)
bool yetkiliMi(uint16_t kartYetki, uint8_t kapiNo) {
  return (kartYetki & (1 << (kapiNo - 1))) != 0;
}

String kayitUret(const String &uid, const String &kimlik, const String &firma, uint8_t kapiNo, uint16_t yetki) {
  unsigned long zaman = millis(); // RTC yok, şimdilik millis()
  // yetkiyi 16 bit string olarak ters sırada değil, doğal sırada gösterelim:
  String yetkiStr = "";
  for (int i = 15; i >= 0; i--) {
    yetkiStr += String((yetki >> i) & 1);
  }

  String satir = uid + "|" + String(zaman) + "|" + kimlik + "|" + firma + "|" + String(kapiNo) + "|" + yetkiStr;
  return satir;
}

void yetkiKontrolVeKayitUret(const String &uid, const String &kartKimligi, const String &firmaAdi, uint8_t kapiNo, uint16_t kartYetkisi) {
  bool yetkili = yetkiliMi(kartYetkisi, kapiNo);
  unsigned long zamanDamgasi = millis();

  if (yetkili) {
    Serial.println(F("✅ GIRIS ONAYLANDI"));
    Serial.println(F("KAPI ACILIYOR..."));
     bipTek(); // gerçek buzzer varsa çağır
    //Serial.println(F("BIP"));
    hataliDenemeSayisi = 0; // başarılı okuma => hata sayacını sıfırla
  } else {
    Serial.println(F("❌ YETKISIZ KISI!"));
    Serial.println(F("❌ BU KAPIDAN GIREMEZSIN!"));
     bipUc(); // hata bipleri
    //Serial.println(F("BIP BIP BIP"));
    hataliDenemeSayisi++;
    HataliDenemeArtir(); // eğer ek işlem istiyorsan bunu çağır (zaten hatalı artıyor olabilir)
  }

  String kayit = kayitUret(uid, kartKimligi, firmaAdi, kapiNo, kartYetkisi);
  Serial.println(F("📝 KAYIT: "));
  Serial.println(kayit);

  // TODO: buraya EEPROM/SD kaydı ekle (isteğe bağlı)
}




// *********** kapı yetkilendirme fonksiyonları sonu. **********



// ===============  RTC UNIXTIME ========================
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

  m  = (m>>4)*10 + (m&0x0F);
  h  = (h>>4)*10 + (h&0x0F);
  d  = (d>>4)*10 + (d&0x0F);
  mo = (mo>>4)*10 + (mo&0x0F);
  y  = (y>>4)*10 + (y&0x0F);

  int yy=y+2000;
  unsigned long rtcUnix = rtcToUnix(yy, mo, d, h, m);

  //Serial.print("chat gpt kod fonksiyonu RTC Unix timestamp: "); Serial.println(rtcUnix);
  

}


// RTC yıl, ay, gün, saat, dakika -> Unix timestamp (saniye)
unsigned long rtcToUnix(int yr, int mn, int day, int hour, int min) {
  const uint8_t dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  unsigned long days = 0;

  // 1970'den önceki yılları ekle
  for(int y=1970; y<yr; y++) {
    days += 365;
    if((y % 4) == 0) days++; // artık yıl
  }

  // Önceki ayların günlerini ekle
  for(int m=1; m<mn; m++) {
    days += dim[m-1];
    if(m==2 && (yr % 4)==0) days++; // Şubat artık yıl
  }

  // Günleri ekle
  days += day - 1;

  // Toplam saniye = gün*86400 + saat*3600 + dakika*60
  RTCunixTime = days*86400UL + hour*3600UL + min*60UL;

  return RTCunixTime ;
}





// ---------------- Setup & Loop ----------------

void setup() {
  Serial.begin(115200);
  BTSerial.begin(BT_BAUD);
  Wire.begin();
  
  pinMode(SS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(BUZZER_PIN, LOW);

  digitalWrite(SS_PIN, HIGH);
  digitalWrite(RST_PIN, HIGH);

  SPI.begin();
  pcdInit();

  Serial.print("MFRC522 Version: 0x");
  Serial.println(rcRead(VersionReg), HEX);
  Serial.println(F("Mini-driver hazir."));
  
  
}

String btBuffer = "";


void loop() {

  //char yeniZaman[13];

  
  
    // 🔒 SİSTEM KİLİTLİ Mİ?
  if (sistemKilitli) {
    if (millis() - kilitBaslangicZamani >= KILIT_SURESI) {
      sistemKilitli = false;
      hataliDenemeSayisi = 0;
      Serial.println(F("SISTEM OTOMATIK ACILDI ✅"));
      kopyaKartTespitEdildi = false;
    } else {
      Serial.println(F("SISTEM KILITLI ❌ 2 DAKIKA BEKLEYIN..."));
      bipUc();
      //Serial.println(F("BIP BIP BIP"));
      delay(1000);
      return; // ✅ Kart okuma tamamen durur
    }
  }

  aktifMod = NORMAL_MOD;
  
  // 3) main state machine
  switch (aktifMod) {
    case NORMAL_MOD:
      kartOku();
      delay(500);
      break;
    
  }
}
 
