#include <SPI.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <EEPROM.h>

#define SS_PIN   10
#define RST_PIN  9
#define BUZZER_PIN 6

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
#define RFCfgReg        0x26

#define PCD_IDLE        0x00
#define PCD_TRANSCEIVE  0x0C
#define PCD_CALCCRC     0x03
#define PCD_RESET       0x0F

#define PICC_WUPA       0x52  // HALT (Uyku) modundaki kartları da zorla uyandıran WUPA komutu
#define PICC_READ       0x30
#define PICC_WRITE      0xA2
#define MAX_LEN         18

const char* KART_TIPLERI[] = {"Normal / Tam", "Ogrenci", "Sehit Yakini", "Engelli", "Ozel Durum"};
int eepromAdres = 10; 

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

void pcdinit() {
  rcWrite(CommandReg, PCD_RESET);
  delay(50);
  rcWrite(TModeReg, 0x8D);
  rcWrite(TPrescalerReg, 0x3E);
  rcWrite(TReloadRegL, 30);
  rcWrite(TReloadRegH, 0x00);
  rcWrite(TxASKReg, 0x40);
  rcWrite(ModeReg, 0x3D);
  
  // Anten Kazancı doğrudan donanım başlangıcına entegre edildi (48 dB Maksimum)
  rcWrite(RFCfgReg, 0x70); 
  
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

bool NTAG213_Authenticate() {
  byte cmd[7]; 
  byte crc[2];
  byte back[MAX_LEN];

  // 1. ŞİFREYİ GÖNDER (S A F K)
  cmd[0] = 0x1B; // PWD_AUTH
  cmd[1] = 0x53; 
  cmd[2] = 0x41; 
  cmd[3] = 0x46; 
  cmd[4] = 0x4B; 

  if (!pcdCalculateCRC(cmd, 5, crc)) return false;
  cmd[5] = crc[0];
  cmd[6] = crc[1];

  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80); 
  rcWrite(ComIrqReg, 0x7F);    
  for (byte i = 0; i < 7; i++) rcWrite(FIFODataReg, cmd[i]);
  rcWrite(CommandReg, PCD_TRANSCEIVE);
  rcSetBitMask(BitFramingReg, 0x80); 
  delay(10); // Kartın komutu işlemesi için kısa süre
  rcClearBitMask(BitFramingReg, 0x80);

  // MFRC522'nin getirdiği yanıta (yankıya) HİÇ BAKMIYORUZ.
  // Doğrudan kartın kapılarını açıp açmadığını canlı test ediyoruz:

  // 2. CANLI KONTROL (PROBE TEST): Konfigürasyon Sayfasını (0x2B) Okumayı Dene
  byte readCmd[4];
  readCmd[0] = 0x30; // NTAG READ KOMUTU
  readCmd[1] = 0x2B; // Sayfa 43 (Konfigürasyon / Şifre Alanı)
  
  if (!pcdCalculateCRC(readCmd, 2, crc)) return false;
  readCmd[2] = crc[0];
  readCmd[3] = crc[1];

  // FIFO ve Kesme temizliği
  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80); 
  rcWrite(ComIrqReg, 0x7F);    

  for (byte i = 0; i < 4; i++) rcWrite(FIFODataReg, readCmd[i]);
  
  rcWrite(CommandReg, PCD_TRANSCEIVE);
  rcSetBitMask(BitFramingReg, 0x80);

  unsigned long start = millis();
  byte irq = 0;
  while (true) {
    irq = rcRead(ComIrqReg);
    if (irq & 0x20) break; // Veri geldi
    if (irq & 0x01) break; // Zaman aşımı
    if (millis() - start > 40) break;
  }
  rcClearBitMask(BitFramingReg, 0x80);

  byte fifoKat = rcRead(FIFOLevelReg);

  // GERÇEK TEŞHİS ŞİMDİ BAŞLIYOR:
  // Eğer şifre doğruysa kart kapıları açmıştır ve Sayfa 43'ün içeriğini (16 bayt) bize döner.
  // Eğer şifre yanlışsa kart kilitlidir, bu okuma komutuna yanıt vermez ve FIFO boş kalır (0).
  if (fifoKat > 0) {
    Serial.println(F("🔑 [GERÇEK TEŞHİS] ŞİFRE DOĞRU! Korunmuş hafıza başarıyla okundu."));
    return true;
  } else {
    Serial.println(F("❌ [GERÇEK TEŞHİS] ŞİFRE HATALI VEYA KART KİLİTLİ! Erişim reddedildi."));
    return false;
  }
}






