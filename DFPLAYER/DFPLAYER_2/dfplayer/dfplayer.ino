///              MP3 PLAYER PROJECT
/// http://educ8s.tv/arduino-mp3-player/
/// softserialden gelirse serial kısma aktar. 
//////////////////////////////////////////
#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11); // RX, TX
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x01 //Returns info with command 0x41 [0x01: info, 0x00: no info]
# define ACTIVATED LOW
int say=0;
int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
boolean isPlaying = false;

void setup () {
pinMode(buttonPause, INPUT);
digitalWrite(buttonPause,HIGH);
pinMode(buttonNext, INPUT);
digitalWrite(buttonNext,HIGH);
pinMode(buttonPrevious, INPUT);
digitalWrite(buttonPrevious,HIGH);
mySerial.begin (9600);
Serial.begin (9600);
Serial.print(" basladi");
delay(1000);
playFirst();
delay(1000);
play();
delay(1000);
playNext();
isPlaying = true;
}
void loop () { 
  
 // Örnek serial read komutu. 10 byte bekle. while (mySerial.available()<10); // Wait until initialization parameters are received (10 bytes) 
 
  if (mySerial.available()) { // dfplayer dan gelen bilgileri yazdır. ****
    say=1;
    Serial.print(mySerial.read(),HEX);
  }
  if (say==1){
    Serial.println("   gelen");
    say=0;
  }
 // if (Serial.available()) {
 //   mySerial.write(Serial.read());
 // }
  
 if (digitalRead(buttonPause) == ACTIVATED)
  {
    if(isPlaying)
    {
      pause();
      isPlaying = false;
    }else
    {
      isPlaying = true;
      play();
    }
  }
 if (digitalRead(buttonNext) == ACTIVATED)
  {
    if(isPlaying)
    {
      playNext();
    }
  }
   if (digitalRead(buttonPrevious) == ACTIVATED)
  {
    if(isPlaying)
    {
      playPrevious();
    }
  }
}
void playFirst()
{
 //execute_CMD(0x0C,0,0); // Reset module
  //delay(500);
  Serial.println("play FIRST ");
 execute_CMD(0x3F, 0, 0);
delay(500);
  setVolume(25);
  delay(500);
  // execute_CMD(0x11,0,1); // repeat play =0 1 repeat stop play 0 0
  //execute_CMD(0x0B,0,0);  // normal çalışma bir değişiklik yaratmıyor. 
  // execute_CMD(0x0D,0,0);
  
  //delay(500);
  //execute_CMD(0x4B,0,0); // hangi parçayı çaldığını gösterir. 
  // execute_CMD(0x0D,0,0);
 // execute_CMD(0x18,0,0); // random all
 // delay(500);
 Serial.println("Hangi parca ");
  execute_CMD(0x4C,0,0); // hangi parçayı çaldığını gösterir.
  //execute_CMD(0x18,0,0); // random all
  delay(500);
  
  //execute_CMD(0x17,0,14); // loop folder  
   //execute_CMD(0x0B,0,0); // Normal Çalışma 
    
  //delay(500);
}
void pause()
{Serial.println("PAUSE");
  execute_CMD(0x0E,0,0);
  delay(500);
}
void play()
{
  Serial.println("play ");
  //execute_CMD(0x0D,0,1); 
  execute_CMD(0x09,0,1); // USB device select 
  delay (500);
  //execute_CMD(0x09,0,2); // TF device select
  execute_CMD(0x0D,0,0); //PLAY command
  
  delay(15000);
}
void playNext()
{
  //execute_CMD(0x0D,0,0);
  Serial.println("play NEXT ");
  
   execute_CMD(0x01,0,0); // next 
  delay(5500);
  //execute_CMD(0x08,0,155); // 155 şarkı numarası devamlı aynı şarkıyı çalar. 155. şarkı yokken hata vermiyor bir şarkı seçiyor. 
 // execute_CMD(0x07,0,0); // EQU seçme 0-5 arası
 // execute_CMD(0x03,0,3);// 3. şarkıyı çalar ve durur. dizin belirtilmez. 
 //execute_CMD(0x0E,0,0); // pause 
// execute_CMD(0x1A,0,1); // special pause mode  ancak 01A 0 0 ile eski haline döner yada reset ile. ***
 //  delay(4500);
// execute_CMD(0x1A,0,0);// special no pause mode. ***  0E gibi değil 0E ile duran şarkı 0D ile çalıştırılabilir. 
//   delay(2500);  
  
   // execute_CMD(0x16,0,0);// stop track fakat 3D durdu bilgisi gelmez. 
   //delay(5500); 
   // execute_CMD(0x11,0,0);// repeat play=0 1   repeat stop = 0 0
   //delay(2500); 
  //execute_CMD(0x48,0,0);  // toplam parça sayısını gösterir. TF için
  //delay(500);
  Serial.println("Çalınan parça numarası ");
  execute_CMD(0x4C,0,0); // hangi parçayı çaldığını gösterir. 
  delay(500);
  
//execute_CMD(0x43,0,0); // valume seviyesini goster
// delay(500);
  //execute_CMD(0x42,0,0);  // play durumunu gösterir. ayrıca hangi aygıt çalıyor onu gösterir. tf usb gibi. 
 // execute_CMD(0x12,0,3);  // mp3 dizinindeki şarkılardan 3. sünü çal. bu komut sadece mp3 dizinindekilerden seçtiğinizi direkt olarak çalar ve bitiminde durur. 
 // delay(500);
}

void playPrevious()
{Serial.println("play PREVIOUS");
  execute_CMD(0x02,0,1);
  delay(500);
}
void setVolume(int volume)
{Serial.println("SET VOLUME");
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(2000);
}
void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command line to the module
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
Serial.print( Command_line[k],HEX);
Serial.print(" , ");
}
Serial.println();
}
