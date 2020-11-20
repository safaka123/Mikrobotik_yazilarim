/*
////////////////////////////////////////////////////////////////////////////////////////////////////
  AUTOR: JUAN BIONDI                                               FECHA:       FEBRERO/2014      
  PROGRAMA:  Potentiometer SPI                                     VERSION:     1.0               
  DISPOSITIVO: ATMEL 328                                           COMPILADOR:  AVR               
  ENTORNO:     PROTEUS                                             SIMULADOR:   VSM        
  TARJETA DE PROGRAMACION:                                         DEBUGGER:                      
////////////////////////////////////////////////////////////////////////////////////////////////////

  Control an Analog Devices AD5206 digital potentiometer.
  The AD5206 has 6 potentiometer channels. Each channel's pins are labeled
  A - connect this to voltage
  W - this is the pot's wiper, which changes when you set it
  B - connect this to ground.
 
 The AD5206 is SPI-compatible,and to command it, you send two bytes, 
 one with the channel number (0 - 5) and one with the resistance value for the
 channel (0 - 255).  
 
 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)



////////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <SPI.h>
const int slaveSelectPin = 10;
int kanal=0;
int pwmdeger=0;

void digitalPotWrite(int address, int value) 
{
  digitalWrite(slaveSelectPin,LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(slaveSelectPin,HIGH);
}

void setup() 
{
  pinMode (slaveSelectPin, OUTPUT);   // set the slaveSelectPin as an output:
  SPI.begin();          // initialize SPI:
  
   for ( kanal = 0; kanal < 6; kanal++)  // Initialize all potentiometers to 0
   { 
     digitalPotWrite(kanal, 0);
     delay(10);
   }

}

void loop() 
{
   if(pwmdeger <= 240 ){
    pwmdeger=pwmdeger+10;
    
   }else{
    delay(3000);
    pwmdeger=0;
   }
   kanal =0 ;
   digitalPotWrite(kanal,pwmdeger);  // Send the data to the potentiometer
   delay(500);       //Delay to see the changes
  
}
