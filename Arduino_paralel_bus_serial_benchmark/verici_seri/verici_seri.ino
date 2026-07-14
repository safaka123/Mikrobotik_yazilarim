#define DATA_PIN  4
#define CLOCK_PIN 5
#define LATCH_PIN 6

const char testCumlesi[] = "Mikrobotik Elektronik Platformu ile donanim ve yazilim mantigini kutuphanesiz ogreniyoruz. Bu deney paralel ve seri haberlesme hiz farkini gosterir.";

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  
  pinMode(8, OUTPUT); // STROBE Pini (PORTB0)
  pinMode(A1, INPUT); // ACK Giriş Pini (PINC1)
  
  PORTB &= B11111110; // STROBE = LOW
  
  Serial.begin(115200);
  delay(2000); 
  yarisiBaslat();
}

void loop() {
  // Yarış bir kez çalışıp duracak
}

void yarisiBaslat() {
  int cumleUzunlugu = sizeof(testCumlesi) - 1; 
  
  // ----------------------------------------------------
  // ETAP 1: PARALEL VERİYOLU YARIŞI
  // ----------------------------------------------------
  for (int i = 0; i < cumleUzunlugu; i++) {
    paralelKarakterGonder(testCumlesi[i]);
  }
  paralelKarakterGonder('\0'); 
  
  entegreyeTemizlikBas(0xFF); // Hattı seri porta devret
  delay(100); 
  
  // ----------------------------------------------------
  // ETAP 2: SERİ HABERLEŞME YARIŞI (115200 Baud)
  // ----------------------------------------------------
  for (int i = 0; i < cumleUzunlugu; i++) {
    Serial.write(testCumlesi[i]);
  }
  Serial.write('\n'); 
}

void paralelKarakterGonder(char c) {
  // 1. 74HC595 entegresine veriyi yükle ve dışarı bas
  digitalWrite(LATCH_PIN, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, (c >> i) & 1);
    digitalWrite(CLOCK_PIN, HIGH);
  }
  digitalWrite(LATCH_PIN, HIGH); 

  // 2. Alıcıya "Veri hazır" diyoruz: STROBE (D8 - PORTB0) HIGH yap ve öyle bırak!
  PORTB |= B00000001;  
  
  // 3. Alıcı işini bitirip ACK (A1 - PINC1) sinyalini HIGH yapana kadar BURADA KİLİTLEN
  while ( !(PINC & B00000010) ) {}
  
  // 4. Alıcı veriyi aldı! STROBE sinyalini kapatıyoruz: LOW
  PORTB &= B11111110;  
  
  // 5. Alıcı bizim STROBE'u kapattığımızı görüp kendi ACK sinyalini LOW yapana kadar BURADA KİLİTLEN
  while (PINC & B00000010) {}
  
  // Döngü bitti, iki taraf da tertemiz sıfıra indi. Yeni karaktere geçebiliriz!
}

void entegreyeTemizlikBas(byte veri) {// bu 74hc595 entegresinin işi bittiğinde tüm bitlerinin HIGH seviyesinde kalmasını sağlar. 
                                      // Alıcı arduino RX girişinde çakışma olmasın paralel ve seri çalışmada sorunsuz çalışsın,
                                      // diye diyotlar konulmuştur. pull up direnç konulmuştur. 
  digitalWrite(LATCH_PIN, LOW);
  for (int i = 7; i >= 0; i--) {
    digitalWrite(CLOCK_PIN, LOW);
    digitalWrite(DATA_PIN, (veri >> i) & 1);// veri değişkeni yani 74hc595 tüm çıkış bitleri 1 oluyor. AND işlemiyle. 
    digitalWrite(CLOCK_PIN, HIGH);
  }
  digitalWrite(LATCH_PIN, HIGH);
}