bool ntagSelect(byte *uidOut, byte &uidSizeOut) {
  byte buffer[MAX_LEN];
  byte backLen;

  rcWrite(BitFramingReg, 0x07);
  buffer[0] = PICC_WUPA; 
  if (!pcdTransceive(buffer, 1, buffer, backLen, 100)) return false;

  rcWrite(BitFramingReg, 0x00);
  byte cmdCL1[2] = {0x93, 0x20};
  if (!pcdTransceive(cmdCL1, 2, buffer, backLen, 100)) return false;
  
  byte selCL1[9] = {0x93, 0x70, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]};
  byte crc[2];
  if (!pcdCalculateCRC(selCL1, 7, crc)) return false;
  selCL1[7] = crc[0]; selCL1[8] = crc[1];
  if (!pcdTransceive(selCL1, 9, buffer, backLen, 100)) return false;
  
  uidOut[0] = buffer[1]; uidOut[1] = buffer[2]; uidOut[2] = buffer[3];

  byte cmdCL2[2] = {0x95, 0x20};
  if (!pcdTransceive(cmdCL2, 2, buffer, backLen, 100)) return false;

  byte selCL2[9] = {0x95, 0x70, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]};
  if (!pcdCalculateCRC(selCL2, 7, crc)) return false;
  selCL2[7] = crc[0]; selCL2[8] = crc[1];
  if (!pcdTransceive(selCL2, 9, buffer, backLen, 100)) return false;

  uidOut[3] = buffer[0]; uidOut[4] = buffer[1]; uidOut[5] = buffer[2]; uidOut[6] = buffer[3];
  uidSizeOut = 7; 
  return true;
}

bool ntagReadPage(byte pageAddr, byte *bufferOut) {
  byte cmd[4];
  byte back[MAX_LEN];
  byte backLen = 0;
  byte crc[2];

  cmd[0] = PICC_READ;
  cmd[1] = pageAddr;
  
  if (!pcdCalculateCRC(cmd, 2, crc)) return false;
  cmd[2] = crc[0]; cmd[3] = crc[1];

  if (!pcdTransceive(cmd, 4, back, backLen, 100)) return false;
  if (backLen < 16) return false; 

  for (byte i = 0; i < 16; i++) bufferOut[i] = back[i];
  return true;
}

bool ntagWritePage(byte pageAddr, byte *data4Byte) {
  byte cmd[8]; 
  byte crc[2];
  unsigned long start, gecenSure;
  byte irq, err, fifoKat;

  cmd[0] = PICC_WRITE; 
  cmd[1] = pageAddr;
  cmd[2] = data4Byte[0];
  cmd[3] = data4Byte[1];
  cmd[4] = data4Byte[2];
  cmd[5] = data4Byte[3];

  if (!pcdCalculateCRC(cmd, 6, crc)) return false;
  cmd[6] = crc[0];
  cmd[7] = crc[1];

  rcWrite(CommandReg, PCD_IDLE);
  rcWrite(FIFOLevelReg, 0x80); 
  rcWrite(ComIrqReg, 0x7F);    
  rcWrite(BitFramingReg, 0x00); 

  for (byte i = 0; i < 8; i++) {
    rcWrite(FIFODataReg, cmd[i]);
  }

  rcWrite(CommandReg, PCD_TRANSCEIVE);
  rcSetBitMask(BitFramingReg, 0x80); 

  start = millis();
  while (true) {
    irq = rcRead(ComIrqReg);
    gecenSure = millis() - start;
    if (irq & 0x21) break; 
    if (gecenSure > 40) break; 
  }
  rcClearBitMask(BitFramingReg, 0x80);

  err = rcRead(ErrorReg);
  fifoKat = rcRead(FIFOLevelReg);
  
  byte ackCevabi = 0xFF;
  if (fifoKat > 0) {
    ackCevabi = rcRead(FIFODataReg) & 0x0F; 
  }

  Serial.print(F(" -> [DEBUG YAZMA v3.2] Süre: ")); Serial.print(gecenSure);
  Serial.print(F("ms | FIFO Alınan: ")); Serial.print(fifoKat);
  Serial.print(F(" | Ham ACK: 0x")); Serial.print(ackCevabi, HEX);
  Serial.print(F(" | ErrorReg: 0x")); Serial.println(err, HEX);

  delay(12); // EEPROM Hücre Kilitleme Toleransı

  if (ackCevabi == 0x0A) {
    return true;
  }
  return false; 
}

