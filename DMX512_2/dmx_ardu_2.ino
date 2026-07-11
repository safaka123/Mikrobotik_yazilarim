#include <SoftwareSerial.h>

// SoftwareSerial tanımlaması: RX=11 (Boşta), TX=10 (FT232RL RX ucuna bağlanacak)
SoftwareSerial debugSerial(11, 10);


#define DMX_START_ADDRESS 4 

// Debug Gösterge Pinleri
#define DEBUG_PIN_BREAK        A0  // BREAK başarıyla doğrulandığında yanar
#define DEBUG_PIN_STARTCODE    A1  // Start Code (0x00) doğruysa yanar
#define DEBUG_PIN_ERROR        A2  // Genel paket/sayaç hatası varsa yanar
#define DEBUG_PIN_FRAME_ERROR  A3  // Donanımsal Çerçeve Hatası (FE0) durumunda yanar

enum DMX_State {
  STATE_WAIT_BREAK,
  STATE_READ_DATA
};

volatile DMX_State current_state = STATE_WAIT_BREAK;
volatile uint16_t channel_counter = 0;
volatile uint8_t r_val = 0, g_val = 0, b_val = 0;
volatile bool dmx_data_ready = false;

volatile unsigned long break_start_time = 0;

void init_hardware(void);

void setup() {
  init_hardware();
}

void loop() {
  if (dmx_data_ready) {
    // RGB Sürücü çıkışları (Donanımsal PWM)
    analogWrite(3, r_val);
    analogWrite(5, g_val);
    analogWrite(6, b_val);

        // --- SOFTWARE SERIAL DEBUG LOG KATMANI ---
    //debugSerial.print(F("START_ADDR [")); debugSerial.print(DMX_START_ADDRESS); debugSerial.print(F("] -> "));
    //debugSerial.print(F("R:")); debugSerial.print(r_val);
    //debugSerial.print(F(" | G:")); debugSerial.print(g_val);
    //debugSerial.print(F(" | B:")); debugSerial.println(b_val); 

    dmx_data_ready = false; 
    current_state = STATE_WAIT_BREAK;

    // Paket işlendi, durum LED'lerini söndür
    digitalWrite(DEBUG_PIN_BREAK, LOW);
    digitalWrite(DEBUG_PIN_STARTCODE, LOW);
  }
}

void init_hardware(void) {
  pinMode(3, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  
  pinMode(DEBUG_PIN_BREAK, OUTPUT);
  pinMode(DEBUG_PIN_STARTCODE, OUTPUT);
  pinMode(DEBUG_PIN_ERROR, OUTPUT);
  pinMode(DEBUG_PIN_FRAME_ERROR, OUTPUT);

  pinMode(2, INPUT); // INT0 Pini (75176 RO ucuna bağlı)

  //debugSerial.begin(9600);
  //debugSerial.println(F("--- DMX Orijinal Standart Kod Yuklendi (9600 Baud) ---"));

  // Donanımsal USART Ayarları (250 kbps, 8-N-2)
  UBRR0H = 0;
  UBRR0L = 3; 
  UCSR0A = 0x00;
  UCSR0C = (1 << USBS0) | (3 << UCSZ00); 
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0);  

  // INT0 Dış Kesme Ayarı: Her lojik değişimde tetiklensin
  EICRA = (1 << ISC00); 
  EIMSK = (1 << INT0);  

  sei(); 
}

// 1. ADIM: BREAK Sinyali Zaman Ölçümü (Dış Kesme)
ISR(INT0_vect) {
  // Hat LOW'a düştüyse (BREAK Başlangıcı)
  if ((PIND & (1 << PORTD2)) == 0) {
    break_start_time = micros(); 
  } 
  // Hat HIGH'a çıktıysa (BREAK Bitişi / MAB Başlangıcı)
  else {
    unsigned long break_duration = micros() - break_start_time; 
    
    // --- İNCE AYAR: TOLERANS ARALIĞINI GENİŞLETTİK (80us - 250us) ---
    // Vericinin jitter (zaman kayması) yapma ihtimaline karşı aralığı esnettik.
    if (break_duration >= 80 && break_duration <= 250) {
      
      // Donanımsal USART tamponunu tamamen boşaltıp resetliyoruz
      uint8_t dummy;
      while (UCSR0A & (1 << RXC0)) { dummy = UDR0; } 
      
      channel_counter = 0;
      current_state = STATE_READ_DATA; 
      
      PORTC |= (1 << PORTC0); // A0 (BREAK OK) LED'ini yak
    } else {
      // Sinyal bu aralığın dışındaysa anlık hata ledini kırpıştır
      PORTC |= (1 << PORTC2); // A2 HIGH
      PORTC &= ~(1 << PORTC2); // A2 LOW
    }
  }
}

// 2. ADIM: Donanımsal Veri Okuma (USART Kesmesi)
ISR(USART_RX_vect) {
  uint8_t status = UCSR0A;     
  uint8_t incoming_byte = UDR0; 

  // Donanımsal Çerçeve Hatası Kontrolü (FE0)
  if (status & (1 << FE0)) {
    PORTC |= (1 << PORTC3);  // A3 (Frame Error LED) yak
    current_state = STATE_WAIT_BREAK;
    PORTC &= ~(1 << PORTC0); 
    PORTC &= ~(1 << PORTC1); 
    return;
  }

  if (current_state != STATE_READ_DATA) return;

  // Kanalları Süzme Bölümü
  if (channel_counter == 0) {
    if (incoming_byte == 0x00) {
      PORTC |= (1 << PORTC1);  // A1 (Start Code OK) LED'ini yak
      PORTC &= ~(1 << PORTC3); // Frame Error LED'ini söndür
    } else {
      current_state = STATE_WAIT_BREAK;
      PORTC &= ~(1 << PORTC0); 
      PORTC &= ~(1 << PORTC1); 
      return;
    }
  }
  else if (channel_counter == DMX_START_ADDRESS) {
    r_val = incoming_byte;
  } 
  else if (channel_counter == DMX_START_ADDRESS + 1) {
    g_val = incoming_byte;
  } 
  else if (channel_counter == DMX_START_ADDRESS + 2) {
    b_val = incoming_byte;
    dmx_data_ready = true; // 3 kanal tamam, loop'u tetikle
  }

  channel_counter++;

  // 512 kanal taşma koruması
  if (channel_counter > 512) {
    current_state = STATE_WAIT_BREAK;
  }
}
