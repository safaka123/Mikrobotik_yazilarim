// ŞİFRE KONTROL PROGRAMI
// bu program ile NTAG etiketine yazdığınız şifreyi kontrol edebilirsiniz
// benim programlarımda şifre 4 byte olarak S A F K (0x53 0x41 0x46 0x4B)
// şeklinde yazıldığı için bu şifreyi hemen doğrular. 
// fakat kendiniz şifre koyduysanız bu şifreleri aşağıda çeşitli şekillerde yazarak kontrol edebilirsiniz. 
// şifrenizi unutursanız ya da yazarken erken çekip yarım yazdırdıysanız artık etiketi başka programlarla okuyamazsınız atmak zorundasınız
// şifre yazma tamamlandı ibaresini göresiye kadar etiketi çekmeyin. 



#include <SPI.h>

// --- PIN TANIMLAMALARI ---
const int chipSelectPin = 10;
const int resetPin      = 3;
const int PN532_IRQ     = 2; 

// --- PROTOKOL SABİTLERİ ---
#define PN532_SPI_STATREAD  0x40 
#define PN532_SPI_DATAWRITE 0x80 
#define PN532_SPI_DATAREAD  0xC0 
#define PN532_COMMAND_INCOMMUNICATETHRU 0x42 // Bulduğun koddaki kritik komut

uint8_t reverseABit(uint8_t x) {
  x = ((x & 0x55) << 1) | ((x & 0xAA) >> 1);
  x = ((x & 0x33) << 2) | ((x & 0xCC) >> 2);
  x = ((x & 0x0F) << 4) | ((x & 0xF0) >> 4);
  return x;
}

bool pn532_waitReady(uint16_t timeout) {
  uint32_t t = millis();
  while (millis() - t < timeout) {
    if (digitalRead(PN532_IRQ) == LOW) {
      digitalWrite(chipSelectPin, LOW);
      SPI.transfer(PN532_SPI_STATREAD);
      uint8_t r = reverseABit(SPI.transfer(0x00));
      digitalWrite(chipSelectPin, HIGH);
      if (r == 0x01) return true;
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

// --- YENİ ŞİFRE DOĞRULAMA (0x42 TÜNEL METODU) ---
bool try_auth_with_tunnel(uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, const char* label) {
  Serial.print("Deneniyor (Tünel 0x42): "); Serial.println(label);
  
  // Paket: D4 (1) + 42 (1) + 1B (1) + PWD (4) = TOPLAM 7 BYTE
  uint8_t cmd[7] = {0xD4, 0x42, 0x1B, p0, p1, p2, p3};
  pn532_writeFrame(cmd, 7); // Burada uzunluğu 7 olarak gönderiyoruz
  
  if (!pn532_waitReady(100)) { Serial.println("ACK Bekleme Hatası"); return false; }
  pn532_readAck();

  if (!pn532_waitReady(200)) { Serial.println("Kart Cevap Vermedi"); return false; }

  digitalWrite(chipSelectPin, LOW);
  SPI.transfer(PN532_SPI_DATAREAD);
  
  uint8_t res[20];
  for (int i = 0; i < 20; i++) res[i] = reverseABit(SPI.transfer(0x00));
  digitalWrite(chipSelectPin, HIGH);

  for (int i = 0; i < 12; i++) {
    if (res[i] == 0xD5 && res[i+1] == 0x43) {
      uint8_t status = res[i+2];
      if (status == 0x00) {
        Serial.print(">>> BAŞARILI! PACK: ");
        Serial.print(res[i+3], HEX); Serial.print(" "); Serial.println(res[i+4], HEX);
        return true;
      } else {
        Serial.print("HATA (Status: "); Serial.print(status, HEX); Serial.println(")");
        return false;
      }
    }
  }
  Serial.println("Yanıt Yapısı Tanınamadı");
  return false;
}

void setup() {
  Serial.begin(115200);
  pinMode(PN532_IRQ, INPUT_PULLUP);
  pinMode(chipSelectPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, LOW); delay(50); digitalWrite(resetPin, HIGH); delay(50);

  SPI.begin();
  SPI.beginTransaction(SPISettings(300000, MSBFIRST, SPI_MODE0));

  // SAM Config
  uint8_t samCmd[] = {0xD4, 0x14, 0x01, 0x14, 0x01};
  pn532_writeFrame(samCmd, 5);
  pn532_waitReady(100); pn532_readAck();

  Serial.println("Yeni Tünel Metodu Hazır. Kart Bekleniyor...");
}

void loop() {
  uint8_t uid[10], uidLen;
  uint8_t cmd[] = {0xD4, 0x4A, 0x01, 0x00}; // Kartı bul
  pn532_writeFrame(cmd, 4);
  
  if (pn532_waitReady(200)) {// ==============  burada şifre olarak koyduğunuzu unutursanız değişik şifreler deneyebilirsiniz. 
    pn532_readAck();
    if (pn532_waitReady(300)) {
       Serial.println("\n--- KART ALGILANDI ---");
       
       // Şifre: S A F K (0x53 0x41 0x46 0x4B)
       uint8_t s=0x53, a=0x41, f=0x46, k=0x4B;
       // Bit-reversal hali (Senin SPI yazma mantığın için)
       uint8_t rs=reverseABit(s), ra=reverseABit(a), rf=reverseABit(f), rk=reverseABit(k);

       // 1. Düz ASCII
       if (try_auth_with_tunnel(s, a, f, k, "S-A-F-K")) goto bulundu;
       
       // 2. Ters Byte sırası
       if (try_auth_with_tunnel(k, f, a, s, "K-F-A-S")) goto bulundu;

       // 3. Aynalanmış Byte'lar (Bit reversal)
       if (try_auth_with_tunnel(rs, ra, rf, rk, "rev-S-A-F-K")) goto bulundu;
       
       // 4. Aynalanmış + Ters sıra
       if (try_auth_with_tunnel(rk, rf, ra, rs, "rev-K-F-A-S")) goto bulundu;

       Serial.println("Sonuç: Hiçbiri tutmadı.");
       goto bitti;

       bulundu:
       Serial.println("TEBRİKLER! ŞİFRE DOĞRU.");
       
       bitti:
       delay(5000);
    }
  }
  delay(200);
}
