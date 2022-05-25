/*
 * Bipolar stepper motor speed and direction control with Arduino.
 * Full step control.HALF step control. SPEED breake control
 * This is a free software with NO WARRANTY.
 * https://www.mikrobotik.com/wp2/
 */


const int wire1 =  8;
const int wire2 =  9;
const int wire3 =  10;
const int wire4 =  11;
int speeddelay=100;
int temp1=0;
int speed_pin = 3;
//const int button =  4; // direction control button is connected to Arduino pin 4
//const int pot    = A0; // speed control potentiometer is connected to analog pin 0

void setup()
{Serial.begin(9600);
  // configure button pin as input with internal pull up enabled
  pinMode(speed_pin, OUTPUT);
  pinMode(wire1, OUTPUT);
  pinMode(wire2, OUTPUT);
  pinMode(wire3, OUTPUT);
  pinMode(wire4, OUTPUT);
  analogWrite(speed_pin, 250);
  
}



void loop()

{
  //analogWrite(speed_pin, 250);
  speeddelay=750;
  Serial.println ( " 1. bolum");
  for (int i = 0; i <= 1; i++) {
  // temp1=B00001101;
  if (i==1){
    analogWrite(speed_pin, 100);
    Serial.print("100 pwm ");
  }
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,LOW);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,HIGH);// B NOT
  
  delay(speeddelay);
  Serial.println ( PORTB,BIN);
  
  
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,LOW);// B
  digitalWrite (wire4,HIGH);// B NOT
  delay(speeddelay);
  Serial.println ( PORTB,BIN);
  
  digitalWrite (wire1,LOW);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,HIGH);// B NOT 
  delay(speeddelay);
  Serial.println ( PORTB,BIN);
   
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,LOW);// B NOT 
  delay(speeddelay);
  Serial.println ( PORTB,BIN);

 
 Serial.println(i); 
 
}

delay(1000);
//***********************************************************
Serial.println ( " 2. bolum");
for (int i=0;i<=1;i++){

  
  digitalWrite (wire1,LOW);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,HIGH);// B NOT
  delay(speeddelay);
Serial.println ( PORTB,BIN);
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,LOW);// B
  digitalWrite (wire4,HIGH);// B NOT
  delay(speeddelay);
Serial.println ( PORTB,BIN);
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,LOW);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,HIGH);// B NOT
  delay(speeddelay);
  Serial.println ( PORTB,BIN);
  digitalWrite (wire1,HIGH);//A
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire3,HIGH);// B
  digitalWrite (wire4,LOW);// B NOT 
  Serial.println ( PORTB,BIN);
  delay(speeddelay);

Serial.println(i); 
}
delay(1000);
}
 
