#include <SPI.h>
#include <MFRC522.h>

// RC522 pinleri
#define SS_PIN 10      // SDA / SS
#define RST_PIN 9      // RST

MFRC522 mfrc522(SS_PIN, RST_PIN); // Modül nesnesi

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  Serial.println("RC522 hazir. Anten kazanci maksimum yapiliyor...");

  // Kazancı maksimum (48 dB) yap
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  // Alternatif & garanti yöntem (48 dB = 0xC0)
  // mfrc522.PCD_WriteRegister(RFCfgReg, 0xC0);

  // Anteni aktif et
  mfrc522.PCD_AntennaOn();

  Serial.println("Anten kazanci MAX -> 48 dB (0xC0)");
  Serial.println("Kart okutunuz...");
}

void loop() {
  // Kart algılanmadıysa çık
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Kart UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Kart türünü göster
  byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print("Kart tipi: ");
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  delay(2000);
}
