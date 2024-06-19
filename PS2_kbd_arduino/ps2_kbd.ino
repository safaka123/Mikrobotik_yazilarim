 /*
 * an arduino sketch to interface with a ps/2 keyboard.
 * Also uses serial protocol to talk back to the host
 * and report what it finds. Used the ps2 library.
 */

 // Lookup table (in: SHIFT state and PS2 scancode => out: desired ASCII code) change for your country
// QWERTY layout
char ScancodeToASCII[2][128] = {// 2 farklı dizilim var 127 karakterden oluşur. 
                                // birincisi SHIFT basılmadan. İkincisi ise SHIFT basıldığında okunur. 
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,9,34,0,0,0,0,0,0,113,49,0,0,0,122,115,97,119,50,0,//31 kod
0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,'b',104,103,121,54,0,0,0,109,106,117,55,56,0,//32 kod
0,44,107,0,111,48,57,0,0,46,46,108,148,112,42,0,0,0,132,0,129,45,0,0,0,0,13,43,0,44,0,0,//32 kod
0,60,0,0,0,0,8,0,0,49,0,52,55,0,0,0,48,46,50,53,54,56,27,0,0,43,51,45,42,57,0,0  },// 32 kod
  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,130,0,0,0,0,0,0,81,33,0,0,0,90,83,65,87,34,0,//31 kod
0,67,88,68,69,36,94,0,0,0,86,70,84,82,37,0,0,78,'B',72,71,89,38,0,0,0,77,74,85,47,40,0,//32 kod
0,59,75,73,79,61,41,0,0,0,58,76,153,80,63,0,0,0,142,0,154,95,0,0,0,0,0,42,0,59,0,0,//32 kod
0,62,0,0,0,0,0,0,0,49,0,52,55,0,0,0,48,46,50,53,54,56,0,0,0,43,51,45,42,57,0,0  } //32 kod
 };

 char altgrcodeToASCII[128] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,64,0,0,0,0,0,0,0,0,'£',0,
  0,0,0,0,0,36,35,0,0,0,0,0,0,0,'½',0,0,0,0,0,0,0,0,0,0,0,0,0,0,123,91,0,
  0,0,0,0,0,125,93,0,0,0,0,0,0,0,92,0,0,0,0,0,0,0,0,0,0,0,0,126,0,92,0,0,
  0,124,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 };

 
/*
  { 0,0,0,0,0,'F4',0,0,         0,0,0,0,0,9,94,0,         0,0,0,0,0,113,49,0,       0,0,121,'a',97,119,50,0,    // w/o SHIFT or ALT(GR)
    0,99,120,100,101,52,51,0,0,32,118,102,116,114,53,0,0,110,'b',104,103,122,54,0,0,0,109,106,117,55,56,0,
    0,44,107,105,111,48,57,0,0,46,45,108,148,112,0,0,  0,0,132,0,129,96,0,0,     0,0,10,43,0,35,0,0,
    0,60,0,0,0,0,8,0,        0,0,0,52,0,0,0,0,          0,0,0,0,0,0,27,0,         0,122,123,0,0,0,0,0  },
  { 0,0,0,0,0,0,0,0,         0,0,0,0,0,0,248,0,        0,0,0,0,0,81,33,0,        0,0,89,83,186,87,34,0,       // with SHIFT
    0,67,88,68,69,36,0,0,    0,0,86,70,84,82,37,0,     0,78,'B',72,71,90,38,0,    0,0,77,74,85,47,40,0,
    0,59,75,73,79,61,41,0,   0,58,95,76,153,80,63,0,   0,0,142,0,154,0,0,0,      0,0,0,42,0,39,0,0,
    0,62,0,0,0,0,0,0,        0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0  } };
*/
#include <ps2.h>

/*
 * Pin 5 ps2 data pin, pin 6 clock pin
 * Feel free to use whatever pins are convenient.
 */
PS2 kbd(6, 5);

int charcode=0;
int altkey=0;
int ctrlkey=0;
int shiftkey=0;
int altgr_code=0;
int keycode=0;
bool e0code=false;
bool altcode=false;
bool altgrcode=false;
bool capskey=false;
bool numkey=false;
bool LCtrlcode=false;
bool RCtrlcode=false;
int iptalcode=0;
int karbul=0;
String karyaz="";
int val=0;
bool shiftIsActive = false;
int LEDSTATUS=0;
bool scrlkey=false;

