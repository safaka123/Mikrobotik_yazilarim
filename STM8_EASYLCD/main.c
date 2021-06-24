//#include "iostm8s103f3.h"  // bu IAR kütüphanesi. bunu basa yazdigimda yaklasik 258 ikaz var. 
                            // nedeni ise stm8s.h özel kütüphanedir. buradaki bazi degiskenler çakisma yapiyor.
                            // programa etkisi yok. bu kütüphaneyi stm8s.h tan sonra yazarsam 
                            // çakisma yapip programi çalistirmiyor. IAR kütüphanesinde hata veren satirin degisken ismini OOPT olarak degistirdim. 

#include "stm8s.h"
#include "string.h"
#include "stdio.h"

char buf[55];
uint8_t yaz1=0;
char komut[7];
char koor[5];
char yazdata[40];
uint8_t rec_data[7];
uint8_t temp=0;
char crlf=0x0D;
uint8_t recflag;
uint8_t anisay=0;
uint8_t str2[10];
//  NOT: komut yazarken CTRL + space çalisiyor

INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{   // rs232 interrupt bölümüdür. 
  // son karaktere kadar alinir. bunu bir array içine karakter olarak aliriz.
yaz1=UART1->SR;   // status register okunuyor ama gerekli mi bilinmiyor.
yaz1=UART1->SR;  // status register okunuyor ama gerekli mi bilinmiyor.
  rec_data[temp]=UART1->DR; // karakter alma yeri
  yaz1=UART1->SR; // status register okunuyor ama gerekli mi bilinmiyor. 
 temp=temp+1;  // her alindiginda array 1 arttirilir siradaki bos alana alinir
   rec_data[temp]=UART1->DR; // karakter alma yeri 

yaz1=UART1->SR;  // status register okunuyor ama gerekli mi bilinmiyor.
 recflag=1;  //Bütün hepsi alindiginda interrupttan çikilirken bir bayrak 1 yapilir ve bu kontrol edilir
            // Sayet 1 ise bilgi gelmistir ekrana bas deniliyor. gelmemis ise 0 dir. 
            // yazdirma islemi bitince program tarafindan bayrak sifirlanmali yanlis bilgi gelmesin diye. 
     

}


void delay(uint32_t n)  // zaman gecikmesi for döngüsünü kaldir yerine delay koy. us ya ms degil bir sayaç olarak kabul et. 
{
  while (n-- > 0);
}

void cevapbekle() // burada seri porttan bilgi alinacagi zaman beklenir ve interrupt çalistiginda recflag=1 oldugunda program gelen cevabi iletir. 
{
 while (recflag==0)
 {
   // interrupt ta recflag1 oldugunda while döngüsünden çikilir. 
 }
 
 recflag=0;
  rec_data[0]=0x00;
    rec_data[1]=0x00;
    rec_data[2]=0x00;
    rec_data[3]=0x00;
    rec_data[4]=0x00;
    rec_data[5]=0x00;
    rec_data[6]=0x00;
  //  temp=0;
    anisay=anisay+1;
    recflag=0;
 
 temp=temp+1;
 
}


