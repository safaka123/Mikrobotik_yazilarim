#include <SPI.h>

// --- PIN TANIMLAMALARI ---
const int chipSelectPin = 10;
const int resetPin      = 3;
const int PN532_IRQ     = 2; 

// --- PROTOKOL SABİTLERİ ---
#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 

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

  SPI.transfer(reverseABit(0x00));
  SPI.transfer(reverseABit(0x00));
  SPI.transfer(reverseABit(0xFF));

  SPI.transfer(reverseABit(len));
  SPI.transfer(reverseABit(0x100 - len));

  for (int i = 0; i < len; i++) {
    SPI.transfer(reverseABit(data[i]));
  }

  SPI.transfer(reverseABit(dcs));
  SPI.transfer(reverseABit(0x00));

  digitalWrite(chipSelectPin, HIGH);
}

// --- KART OKUMA (UID + SAK) ---
bool pn532_readCard(uint8_t *uid, uint8_t &uidLen, uint8_t &sak) {

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

      reverseABit(SPI.transfer(0x00)); // NbTg
      reverseABit(SPI.transfer(0x00)); // Tg

      reverseABit(SPI.transfer(0x00)); // ATQA
      reverseABit(SPI.transfer(0x00)); // ATQA

      sak = reverseABit(SPI.transfer(0x00)); // 🔥 Kart tipi

      uidLen = reverseABit(SPI.transfer(0x00));

      for (int k = 0; k < uidLen; k++) {
        uid[k] = reverseABit(SPI.transfer(0x00));
      }
      Serial.print("UID Length: ");
      Serial.println(uidLen);
      break;
    }
  }

  digitalWrite(chipSelectPin, HIGH);
  return found;
}

// --- SETUP ---
void setup() {
  Serial.begin(115200);

  pinMode(PN532_IRQ, INPUT_PULLUP);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(resetPin, OUTPUT);

  digitalWrite(resetPin, LOW); delay(50);
  digitalWrite(resetPin, HIGH); delay(50);

  SPI.begin();
  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE0));

  // SAM CONFIG
  uint8_t samCmd[] = {0xD4, 0x14, 0x01, 0x14, 0x01};
  pn532_writeFrame(samCmd, 5);
  pn532_waitReady(100);
  pn532_readAck();

  Serial.println("PN532 Hazir");
  Serial.println("Kart Gosterin...");
}

// --- LOOP ---
void loop() {

  uint8_t uid[10], uidLen, sak;

  if (pn532_readCard(uid, uidLen, sak)) {

    Serial.println("\n--- KART OKUNDU ---");

    Serial.print("UID: ");
    for (int i = 0; i < uidLen; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i], HEX); Serial.print(" ");
    }
    Serial.println();

    Serial.print("SAK: ");
    Serial.println(sak, HEX);

    // --- KART TİPİ ---
    if (sak == 0x08 || sak == 0x18) {
      Serial.println(">>> MIFARE CLASSIC");

    } else if (sak == 0x00) {
      Serial.println(">>> NTAG / ULTRALIGHT");

    } else {
      Serial.println(">>> BILINMEYEN KART");
    }

    Serial.println("\nKarti cekin...");
    delay(3000);
  }
}