void ledayar(){  // *****  bu bölüm klavye ledlerini ayarlar. num+caps+scrl fakat scrl kontrolü eklenmedi.
  if (numkey==0){
    LEDSTATUS= bitClear(LEDSTATUS, 1);
  }else if (numkey==1){
    LEDSTATUS= bitSet(LEDSTATUS, 1);
  }
if (capskey==0){
    LEDSTATUS= bitClear(LEDSTATUS, 2);
  }else if (capskey==1){
    LEDSTATUS= bitSet(LEDSTATUS, 2);
  }
if (scrlkey==0){
    LEDSTATUS= bitClear(LEDSTATUS, 0);
  }else if (scrlkey==1){
    LEDSTATUS= bitSet(LEDSTATUS, 0);
  }
char ack;
kbd.write(0xed);  // send reset code
  ack = kbd.read(); 
//ack = kbd.read(); 
Serial.print("LED AYARLANDI : ");
Serial.println(LEDSTATUS);
kbd.write(LEDSTATUS);// num=2, caps=4, scrolllock=1 binary
  ack = kbd.read(); 
}

void capscontrol(){ // capslock tuşuna basıldığında shift tuşuna kalıcı basılmış olur. 
  if (capskey==1){
    shiftIsActive=true;
    }else if (capskey==0){
     shiftIsActive=false;
    }
}

void kbd_init()   // ps2 klavye ya da usb olup adaptörle kullandığınızda klavye bağlantı için bir kod gönderir
                  // bu koda karşılık RESET kodu gönderildiğinde RESET atar. burası bunun içindir. 
                  // Normalde benim yetiyordu ama arasıra klavye sorun yaratıyordu belki de 5V arduinodan alındığından olabilir
                  // bundan dolayı 2 kez yaptım fakat sorun arduinoya enerji verdikten sonra klavyeyi takarsanız çözülüyor. 
{                 //1 kez reset atmanız yeterli olabilir.
  char ack;
  kbd.write(0xff);  // send reset code
  delay(10);
  ack = kbd.read();  // byte, kbd does self test
  delay(10);
  ack = kbd.read();  // another ack when self test is done
  delay(100);
kbd.write(0xff);  // send reset code
  delay(10);
  ack = kbd.read();  // byte, kbd does self test
  delay(10);
  ack = kbd.read();  // another ack when self test is done
  delay(300);
}


void turkishcar(){// ********** Burası türkçe karakterler için yapıldı. Normalde seri monitöre asc127 kodundan fazla verdiğinizde
                  // garip karakter koyar. fakat serial print ile "Ş" karakteri yazarsanız UNICODE olarak seri monitore 
                  // yazar. ya da serial.write (0xc5;Serial.write(0x9E) gibi 2 komutu arka arkaya yollarsanız yazabiliyor.
    if (val==76 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ş");
  }
  if (val==76 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("Ş");
  }
  if (val==82 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("i");
  }
  if (val==82 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("İ");
  }
  if (val==91 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ü");
  }
  if (val==91 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("Ü");
  }
  if (val==84 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ğ");
  }
  if (val==84 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("Ğ");
  }
  if (val==73 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ç");
  }
  if (val==73 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("Ç");
  }
  if (val==65 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ö");
  }
  if (val==65 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("Ö");
  }
   if (val==67 && shiftIsActive==0 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("ı");
  }
  if (val==67 && shiftIsActive==1 && altgrcode==0){
    Serial.print(" basilan karakter : ");
    Serial.println("I");
  }
    capscontrol();
}

void setup()
{
  Serial.begin(9600);
  Serial.println("test *şiğüöçı * deneme");
  kbd_init();
  delay (100);
  ledayar();
  Serial.print(" Ş karakteri Serial.write ile unicode utf-8 olarak yazılır : ");
  Serial.write (0xc5);Serial.write(0x9E);// Ş karakterini ister Serial.print("Ş") olarak yazın isterseniz bu şekilde.
  Serial.println(" ");
  Serial.println(" ");
  
}

/*
 * get a keycode from the kbd and report it back to the
 * host via the serial line.
 */
