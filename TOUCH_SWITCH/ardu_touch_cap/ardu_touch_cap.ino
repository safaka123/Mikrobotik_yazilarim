//The LED code:
 int inPin = A5;             // analog 5 
int say=0;
int val = 0;                 // where to store info from analog 5
int pin10 = 10;         // output of red led
int yak=0; // led yanık sönük durumunu gösterir
int kontrol=0; // while döngüsüne kaçıncı kez girdi
int degistir=0; // buton bırakıldı mı şayet devamlı basılıysa 1 olur. 
void setup() {
  Serial.begin(9600);
pinMode(pin10, OUTPUT);
}
// aşağıdaki program led yanıp söndüren Toggle FF kısmıdır. 
void yaksondur(){
 if (yak==0){
  digitalWrite(pin10,LOW);
 }
 if (yak==1){
  digitalWrite(pin10,HIGH);
 }
  
}

void loop() {
  pinMode(inPin, OUTPUT); // Analog pim dijital pim olarak ayarlanır. 
  digitalWrite(inPin,HIGH);// analog pimdeki kondansatör şarj edilir. 
  //delay(10); // şarj edilmesi için bir süre verilir. kondansatör küçük değerlerde gecikme verilmese de olabilir. 
  pinMode(inPin, INPUT); // kondansatör şarj olduktan sonra giriş olarak ayarlanarak kondansatörün üzerindeki gerilim ölçülür.
  val = analogRead(inPin); 
 
 
  kontrol=0;
 while (val >=700 ) {
  val = analogRead(inPin);
  
  kontrol=1;
  if (val>140){  //  ölçülen değer 300 üzerindeyse butona basılmıştır.
    yak=1;degistir=1;//digitalWrite(pin10, !digitalRead(pin10));
  }
  
  Serial.print("okunan deger: icerde  ");Serial.println(val); 
  
 }

 
  if (kontrol==0 && degistir==1){
    degistir=0;
    say=say+1;}
  if (say==2){yak=0;yaksondur();say=0;}
  if (say==1){yak=1;yaksondur();}
    
  Serial.print("Buton birakildi mi: ");Serial.println(degistir);
  Serial.print("kontrol: ");Serial.println(kontrol);
 Serial.print("okunan deger:sss  ");Serial.println(val); 
 Serial.println("==============================================");
  delay(500);
}
