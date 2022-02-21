    /*
  XD-62B-TTP229-4x4-Keypad-16
  modified on 11 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

  based on forum.hobbycomponents.com examples
*/

/* Define the digital pins used for the clock and data */
#define SCL_PIN 10
#define SDO_PIN 11

/* Used to store the key state */
byte Key;
byte gelen[16] = {1,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup()
{
  /* Initialise the serial interface */
  Serial.begin(9600);
  /* Configure the clock and data pins */
  pinMode(SCL_PIN, OUTPUT);  
  pinMode(SDO_PIN, INPUT); 
}

/* Main program */
void loop()
{
  /* Read the current state of the keypad */
  Key = Read_Keypad();
  //Serial.print(gelen[0]," , ");
  /* If a key has been pressed output it to the serial port */
if (Key){
    for(int i = 1; i < 16; i++)
{
  Serial.print(gelen[i]);
}
Serial.println("");
}

  if (Key)
    Serial.println(Key);

  /* Wait a little before reading again 
     so not to flood the serial port*/
  delay(100);
}


/* Read the state of the keypad */
byte Read_Keypad(void)
{
  byte Count;
  byte Key_State = 0;

  /* Pulse the clock pin 16 times (one for each key of the keypad) 
     and read the state of the data pin on each pulse */
  for(Count = 1; Count <= 16; Count++)
  {
    digitalWrite(SCL_PIN, LOW); 
    delayMicroseconds(150); // Stabilite olarak kullanıldı. datasheet teki ilk kalkışı ve LOW seviyesinde 
                            //sinyalin ortasından ölçmek için50-500 arası kullanılır.
                            // Bu gecikme olmadığında bazen bir üsttekini ya da bir alttakini yazıyordu.
      gelen[Count]=digitalRead(SDO_PIN); 
    /* If the data pin is low (active low mode) then store the 
       current key number */
    if (!digitalRead(SDO_PIN))
      Key_State = Count; 
      
    digitalWrite(SCL_PIN, HIGH);
  }  
  //Serial.print(gelen[0]," , ");
  return Key_State; 
}

