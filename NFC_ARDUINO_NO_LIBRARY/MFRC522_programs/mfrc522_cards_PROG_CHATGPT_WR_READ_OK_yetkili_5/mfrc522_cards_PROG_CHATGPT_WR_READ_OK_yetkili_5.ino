//Program hem kart yazma(admin buton) hem de okuma OK eproma log yazma OK pc ye bluetooth üzerinden gönderme denenecek 
// seri port çalışmıyorsa eproma yazacak. 


// yetkili kısmında okuma tamam ama createbitmask ve admin çoklu kapıyı destekliyor Ali yilmaz,delta.ltd,1.2.5.6.7 formatında. seri porttan alıyor
// gerekirse bluetooth seri port olabilir ya da usb seri çevirici ile pc ye bağlanır soft serial ile bu yapılabilir. 
// bluetooth soft serial hazır admin bilgisi bluetooth ile telefondan bile gönderilebilir ya da pc den gönderilir. 

// ==============  serial.print satırları F ile üst belleğe atılacak. ================== OK
// ***** bu programa RTC eklenecek fakat karta yazılmayacak seri port üzerinden gönderme ve eeproma yazma kısmı kredili sistem gibi olacak. OK
// unixtime karta yazılmayacak seri port üzerinden gönderilecek. ******************* OK


// NTAG etiketinde zaman damgası kartın geçerlilik süresi olarak kullanıldı. 
// buraya bilgi yazmayacak fakat rtc ile zamanı karşılaştıracak. 
// şayet zaman eskimişse o zaman KART KULLANILAMAZ diyecek ve yetkisi olsa bile kapı açılmayacak. 
// bu misafir kartları ve normal kullanımdaki kartı yazarken bir son tarih yazılmasını gerektirecek. 


/*
 * #define RES_RED            0
#define RES_OK             1
#define RES_YETKISIZ       2
#define RES_HATALI_KART    3
#define RES_KREDI_YOK      4
#define RES_KART_YOK       5
#define RES_SISTEM_HATA    6

durum sayısı aşağıdaki gibi kullanılacak. ve yukarıdaki gibi tanımlanacak. 
log.result = RES_OK;
log.result = RES_YETKISIZ;
 */

// bu program admin yazma ve yetki OK fakat aynı kart gelirse RET etmesi lazım son kart karşılatır.
// Aynı kart geldiğinde tekrar tekrar kapı aç yazıyor sorun yok. fakat 1 kere eeproma yazıyor. aynı kart ise eproma kayıt yazmıyor. OK

//*** dikkat gerçek blok3 kullanılmayuacak ve blok 7 kullanılmayacak bunlar 
// *** kart parametreleridir bozulursa kart okuma hatası verir. 

// Tam Program: RC522 mini-driver + SoftSerial (HC-05/06) + Admin programlama (AD_ prefix)
// SPI: 11(MOSI),12(MISO),13(SCK)
// SS=10, RST=9
// SoftwareSerial: RX=7 (to BT TX), TX=8 (to BT RX)
// Admin button: D2 (INPUT_PULLUP)

#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>

#define SS_PIN   10
#define RST_PIN  9
#define ADMIN_BUTTON 2
#define BUZZER_PIN  6

// *********** hatalı kart değişkenleri **********
int hataliDenemeSayisi = 0;
bool sistemKilitli = false;
unsigned long kilitBaslangicZamani = 0;

const unsigned long KILIT_SURESI = 1000; // 2 dakika = 120.000 ms
const int MAKS_HATALI_DENEME = 15;
unsigned long RTCunixTime=0;

// Hangi kapı bu okuyucuya bağlı? (0..15)
const uint8_t aktifKapiNo = 2;  // test için "2" (3. kapı insan dilinde)

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

byte Nuid=0;
byte uid[7];
byte uidSize=4;


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
//=========== LOG result değerleri 
#define RES_RED            0
#define RES_OK             1
#define RES_YETKISIZ       2
#define RES_HATALI_KART    3
#define RES_KREDI_YOK      4
#define RES_KART_YOK       5
#define RES_SISTEM_HATA    6

