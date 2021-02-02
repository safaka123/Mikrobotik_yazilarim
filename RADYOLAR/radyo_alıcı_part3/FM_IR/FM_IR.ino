// herhangbir TV kumandasi ile kontrol. yazan ve programi derleyen Mustafa Avci.
//Bunun icin asagidaki kütüp haneleri kullanmak lazim.
//IR kommando icin /IRremote.ArduinoIRremote gibi. Serial monitorda komandonun kodlarin okuyup yazili 
//olan kodlarla degistirmek lazim.
///lcd icin LiquidCrystal_I2C.h kütüphanesi lazim. bazen adress lcd(027,16,2); bazende (0x3F,16,2);
// Tea 5767 icin cok program var benimki tea5767N-master olacak, kütüphaneye  baglamak, almak lazim.
//Yöresel istasyonlari mutlaka kendiniz vermeniz lazim. Frekanslari bilmezseniz baska bir radyo ile 
// Tespit etmek mümküm ben öyle yaptim. Tea kendiside istasyon arayabilir ama bunun icin Tea5767N kütüphane
//sini inceleyebilirsiniz video 3 cü bölümde bu konuda yeteri bilgi var.


#include <Wire.h>
#include <IRremote.h>
int RECV_PIN = 11; 
IRrecv irrecv(RECV_PIN); 
decode_results results;
////////////////////////////// 
#include <Wire.h>
#include <TEA5767N.h>
TEA5767N radio = TEA5767N();
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
pinMode(RECV_PIN, INPUT);
irrecv.enableIRIn();
Serial.begin(9600);
lcd.clear(); 
Wire.begin(); 
lcd.backlight(); 
radio.selectFrequency(91.3);
lcd.print("SRF3");
lcd.setCursor(0,1);
lcd.print("91.3 MHz");
Wire.beginTransmission(0x60); //writing TEA5767

Wire.write(0x17);
Wire.write(0x20);
Wire.write(0xB0);
Wire.write(0x10);
Wire.write(0x00);
Wire.endTransmission();
} 

void loop() 
{ 
  int i=0; 
  if (irrecv.decode(&results)) 
  {
    translateIR();
    unknownRemoter();
    irrecv.resume(); 
  } 
 }    
    void translateIR() 
    {
      switch(results.value)
      {
      case 0x94F37EE4: /// kanal  1
      lcd.clear();
      lcd.print("SWR3");
      lcd.setCursor(0,1);
      lcd.print("93.3 MHz");      
      radio.selectFrequency(91.3); 
      break; 
      
       case 0xF61D79DE://////////////// kanal 2
      lcd.clear();
      lcd.print("SRF2");
      lcd.setCursor(0,1); 
      lcd.print("98.75");
      radio.selectFrequency(98.75); 
      break; 
      
       case 0x81772F84:////////////Kanal 3
      lcd.clear(); 
      lcd.print("104 MHz");
      lcd.setCursor(0,1); 
      lcd.print("");
      radio.selectFrequency(104.0);       
      break; 
      
        case 0x4D91BBBE:////////////Kanal 4
      lcd.clear(); 
      lcd.print("105.55");
      lcd.setCursor(0,1); 
      lcd.print("");
      radio.selectFrequency(105.55);       
      break;  
      
 case 0xC7695F20://///////Kanal 5
      lcd.clear(); 
      lcd.print("107  MHz");
      lcd.setCursor(0,1); 
      lcd.print("RSI rete uno");
      radio.selectFrequency(106.20);       
      break;  
      
      case 0x8AC8FA2:////// Kanal 6
      lcd.clear(); 
      lcd.print("107.80 MHz");
      lcd.setCursor(0,1); lcd.print("RSI rete uno");
      radio.selectFrequency(107.8);       
      break; 
      
        case 0x95D2E7E4:///////////// Kanal 7
      lcd.clear(); 
      lcd.print("89.8 MHz");
      lcd.setCursor(0,1); lcd.print("");
      radio.selectFrequency(89.8);       
      break;  

       case 0x1353935E: //////////////Kanal 8
       lcd.clear();
      lcd.print("90.65 MZ ");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(90.65);       
      break; 
       
       case 0xCC7E81C8://///////Kanal 9
       lcd.clear();
      lcd.print("Klassik");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(91.60);       
      break; 
      
       case 0x23EAE8C2://///////Kanal 0
       lcd.clear();
      lcd.print("kKassik");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");

      radio.selectFrequency(92.00);       
      break; 

       case 0x3641054C://///////Kanal subtitle
       lcd.clear();
      lcd.print("Argovia");
      lcd.setCursor(0,1); lcd.print("94.00 MHz");
      radio.selectFrequency(94.00);       
      break; 
      
        case 0xCBE92448://///////  I>
        lcd.clear();
      lcd.print("Bayern");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(95.10);       
      break; 
   
          case 0xC2E35B04:///////// II 
          lcd.clear();
      lcd.print("Oesterreich");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(95.70);       
      break; 
   
      case 0x6AC61222://///////  stop taste []
      lcd.clear();
      lcd.print("Kanal k");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(96.30);       
      break; 
      
      case 0x4559419A:///////// Audio 
      lcd.clear();
      lcd.print("");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(97.00);       
      break; 
      
        case 0x56E6BC1E:///////// diskmenu
        lcd.clear();
      lcd.print("");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(98.75);       
      break; 
      
        case 0x11DB53E4:///////// menü
        lcd.clear();
      lcd.print("");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(101.50);       
      break; 

      case 0x47FC096B:///////// Tools
      lcd.clear();
      lcd.print("Kanal K");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(103.40);       
      break; 
      
      case 0x66387AC0:///////// info
      lcd.clear();
      lcd.print("");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(105.60);       
      break; 
     /////////// 
      case 0xD04CFC60:///////// video yukari ^
      lcd.clear();
      lcd.print("Kanal ka");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(106.20);       
     break; 
    

      case 0x61DB14E2:///////// video ASAGI
      lcd.clear();
      lcd.print("SEEFUNK");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(107.00);       
      break;

      case 0x6F89644:///////// video SAGA >
      lcd.clear();
      lcd.print("");
      lcd.setCursor(0,1); lcd.print("Atmega 328P");
      radio.selectFrequency(107.80);       
      break;     
      default:
     
      //////////////////////// Bu bölüm yalniz Komando kodlari icin. Serial monitorda bakilabilir.
      Serial.print(" unknown button ");
      Serial.println(results.value, HEX);
      }
      delay(10); 
      } 
      void unknownRemoter()
      { 
        Serial.print(" still an unknown button ");
        Serial.println(results.value, HEX); 
      }
