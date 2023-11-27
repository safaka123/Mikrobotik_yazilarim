// LED'in bağlı olduğu pin numarasını tanımla
const int ledPin = 13;

void setup() {
  // Setup kodları buraya yazılır ve sadece bir kez çalışır

  // LED pinini çıkış olarak ayarla
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Loop kodları buraya yazılır ve sürekli olarak çalışır

  // LED'i aç
  digitalWrite(ledPin, HIGH);

  // 1000 milisaniye (1 saniye) bekle
  delay(1000);

  // LED'i kapat
  digitalWrite(ledPin, LOW);

  // 1000 milisaniye (1 saniye) bekle
  delay(1000);
}
