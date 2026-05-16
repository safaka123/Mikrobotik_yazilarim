#include <SPI.h>

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

void readSectorBlocks(uint8_t b1, uint8_t b2, uint8_t b3) {
  uint8_t buffer[16];
  uint8_t blocks[] = {b1, b2, b3};

  for (int i = 0; i < 3; i++) {
    if (pn532_readBlock(blocks[i], buffer)) {
      Serial.print("  [SUCCESS] Block "); Serial.print(blocks[i]); Serial.print(": ");
      for (int j = 0; j < 16; j++) {
        if (buffer[j] < 0x10) Serial.print("0");
        Serial.print(buffer[j], HEX); Serial.print(" ");
      }
      Serial.println();
    } else {
      Serial.print("  [ERROR] Read failed: "); Serial.println(blocks[i]);
    }
  }
}


#define PN532_IRQ (2) // Arduino D2 pini

bool isDataReady() {
  // P70_IRQ hattı LOW (0) ise veri hazırdır
  return (digitalRead(PN532_IRQ) == LOW);
}

// -------------------------------
// Mifare Classic Write Block
// -------------------------------
bool pn532_writeBlock(uint8_t blockAddr, uint8_t *buffer) {
  // Komut: 0xD4, 0x40 (InDataExchange), 0x01 (Target 1), 0xA0 (Mifare Write)
  // Devamı: BlockAddr, Data (16 byte)
  uint8_t cmd[20];
  cmd[0] = 0xD4;
  cmd[1] = 0x40; 
  cmd[2] = 0x01; 
  cmd[3] = 0xA0; // 0xA0 = Mifare Write
  cmd[4] = blockAddr;
  
  for (int i = 0; i < 16; i++) cmd[5 + i] = buffer[i];

  pn532_writeFrame(cmd, 21); // 5 (header) + 16 (data) = 21 byte

  if (!pn532_waitReady(100)) return false;
  pn532_readAck();
  if (!pn532_waitReady(100)) return false;

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);

  bool success = false;
  for (int i = 0; i < 20; i++) {
    uint8_t d = reverseABit(SPI.transfer(0x00));
    if (d == 0xD5) {
      if (reverseABit(SPI.transfer(0x00)) == 0x41) {
        if (reverseABit(SPI.transfer(0x00)) == 0x00) { // Status OK
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

// -------------------------------
// KAPI KONTROL ETME
// -------------------------------

bool checkDoorBitmask(uint8_t *block6, int doorNumber) {

  if (doorNumber < 1 || doorNumber > 16) return false;

  int bitIndex = doorNumber - 1;

  int byteIndex = bitIndex / 8;   // 0 veya 1
  int bitPos    = bitIndex % 8;

  uint8_t value = block6[byteIndex];

  // LSB -> bit0
  if (value & (1 << bitPos)) {
    return true;
  }

  return false;
}




/*bool checkDoorAccess(String company, String doors, int myDoor) {

  // şirket kontrolü
  if (company != "izbb") {
    Serial.println("Sirket uyusmuyor!");
    return false;
  }

  // kapı listesi içinde var mı?
  String doorStr = String(myDoor);

  if (doors.indexOf(doorStr) != -1) {
    return true;
  }

  return false;
}
*/


// -------------------------------
// BLOK 6 KAPI NUMARALARINI ASCII ŞEKLİNE DÖNÜŞTÜRÜYOR. 
// -------------------------------

String bitmaskToString(uint8_t *block6) {

  String result = "";

  for (int door = 1; door <= 16; door++) {

    int bitIndex = door - 1;
    int byteIndex = bitIndex / 8;
    int bitPos = bitIndex % 8;

    if (block6[byteIndex] & (1 << bitPos)) {

      if (result.length() > 0) result += ",";
      result += String(door);
    }
  }

  return result;
}


// -------------------------------
// SETUP
// -------------------------------
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

  int myDoor = 2;// OKUYUCU KAPI NO BURADA DEĞİŞTİR. YA DA DIPSWITCH OLARAK YAP. 
  
  uint8_t uid[10];
  uint8_t uidLen;

  uint8_t keyB[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 

  // SADECE GEREKEN BLOKLAR
  uint8_t sectorData[3][16]; 
  bool successFlags[3];

  uint8_t targetBlocks[] = {4, 5, 6};

  if (pn532_readUID(uid, uidLen)) {

    Serial.println("\n--- KAPI OKUMA ---");

    // -------- BLOK OKUMA --------
    for (int i = 0; i < 3; i++) {

      uint8_t target = targetBlocks[i];
      uint8_t authGate = 6; // 4-5-6 aynı sector

      successFlags[i] = false;

      // KRİTİK DELAY (KORUNDU)
      delay(100);

      // AUTH
      if (pn532_mifareAuthenticate(uid, uidLen, authGate, 1, keyB)) {

        // IRQ BEKLE
        uint32_t irqStart = millis();
        while (digitalRead(PN532_IRQ) == HIGH && (millis() - irqStart < 50));

        delay(5); // STABİLİZASYON

        // OKUMA
        if (pn532_readBlock(target, sectorData[i])) {
          successFlags[i] = true;
          Serial.print("B"); Serial.print(target); Serial.print(":OK ");
        } else {
          Serial.print("B"); Serial.print(target); Serial.print(":RE ");
        }

      } else {
        Serial.print("B"); Serial.print(target); Serial.print(":AE ");
      }
    }

    // -------- RAPOR --------
    Serial.println("\n\n--- OKUMA SONUCU ---");

    for (int i = 0; i < 3; i++) {
      Serial.print("Block "); Serial.print(targetBlocks[i]); Serial.print(": ");

      if (successFlags[i]) {
        for (int j = 0; j < 16; j++) {
          char c = (char)sectorData[i][j];
          if (c >= 32 && c <= 126) Serial.print(c);
          else Serial.print(".");
        }
      } else {
        Serial.print("Hata");
      }

      Serial.println();
    }

    // -------- KAPI KONTROL --------
    if (successFlags[0] && successFlags[1] && successFlags[2]) {

      String name    = blockToString(sectorData[0]); // 4
      String company = blockToString(sectorData[1]); // 5
      String doors   = blockToString(sectorData[2]); // 6

      Serial.println("\n--- KAPI KONTROL ---");
      Serial.print("Isim: "); Serial.println(name);
      Serial.print("Sirket: "); Serial.println(company);
      //Serial.print("Yetkiler: "); Serial.println(doors);
      String doorList = bitmaskToString(sectorData[2]);

      Serial.print("Yetkili Kapilar: ");
      Serial.println(doorList);

      Serial.print("Bu Okuyucu Kapisi: ");
      Serial.println(myDoor);

      
      bool companyOK = (company == "izbb");
      bool doorOK = checkDoorBitmask(sectorData[2], myDoor);
      
      if (!companyOK) {

        Serial.println(">>> YETKISIZ ERISIM (SIRKET HATALI)");
        BIP_BIP();

      } else if (!doorOK) {

                Serial.println(">>> YETKISIZ ERISIM (KAPI YETKISI YOK)");
                BIP_BIP();

      } else {

            Serial.println(">>> KAPI ACILDI");
        BIP();
        }
    } else {
      Serial.println(">>> OKUMA HATASI - ERISIM RED");
      BIP_BIP();
    }

    // KARTI CEKME SURESI (KORUNDU)
    delay(2000);
  }
}
