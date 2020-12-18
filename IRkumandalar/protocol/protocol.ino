
int RECV_PIN = 11;

void setup() {
  Serial.begin(9600);
  
  Serial.println(" IR gönder ");


}

void loop() {
  Serial.println(" IR gönder ");
int temp=0;uint16_t basla=0;
uint16_t temp2=0;
uint16_t temp3=0;
while (pulseIn(RECV_PIN,HIGH)>21000){
  }
  while (temp==LOW){
temp=digitalRead(RECV_PIN);
  // Serial.print(" temp :  ");Serial.println(temp); 
  }
 temp3=0;
while (temp3==0)   {
   
  temp=digitalRead(RECV_PIN);
  
  if (temp==0 && temp2==0){
    temp2=micros();
    //Serial.print(" süre :  ");Serial.println(temp2);
   }
   if (temp==1 && temp2>0){
    temp3=micros();
    //Serial.print(" sssssüre :  ");Serial.print(temp2);Serial.print("  ,  ");Serial.println(temp3);
   }
  
  }
  if (temp3<temp2){
    loop();
  }
  temp=temp3-temp2;
 Serial.print(" süre :  ");Serial.print(temp2);Serial.print("  ,  ");Serial.println(temp3); 
 Serial.print(" Başlangıç palsi mikrosaniye ");Serial.println(temp);
delay(1000);
}