void bipTek() { digitalWrite(BUZZER_PIN, HIGH); delay(120); digitalWrite(BUZZER_PIN, LOW); }
void bipHata() { digitalWrite(BUZZER_PIN, HIGH); delay(400); digitalWrite(BUZZER_PIN, LOW); }

void ntagHaritaOkuVeYazTesti() {
  byte fullUid[7];
  byte fullUidSize = 0;

  if (!ntagSelect(fullUid, fullUidSize)) return;

  bipTek();
  Serial.println(F("\n==================================================="));
  Serial.println(F("              NTAG213 ETİKET ALGILANDI             "));
  Serial.println(F("==================================================="));
  
  Serial.print(F("Etiket UID       : "));
  for (byte i = 0; i < fullUidSize; i++) {
    if (fullUid[i] < 16) Serial.print("0");
    Serial.print(fullUid[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // ---------------------------------------------------
  // YENİ ŞİFRE KONTROL KATMANI
  // ---------------------------------------------------
  Serial.println(F("🔒 Şifre kontrol ediliyor..."));
  if (!NTAG213_Authenticate()) {
    Serial.println(F("❌ Şifre Hatalı veya Kart Yanıt Vermedi!"));
    Serial.println(F("⚠️ İşlem İptal Edildi. Kartı Tekrar Gösterin."));
    Serial.println(F("==================================================="));
    bipHata();
    delay(2000); // Kullanıcının kartı çekmesi için süre
    return;      // loop()'un başına dön, alt taraftaki okuma/yazma kodlarına GEÇME!
  }
  // ---------------------------------------------------

  byte okumaTamponu[16];
  bool isimOkundu = false, sirketOkundu = false, krediOkundu = false, zamanOkundu = false;

  for (int deneme = 0; deneme < 3; deneme++) {
    delay(20);
    if (ntagReadPage(4, okumaTamponu)) { isimOkundu = true; break; }
  }
  if (isimOkundu) {
    Serial.print(F("İsim Soyad       : "));
    for (byte i = 0; i < 16; i++) { if (okumaTamponu[i] >= 32 && okumaTamponu[i] <= 126) Serial.print((char)okumaTamponu[i]); }
    Serial.println();
  }

  for (int deneme = 0; deneme < 3; deneme++) {
    delay(20);
    if (ntagReadPage(8, okumaTamponu)) { sirketOkundu = true; break; }
  }
  if (sirketOkundu) {
    Serial.print(F("Şirket Adı       : "));
    for (byte i = 0; i < 16; i++) { if (okumaTamponu[i] >= 32 && okumaTamponu[i] <= 126) Serial.print((char)okumaTamponu[i]); }
    Serial.println();
  }

  uint32_t kalanKredi = 0;
  for (int deneme = 0; deneme < 3; deneme++) {
    delay(20);
    if (ntagReadPage(12, okumaTamponu)) { krediOkundu = true; break; }
  }
  
  if (krediOkundu) {
    uint8_t kapiYetki = okumaTamponu[0]; 
    Serial.print(F("Kapı Yetki (Bit) : ")); Serial.println(kapiYetki);

    String bakiyeStr = "";
    for(int i = 4; i < 8; i++) { 
      if(okumaTamponu[i] >= '0' && okumaTamponu[i] <= '9') {
        bakiyeStr += (char)okumaTamponu[i]; 
      }
    }

    if (bakiyeStr.length() > 0) {
      kalanKredi = bakiyeStr.toInt();
    } else {
      kalanKredi = ((uint32_t)okumaTamponu[7] << 24) | ((uint32_t)okumaTamponu[6] << 16) | ((uint32_t)okumaTamponu[5] << 8) | okumaTamponu[4];
    }
    Serial.print(F("Mevcut Kredi     : ")); Serial.println(kalanKredi);
  }

  for (int deneme = 0; deneme < 3; deneme++) {
    delay(20);
    if (ntagReadPage(15, okumaTamponu)) { zamanOkundu = true; break; }
  }
  if (zamanOkundu) {
    String zamanStr = ""; bool asciiZaman = false;
    if (okumaTamponu[0] >= '0' && okumaTamponu[0] <= '9') {
      asciiZaman = true;
      for(int i = 0; i < 12; i++) { if (okumaTamponu[i] >= '0' && okumaTamponu[i] <= '9') zamanStr += (char)okumaTamponu[i]; }
    }
    unsigned long unixZamani = 0;
    if (asciiZaman && zamanStr.length() >= 9) {
      if(zamanStr.length() > 10) zamanStr = zamanStr.substring(0, 10);
      unixZamani = strtoul(zamanStr.c_str(), NULL, 10);
    } else {
      unixZamani = ((uint32_t)okumaTamponu[3] << 24) | ((uint32_t)okumaTamponu[2] << 16) | ((uint32_t)okumaTamponu[1] << 8) | okumaTamponu[0];
    }
    uint8_t hamKartTipi = okumaTamponu[12]; uint8_t hamAktarma  = okumaTamponu[13];      
    uint8_t kartTipi = (hamKartTipi >= '0' && hamKartTipi <= '9') ? (hamKartTipi - '0') : hamKartTipi;
    uint8_t aktarmaDurumu = (hamAktarma >= '0' && hamAktarma <= '9') ? (hamAktarma - '0') : hamAktarma;

    Serial.print(F("Zaman Damgası    : ")); Serial.println(unixZamani);
    Serial.print(F("Kart Tipi Kodu   : ")); Serial.println(kartTipi);
    Serial.print(F("Kart Tipi Açıkl. : ")); if(kartTipi < 5) Serial.println(KART_TIPLERI[kartTipi]); else Serial.println(F("Bilinmeyen Tip"));
    Serial.print(F("Aktarma Durumu   : ")); Serial.println(aktarmaDurumu);
  }

  if (isimOkundu && sirketOkundu && krediOkundu && zamanOkundu) {
    Serial.println(F("---------------------------------------------------"));
    Serial.println(F("Okuma Başarılı. Kredi Güncelleniyor (Sayfa 13)..."));

    int dinamikSayac;
    EEPROM.get(eepromAdres, dinamikSayac);
    if (dinamikSayac < 1000 || dinamikSayac > 9999) dinamikSayac = 1000;

    String yaziKredi = String(dinamikSayac);
    byte yazmaTamponu[4];
    yazmaTamponu[0] = yaziKredi[0];
    yazmaTamponu[1] = yaziKredi[1];
    yazmaTamponu[2] = yaziKredi[2];
    yazmaTamponu[3] = yaziKredi[3];

    bool yazmaBasarili = false;
    int yazmaDenemeKalan = 3;

    while (yazmaDenemeKalan > 0) {
      if (ntagWritePage(13, yazmaTamponu)) {
        yazmaBasarili = true;
        break; 
      }
      yazmaDenemeKalan--;
      if(yazmaDenemeKalan > 0) {
        Serial.println(F("⚠️ Sinyal kaçtı veya ACK gelmedi. Kart uyandırtılıp yeniden seçiliyor..."));
        delay(15); 
        
        byte reUid[7]; byte reSize;
        ntagSelect(reUid, reSize); 
      }
    }

    if (yazmaBasarili) {
      Serial.print(F("✅ BAŞARILI! Sayfa 13 Güncellendi. Yeni Kredi: ")); Serial.println(dinamikSayac);
      dinamikSayac++;
      EEPROM.put(eepromAdres, dinamikSayac);
    } else {
      Serial.println(F("❌ HATA: Kart canlandırılmasına rağmen 3 denemede de yazmayı onaylamadı!"));
      bipHata();
    }
  }

  Serial.println(F("===================================================\n"));
  delay(3000); 
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  SPI.begin();
  
  pinMode(SS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  delay(50);
  digitalWrite(RST_PIN, HIGH);
  
  // pcdinit() artık içeride otomatik olarak anten kazancını da maksimuma çıkarıyor
  pcdinit(); 
  
  byte v = rcRead(VersionReg);
  if (v == 0x00 || v == 0xFF) {
    Serial.println(F("❌ MFRC522 Okuyucu Bulunamadı!"));
    while(1); 
  }
  
  Serial.print(F("✅ MFRC522 Okuyucu Hazır. Versiyon: 0x")); Serial.println(v, HEX);
  Serial.println(F("Lütfen Yazma Kontrolü İçin Bir NTAG213 Etiketi Gösterin...\n"));
}

void loop() {
  ntagHaritaOkuVeYazTesti();
  delay(10);
}
