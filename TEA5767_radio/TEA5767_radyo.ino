/////////////////////////////////////////////////////////////////////

#include <Wire.h>

#include <TEA5767N.h>

TEA5767N Radio = TEA5767N();

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int MUTEPIN = 2;

int STATIONPIN = 3;

int flag = 0;

double stations[] = {87.60,88.00,88.40,88.70,89.00,89.30,89.50,89.70,90.90,91.60};

int currentstation =0;

int maxstation =9;

bool mutestate =0;

void setup() {

pinMode(MUTEPIN,INPUT);

pinMode (STATIONPIN,INPUT);

Wire.begin();

lcd.clear();

lcd.backlight();

lcd.begin();

Radio.selectFrequency(stations[currentstation]);

delay(250);

}

void loop() {

if(digitalRead(MUTEPIN)==HIGH){

mutestate = !mutestate ;

if(mutestate){

delay(250);

lcd.clear();

lcd.print("SES KAPALI");

Radio.mute();

}else{

Radio.turnTheSoundBackOn();

lcd.clear();

lcd.setCursor(0,0);

lcd.print("Frekans: ");

lcd.print(Radio.readFrequencyInMHz());

lcd.print(" MHz ");

lcd.setCursor(0,1);

lcd.print("Sinyal: ");

lcd.print(Radio.getSignalLevel());

}

}

if(digitalRead(STATIONPIN)==HIGH){

currentstation++;

lcd.clear();

if(currentstation>maxstation){

currentstation =0;

}

Radio.selectFrequency(stations[currentstation]);

flag =0;

delay(250);

}

if(flag == 0) {

lcd.clear();

lcd.print("Frekans: ");

lcd.print(Radio.readFrequencyInMHz());

lcd.print("  MHz Signal: ");

lcd.setCursor(1,1);

lcd.print("Sinyal: ");

lcd.print(Radio.getSignalLevel());

  flag=1;

}

delay(100);

}

///////////////////////////////////////////////////////////////////////////////////
