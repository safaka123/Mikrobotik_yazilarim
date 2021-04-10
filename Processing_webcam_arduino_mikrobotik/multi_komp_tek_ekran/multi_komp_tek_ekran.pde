/** 
 * Registered Class (v1.0)
 * GoToLoop (2017/Aug/28)
 *
 * Forum.Processing.org/two/discussion/23950/
 * how-to-use-the-draw-function-in-multiple-tabs#Item_8
 */
 
 import processing.video.*;
 import controlP5.*;
 import processing.serial.*;
 
 DropdownList serport, serbaud;
 ControlP5 cp5;
 Capture kameram;
 int sliderValue = 100;
 int myColor = color(0,0,0);
 int temp=100;
 //float temp2=128;
 float tempR=255;
 float tempG=128;
 float tempB=128;
 color yakin;
 float enbuyuk=700;
 int toplamx=0;
int toplamy=0;
int toplamsay=0;
String isim="";
float deger=0;
int portnumber;
int deger2=0;
int buttonpressed1=0;
int buttonpressed2=0;

Serial myPort; 
String inBuffer;
String[] portNames;
String comisim="";
int combaud=0;
int commb=0;  // comb ve comp ikisi de drop down kutusunda seçildikten sonra port açılacak. 
int commp=0;

int kyaz=0; // seri port gönderilecek renk değerleri floattan int şekline çevrilip gönderiliyor.
int yyaz=0;
int myaz=0;
int renkbasla=0;


 
 Textlabel t;
 
 
