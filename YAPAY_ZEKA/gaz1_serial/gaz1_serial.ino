String gelendata="";
int kontrol;
int analogtemp;
int analoghum;
int analogtvo;
int analogeoc2;
int analogm135;
int degertemp=0;
int degerhum=0;
int degertvo=0;
int degereoc2=0;
int degerm135=0;
const int GledPin = 11;
const int YledPin = 12;
const int RledPin = 13;
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); // RX, TX

void setup() {
  pinMode(A0, INPUT);   // Set A0 as an input
  pinMode(A1, INPUT);   // Set A0 as an input
  pinMode(A2, INPUT);   // Set A0 as an input
  pinMode(A3, INPUT);   // Set A0 as an input
  pinMode(GledPin, OUTPUT);
  pinMode(YledPin, OUTPUT);
  pinMode(RledPin, OUTPUT);
 // pinMode(9, OUTPUT);   // Set pin 9 as an output for the LED
  Serial.begin(9600);   // Start serial communication
  //Serial.println("hello");
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}
void oku(){
    analogtemp = analogRead(A0);  // Read the analog value from the potentiometer
  analoghum = analogRead(A1); 
  analogtvo = analogRead(A2); 
  analogeoc2 = analogRead(A3); 
  analogm135 = analogRead(A4);

  degertemp = (analogtemp*4.88)/10;  
  int analoghum_2=analoghum;
  int analoghum_1=analoghum-155;
  int moddeger=0;
  if (analoghum_2<410){
    moddeger=(analoghum%100);moddeger=(((analoghum-moddeger)/100));analoghum=analoghum-155;analoghum=analoghum+moddeger*36;
  }
  if (analoghum_2>440 && analoghum<460){
    moddeger=(analoghum%100);moddeger=(((analoghum-moddeger)/100));analoghum=analoghum-155;analoghum=analoghum+moddeger*40;
  }
  if (analoghum_2>459 && analoghum<550){
    moddeger=(analoghum%100);moddeger=(((analoghum-moddeger)/100));analoghum=analoghum-155;analoghum=(analoghum+(moddeger*40)+5);
  }
  if (analoghum_2>549 && analoghum<650){
    moddeger=(analoghum%100);moddeger=(((analoghum-moddeger)/100));analoghum=analoghum-155;analoghum=(analoghum+(moddeger*40)+20);
  }
  if (analoghum_2>649){
    moddeger=(analoghum%100);moddeger=(((analoghum-moddeger)/100));analoghum=analoghum-155;analoghum=(analoghum+(moddeger*40)+40);
  }
  //degerhum = map(analoghum, 0, 1023, 0, 100);  // Map it to the 0-255 range
  degerhum=analoghum/10;
  degertvo = map(analogtvo, 0, 1023, 0, 6000);  // Map it to the 0-255 range
  degereoc2 = map(analogeoc2, 0, 1023, 0,6000);  // Map it to the 0-255 range
  degerm135 = map(analogm135, 0, 1023, 0,255);  // Map it to the 0-255 range
int atla=1;
String mixstr=String(atla)+","+String(degerhum)+","+String(degertemp)+","+String(degerm135)+","+String(degertvo)+","+String(degereoc2)+","+String(atla);

//Serial.print("moddeger: ");Serial.println(moddeger);
int deger1=(degerhum*0.70)*1.6;
//Serial.print("temp: ");Serial.println(degertemp);
//Serial.print("HUM: ");Serial.println(degerhum);Serial.println(analoghum);//Serial.println(analoghum_2);
//Serial.print("TVO: ");Serial.println(degertvo);
//Serial.print("EOC2: ");Serial.println(degereoc2);
//Serial.print("M135: ");Serial.println(degerm135);
//Serial.print("MIX: ");
Serial.println(mixstr);


}
void ledgoster(){
  mySerial.println(kontrol);
  delay(100);
  int uzun=kontrol+1;
  mySerial.println(uzun);
  delay(100);
  //gelendata.length();
  //uzun=uzun-1;
  String aktar=gelendata.substring(uzun,uzun+1);
  mySerial.println(gelendata);
  delay(100);
  
  
  mySerial.println(aktar);
  delay(100);
  int cevap=aktar.toInt();
  mySerial.println(cevap);
  delay(100);
  
  if (cevap==0){
    digitalWrite(GledPin, HIGH);
    digitalWrite(YledPin, LOW);
    digitalWrite(RledPin, LOW);
  }
  if (cevap==1){
    digitalWrite(GledPin, LOW);
    digitalWrite(YledPin, HIGH);
    digitalWrite(RledPin, LOW);
  }
  if (cevap==2){
    digitalWrite(GledPin, LOW);
    digitalWrite(YledPin, LOW);
    digitalWrite(RledPin, HIGH);
  }
  
  
}

void loop() {
  if (Serial.available()) {
    gelendata = Serial.readString();
    //Serial.print("gelendata "); Serial.println(gelendata);
    if (gelendata=="OKU"){
      oku();
    }
    kontrol = gelendata.indexOf('WRITE');
    if (kontrol>0){
      ledgoster();
    }
    
  }

delay(1000);
}
