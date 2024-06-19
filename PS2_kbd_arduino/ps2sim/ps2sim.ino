/*
 * Bu program çok basit olarak ps2 karakter kodunu yollamanızı sağlar.
 * bununla birlikte ps2 kod çözücü programda kbd_init gibi ledayar gibi veri gönderme programları ACK sinyali beklediğinden 
 * önce bir kaç kez butona basın ki bu kilitlenme açılsın. 
 * Şayet bunu kendinize göre ayarlayacaksanız ACK sinyalini önceden yollayarak bu kilitlenmeyi açarsınız
 * sonrasında ise tuşlara basarak tarama kodunuzu gönderebilirsiniz. 
 * Bu tip bir programa neden gerek var. bazen tüm klavyeyi kullanmanıza gerek yoktur sadece bazı tuşları simüle etmeniz gerekebilir. 
 * bu şekilde tuş kodlarını karşı tarafa yollarsınız. Küçük bir klavyeniz olabilir.
 * Program çok basit yapıldı sinyalleri görmeniz için. 
 * Sizler daha uygun hale getirirsiniz. 
 * proteus 8.6 versiyonu kullandım. 
 * 
 */


int data = 5;
int clk=6;
int button1=7;
int but1=0;
int cont=0;


void setup()
{
  pinMode(button1, INPUT);
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  Serial.begin(9600);
  Serial.println("test *şiğüöçı * deneme");

  delay (100);
  Serial.print(" Ş karakteri Serial.write ile unicode utf-8 olarak yazılır : ");
  Serial.write (0xc5);Serial.write(0x9E);// Ş karakterini ister Serial.print("Ş") olarak yazın isterseniz bu şekilde.
  Serial.println(" ");
  Serial.println(" ");
  
}
void loop()
{// ( a ) harfi tarama kodu 1C = 00011100 fakat sinyali tam tersi vereceğiz. 00111000

but1=digitalRead(button1);


if (but1==0){ 
  Serial.println( "basilan karakter yollandi");
cont=1;
digitalWrite(data, LOW);//start

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);  
  
digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);// 1

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);
  
digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
 delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//parity

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delay(70);
}

if (but1==1 && cont==1 ){
// F0+karakter yolla.
// F0 tuş bırakma karakteri yolla. F0=11110000 gönderilirken tersi olur. 00001111
Serial.println ("F0 yollandi buton birakıldi");
digitalWrite(data, LOW);//start

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);  
  
digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);
  
digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
 delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//parity

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delay(70);

// son basılan karakter kodu aşağıdadır. 
Serial.println ("birakilan karakter yollandı");
Serial.println ("");
digitalWrite(data, LOW);//start

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);  
  
digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);// 1

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);//1

digitalWrite(clk, LOW);
 delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);
  
digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
 delayMicroseconds(50);

digitalWrite(data, LOW);//0

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, LOW);//parity

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  delayMicroseconds(50);

digitalWrite(data, HIGH);

digitalWrite(clk, LOW);
  delayMicroseconds(50);
digitalWrite(clk, HIGH);
  

  cont=0;
  but1=0;
}
delay(70);







// bir değişken koy basılırsa 1 olsun f0 geldiğinde sıfırlansın

//28 f0 28 gelmesi lazım



  
}
