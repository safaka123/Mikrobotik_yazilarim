/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 Red POS to Arduino pin 11
 Green POS to Arduino pin 10
 560 ohm resistor to both LED NEG and GRD power rail
 More info at: http://goo.gl/kJ8Gl
 Original code improvements to the Ping sketch sourced from Trollmaker.com
 Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
 */

#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
 //  int distance=0;
 int dist=0;
 int hesap=0;
 int blok=0;
 String stringThree ="LCDWR 1,1-";
 int col[17];
 int kalan=0;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.print("LCDDD");delay(300);
  
  Serial.print("LCDSC 15,0");delay(300);
  Serial.print("LCDSC 16,1");delay(300);
  Serial.print("LCDSC 17,2");delay(300);
  Serial.print("LCDSC 18,3");delay(300);
  Serial.print("LCDSC 19,4");delay(300);
//  delay (1000);
 
}

void cevap(){
       
  char inChar ; 
          while (inChar != 'R'){
        
         inChar = (char) Serial.read();
    
  }
  delay(10);
    }



void grafislem(){
  
     
    hesap=dist/5;
    blok=(hesap/5);
    kalan=dist-(hesap*5);
    
   stringThree ="LCDWR 1,1-";
  //   Serial.println(dist);
  //   Serial.println(hesap);
  //   Serial.println(blok);

   //blok=8;
  for (int i=1; i < blok+1; i++){
    col[i]=(0);
   // Serial.println(blok);
  }
 
   if (kalan==0){
      col[blok+1]=(32);
   }
   if (kalan==1){
      col[blok+1]=(1);
   }
   if (kalan==2){
      col[blok+1]=(2);
   }
   if (kalan==3){
      col[blok+1]=(3);
   }
   if (kalan==4){
      col[blok+1]=(4);
   };
   
   for (int i=blok+2; i <17; i++)
   {
     col[i]=(32);
   }
   
  
   
   //Serial.println(kalan);
   Serial.print(stringThree);
   Serial.write(col[1]);
   Serial.write(col[2]);
   Serial.write(col[3]);
   Serial.write(col[4]);
   Serial.write(col[5]);
  Serial.write(col[6]);
  Serial.write(col[7]);
  Serial.write(col[8]);
  Serial.write(col[9]);
  Serial.write(col[10]);
  Serial.write(col[11]);
  Serial.write(col[12]);
  Serial.write(col[13]);
  Serial.write(col[14]);
  Serial.write(col[15]);
  Serial.write(col[16]);
   // cevap();
delay(100);
    
    
    Serial.print("LCDWR 2,1- MESAFE : "); Serial.print(dist);Serial.print("   ");
  //  cevap();
  delay(100);
}

void lcdgoster() {

// Serial.print("LCDWR 1,1-");Serial.print(dist); Serial.write(0x2D);
// karakter 0 beyaz blok, 1 sol 1,2 sol 2, 3 sol 3 , 4 sol 4, 5 siyah blok

 //   Serial.println(dist);
    

    if (dist < 4) {  // This is where the LED On/Off happens
    Serial.print("LCDWR 2,1- kucuk          ");
    delay(300);
}
  
  else if (dist >= 400 || dist <= 0){
    Serial.print("LCDWR 2,1-Out of range    ");
    delay(300);
  }

  else {
    
    grafislem();
  
   /*
   kalan=dist-(hesap*5);
   if (kalan==0){
      col[hesap+1]=(0x32);
   }
   if (kalan==1){
      col[hesap+1]=(0x01);
   }
   if (kalan==2){
      col[hesap+1]=(0x02);
   }
   if (kalan==3){
      col[hesap+1]=(0x03);
   }
   if (kalan==4){
      col[hesap+1]=(0x04);
   }
   
   for (int i=hesap+1; i <=16; i++){
     col[i]=(0x32);
   }
   
   Serial.println(dist);
  // Serial.print(stringThree);
   //Serial.write(col[0]);
  // Serial.write(col[1]);
  // Serial.write(col[2]);
  // Serial.write(col[3]);
  // Serial.write(col[4]);
  // Serial.write(col[5]);
   //Serial.print(col[6]);Serial.print(col[7]);Serial.print(col[8]);Serial.print(col[9]);Serial.print(col[10]);Serial.print(col[11]);Serial.print(col[12]);Serial.print(col[13]);Serial.print(col[14]);Serial.print(col[15]);Serial.print(col[16]);
 
    */  
  };

  }


void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
  dist=distance;
 
 
  lcdgoster();
  delay(50);
}
