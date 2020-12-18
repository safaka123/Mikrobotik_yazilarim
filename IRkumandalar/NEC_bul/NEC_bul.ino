/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


uint16_t basla=0;
int RECV_PIN = 11;

int ii=0;
int jj=0;
int kk=0;

uint16_t sayL[50];
uint16_t sayH[50];

uint16_t sayLL[30];
uint16_t sayHH[30];



void setup()
{
  Serial.begin(9600);
  
  Serial.println("Enabled IRin");
  
}




void loop() {
again:   // for repeating this program when same button is pressed twice
  boolean bin[32];                    //boolean consumes less space
  int addr = 0, data = 0;             // address and data variabels
  int sayy;
sayy=0;
 basla=0;
/*
 while (basla==0)
 {
sayy=(pulseIn(RECV_PIN,LOW));
 // Serial.println(sayy);
  if (sayy>2000 && sayy<=9500){
    Serial.println(sayy);
   basla=1;
  }
 }
 */ 
  
  
  while (pulseIn(RECV_PIN,LOW) < 8000); // wait until start bit is received.
  {
  
  }

while (basla==0)
 {
sayy=(pulseIn(RECV_PIN,HIGH));
 // Serial.println(sayy);
  if (sayy>3000 && sayy<=5000){
   //Serial.println(sayy);
   basla=1;
  }
 }





  for (int i = 0; i < 32; i++)
  {

    if (pulseIn(RECV_PIN, HIGH) > 1000) 
      bin[i] = 1;
    else
      bin[i] = 0;
  }

  Serial.print("Bit Stream = ");
  for (int i = 0; i < 32; i++)     
  {
    Serial.print(bin[i]);
  }
  Serial.println();

  Serial.print("Address = ");
  for (int i = 0; i < 8; i++)     
  {

    if (bin[i] == 1)
      addr += 1 << i;

  }
  Serial.print("   ");
  Serial.println(addr);
 
  Serial.print("Data = ");
  for (int i = 0; i < 8; i++)     
  {

    if (bin[i + 16] == 1)
      data += 1 << i;
  }

  Serial.print("   ");
  Serial.println(data);
  Serial.println();

    

}
