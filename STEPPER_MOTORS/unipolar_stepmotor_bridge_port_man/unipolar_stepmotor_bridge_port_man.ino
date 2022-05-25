/*
 * UNIPOLAR stepper motor speed and direction control with Arduino.
 * Full step control. PORT MANIPULATION KULLANILDI. 
 * This is a free software with NO WARRANTY.
 *  https://www.mikrobotik.com/wp2/
 */


const int wire1 =  8;
const int wire2 =  9;
const int wire3 =  10;
const int wire4 =  11;
int speeddelay=1000;
int temp1=0;
const int homebutton =  4;
const int directionbutton =  2;
int counter=0;// ileri ya da geri son ilerleme sayısı.
int direct=0;//  yön değiştirme 0 ileri 1 geri
int totalcount=0;// toplam gidilen yol.
int homesw=0;
int cont=0;

void setup()
{Serial.begin(9600);

pinMode(homebutton, INPUT);
pinMode(directionbutton, INPUT);

DDRB=B11111111;// tüm B portları output ayarlandı.

}

void D1(){
  int TEMP= B00001001;
  PORTB=TEMP;
  delay(speeddelay);
}
void D2(){
  int TEMP= B00000011;
  PORTB=TEMP;
 delay(speeddelay);
}
void D3(){
  int TEMP= B00000110;
  PORTB=TEMP;
  delay(speeddelay);
}
void D4(){
  int TEMP = B00001100;
  PORTB= TEMP;
  delay(speeddelay);
}

void loop()
{
 cont=0;
    while(digitalRead(homebutton)==LOW)
{
if (cont==0){
   direct=1;
   homesw=1;
   //counter=counter+1;
   Serial.println("direction : "+String(direct));
  }
  cont=1;
}
cont=0;
    while(digitalRead(directionbutton)==LOW)
{
if (cont==0){
   direct=direct = !direct;// toggle çalışma
   Serial.println("direction : "+String(direct));
  }
  cont=1;
}



  //Serial.println("direction : "+String(direct));
  speeddelay=750;
  if (direct==0){
  counter--;
  }
 if (direct==1){
  counter++;
  }
  
  if (counter==5){
    counter=1;
  }
  if (counter<1){
    counter=4;
  }
  Serial.println(" Counter : "+String(counter,DEC));
  

 /* if (digitalRead(homebutton)==LOW){
   direct=direct = !direct;// toggle çalışma
   homesw=1;
   Serial.println("direction : "+String(direct));
  }
  */
  
switch (counter) {
  case 1:
    D1();
    break;
  case 2:
    D2();
    break;
  case 3:
    D3();
    break;
  case 4:
    D4();
    break;  
}
if (direct==0 && homesw==1){
  totalcount--;
}
if (direct==1 && homesw==1){
  totalcount++;
}
if (totalcount<1){
  //direct=direct = !direct;// toggle çalışma
  totalcount=1;
  Serial.println ("******** LiMiT SW BASILDI***********");
}
Serial.println("TOTAL COUNT : "+String(totalcount,DEC));

}
 
