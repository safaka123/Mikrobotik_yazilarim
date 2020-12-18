/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


uint16_t basla=0;
int RECV_PIN = 11;
int temp=0;
int ii=0;
int jj=0;
int kk=0;

uint16_t sayL[30];
uint16_t sayH[30];

uint16_t sayLL[12];
uint16_t sayHH[12];



void setup()
{
  Serial.begin(9600);
  
  //Serial.println("bekleyin ");

  
}

void tekrarla(){  // burada sayL değişkeni artık son diziyi toparlama değişkeni oluyor.  Burada 1 ve 0 lardan oluşan dizi oluşturuluyor. 
                  //Oluşan dizi : 0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,0,0,1  gibidir. 

if (sayHH[ii]<1200 ){    // 0,843,844,1784,895,872,896,893,840,1781,845,865,843
   // Serial.print("  sayHH[ii]  ");Serial.print(sayHH[ii]);Serial.print(" ii,tek  ");Serial.println(ii);
    sayL[kk]=1;ii++;kk++;
}else if(sayHH[ii]>1200){
  //Serial.print("  sayHH[ii]  ");Serial.print(sayHH[ii]);Serial.print(" ii,cift  ");Serial.println(ii);
  sayL[kk]=1;kk++;sayL[kk]=1;kk++;ii++;
}
 
 if (sayLL[jj]<1200 ){  // 939,909,911,882,858,918,936,1773,915,909,1773
  // Serial.print("  sayLL[jj]  ");Serial.print(sayLL[jj]);Serial.print(" jj,tek  ");Serial.println(jj);
    sayL[kk]=0;jj++;kk++;
}else if(sayLL[jj]>1200){
 // Serial.print("  sayLL[jj]  ");Serial.print(sayLL[jj]);Serial.print(" jj,cift  ");Serial.println(jj);
  sayL[kk]=0;kk++;sayL[kk]=0;kk++;jj++;  
}
}


void sonkod() {  // 1 ve 0 lardan oluşan array tek bir değişkene sola doğru 1 kaydırılarak kayıt edilir. 
  kk=0;temp=0;
  for (int i = 0; i <= 26; i=i+2){
  

//Serial.println(i);
    if (sayL[i]==1 && sayL[i+1]==0){
    temp=temp<<1;
     temp=temp+1;

    }
    if (sayL[i]==0 && sayL[i+1]==1){
    temp=temp<<1;

    temp=temp+0;
    }
  }
   Serial.println(temp,BIN);
   Serial.println(temp,HEX);
}

void loop() {// ==============================================================================
  Serial.println("  IR sinyalini gonder  ");
 temp=0;basla=0;
 

 while (temp==0){
  basla=pulseIn(RECV_PIN,LOW)>0;
  if (basla<1200 && basla>0 ){
    temp=1;
  }
  }
//Serial.print("  temp  ");Serial.println(temp);Serial.println(basla);
for (int i = 0; i < 30; i++)
  {
  sayL[i]=pulseIn(RECV_PIN, LOW,300000);
  }

  while (pulseIn(RECV_PIN,HIGH)>21000){
  }

for (int i = 0; i < 30; i++)
  {
    
sayH[i]=pulseIn(RECV_PIN, HIGH,300000);

  }


 ii=0;
for(int i=0; i<=30; i++){
if (sayL[i]>0){
  sayLL[ii]=sayL[i];
  ii++;
 }
 if (ii==11){
  break;
 }
}
Serial.println("==========sayLL[i]======================");
for(int i=0; i<=10; i++){
Serial.println(sayLL[i]);
}

ii=0;temp=0;
for(int i=0; i<=30; i++){

  if (temp==1){
  sayHH[ii]=sayH[i];
  ii++;
  }
  if (sayH[i]>20000){
  temp=1;
  }

 
 if (ii==11){
  break;
 }
}
Serial.println("==========sayHH[i]======================");
for(int i=0; i<=11; i++){
Serial.println(sayHH[i]);
}

Serial.println("  Son dizilim 1 ve 0 olarak. 1 den 0 a giderse 1, 0 dan 1 e giderse 0 sayilacak. alt alta cift olarak kontrol.");
ii=0;jj=0;kk=0;  // sinyal değerleri incelenip tek bir rc5 kod uretilir. 

  sayL[0]=1;sayL[1]=0;kk=kk+2;
 
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
tekrarla();
for(int i=0; i<=28; i++){
Serial.println(sayL[i]);
}

sonkod();

}
