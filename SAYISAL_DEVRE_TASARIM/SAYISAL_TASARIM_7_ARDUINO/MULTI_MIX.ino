//#define S_DATA B1;
#define S_CLK 8
#define S_DATA 9
#define S_LOAD 13
#define S_DATA_S 11
const byte interruptPin1 = 2;
const byte interruptPin2 = 3;

int kes=2;
byte d;
int kart1=0;
int kart2=0;
int vartop=0;
int temp2=40;
int temp22=8;
int temp3=150;
int temp33=15;
int tempoku=0;

void setup()
{
  pinMode(S_LOAD, OUTPUT);
   pinMode(S_CLK, OUTPUT);
   pinMode(S_DATA, INPUT);
   pinMode(S_DATA_S, OUTPUT);
  kes=0;
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  DDRD = B11110010; // set PORTD (digital 1,4-7) to outputs
  attachInterrupt(digitalPinToInterrupt(interruptPin2),kesme, LOW);//CHANGE,LOW,HIGH,RISING,FALLING
  attachInterrupt(digitalPinToInterrupt(interruptPin1),kesme2, LOW);
  Serial.begin(9600);
  PORTD = B11111111 & B10110000; 
  delay(20);
  PORTD = B11111111 & B11000000; 
  delay(20);
  PORTD = B11111111 & B00000000; 
  delay(20);
  MOTOR_KONT();
}

void kesme2()
{
  kes=2;
  Serial.print("millis 3: ");Serial.println(millis());
}

void kesme()
{
  kes=1;
}
void oku()
{
  PORTD = B11111111 & B00010000; 
  delay(10);
  seri_oku();kart1=vartop;
  PORTD = B11111111 & B10010000; 
  delay(10);
  PORTD = B11111111 & B00100000; 
  delay(10);
  seri_oku();kart2=vartop;
  PORTD = B11111111 & B10100000; 
  delay(10);
  PORTD = B11111111 & B00000000; 
  Serial.println("");
  Serial.print("kart1  :");Serial.println(kart1,BIN);
  Serial.print("kart2  :");Serial.println(kart2,BIN);
  Serial.println("OKUMA TAMAM ");
  if (kart1==1){
    temp2=40;// program başındakiyle aynı olacak. Normalde burada kullanılmıyor. video için burada. ******
    temp3=150;// program başındakiyle aynı olacak. Normalde burada kullanılmıyor. video için burada.****** 
  }
  delay(1000);
  kes=0;
}

void MOTOR_KONT()// step motor kontrolleri
{
 PORTD = B11111111 & B00110000;
 digitalWrite(S_CLK, HIGH); // *********************  S_CLK ları const ile tanımla.
 delay(1200);
 tempoku=digitalRead(S_DATA);
 Serial.println(S_DATA);
 Serial.println(tempoku);
 if (tempoku==1){
  Serial.println("motor 1 gonder");
  motor1_gonder();tempoku=0;
 }
  digitalWrite(S_CLK, LOW);
  delayMicroseconds(200);
  PORTD = B11111111 & B01000000;
  
 digitalWrite(S_CLK, HIGH);
 tempoku=digitalRead(S_DATA);
 if (tempoku==1){
  motor2_gonder();tempoku=0;
 }
  digitalWrite(S_CLK, LOW);


  
}

void motor1_gonder()// step motor kontrolleri
{
 if (temp2>=temp22)
  {
  temp2=temp2-temp22;
 
 //Serial.print("millis 2 : ");Serial.println(millis());
 // Serial.print("temp2 : ");Serial.println(temp2);
 delay(100);
  PORTD = B11111111 & B10110000;  
   digitalWrite(S_LOAD, LOW); 
   delayMicroseconds(200);
  shiftOut(S_DATA_S, S_CLK, MSBFIRST, temp22);
  digitalWrite(S_LOAD, HIGH); 
  delayMicroseconds(200);
  delay(100);
  PORTD = B11111111 & B00000000;
  delay(10);
  }
  kes=0;
}

void motor2_gonder()// step motor kontrolleri
{int temp4=0;
 if (temp3>=temp33)
  {
  temp3=temp3-temp33;
  temp4=B01000000|temp33;// yön bilgisi eklendi. sola doğru olması için. 
 
 // Serial.print("millis 3: ");Serial.println(millis());
  Serial.print("temp3 : ");Serial.println(temp4,BIN);
 delay(100);
  PORTD = B11111111 & B11000000;  
   digitalWrite(S_LOAD, LOW); 
   delayMicroseconds(200);
  shiftOut(S_DATA_S, S_CLK, MSBFIRST, temp4);
  digitalWrite(S_LOAD, HIGH); 
  delayMicroseconds(200);
  delay(100);
  PORTD = B11111111 & B00000000;
  delay(10);
  }
  kes=0;
}

void seri_oku()
{int value=0;
vartop=0;

  digitalWrite(S_LOAD, LOW);
  digitalWrite(S_LOAD, HIGH);
  for (int i = 0; i < 8; ++i) {
    if (i<7){
    value =digitalRead(S_DATA);
    vartop=vartop+value;vartop=vartop<<1;
    }else{
      value =digitalRead(S_DATA);
    vartop=vartop+value;
    }
    
    digitalWrite(S_CLK, LOW);
    delay(10);
    digitalWrite(S_CLK, HIGH);
    delay(10);
  }
  //Serial.println(value,BIN); 
}

void loop()
{
  if(kes==1){
    oku();
    detachInterrupt(1);
    attachInterrupt(digitalPinToInterrupt(interruptPin2),kesme, LOW);
  }
    if(kes==2){
    MOTOR_KONT();//oku_gonder();
    detachInterrupt(0);
    attachInterrupt(digitalPinToInterrupt(interruptPin1),kesme2, LOW);
  }
  
  Serial.print("LOOP  icinde INT NO : ");Serial.println(kes);
  Serial.print("temp2 : ");Serial.println(temp2);
  Serial.print("temp3 : ");Serial.println(temp3);
  delay(200);
}