// ***************** EEPROM KAYIT ETME DEĞİŞKEN *******************
#define LOGSIZE 16
#define EEPROM_START 2
#define EEPROM_SIZE 1024
#define MAXLOG ((EEPROM_SIZE-EEPROM_START)/LOGSIZE)

#define ACK_TIMEOUT 300  // ms

struct LOG {
  uint32_t time;   // unix time
  uint8_t uidSize1; // 4 veya 7 byte uid sayisi.
  uint8_t uid[7];  // kart UID
  uint8_t gate;    // kapı numarası
  uint16_t kredi;  // düşülen veya kalan kredi
  uint8_t result;  // sonuç
};
// ***************** EEPROM KAYIT ETME DEĞİŞKEN SONU *******************

// ============ EEPROM KAYIT FONK. ========================
// Fonksiyon: log gönder ve EEPROM backup
void logGonder(LOG &log) {
  uint16_t pointer;
   if (Nuid == 1){
    return;
    }

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



// ADMIN state machine
enum SistemModu { NORMAL_MOD, AD_VERI_HAZIR, AD_KART_YAZMA };
SistemModu aktifMod = NORMAL_MOD;

unsigned long AD_sonIslemZamani = 0;
const unsigned long AD_timeout = 120000; // 2 dakika

byte AD_bekleyenVeri[16];// bu artık kullanılmıyor olabilir. 
bool AD_veriHazir = false;
byte AD_bekleyenBlok[3][16];

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

/*
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
}*/

// UID okuyucu (4 veya 7 byte)
bool mifareAnticoll(byte *uid, byte &uidSize) {

  byte ser[2];
  byte back[MAX_LEN];
  byte backLen = 0;

  rcWrite(BitFramingReg, 0x00);

  // Cascade Level 1
  ser[0] = 0x93;
  ser[1] = 0x20;

  if (!pcdTransceive(ser, 2, back, backLen, 200)) return false;
  if (backLen != 5) return false;

  byte bcc = back[0]^back[1]^back[2]^back[3];
  if (bcc != back[4]) return false;

  // CASCADE TAG kontrolü
  if(back[0] == 0x88) {

    // UID 7 byte
    uid[0] = back[1];
    uid[1] = back[2];
    uid[2] = back[3];

    // Cascade Level 2
    ser[0] = 0x95;
    ser[1] = 0x20;

    if (!pcdTransceive(ser, 2, back, backLen, 200)) return false;
    if (backLen != 5) return false;

    bcc = back[0]^back[1]^back[2]^back[3];
    if (bcc != back[4]) return false;

    uid[3] = back[0];
    uid[4] = back[1];
    uid[5] = back[2];
    uid[6] = back[3];

    uidSize = 7;

  } 
  else {

    // UID 4 byte
    for(byte i=0;i<4;i++) uid[i] = back[i];

    uidSize = 4;
  }

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

// ----------------- ADMIN (AD_) FUNCTIONS -----------------

void prepareBlock(byte *dest, String s) {
  s.trim();
  if (s.length() > 16) s = s.substring(0, 16);
  while (s.length() < 16) s += ' ';
  for (byte i=0; i<16; i++) dest[i] = (byte)s[i];
}


void createBitmask(byte *dest, String doorList) {

  unsigned int mask = 0;

  int start = 0;

  while (true) {

    int dot = doorList.indexOf('.', start);

    String doorStr;

    if (dot == -1)
      doorStr = doorList.substring(start);
    else
      doorStr = doorList.substring(start, dot);

    int doorNo = doorStr.toInt();

    if (doorNo >= 1 && doorNo <= 16) {
      mask |= (1 << (doorNo - 1));
    }

    if (dot == -1) break;

    start = dot + 1;
  }

  //dest[0] = (mask >> 8) & 0xFF;
  //dest[1] = mask & 0xFF;

  dest[0] = mask & 0xFF;
  dest[1] = (mask >> 8) & 0xFF;

  for (int i=2; i<16; i++) dest[i] = ' ';
}
/*void createBitmask(byte *dest, int doorNo) {
  // kapı 1–16 arası
  unsigned int mask = (1 << (doorNo - 1));  // ör: 2 → 00000000 00000010

  dest[0] = (mask >> 8) & 0xFF;
  dest[1] = mask & 0xFF;

  // kalan 14 byte boşluk
  for (int i=2; i<16; i++) dest[i] = ' ';
}
*/

// AD_VeriGeldi: Bluetooth veya keypad tarafından gelen 16 byte alınıp RAM'de saklanır.
// Bu örnekte sadece BT üzerinden alınan metin ile çalışıyoruz. Keypad daha sonra eklenebilir.

void AD_VeriGeldi(String s) {
/*  s.trim();  // Baş–son boşlukları sil
  Serial.println("AD: Gelen ham veri: " + s);

  // 1️⃣ Virgülle ayır
  int p1 = s.indexOf(',');
  int p2 = s.indexOf(',', p1 + 1);

  if (p1 < 0 || p2 < 0) {
    Serial.println("AD: HATA → 3 parça bulunamadi!");
    return;
  }

  String isim = s.substring(0, p1);
  String firma = s.substring(p1 + 1, p2);
  String kapiStr = s.substring(p2 + 1);
  int kapiNo = kapiStr.toInt();

  // 2️⃣ Blok 1 → isim
  prepareBlock(AD_bekleyenBlok[0], isim);

  // 3️⃣ Blok 2 → firma
  prepareBlock(AD_bekleyenBlok[1], firma);

  // 4️⃣ Blok 3 → bitmask
  createBitmask(AD_bekleyenBlok[2], kapiNo);
*/

   s.trim();
  Serial.println("AD: Gelen ham veri: " + s);

  int p1 = s.indexOf(',');
  int p2 = s.indexOf(',', p1 + 1);

  if (p1 < 0 || p2 < 0) {
    Serial.println(F("AD: HATA → 3 parça bulunamadi!"));
    return;
  }

  String isim = s.substring(0, p1);
  String firma = s.substring(p1 + 1, p2);
  String kapiStr = s.substring(p2 + 1);

  prepareBlock(AD_bekleyenBlok[0], isim);
  prepareBlock(AD_bekleyenBlok[1], firma);

  createBitmask(AD_bekleyenBlok[2], kapiStr);

  
  AD_veriHazir = true;
  aktifMod = AD_VERI_HAZIR;
  AD_sonIslemZamani = millis();

  Serial.println(F("AD: 3 blok hazirlandı."));
  
}


// Admin buton: kısa basış kontrolü (press & release). Eğer veri hazir ise AD_KART_YAZMA moduna geç.
unsigned long lastButtonStateChange = 0;
bool lastButton = HIGH;


void AD_AdminButonKontrol() {
  bool cur = digitalRead(ADMIN_BUTTON);
  if (cur != lastButton) {
    lastButtonStateChange = millis();
    lastButton = cur;
  }
  // detect short press release
  if (cur == HIGH && lastButton == HIGH) {
    // nothing
  }
  // If release just happened from LOW to HIGH and lasted < 1500ms => short press
  static bool wasLow = false;
  static unsigned long lowTime = 0;
  if (cur == LOW && !wasLow) {
    wasLow = true; lowTime = millis();
  }
  if (cur == HIGH && wasLow) {
    unsigned long dur = millis() - lowTime;
    wasLow = false;
    if (dur < 1500) {
      // short press
      Serial.println(F("AD: Kisa basinak algilandi."));
      if (AD_veriHazir) {
        aktifMod = AD_KART_YAZMA;
        AD_sonIslemZamani = millis();
        Serial.println(F("AD: Kart yazma modu aktif. Lütfen karti getiriniz."));
      } else {
        Serial.println(F("AD: Veri hazir degil. Once telefon/keypad ile veri gonderin."));
      }
    } else {
      Serial.println(F("AD: Uzun basinak (gorsel)."));
    }
  }
}

// AD_TimeoutKontrol: 2dk dolarsa programlamayi kapat
void AD_TimeoutKontrol() {
  if ((aktifMod == AD_VERI_HAZIR || aktifMod == AD_KART_YAZMA) && AD_veriHazir) {
    if (millis() - AD_sonIslemZamani > AD_timeout) {
      Serial.println(F("AD: Timeout. Programlama kapatildi."));
      AD_veriHazir = false;
      aktifMod = NORMAL_MOD;
    }
  }
}

// AD_KartProgramla: bekleyen veriyi karta yaz. başarılı ise tekrar AD_VERI_HAZIR moduna döner ve timer sıfırlanır.
// blok olarak 3 blok kullanıyoruz (kullanıcı isim alanı,firma ismi, kapı no)

// AD_KartProgramla: bekleyen veriyi karta yaz.
// Kullanıcı için 3 blok = 4, 5, 6
void AD_KartProgramla() {
  Serial.println(F("AD: Kart yazma bekleniyor..."));

  byte atqa[2]; 
  byte atqaLen = 0;
  if (!mifareRequest(atqa, atqaLen)) { 
    delay(200); 
    return; 
  }
  Serial.print("ATQA: "); 
  printHex(atqa, atqaLen);

  byte uid[4];
  if (!mifareAnticoll(uid,uidSize)) { 
    Serial.println(F("AD: Anticoll fail")); 
    delay(200); 
    return; 
  }
  Serial.print("UID: "); 
  printHex(uid, 4);

  if (!mifareSelect(uid)) { 
    Serial.println(F("AD: Select fail")); 
    delay(200); 
    return; 
  }
  Serial.println(F("AD: Select OK"));

  // 3 blok = 4, 5, 6
  for (byte i = 0; i < 3; i++) {

    byte block = 4 + i;   // 4, 5, 6

    if (!mifareAuthenticate(PICC_AUTH_KEY_B, block, defaultKey, uid)) {
      Serial.print(F("AD: Auth fail block ")); 
      Serial.println(block);
      mifareStopCrypto(); 
      delay(200); 
      return;
    }

    if (!mifareWrite(block, AD_bekleyenBlok[i])) {
      Serial.print(F("AD: Write FAIL block ")); 
      Serial.println(block);
      mifareStopCrypto(); 
      delay(200); 
      return;
    }
  }

  Serial.println(F("AD: Blok 4, 5, 6 başarıyla yazıldı."));

  aktifMod = AD_VERI_HAZIR;
  AD_sonIslemZamani = millis();
  bipTek();
}




// *************** AD_YAZMA _PROGRAM SONU ********************

// ---------------- NORMAL USER FUNCTIONS ----------------

void kartOku() {
  byte atqa[2]; byte atqaLen=0;
  if (!mifareRequest(atqa, atqaLen)) { delay(200); return; }
  Serial.print("ATQA: "); printHex(atqa, atqaLen);

  byte uid[4];
  if (!mifareAnticoll(uid,uidSize)) { Serial.println(F("Anticoll FAIL")); delay(200); HataliDenemeArtir(); return; }
  Serial.print("UID: "); printHex(uid,4);
  

  if (!mifareSelect(uid)) { Serial.println(F("Select FAIL")); delay(200); HataliDenemeArtir(); return; }
  Serial.println("Select OK");

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
  bipTek();

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
  uint16_t kartBitmask = ((uint16_t)buf[1] << 8) | (uint16_t)buf[0];

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
  Serial.print(F("Okunan BITMASK: ")); Serial.println(kartBitmask);
  // Kopya kart kontrol (aynı uid ardışık okuma vs.)
  KopyaKartKontrolFonksiyonu(uid, 4);

  // Eğer kopya değil ve sistem kilitli değilse yetki kontrolüne gönder
  if (!kopyaKartTespitEdildi && !sistemKilitli) {
    yetkiKontrolVeKayitUret(uid, kartIsmi, firmaAdi, aktifKapiNo, kartBitmask);
  }

  mifareStopCrypto();
  delay(3000);
}




// ------------- BUZZER BİP SESİ ------------
void bipTek() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(120);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("BIP");
}

void bipUc() {
  for (byte i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(120);
  }
  Serial.println("BIP");
  Serial.println("BIP");
  Serial.println("BIP");
}

//---------------- hatalı kart deneme sayısı arttırma -------------
void HataliDenemeArtir() {
  hataliDenemeSayisi++;

  Serial.print(F("HATALI DENEME: "));
  Serial.println(hataliDenemeSayisi);
  Serial.println("BIP BIP");

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
    if (memcmp(uid, sonUID, uidLen) == 0){
      ayniKart = true;
       Serial.println( "******************  AYNI KART **************************");
       Nuid=1;
    } else{
      Nuid=0;
    }
     
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

void yetkiKontrolVeKayitUret(byte *uid, const String &kartKimligi, const String &firmaAdi, uint8_t kapiNo, uint16_t kartYetkisi) {
  bool yetkili = yetkiliMi(kartYetkisi, kapiNo);
  unsigned long zamanDamgasi = millis();
  

  if (yetkili) {
    Serial.println(F("✅ GIRIS ONAYLANDI"));
    Serial.println(F("KAPI ACILIYOR..."));
    // bipTek(); // gerçek buzzer varsa çağır
    Serial.println("BIP");
      
    
    hataliDenemeSayisi = 0; // başarılı okuma => hata sayacını sıfırla
    rtcZamanPlusDakika();
    Serial.print(" RTC_UNIXTIME  ");
    Serial.println(RTCunixTime);
    // Örnek log
    uidSize=4; //****************** bu sonradan 4 ve 7 byte olmasına göre değişebilir. ***********************
    LOG yeniLog;
    yeniLog.time = RTCunixTime;
    yeniLog.uidSize1=uidSize;      // 4 veya 7 byte UID tipi. 
    // UID kopyalama ve padding işlemi
    for (int i = 0; i < 7; i++) {
        if (i < uidSize) {
            // UID'nin gerçek byte'larını kopyala
            yeniLog.uid[i] = uid[i];
        } else {
            // UID boyutundan fazla olan alanları 0 ile doldur (padding)
            yeniLog.uid[i] = 0x00;
        }
    }
    yeniLog.gate = 2; // bu kapı no 1 den fazla olabilir
    yeniLog.kredi = 0;
    yeniLog.result = RES_OK;
  
    logGonder(yeniLog);
  
  } else {
    Serial.println(F("❌ YETKISIZ KISI!"));
    Serial.println(F("❌ BU KAPIDAN GIREMEZSIN!"));
    // bipUc(); // hata bipleri
    Serial.println("BIP BIP BIP");
    hataliDenemeSayisi++;
    HataliDenemeArtir(); // eğer ek işlem istiyorsan bunu çağır (zaten hatalı artıyor olabilir)
      // Örnek log
    uidSize=4; //****************** bu sonradan 4 ve 7 byte olmasına göre değişebilir. ***********************  
    LOG yeniLog;
    yeniLog.time = RTCunixTime;
    yeniLog.uidSize1=uidSize;      // 4 veya 7 byte UID tipi. 
    // UID kopyalama ve padding işlemi
    for (int i = 0; i < 7; i++) {
        if (i < uidSize) {
            // UID'nin gerçek byte'larını kopyala
            yeniLog.uid[i] = uid[i];
        } else {
            // UID boyutundan fazla olan alanları 0 ile doldur (padding)
            yeniLog.uid[i] = 0x00;
        }
    }
    yeniLog.gate = 2; // bu kapı no 1 den fazla olabilir
    yeniLog.kredi = 0;
    yeniLog.result = RES_YETKISIZ;
  
    logGonder(yeniLog);
  }
  String uidStr = uidToString(uid, uidSize);
  Serial.println(uidStr);
  String kayit = kayitUret(uidStr, kartKimligi, firmaAdi, kapiNo, kartYetkisi);
  Serial.println("📝 KAYIT: ");
  Serial.println(kayit);

  // TODO: buraya EEPROM/SD kaydı ekle (isteğe bağlı)
}

//============  bu fonk. ile 7 byte uid değişkenini yazdırabilmek ve kayitUret fonksiyonunda kullanmak için STRING şekline dönüştürdük. =========
String uidToString(const uint8_t *uid, uint8_t uidSize)
{
  String s = "";

  for (uint8_t i = 0; i < uidSize; i++)
  {
    if (uid[i] < 0x10) s += "0";   // tek haneli ise başına 0 koy
    s += String(uid[i], HEX);
  }

  s.toUpperCase(); // isteğe bağlı (daha temiz görünür)
  return s;
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
  pinMode(ADMIN_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(BUZZER_PIN, LOW);

  digitalWrite(SS_PIN, HIGH);
  digitalWrite(RST_PIN, HIGH);

  SPI.begin();
  pcdInit();

  Serial.print(F("MFRC522 Version: 0x"));
  Serial.println(rcRead(VersionReg), HEX);
  Serial.println(F("Mini-driver hazir."));

  // If admin button held during powerup, we can optionally enter AD_VERI_HAZIR
  if (digitalRead(ADMIN_BUTTON) == LOW) {
    Serial.println(F("AD: Basili giris tespit edildi. Programlama modu acilmasi bekleniyor (veri bekleniyor)."));
    aktifMod = AD_VERI_HAZIR;
    AD_sonIslemZamani = millis();
  }
  rtcZamanPlusDakika();
  Serial.print(" RTC_UNIXTIME  ");
  Serial.println(RTCunixTime);
}

String btBuffer = "";


void loop() {
  
    // 🔒 SİSTEM KİLİTLİ Mİ?
  if (sistemKilitli) {
    if (millis() - kilitBaslangicZamani >= KILIT_SURESI) {
      sistemKilitli = false;
      hataliDenemeSayisi = 0;
      Serial.println(F("SISTEM OTOMATIK ACILDI ✅"));
      kopyaKartTespitEdildi = false;
    } else {
      Serial.println(F("SISTEM KILITLI ❌ 2 DAKIKA BEKLEYIN..."));
      Serial.println("BIP BIP BIP");
      delay(1000);
      return; // ✅ Kart okuma tamamen durur
    }
  }

  
  // 1) read bluetooth serial (non-blocking)
  while (Serial.available()) {//while (BTSerial.available()) {
    char c = Serial.read();  //BTSerial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      if (btBuffer.length() > 0) {
        Serial.print("BT gelen: ");
        Serial.println(btBuffer);
        AD_VeriGeldi(btBuffer);
        btBuffer = "";
      }
    } else {
      btBuffer += c;
      if (btBuffer.length() > 64) btBuffer = btBuffer.substring(btBuffer.length()-64); // safety
    }
  }

  // 2) admin button & timeout
  AD_AdminButonKontrol();
  AD_TimeoutKontrol();

  // 3) main state machine
  switch (aktifMod) {
    case NORMAL_MOD:
      kartOku();
      break;
    case AD_VERI_HAZIR:
      // waiting for admin short press or new data; do nothing active
      // optionally print a short heartbeat
      // Serial.println("AD: Veri hazir. Admin basarsa yazma moduna gecilecek.");
      delay(200);
      break;
    case AD_KART_YAZMA:
      AD_KartProgramla();
      break;
  }
}
 
