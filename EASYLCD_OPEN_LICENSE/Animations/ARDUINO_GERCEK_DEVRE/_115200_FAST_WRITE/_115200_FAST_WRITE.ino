// Arduino ve EASYLCD en hızlı yazabileceği mod. HArdware serial ve Geri bildirim kullanır. LCD R bekler. R=Ready
  int a = 5;   // değişken
   int b = 0;   // değişken
      int saat=0;
     int dak=0;
     int san=0;
   //   String stringOne ="denek";
      String stringThree = "LCDWR 1,1-";//+a;
       String YAZI ="";
 //     String stringnew =  String(53, HEX);
 //     int thisByte = 3;
      char inChar ;


void setup() {
 
    delay(10);
    
  Serial.begin(115200);
 
}

void EkranHex(){
       
  char inChar ; 
          while (inChar == 'R'){
        
         inChar = (char) Serial.read();
    
  }
  delay(10);
    }
  void EkranYaz(){
          
        Serial.print(stringThree);
char inChar ; 
         while (inChar != 'R'){
            
         inChar = Serial.read();
  }
 delay(10);
    }

void loop() {
  // put your main code here, to run repeatedly:
  stringThree= "LCDDD" ;EkranYaz();
  delay(100);
  
    saat=0;
      dak=0;
      san=0;
      stringThree= "LCDWR 1,2-FASTEST WRITE" ;EkranYaz();//YAZI="";
      stringThree= "LCDWR 1,2-FASTEST WRITE" ;EkranYaz();//YAZI="";
      stringThree= "LCDWR 2,3-"+YAZI+ saat +"  " ; EkranYaz();stringThree= "LCDWR 2,6-/ "+ YAZI+dak +"  " ; EkranYaz();stringThree= "LCDWR 2,11-/ " +YAZI + san +" " ; EkranYaz();
 
     while (saat<59){
        stringThree= "LCDWR 2,3-"+YAZI+  saat +"  " ; EkranYaz(); saat=saat+1 ;
           while (dak<59){
            stringThree= "LCDWR 2,6-/ " +YAZI+ dak +"  " ; EkranYaz(); dak=dak+1 ;
  saniye:              
       
         if ( san > 59 ) {} else {  
                    stringThree= "LCDWR 2,11-/ " +YAZI+ san +" " ; EkranYaz(); san=san+1 ;goto saniye; }
               
                 san=0 ; stringThree= "LCDWR 2,11-/ "+YAZI+ san +" " ; EkranYaz() ; 
           
           }
           dak=0; stringThree= "LCDWR 2,6-/ "+YAZI+ dak +"  " ; EkranYaz(); 
      
    }
    saat=0; stringThree= "LCDWR 2,3-"+YAZI+ saat +"  " ; EkranYaz();


}