void setup() {
  cp5 = new ControlP5(this);
  size(600, 600);
  smooth(3);
  frameRate(1);
 
  colorMode(RGB);
  blendMode(REPLACE);
  ellipseMode(CENTER);
  PFont p = createFont("Verdana",14); 
  
 ControlFont font = new ControlFont(p);

 
  fill(-1);//fill(-1);
  stroke(0);
  strokeWeight(2.5);
  frameRate(30);
  printArray(Capture.list());
  kameram=new Capture(this,Capture.list()[0]);
  kameram= new Capture(this, 600, 450,Capture.list()[1]);
 
  seriinit();
  // delay(10000);
  
  
  
  
  
  
  
kameram.start();

yakin=color(0,70,200); // önemsiz başlangıç değerleri

cp5.addSlider("RENKR")
     .setPosition(30,490)
     .setSize(200,20)
     .setRange(0,250)
     .setFont(font)
     .setValue(128)
     ;
cp5.addSlider("RENKG")
     .setPosition(30,520)
     .setSize(200,20)
     .setRange(0,250)
     .setFont(font)
     .setValue(128)
     ;
cp5.addSlider("RENKB")
     .setPosition(30,550)
     .setSize(200,20)
     .setRange(0,250)
     .setFont(font)
     .setValue(128)
     ;     
     
  // create a new button with name 'buttonA'
  cp5.addButton("colorA")
     .setValue(0)
     .setPosition(415,540)
     .setSize(70,55)
     .setFont(font)
     .setColorBackground(#ff1010)
     ;   
     // create a new button with name 'buttonA'
  cp5.addButton("commstop")
     .setValue(0)
     .setPosition(415,450)
     .setSize(70,35)
     .setFont(font)
     .setColorBackground(#ff1010)
     ;   
 t = new Textlabel(cp5,"--",100,100,100,100);// setposition kullanılmazsa x,y,W,H demektir. 
 
 
  
}

void elipsciz()   //bulunan rengin bulunduğu yere elips çizer.
  {
    if(enbuyuk<100)
    {
    fill(yakin);
    strokeWeight(10.0);
    stroke(0);
    ellipse(toplamx,toplamy,16,16);
    //print(toplamx);print("      ");println(toplamy);
    }
       //print(toplamx);print("      ");println(toplamy);
  }


 //<>//



void renkbul(){
  
       if(kameram.available()) {
kameram.read();
}
  kameram.loadPixels();//açacağımız kamera penceresinde her pixeli aktif ettik.

  image(kameram,0,0); //Tek bir ekran olmasını istedik.bunu image(kameram,random.width,random.height) olarak değiştirirseniz ne demek istediğimi anlarsınız.

   enbuyuk=700; //Karşılaştırma fonksiyonumuz için değer atadık.


  
  //takibe başlangıç değerlerinı set ettik.

 int yakinx=0;
 int yakiny=0;
 
 for(int i=0; i<kameram.width; i++)
{
for(int j=0; j<kameram.height; j++)
{
    int yer=i+j*kameram.width;
    color anlik=kameram.pixels[yer];
 //Burada rgb mantığı renk değlerini aldık.

 


float kirmizi=red(anlik);
float yesil=green(anlik);
float mavi=blue(anlik);
float _kirmizi=red(yakin);
float _yesil=green(yakin);
float _blue=blue(yakin);
//dist komutu ile aldığımız değerleri karşılaştırdık
float karsilastirma=dist(kirmizi,yesil,mavi,_kirmizi,_yesil,_blue);
//println(karsilastirma);
//İlk başta değerimize göre durumunu denedik.

  if(karsilastirma<enbuyuk)
  {
  enbuyuk=karsilastirma;
  yakinx=i;
  yakiny=j;
  kyaz=(int)(kirmizi);yyaz=(int)(yesil);myaz=(int)(mavi);
  //print(kirmizi);print("    ");print(yesil);print("    ");println(mavi);
    }
}}

//Sağlaması durumunda bulunduğu bölgede bir elipse şekli oluşturması ve içinin o renk ile dolu olmasını sağladık.

toplamsay=toplamsay+1;
if (toplamsay==1){   // *********************** 30 kez koordinat toplayıp 1 kez işaretleme yapıyor ortalama değere göre **************
  
  toplamx=toplamx/30;
  toplamy=toplamy/30;
 // elipsciz();
  toplamsay=0;
  toplamx=yakinx;
  toplamy=yakiny;
  elipsciz();
  
}else {
  toplamx=toplamx+yakinx;
  toplamy=toplamy+yakiny;
}


  //t.setText("X"+str(mouseX)+"-"+"Y"+str(mouseY)); // tlabele yazılacak bilgi int olarak değil string olarak yazmak için str kullanıldı.
  t.setText("X"+str(toplamx)+"-"+"Y"+str(toplamy));
  if (toplamx>130 && toplamx<340 && toplamy>250 && toplamy<300 ){ // ********* renkli parçanın bulunduğu koordinatı gösterecek. **************   if (mouseY<479){
    
  
  t.draw(this);
   t.setColor(0xffF5F500);
   t.setFont(createFont("arial", 20));
   t.setColorBackground(0xff00FFFF);  //Dark Red
   t.setPosition(toplamx-5, toplamy-20);
   t.setColorBackground(0xff880000);
   
   
  t.setPosition(toplamx-5, toplamy-20);// bu satır t.labelin yazılacağı yeri belirliyor
  // bu olmasaydı yukarıda textlabel satırındaki 100,100 pozisyonuna kalıcı olarak yazacaktı
  
  print(kyaz);print("    ");print(yyaz);print("    ");println(myaz);
  
  // seri port ile Arduinoya gönderilecek. tempR,tempG,tempB,toplamx,toplamy,
while (myPort.available() > 0) {
  //myPort .write("R, "+kyaz+", G, "+yyaz+", B, "+myaz+"\r");
  myPort .write(kyaz+","+yyaz+","+myaz+","+toplamx+","+toplamy+"-"+"\r"); // **********  SERİ PORT GÖNDER
     inBuffer = myPort.readString();   
    if (inBuffer != null) {
  if (inBuffer.equals("OK")==true) {
      print(inBuffer);println("den");
    } 
    inBuffer="";
  }  
  } 

  
  }
  
}

 // *****************  SLIDER ayar yerlerinin kontrolü *****************
void draw() {
 //background((color) random(#000000));
 background(60,150,0);
 
 if (renkbasla==1){
   renkbul();
 }

}

 
   void RENKR(float theColor) {
  myColor = color(theColor);
  tempR=theColor;
  println("a slider event. setting background to "+theColor);
  //println("a slider event. setting background to "+myColor);
  yakin=color(tempR,tempG,tempB);
  fill(tempR,tempG,tempB);
    rect(300, 490, 55, 55, 7);
    //ellipse(width>>1, height>>1, width>>1, height>>1);
  
}

   void RENKG(float theColor) {
  myColor = color(theColor);
  tempG=theColor;
  println("a slider event. setting background to "+theColor);
  //println("a slider event. setting background to "+myColor);
  yakin=color(tempR,tempG,tempB);
  fill(tempR,tempG,tempB);
    rect(300, 490, 55, 55, 7);
    //ellipse(width>>1, height>>1, width>>1, height>>1);
  
  
}

   void RENKB(float theColor) {
  myColor = color(theColor);
  tempB=theColor;
  println("a slider event. setting background to "+theColor);
  //println("a slider event. setting background to "+myColor);
  yakin=color(tempR,tempG,tempB);
  fill(tempR,tempG,tempB);
    rect(300, 490, 55, 55, 7);
    //ellipse(width>>1, height>>1, width>>1, height>>1);
  
  
}

// function colorA will receive changes from **********  bu ekran renk okumayı başlatacak. ****************
// controller with name colorA
public void colorA(int theValue) {
  println("a button event from colorA: "+tempR+"  "+tempG+"  "+tempB);
  buttonpressed1=1;
}
public void commstop(int theValue) {
  println("COM PORT CLOSED");
  buttonpressed2=1;
  renkbasla=0;
  myPort .stop();
}

    
    //***************   DROPDOWN  KONTROL *************************
void controlEvent(ControlEvent theControlEvent) 
{
/*  if (theControlEvent.isFrom(serport))
  {  
    println("Menu 11111");
    
  }
  if (theControlEvent.getName().equals("serbaud"))
  {
    println("Menu 22222");
 }*/
  
  
  if (theControlEvent.isController()) {
    if (buttonpressed1==1 || buttonpressed2==1){ // controller butonlarda da aynı yere geliyor buton değişkenine göre de burada kontrol ediliyor.
      buttonpressed1=0;
      buttonpressed2=0;
      println(" buton basimi ");
    } 
    else 
    {
    println("event 22 from controller : "+theControlEvent.getController().getValue()+" from "+theControlEvent.getController());
    float deger=theControlEvent.getController().getValue();
    deger2=(int)(deger); // float değeri int değere çevirdim.
    String deger1=theControlEvent.getController().getName(); // seçilen ismi saklar. 
    println("deger : "+deger+"   "+deger1+"   "+deger2);

// ***************  SERİ PORT AYARLARI DROPDOWN LİSTESİNDEN ALINIR VE PORT AÇILIR.*************************    
    
    if(deger1=="SerPort"){
      //println(portNames[deger2]);
      commp=1;comisim=portNames[deger2];
      println(comisim);
      
      }
    if(deger1=="SerBaud"){
      // deger1=theControlEvent.getController().getStringValue();
      
      if (deger==0){
        combaud=2400;commb=1;
        println(combaud);
       }
      if (deger==1){
        combaud=4800;commb=1;
        println(combaud);
       }
      if (deger==2){
        combaud=9600;commb=1;
        println(combaud);
       }
      if (deger==3){
        combaud=19200;commb=1;
        println(combaud);
       }
      if (deger==4){
        combaud=57600;commb=1;
        println(combaud);
       }
      if (deger==5){
        combaud=115200;commb=1;
        println(combaud);
       }
  // Open the port you are using at the rate you want:
       if (commb==1 && commp==1){
        myPort = new Serial(this, comisim, combaud);
        myPort .write("PORT OPENED");
        renkbasla=1;
        //myPort .stop();
       }
      }
  }
}
}

void seriinit(){//****************** seriport ayarlama *********************
PFont pfont = createFont("Arial", 12, true);
   serport = cp5.addDropdownList("SerPort")
    .setPosition(300, 450)
    .setItemHeight(20)// seçenek satır yüksekliği
    .setBarHeight(20)// 
    .setColorActive(color(255,128))
    .setSize(100,120)
    //.setControlFont(new ControlFont(createFont("Arial", 20), 20));
    .setFont(pfont);
    
   // List all the available serial ports:
    portNames = Serial.list(); //Seri portları bir array içerisinde toplar. 
    for(int i = 0 ; i < portNames.length; i++) { // array uzunluğu kadar for döngüsü çalışır. 
    serport.addItem(portNames[i], i); // dropbox için item ekleme.
  println(portNames[i]);}
    
    
  
  serbaud = cp5.addDropdownList("SerBaud")
    .setPosition(500,450)
    .setItemHeight(20)// seçenek satır yüksekliği
    .setBarHeight(20)// 
    .setColorActive(color(255,128))
    .setSize(100,120)
    //.setControlFont(new ControlFont(createFont("Arial", 20), 20));
    .setFont(pfont);
    
  serbaud.addItem("2400", 0);
  serbaud.addItem("4800", 1);
  serbaud.addItem("9600", 2);
  serbaud.addItem("19200", 3);
  serbaud.addItem("57600", 4);
  serbaud.addItem("115200", 5);
  
  background(60,150,0);
  
  //while (temp>80) { } 
   
}


  
  
