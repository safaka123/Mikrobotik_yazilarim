/******************************************************
      PIC16F877 ile RS232 Seri Ýletiþim Uygulamasý      val = 0x0A; printf("%c", val); 
PIC PROG/DEKA     : Port B jumper'ý LCD konumunda olmalý
*******************************************************/

#include <16f877.h>     // Kullanýlacak denetleyicinin baþlýk dosyasý tanýtýlýyor.

// Denetleyici konfigürasyon ayarlarý
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanýlacak osilatör frekansý belirtiliyor.

#define use_portb_lcd TRUE   // LCD B portuna baðlý

#include <lcd.c>   // lcd.c dosyasý tanýtýlýyor

#use rs232 (baud=9600, xmit=pin_C6, rcv=pin_C7, parity=N, stop=1) // RS232 protokolünün 9600 bit/sn baud hýzýnda olacaðýný ve
 int  a=0;                                                                 // TX,RX uçlarýnýn hangi pinler olacaðýný tanýmlýyor
 int  deg=0;                                                                 // parity bitinin olmadýðýný, stop bitinin 1 bit olacaðý belirtiliyor


#int_rda   // RX ucuna veri gelince meydane gelen kesme
void serihaberlesme_kesmesi ()
{
   disable_interrupts(int_rda); // int_rda kesmesini pasif yap
   output_high(pin_c5);  // RC5 çýkýþý lojik-1

bekle:
  deg=getch();
      
 if (deg==82) {
  goto atla;
  }  
 if (deg==80) {
 a=a-1; deg = 82;
//delay_ms(1000);
 goto atla;
};

  
// goto bekle;
 
 atla:  
  
   
   enable_interrupts(int_rda); // int_rda kesmesi aktif
    }

void KONTROL()
{
if (deg==82) {
 a=a+1;
 deg =0;
};
if (deg==80) {
 a=a-1; deg = 82;
};
}

