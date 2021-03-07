int satirno=0;
int sutunno=0;
int clk=3;
int mreset=2;
int keyin=4;
int tuskod=0;

void setup() {
  // put your setup code here, to run once:
pinMode(keyin, INPUT); 
pinMode(mreset, OUTPUT);
pinMode(clk, OUTPUT);
digitalWrite(mreset, LOW); // sistem reset
Serial.begin(9600);
Serial.println("TUS BASIMI");

}

void tuskontrol(){

 
tuskod = digitalRead(keyin);
if (tuskod==LOW){
  Serial.println("TUS BASILDI");
}

  
}

void tustara(){
  //digitalWrite(mreset, HIGH); // sistem reset
//Serial.println("resetlendi");
//delay(1000);
Serial.print(satirno);Serial.print("   ");Serial.println(sutunno);
tuskontrol();
for (satirno = 1; satirno <= 10; satirno++){
digitalWrite(clk, LOW); //  satır sayıcı ve multiplexer sayıcı clk=HIGH;
delay(100);
digitalWrite(clk, HIGH);// satır sayıcı ve multiplexer sayıcı clk=LOW;
  if (satirno<10){
  Serial.print(satirno);Serial.print("   ");Serial.println(sutunno);
  tuskontrol();
  }

}
satirno=0;
sutunno++;
if (sutunno==19){
 digitalWrite(mreset, LOW); // sistem reset
  satirno=0;
  sutunno=0;
  Serial.println("basa donuldu");
}
//Serial.print(satirno);Serial.print(" for sayac bitti   ");Serial.println(sutunno);
Serial.println("satir bitti sutun 1 kaydi");
delay(300);

 


  
}

void loop() {
  digitalWrite(mreset, HIGH); // sistem reset
Serial.println("resetlendi");
  tustara();

}
