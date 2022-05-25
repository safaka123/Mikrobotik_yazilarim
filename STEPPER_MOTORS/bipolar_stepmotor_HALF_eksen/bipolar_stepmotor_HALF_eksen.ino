/*
 * BIPOLAR stepper motor speed and direction control with Arduino.
 * Full step control.
 * This is a free software with NO WARRANTY.
 * https://www.mikrobotik.com/wp2/
 */


const int wire1 =  8;
const int wire2 =  9;
const int wire3 =  10;
const int wire4 =  11;
int speeddelay=2000;
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
 
  pinMode(wire1, OUTPUT);
  pinMode(wire2, OUTPUT);
  pinMode(wire3, OUTPUT);
  pinMode(wire4, OUTPUT);

}

void D1(){
    digitalWrite (wire1,HIGH);//A
    digitalWrite (wire2,LOW);//A NOT
    digitalWrite (wire3,LOW);// B
    digitalWrite (wire4,LOW);// B NOT 
  delay(speeddelay);
}
void D2(){
    digitalWrite (wire1,HIGH);//A       3
    digitalWrite (wire2,HIGH);//A NOT
    digitalWrite (wire3,LOW);// B
    digitalWrite (wire4,LOW);// B NOT 
  delay(speeddelay);
}

void D3(){
    digitalWrite (wire1,LOW);//A     2
    digitalWrite (wire2,HIGH);//A NOT
    digitalWrite (wire3,LOW);// B
    digitalWrite (wire4,LOW);// B NOT
  delay(speeddelay);
}
void D4(){
  digitalWrite (wire1,LOW);//A     1
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,LOW);// B NOT
  delay(speeddelay);
}
void D5(){
      digitalWrite (wire1,LOW);//A        8
    digitalWrite (wire2,LOW);//A NOT
    digitalWrite (wire3,HIGH);// B
    digitalWrite (wire4,LOW);// B NOT 
  delay(speeddelay);
}
void D6(){
    digitalWrite (wire1,LOW);//A
    digitalWrite (wire2,LOW);//A NOT     7
    digitalWrite (wire3,HIGH);// B
    digitalWrite (wire4,HIGH);// B NOT 
  delay(speeddelay);
}
void D7(){
    digitalWrite (wire1,LOW);//A        6
    digitalWrite (wire2,LOW);//A NOT
    digitalWrite (wire3,LOW);// B
    digitalWrite (wire4,HIGH);// B NOT 
  delay(speeddelay);
}
void D8(){
    digitalWrite (wire1,HIGH);//A        5
    digitalWrite (wire2,LOW);//A NOT
    digitalWrite (wire3,LOW);// B
    digitalWrite (wire4,HIGH);// B NOT 
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
  
  if (counter==9){
    counter=1;
  }
  if (counter<1){
    counter=8;
  }
  //Serial.println(" Counter : "+String(counter,DEC));
  

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
  case 5:
    D5();
    break;
  case 6:
    D6();
    break;

  case 7:
    D7();
    break;
  case 8:
    D8();
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
 