void goster()
{

if (a==0){  printf("LCDWR 1,1-A%c",0);printf("IK");};// ekstra karakterin yazýlmasý. 0-7 yeni karakter arasý. 
if (a==1){  printf("LCDSC 1,0-");}
if (a==2){printf("LCDWR 2,1-%c"0);printf(" READ CH. EPROM");}
  //delay_ms(1000);// ms için bu mikro saniye için delay_us(100)
if (a==3){ printf("LCDWR 2,1-HEX %X"65);printf(" DEC %u"65);printf("(A)");}// hex dec ve karakter yazýlýmý
if (a==4){printf("LCDWR 1,9- %c"255);}// 128 üstündeki karakterlerin basýmý 
if (a==5){printf("LCDNC 0-%c"14);printf("%c"17);printf("%c"16);printf("%c"14);printf("%c"1);printf("%c"21);printf("%c"14);printf("%c"4);}// NEW CHARACTER
if (a==6){printf("LCDWR 1,1-DISP. WILL CLOSE");}
if (a==7){printf("LCDDC");}      // **********************************
if (a==8){printf("LCDWR 1,1-DISP OPENED     ");}
if (a==9){printf("LCDDO");}
if (a==10){printf("LCDWR 1,1-CUR.HIDDEN ");}
if (a==11){printf("LCDCH");}
if (a==12){printf("LCDWR 1,1-CUR.UNDER  ");}
if (a==13){printf("LCDCU");}
if (a==14){printf("LCDWR 1,1-CUR.BOX    ");}
if (a==15){printf("LCDCB");}
if (a==16){printf("LCDWR 1,1-CUR SHIFT L<=");}
if (a==17){printf("LCDCL");}
if (a==18){printf("LCDCL");}
if (a==19){printf("LCDCL");}
if (a==20){printf("LCDWR 1,1-CUR SHIFT R=>");}
if (a==21){printf("LCDCR");}
if (a==22){printf("LCDCR");}
if (a==23){printf("LCDCR");}
if (a==24){printf("LCDWR 1,1-DISP. SHIFT R==>");}
if (a==25){printf("LCDSR");}
if (a==26){printf("LCDSR");}
if (a==27){printf("LCDWR 1,1-DISP. SHIFT L<==");}
if (a==28){printf("LCDSL");}
if (a==29){printf("LCDSL");}
if (a==30){printf("LCDWR 1,1-CURSOR HOME     ");}
if (a==31){printf("LCDHO");}
if (a==32){printf("LCDWR 1,1-BACKLIGHT CLOSE ");}
if (a==33){printf("LCDBC");}
if (a==34){printf("LCDWR 1,1-BACKLIGHT OPEN  ");}
if (a==35){printf("LCDBO");}
if (a==36){printf("LCDWR 1,1-BACKLIGHT %%10   ");}
if (a==37){printf("LCDBL 1");}
if (a==38){printf("LCDWR 1,1-BACKLIGHT  %%90  ");}
if (a==39){printf("LCDBL 9");}
if (a==40){printf("LCDWR 1,1-BACKLIGHT  %%40  ");}
if (a==41){printf("LCDBL 4");}
if (a==42){printf("LCDCH");}
if (a==43){printf("LCDWR 1,1-EEPROM RECORDING");}
if (a==44){printf("LCDWR 2,1-                ");}
if (a==45){printf("LCDEW 0-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"14);printf("%c"1);printf("%c"21);printf("%c"14);printf("%c"4);}// Þ NEW CHARACTER
if (a==46){printf("LCDEW 1-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"16);printf("%c"17);printf("%c"14);printf("%c"4);printf("%c"0);}// Ç NEW CHARACTER
if (a==47){printf("LCDEW 2-");printf("%c"10);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}// Ü NEW CHARACTER
if (a==48){printf("LCDEW 3-");printf("%c"10);printf("%c"0);printf("%c"14);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}//Ö NEW CHARACTER
if (a==49){printf("LCDEW 4-");printf("%c"14);printf("%c"0);printf("%c"15);printf("%c"16);printf("%c"19);printf("%c"17);printf("%c"15);printf("%c"0);}//Ð NEW CHARACTER
if (a==50){printf("LCDEW 5-");printf("%c"4);printf("%c"0);printf("%c"14);printf("%c"4);printf("%c"4);printf("%c"4);printf("%c"14);printf("%c"0);}// Ý NEW CHARACTER
if (a==51){printf("LCDEW 6-");printf("%c"12);printf("%c"18);printf("%c"18);printf("%c"12);printf("%c"0);printf("%c"0);printf("%c"0);printf("%c"0);}// ° NEW CHARACTER
if (a==52){printf("LCDEW 7-");printf("%c"4);printf("%c"4);printf("%c"31);printf("%c"4);printf("%c"4);printf("%c"0);printf("%c"31);printf("%c"0);}// ± NEW CHARACTER
if (a==53){printf("LCDEW 8-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"14);printf("%c"1);printf("%c"21);printf("%c"14);printf("%c"4);}// Þ NEW CHARACTER
if (a==54){printf("LCDEW 9-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"16);printf("%c"17);printf("%c"14);printf("%c"4);printf("%c"0);}// Ç NEW CHARACTER
if (a==55){printf("LCDEW 10-");printf("%c"10);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}// Ü NEW CHARACTER
if (a==56){printf("LCDEW 11-");printf("%c"10);printf("%c"0);printf("%c"14);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}//Ö NEW CHARACTER
if (a==57){printf("LCDEW 12-");printf("%c"14);printf("%c"0);printf("%c"15);printf("%c"16);printf("%c"19);printf("%c"17);printf("%c"15);printf("%c"0);}//Ð NEW CHARACTER
if (a==58){printf("LCDEW 13-");printf("%c"4);printf("%c"0);printf("%c"14);printf("%c"4);printf("%c"4);printf("%c"4);printf("%c"14);printf("%c"0);}// Ý NEW CHARACTER
if (a==59){printf("LCDEW 14-");printf("%c"12);printf("%c"18);printf("%c"18);printf("%c"12);printf("%c"0);printf("%c"0);printf("%c"0);printf("%c"0);}// ° NEW CHARACTER
if (a==60){printf("LCDEW 15-");printf("%c"4);printf("%c"4);printf("%c"31);printf("%c"4);printf("%c"4);printf("%c"0);printf("%c"31);printf("%c"0);}// ± NEW CHARACTER
if (a==61){printf("LCDEW 16-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"14);printf("%c"1);printf("%c"21);printf("%c"14);printf("%c"4);}// Þ NEW CHARACTER
if (a==62){printf("LCDEW 17-");printf("%c"14);printf("%c"17);printf("%c"16);printf("%c"16);printf("%c"17);printf("%c"14);printf("%c"4);printf("%c"0);}// Ç NEW CHARACTER
if (a==63){printf("LCDEW 18-");printf("%c"10);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}// Ü NEW CHARACTER
if (a==64){printf("LCDEW 19-");printf("%c"10);printf("%c"0);printf("%c"14);printf("%c"17);printf("%c"17);printf("%c"17);printf("%c"14);printf("%c"0);}//Ö NEW CHARACTER
if (a==65){printf("LCDEW 20-");printf("%c"14);printf("%c"0);printf("%c"15);printf("%c"16);printf("%c"19);printf("%c"17);printf("%c"15);printf("%c"0);}//Ð NEW CHARACTER
if (a==66){printf("LCDEW 21-");printf("%c"4);printf("%c"0);printf("%c"14);printf("%c"4);printf("%c"4);printf("%c"4);printf("%c"14);printf("%c"0);}// Ý NEW CHARACTER
if (a==67){printf("LCDEW 22-");printf("%c"12);printf("%c"18);printf("%c"18);printf("%c"12);printf("%c"0);printf("%c"0);printf("%c"0);printf("%c"0);}// ° NEW CHARACTER
if (a==68){printf("LCDEW 23-");printf("%c"4);printf("%c"4);printf("%c"31);printf("%c"4);printf("%c"4);printf("%c"0);printf("%c"31);printf("%c"0);}// ± NEW CHARACTER
if (a==69){printf("LCDDD");}
if (a==70){printf("LCDCB");}
if (a==71){printf("LCDER");}
if (a==72){printf("LCDDD");}
if (a==73){printf("LCDCB");}
if (a==74){printf("LCDWR 1,1-READ   CHARACTER");}
if (a==75){printf("LCDRC 1,14-");}
if (a==76){printf("LCDDD");}

}



/********* ANA PROGRAM FONKSÝYONU********/

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre dýþý
   setup_timer_1(T1_DISABLED);     // T1 zamanlayýcýsý devre dýþý
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayýcýsý devre dýþý
   setup_adc_ports(NO_ANALOGS);    // ANALOG giriþ yok
   setup_adc(ADC_OFF);             // ADC birimi devre dýþý
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre dýþý
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre dýþý

   output_low(pin_c5); // RC5 çýkýþý ilk anda sýfýrlanýyor
   lcd_init();   // LCD'yi hazýrla

   deg = 0x00; 
   enable_interrupts(GLOBAL);  // Aktif edilen tüm kesmelere izin ver
   enable_interrupts(int_rda); // int_rda kesmesi aktif
printf ("LCDDD");
delay_ms(500);  //************  ms için bu mikro saniye için delay_us(100)****
dene:
if (a==77){a=0;deg=82;};
if (deg==82) {
//printf(lcd_putc,"\f gelen: %x",deg);printf(lcd_putc," %u",a);

delay_ms(1000);

goster();

KONTROL();

}

goto dene;

}
