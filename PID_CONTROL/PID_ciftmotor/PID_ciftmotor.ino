int led = 9 ;
#define m1oku 6
#define m2oku 7
#define button 8
int butonsay=20;
int say=0;
int times[23] = {1948,1868,1778,1706,1628,1524,1470,1390,1300,1220,1155,1067,986,920,834,760,674,593,520,434,360,280,200};
int pwms[23] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230};
int pwmsx=0;

int yenipwm=150;
int led3 = 11 ;
double m1val=0;
double m2val=0;
int pot_pin = A0; //Potansiyometre Pinimizi ve ismini tanımladık.
int pot_deger = 0; //Potansiyometremizin başlangıç değerini atadık.
extern volatile unsigned long timer0_millis;

void setup() {
 Serial.begin(9600);
 pinMode(led, OUTPUT); // led değişkeni yani 9 numaralı pin ÇIKIŞ olarak tanımlandı. 
 pinMode(led3, OUTPUT);
 pinMode(m1oku, INPUT);
 pinMode(m2oku, INPUT);
 pinMode(button, INPUT);
}

void pulsebekle() {
  float timesx=0;
  float sondeger=0;
  float sondeger2=0;
  say=say+1;
  float m1valo=0;
  float m2valo=0;
    while(digitalRead(m1oku)==HIGH)
  {//Serial.println(" sifirhigh ");
    }
   while(digitalRead(m1oku)==LOW)
  {
    //Serial.print("m1oku low  ");Serial.println(m1oku,BIN );
  }

  noInterrupts ();
timer0_millis = 0;
interrupts ();
  m1valo=millis();
   m1val = pulseIn(m1oku, LOW,5000000);
  
for (int x = 0; x < 23; x++) {  // pwm değeri ve zaman aralıklarını belirleme
  if (m1val<times[x] & m1val>times[x+1]){
 timesx=times[x];
 sondeger=times[x]-times[x+1];
 sondeger2=sondeger/10; 
 pwmsx=pwms[x];   
Serial.print("sondeger2 : " );Serial.println(sondeger2,2);


    Serial.println(m1val);
  //  Serial.println(x);
    Serial.println(times[x]);
    Serial.println(times[x+1]);
    Serial.println(pwms[x]);
  }
   
  
}
for (int x = 1; x < 11; x++) {// pwm birler basamağı ekleme
  timesx=timesx-sondeger2;
  Serial.print( "kontrol : ");Serial.println(timesx);
  if (timesx<m1val){
    Serial.print( "hesaplanan son deger : ");Serial.println(timesx);
    pwmsx=pwmsx+x;
    Serial.print( "son pwm : ");Serial.println(pwmsx);
    Serial.println("====================== ");
    Serial.println(" ");
    break;
  }
}
analogWrite(led,pwmsx);

}

void loop() {
  
 pot_deger = analogRead(pot_pin); // Potansiyometrenin bağlı olduğu pini(A0) Analog olarak okuduk ve pot_deger değişkenine atadık.
//pot_deger değişkeni 0-1023 arasında değer alacaktır. (10 Bit’lik ADC olduğu için) Biz bu değişkeni Arduino kartımız maksimum 8 bit’lik PWM çıkışı verebildiği için 0-255 arasında sınırlandırmamız gerekmektedir. Bu dönüşümü map fonksiyonu ile yapacağız.
 pot_deger = map(pot_deger,0,1023,0,255); // pot_deger değerini 0-1023 arası değerden 0-255 arası değere dönüştürdük.
Serial.print("pot_deger : ");Serial.println(pot_deger);
analogWrite(led3,pot_deger); // 0-255 arasına sınırlandırılan değeri led çıkışına yaz.
analogWrite(led,pwmsx);

pulsebekle();
delay(500);
}