int main( void )
{
  
     while(!CLK_ICKR_HSIRDY);  // osilatör hazir olasiya kadar bekle. 
  CLK->CKDIVR=0;   // clock 16mhz full speed
  
 
  enableInterrupts();   // RS232 interrupt çalissin. 
  
  // baud rate hesabi için detaylar : https://www.mcu-turkey.com/stm8s-uart-modulu-kullanimi/
  // bu ayarlar 9600 baud için yapilmistir. 
  
 UART1->BRR1=0x68;  //uart  56kpbs =0x011
  UART1->BRR2=0x02;   //uart  56kpbs =0x06
  UART1->CR1=0xC0; //  8bit /even parity
  UART1->CR2=0x2C; // ritrupten ren ten
  UART1->CR3=0x0; 
  UART1->CR4=0x0;
  UART1->CR5=0x0;  
  UART1->PSCR=0x0;
 
  
 
  while (1)            // arduino daki loop sonsuz döngü bölümü
  {
  delay(600000);
  // memset clear array
  memset(buf, 0, sizeof buf);  
  memset(komut, 0, sizeof komut);    
  memset(koor, 0, sizeof koor); 
  memset(yazdata, 0, sizeof yazdata);  
 
  if(anisay==0)
  { 
    strncpy(komut,"LCDDD",7);
  }
  
  //if(anisay==2){ strncpy(komut,"LCDWR",7);strncpy(koor,"1,3",5);strncpy(yazdata,"hex kullanmayacaksaniz bu sekilde yazin",40);}

  if(anisay==1){
    char tempvalue=26;
    sprintf(yazdata, "%s%X", "DEC:26 HEX: ",tempvalue);
    strncpy(komut,"LCDWR",7);strncpy(koor,"2,1",5);
  }
  if(anisay==2){ strncpy(komut,"LCDDD",7);}
  
  if(anisay==3){ strncpy(komut,"LCDWR",7);strncpy(koor,"1,2",5);strncpy(yazdata,"SATIR - 1",40);}
  if (anisay==4){strncpy(komut,"LCDSC",7); strncpy(koor,"1,3",5);} // S karakteri
  if(anisay==5){ strncpy(komut,"LCDWR",7);strncpy(koor,"2,2",5);strncpy(yazdata,"SATIR - 2 A\3IK",40);}
  if (anisay==6){strncpy(komut,"LCDSC",7); strncpy(koor,"2,3",5);} // Ç karakteri
   
  if(anisay==7){ strncpy(komut,"LCDSL",7);}
  if(anisay==8){ strncpy(komut,"LCDSL",7);}
  if(anisay==9){ strncpy(komut,"LCDSL",7);}
  
  if(anisay==10){ strncpy(komut,"LCDSR",7);}
  if(anisay==11){ strncpy(komut,"LCDSR",7);}
  if(anisay==12){ strncpy(komut,"LCDSR",7);}
  
  if (anisay==13){strncpy(komut,"LCDDC",7);}
  if (anisay==14){strncpy(komut,"LCDDO",7);}
  
  if (anisay==15){strncpy(komut,"LCDCU",7);}
  if (anisay==16){strncpy(komut,"LCDCH",7);}
  if (anisay==17){strncpy(komut,"LCDCB",7);}
  if (anisay==18){strncpy(komut,"LCDHO",7);}
  
  if (anisay==19){strncpy(komut,"LCDCR",7);}
  if (anisay==20){strncpy(komut,"LCDCR",7);}
  if (anisay==21){strncpy(komut,"LCDCR",7);}
  
  if (anisay==22){strncpy(komut,"LCDCL",7);}
  if (anisay==23){strncpy(komut,"LCDCL",7);}
  if (anisay==24){strncpy(komut,"LCDCL",7);}
  
  if (anisay==25){strncpy(komut,"LCDBC",7);}
  if (anisay==26){strncpy(komut,"LCDBO",7);}
  if (anisay==27){strncpy(komut,"LCDBL 1",7);}
  if (anisay==28){strncpy(komut,"LCDBL 9",7);}
  
  if (anisay==29){strncpy(komut,"LCDER",7);}
  
  if (anisay==30){ anisay=0;}
 
  snprintf(buf, 55, "%s%s%s%s%s", komut," ", koor,"-",yazdata);
 /* for(int i=0;i<strlen(komut);i++){
    buf[i]=komut[i];
    
  }
  int ii=0;
  for(int i=strlen(komut);i<strlen(komut)+strlen(koor);i++){
    
    buf[i]=koor[ii];
    ii=ii+1;
    
  }
  
   ii=0;
  for(int i=strlen(komut)+strlen(koor);i<strlen(komut)+strlen(koor)+strlen(yazdata);i++){
    
    buf[i]=yazdata[ii];
    ii=ii+1;
    
  }
  */
 
  
      for(int i=0;i<strlen(buf);i++){    // yaz bekle array degiskenindeki (tusbasildi veri gönder kelimesini karakter olarak seri porta yollar. 
        UART1->DR=buf[i];
        delay(300); // bu gecikmeyi vermeliyiz. yoksa karakterler arka arkaya tek tek iletildiginden gönderme hatasi yapiyor. 
      }
      recflag=0;
      cevapbekle();
      
      }
    
    
 
  }  
  
    
    












