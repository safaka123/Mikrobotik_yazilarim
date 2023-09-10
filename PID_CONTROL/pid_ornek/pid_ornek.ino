/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
int led = 11 ;

int PWMS=0;
void setup()
{Serial.begin(9600);
pinMode(led, OUTPUT);
  //initialize the variables we're linked to
  Input = analogRead(0);
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  
  Input = analogRead(0);
  myPID.Compute();
  Serial.print("SETPOINT : ");Serial.println(Setpoint);
  Serial.print("INPUT POT : ");Serial.println(Input);
  
  
  Serial.print("OUTPOINT : ");Serial.println(Output);
  Serial.println("=====================");
  Serial.println(" ");

  PWMS=Output;
  //analogWrite(led,PWMS);
  analogWrite(led,Output);
delay(500);
}
