//// Bu TEA 5767 icin degisik kütüphaneler var bu programm >TEA5767N.h< kullanir.
// programi hazirlayan ve kodlarin uygulanmasi Mustafa Avci tarafindan hazirlanmistir.Sorularinizi 
// Bu sitede sorabilirsiniz.
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TEA5767N.h>
TEA5767N radio = TEA5767N();
const int buttonPin1 = 2, buttonPin2 = 3;    
int button1_State = 0, button2_State = 0;
int count_value =0;
int prestate =0;
LiquidCrystal_I2C lcd(0x27,16,2);// Bu lcd adress bazen 027/ yerine 3F olabiliyor (lcd(0x27,16,2);)
////////////////////// Burda Radyo sinyali gösteriliyor.
void updateLevelIndicator() {
  byte x, y, sl;
  char barGraph[17];  
  lcd.setCursor(0,1);
  sl = radio.getSignalLevel();
  for (x=0 ; x<sl ; x++) {
    barGraph[x] = 255;
  }
  for (y=x ; y<16 ; y++) {
    barGraph[y] = 32;
  }
  barGraph[y] = '\0';
  lcd.print(barGraph);
}

void setup() { 
  lcd.begin();
  radio.mute();
  radio.selectFrequency(91.3);// ilk acilista bir radio.
  radio.turnTheSoundBackOn();
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  lcd.begin();
  radio.mute();//Radio sessize aliniyor . istasyonlar arasi hisirtiyi önlüyor.
  radio.selectFrequency(91.3);// Radio nun frekans secmesi.
  radio.turnTheSoundBackOn();//Sessize alinan radio tekrar sesi aciyor.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);// Radiyo aldigi frekansi ekrana yaziyor.
  lcd.print("  MHz");
  lcd.setCursor(0,1);
  updateLevelIndicator();// Radiyo Sinyalinin göstergesini yeniliyor.    
}
///////////Yukarda yapilan aciklamarin detailarini kütüphande görebilirsiniz. >TEA5767N.h<
////////////////////////////
void loop() {
  // Buttonlarin okunmasi 
  button1_State = digitalRead(buttonPin1);
  button2_State = digitalRead(buttonPin2);
  // Butonlarin okunmasini denetle.
  if (button1_State == HIGH && prestate == 0) {/// Buton1 == yüksekse ve ilk durumu== 0 ise. 
    count_value++;  // saydegeri ++.
    prestate = 1;//ilk durumu = 1;
    ///////
  if(count_value==1){
  radio.mute();
  radio.selectFrequency(87.7);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }  
  else if(count_value==2){
  radio.mute();
  radio.selectFrequency(89.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }  
  else  if(count_value==3){
  radio.mute();
  radio.selectFrequency(89.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==4){
  radio.mute();
  radio.selectFrequency(90.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==5){
  radio.mute();
  radio.selectFrequency(90.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==6){
  radio.mute();
  radio.selectFrequency(91.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==7){
  radio.mute();
  radio.selectFrequency(92.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==8){
  radio.mute();
  radio.selectFrequency(93.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==9){
  radio.mute();
  radio.selectFrequency(94.0);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==10){
  radio.mute();
  radio.selectFrequency(94.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==11){
  radio.mute();
  radio.selectFrequency(94.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==12){
  radio.mute();
  radio.selectFrequency(95.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==13){
  radio.mute();
  radio.selectFrequency(96.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==14){
  radio.mute();
  radio.selectFrequency(96.4);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==15){
  radio.mute();
  radio.selectFrequency(96.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==16){
  radio.mute();
  radio.selectFrequency(97.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==17){
  radio.mute();
  radio.selectFrequency(97.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==18){
  radio.mute();
  radio.selectFrequency(98.5);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==19){
  radio.mute();
  radio.selectFrequency(98.7);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==20){
  radio.mute();
  radio.selectFrequency(99.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==21){
  radio.mute();
  radio.selectFrequency(99.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==22){
  radio.mute();
  radio.selectFrequency(99.0);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==23){
  radio.mute();
  radio.selectFrequency(100.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==24){
  radio.mute();
  radio.selectFrequency(100.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==25){
  radio.mute();
  radio.selectFrequency(101.1);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==26){
  radio.mute();
  radio.selectFrequency(101.5);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  
  }
  else  if(count_value==27){
  radio.mute();
  radio.selectFrequency(102.5);//Radio 7
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  
  }
  else  if(count_value==28){
  radio.mute();
  radio.selectFrequency(103.4);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==29){
  radio.mute();
  radio.selectFrequency(104.0);// 
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==30){
  radio.mute();
  radio.selectFrequency(104.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==31){
  radio.mute();
  radio.selectFrequency(105.1);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==32){
  radio.mute();
  radio.selectFrequency(105.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==33){
  radio.mute();
  radio.selectFrequency(106.2);///Tessin
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==34){
  radio.mute();
  radio.selectFrequency(107.0);
  radio.turnTheSoundBackOn();
  }
  else  if(count_value==35){
  radio.mute();
  radio.selectFrequency(107.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
   else  if(count_value>=36){
    count_value=0;////////////////////burdan basa gecer. ve sifirdan yukari devam eder.
  
  }
  } 
///////////////////////////Bu bölüm geri sayim. icin ama hatali calisabilir. 
//////////Ya yeniden gözden gecirmek lazim yada bu kismi silmek lazim. 
  else if (button2_State == HIGH && prestate == 0) {
    count_value--;  
   prestate = 1;
  if(count_value==1){
  radio.mute();
  radio.selectFrequency(87.7);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }  
  else if(count_value==2){
  radio.mute();
  radio.selectFrequency(89.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }  
  else  if(count_value==3){
  radio.mute();
  radio.selectFrequency(89.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==4){
  radio.mute();
  radio.selectFrequency(90.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==5){
  radio.mute();
  radio.selectFrequency(90.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==6){
  radio.mute();
  radio.selectFrequency(91.3);//SWF 3
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==7){
  radio.mute();
  radio.selectFrequency(92.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==8){
  radio.mute();
  radio.selectFrequency(93.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==9){
  radio.mute();
  radio.selectFrequency(94.0);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==10){
  radio.mute();
  radio.selectFrequency(94.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==11){
  radio.mute();
  radio.selectFrequency(94.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==12){
  radio.mute();
  radio.selectFrequency(95.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==13){
  radio.mute();
  radio.selectFrequency(96.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==14){
  radio.mute();
  radio.selectFrequency(96.4);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==15){
  radio.mute();
  radio.selectFrequency(96.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==16){
  radio.mute();
  radio.selectFrequency(97.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==17){
  radio.mute();
  radio.selectFrequency(97.9);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==18){
  radio.mute();
  radio.selectFrequency(98.5);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==19){
  radio.mute();
  radio.selectFrequency(98.7);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==20){
  radio.mute();
  radio.selectFrequency(99.3);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==21){
  radio.mute();
  radio.selectFrequency(99.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==22){
  radio.mute();
  radio.selectFrequency(99.0);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==23){
  radio.mute();
  radio.selectFrequency(100.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==24){
  radio.mute();
  radio.selectFrequency(100.6);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==25){
  radio.mute();
  radio.selectFrequency(101.1);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==26){
  radio.mute();
  radio.selectFrequency(101.5);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  
  }
  else  if(count_value==27){
  radio.mute();
  radio.selectFrequency(102.5);//Radio 7
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  
  }
  else  if(count_value==28){
  radio.mute();
  radio.selectFrequency(103.4);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==29){
  radio.mute();
  radio.selectFrequency(104.0);// SW3 Baden
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==30){
  radio.mute();
  radio.selectFrequency(104.2);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==31){
  radio.mute();
  radio.selectFrequency(105.1);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==32){
  radio.mute();
  radio.selectFrequency(105.6);///SRF 3
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==33){
  radio.mute();
  radio.selectFrequency(106.2);///Tessin
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
  else  if(count_value==34){
  radio.mute();
  radio.selectFrequency(107.0);
  radio.turnTheSoundBackOn();
  }
  else  if(count_value==35){
  radio.mute();
  radio.selectFrequency(107.8);
  radio.turnTheSoundBackOn();
  lcd.setCursor(0,0);
  lcd.print(radio.readFrequencyInMHz(), 1);
  updateLevelIndicator();
  }
   else  if(count_value>=36){
   count_value=0;
 
  }
  } 
 else if(button1_State == LOW && button2_State == LOW) {
    prestate = 0;
  }
}
