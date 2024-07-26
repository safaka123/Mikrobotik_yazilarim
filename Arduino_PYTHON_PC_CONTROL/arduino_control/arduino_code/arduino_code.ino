int sw1=1;
int sw2=1;
int sw3=1;

void setup(){
 pinMode(2, INPUT); 
 pinMode(3, INPUT);
 pinMode(4, INPUT); 
 Serial.begin(9600);        
}

void loop(){
sw1=0;
//while (digitalRead(2)==0){
// sw1=1; 
//}
if (digitalRead(2)==1){
  sw1=1;
}
//Serial.println (sw1);

//while (digitalRead(3)==0){
  //sw1=2; 
//}
if (digitalRead(3)==0){
  sw1=2;
}

//Serial.println (sw1);
//while (digitalRead(4)==0){
//  sw1=3; 
//}
if (digitalRead(4)==0){
  sw1=3;
}
//Serial.println (sw1);

switch (sw1){
  case 1:
    Serial.println ("SC57");
    break;
  case 2:  
    Serial.println ("SC56");
    break;
  case 3:  
    Serial.println ("SC55");
    break;
    
}



    delay(500);
}