void loop()
{
  capscontrol(); // capslock durumunu kontrol ediyor.
  unsigned char code;
   String char_code="";
  shiftIsActive = false;      // shift tuşu basılmadı her defasında sıfırlanıyor. sadece anlık geldiğinde çalışıyor
  for (;;) { /* ever */ 
    
    /* read a keycode */
    code = kbd.read();   // kodlar her okunduğunda işleme giriyor sonrasında bir kod daha okunuyor. 
    /* send the data back up */
    Serial.println(code, HEX);
    //delay(20);  /* twiddle */


  char_code=(code);
  keycode=char_code.toInt();// *** kodlar HEX olarak okunur. burada decimal şekle çevrilerek okunması kolay olur. 


  karbul=0; // **** bu bir işarettir. Şayet IF cümlelerinden biri çalışmışsa bu karakter değil komuttur. Çalışmamışsa karakterdir.
Serial.print(" karakter kodu DEC : ");
Serial.println(keycode);

  if (keycode==18 && iptalcode==0  || keycode==89 && iptalcode==0){// left shift =18 Right shift=89 kontrolü
    karbul=1;
    shiftIsActive =!shiftIsActive ;  // bool değişken burada tersine çevriliyor. toggle gibi.
    Serial.print(" shift is active: ");
    Serial.println(shiftIsActive);
  }
    if (keycode==119 && iptalcode==0 ){// NUMLOCK ruşuna basıldı mı basıldıysa değişkeni ayarla keypad kısmı karakter değişimi
    karbul=1;
    numkey =!numkey ;
    Serial.print(" NUMLOCK: ");
    Serial.println(numkey);
    ledayar();  
  }
    if (keycode==88 && iptalcode==0 ){// capslock tuşuna basıldıysa caplock değişkeni değişir ve led yakma kısmına gider.
    karbul=1;
    capskey =!capskey ;
    Serial.print(" CAPSLOCK: ");
    Serial.println(capskey);
    ledayar();  
  }

  
  if (keycode==224 && iptalcode==0){  // CTRL gibi özel tuşlarda aktiftir.E0 kodu gelir. 2 aynı tarama kodunu ayırma şekli.
                                      // mesela Keypad LEFT ile normal LEFT butonları aynı koddur. Bazen de sağ sol ayrımıdır
    karbul=1;
    e0code =!e0code ;
    Serial.print(" e0code ");
    Serial.println(e0code);
  }
  if (keycode==17 && e0code==0 && iptalcode==0){// ALT tuşuna basıldı mı? ALT =17 AltGR=e0 17
    karbul=1;
    altcode =!altcode ;
    Serial.print(" altcode ");
    Serial.println(altcode);
  }

  if (keycode==17 && e0code==1 && iptalcode==0){// ALTGR tuşuna basıldı mı? Alt tuşu ile aynı ama başında E0 var. 
    karbul=1;
    altgrcode =!altgrcode ;
    Serial.print(" altgrcode ");
    Serial.println(altgrcode);
  }
  
  if (keycode==20 && e0code==0 && iptalcode==0){// LEFT CTRL tuşuna basıldı mı?  
    karbul=1;
    LCtrlcode =!LCtrlcode ;
    Serial.print(" Left Ctrl ");
    Serial.println(LCtrlcode);
  }
  if (keycode==20 && e0code==1 && iptalcode==0){//  RIGHT CTRL tuşuna basıldı mı?
    karbul=1;
    RCtrlcode =!RCtrlcode ;
    Serial.print(" Righr Ctrl");
    Serial.println(RCtrlcode);
  }

  if (keycode==224 && iptalcode==1){  // CTRL gibi özel tuşlarda aktiftir. bu şekilde F0 dan sonra geldimi kontrol
    karbul=1;
    e0code =false ;
    Serial.print(" e0code ");
    Serial.println(e0code);
  }
  if (keycode==17 && e0code==0 && iptalcode==1){// ALT tuşuna basıldı mı? ALT =17 AltGR=e0 17 bu şekilde F0 dan sonra geldi mi kontrol
    karbul=1;
    altcode =false ;
    Serial.print(" altcode ");
    Serial.println(altcode);
  }

  if (keycode==17 && e0code==1 && iptalcode==1){// ALTGR tuşuna basıldı mı? Alt tuşu ile aynı ama başında E0 var. 
    karbul=1;
    altgrcode =false ;
    Serial.print(" altgrcode ");
    Serial.println(altgrcode);
  }
  
    if (keycode==20 && e0code==0 && iptalcode==1){// LEFT CTRL tuşuna basıldı mı?  
    karbul=1;
    LCtrlcode =false ;
    Serial.print(" Left Ctrl ");
    Serial.println(LCtrlcode);
  }
    if (keycode==20 && e0code==1 && iptalcode==1){//  RIGHT CTRL tuşuna basıldı mı?
    karbul=1;
    RCtrlcode =false ;
    Serial.print(" Righr Ctrl");
    Serial.println(RCtrlcode);
  }
  
  
  if (karbul==0 && iptalcode==0){
    
    val=keycode;
   // if (val==76 && val==82 && val==91 && val==84 && val==73 && val==65){// türkçe tarama kodlarına geldiyse türkçe yaz bölümüne git.
   //   turkishcar();
   // }
    if (val==122 && e0code==1 && altgrcode==0 && numkey==0){
    Serial.print(" basilan karakter : ");// F1 gibi diğer özel anahtarları da bu şekilde ekleyebilirsiniz.
    Serial.println("PAGE DOWN");
    }else if (val==125 && e0code==1 && numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("PAGE UP");
    }else if (val==108 && e0code==1 && numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("HOME");
    }else if (val==105 && e0code==1 && numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("END");
    }else if (val==122 && e0code==0 && numkey==0 ){// e0 code Keypad kısmında gelmez. bu ve altındakiler KP tuşudur.
    Serial.print(" basilan karakter : ");// F1 gibi diğer özel anahtarları da bu şekilde ekleyebilirsiniz.
    Serial.println("PAGE DOWN");
    }else if (val==125 && e0code==0 && numkey==0 ){
    Serial.print(" basilan karakter : ");
    Serial.println("PAGE UP");
    }else if (val==108 && e0code==0 && numkey==0 ){
    Serial.print(" basilan karakter : ");
    Serial.println("HOME");
    }else if (val==105 && e0code==0 && numkey==0 ){
    Serial.print(" basilan karakter : ");
    Serial.println("END");
    }else if (val==112  && numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("INSERT");
    }else if (val==113 && numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("DEL");
    }else if (val==107 && e0code==1){// bu tuşlar harici yön tuşlarıdır ve E0 kod gelmiştir.
    Serial.print(" basilan karakter : ");
    Serial.println("LEFT");
    }else if (val==117 && e0code==1  ){
    Serial.print(" basilan karakter : ");
    Serial.println("UP");
    }else if (val==114 && e0code==1){
    Serial.print(" basilan karakter : ");
    Serial.println("DOWN");
    }else if (val==116 && e0code==1){
    Serial.print(" basilan karakter : ");
    Serial.println("RIGHT");
    }else if (val==107 && e0code==0 && numkey==0){// bu ve altındaki tuşlar KP tuşlarıdır numlock basılmamışsa çalışır.
    Serial.print(" basilan karakter : ");
    Serial.println("LEFT");
    }else if (val==117 && e0code==0&& numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("UP");
    }else if (val==114 && e0code==0&& numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("DOWN");
    }else if (val==116 && e0code==0&& numkey==0){
    Serial.print(" basilan karakter : ");
    Serial.println("RIGHT");
    }else if (val==74 && e0code==1){
    Serial.print(" basilan karakter : ");// F1 gibi diğer özel anahtarları da bu şekilde ekleyebilirsiniz.
    Serial.println("/");
    } else   if (val==90 && e0code==1){
    Serial.print(" basilan karakter : ");
    Serial.println("KP_ENTER");
    } else if (val==76 || val==82 || val==91 || val==84 || val==73 || val==65 || val==67){// türkçe tarama kodlarına geldiyse türkçe yaz bölümüne git.
      turkishcar();
    }else if(altgrcode==0){
    karyaz=ScancodeToASCII[shiftIsActive][val & 127];// basılan karakteri yazmak için baştaki tablodan al.
    Serial.print(" basilan karakter altgrcode 0 : ");
    Serial.println(karyaz);
    capscontrol();
    }
    //**************************************
    // büttün iflerde serialprint yapmanıza gerek kalmaz. bir değişkene aktrıp burada yazdırabilirsiniz
    // hafızayı daha uygun kullanmış olursunuz.
   
  }
  if (numkey==1){// numlock tuşuna basıldıysa KP tuşlarının 1 2 3 gibi yazmansını sağlar. 
    if (val==112 || val==105 || val==114 || val==122 || val==107 || val==115 || val==116 || val==117 || val==108 || val==125){
      karyaz=ScancodeToASCII[shiftIsActive][val & 127]; // shift tuşu önemli değil her ikisindede yeralırlar.
    Serial.print(" basilan karakter KP: ");
    Serial.println(karyaz);
    }
    
  }
  
  if (altgrcode==1){
    karyaz=altgrcodeToASCII[val & 127];
    Serial.print(" basilan karakter altgrcode 1 : ");
    Serial.println(karyaz);
  }
  if (iptalcode==1){ // iptal kodu sıfırlar ve yeni tuş bekler.
    karbul=0;
    iptalcode=0;

  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
  }

  
  if (keycode==240 && iptalcode==0){//  F0 kodu geldiyse elinizi butondan çekmişsinizdir. iptal kod başlar herşey sıfırlanır.
    karbul=1;
    e0code=false;
    altcode=false;
    altgrcode=false;
    LCtrlcode=false;
    RCtrlcode=false;
    iptalcode=1;
    capscontrol();
    Serial.print(" iptal code: ");
    Serial.println(iptalcode);
  
  }
    
  } //burası sonsuz for döngüsü bitme noktasıddır. kodlar okundukça işlem yapılır kod gelmezse işlem yapılmaz.

}
