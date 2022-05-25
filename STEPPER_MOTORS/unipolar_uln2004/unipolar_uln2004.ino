/*
 * Bipolar stepper motor speed and direction control with Arduino.
 * Full step control.
 * This is a free software with NO WARRANTY.
 * https://simple-circuit.com/
 */

// include Arduino stepper motor library
//#include <Stepper.h>

// change this to the number of steps on your motor
//#define STEPS 20

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//Stepper stepper(STEPS, 8, 9, 10, 11);
const int wire1 =  8;
const int wire2 =  9;
const int wire3 =  10;
const int wire4 =  11;
int speeddelay=100;

//const int button =  4; // direction control button is connected to Arduino pin 4
//const int pot    = A0; // speed control potentiometer is connected to analog pin 0

void setup()
{Serial.begin(9600);
  // configure button pin as input with internal pull up enabled
 
  pinMode(wire1, OUTPUT);
  pinMode(wire2, OUTPUT);
  pinMode(wire3, OUTPUT);
  pinMode(wire4, OUTPUT);
}



void loop()

{
  //delay(10000);
  speeddelay=2000;
  Serial.println ( " 1. bolum");
  for (int i = 0; i <= 2; i++) {
    
  digitalWrite (wire1,HIGH);//A
    digitalWrite (wire3,HIGH);// B
  digitalWrite (wire2,LOW);//A NOT
  digitalWrite (wire4,LOW);// B NOT
  delay(speeddelay);

digitalWrite (wire1,LOW);
  digitalWrite (wire3,HIGH);
  digitalWrite (wire2,HIGH);
  digitalWrite (wire4,LOW);
  delay(speeddelay);

 digitalWrite (wire1,LOW);
   digitalWrite (wire3,LOW);
  digitalWrite (wire2,HIGH);
  digitalWrite (wire4,HIGH);
  delay(speeddelay);

  digitalWrite (wire1,HIGH);
    digitalWrite (wire3,LOW);
  digitalWrite (wire2,LOW);
  digitalWrite (wire4,HIGH);
  delay(speeddelay);
 
 Serial.println(i); 
 
}
delay(1000);
//***********************************************************
Serial.println ( " 2. bolum");
for (int i=0;i<=2;i++){

   digitalWrite (wire1,LOW);//A
    digitalWrite (wire3,LOW);// B
  digitalWrite (wire2,HIGH);//A NOT
  digitalWrite (wire4,HIGH);// B NOT
  
  delay(speeddelay);
digitalWrite (wire1,LOW);
  digitalWrite (wire3,HIGH);
  digitalWrite (wire2,HIGH);
  digitalWrite (wire4,LOW);
  delay(speeddelay);

  digitalWrite (wire1,HIGH);
  digitalWrite (wire3,HIGH);
  digitalWrite (wire2,LOW);
  digitalWrite (wire4,LOW);
  delay(speeddelay);

  digitalWrite (wire1,HIGH);
  digitalWrite (wire3,LOW);
  digitalWrite (wire2,LOW);
  digitalWrite (wire4,HIGH);
  delay(speeddelay);
  
Serial.println(i); 
}
delay(1000);
}
 
