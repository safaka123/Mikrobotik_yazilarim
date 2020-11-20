
 uint32_t addr=0x010379;
 uint8_t x=0;
 uint8_t y=0;
 uint8_t z=0;
 int sil=0x0080;
 uint8_t yaz=0;

void setup (void)
{
  
  
  Serial.begin(9600);

}

void loop(){
  
  z=addr;
  x=addr>>16;
  Serial.print(" HEX :  ");Serial.print(x,HEX);Serial.print("  ");Serial.println(x,BIN);
  y=addr>>8;
  Serial.print(" HEX :  ");Serial.print(y,HEX);Serial.print("  ");Serial.println(y,BIN);
  
  Serial.print(" HEX :  ");Serial.print(z,HEX);Serial.print("  ");Serial.println(z,BIN);
  
// if (addr==0){
//  addr=0x010000;
// }
delay(10000);
} 
