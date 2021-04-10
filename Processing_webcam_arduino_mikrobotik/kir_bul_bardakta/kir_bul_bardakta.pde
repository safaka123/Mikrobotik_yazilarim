import processing.video.*;




//video kütüphanemizi tanımladık
//import processing.video.*;

//kameram adında nesnemizi yarattık.

Capture kameram;
color yakin;
int genislik=640;
int yukseklik=480;
int toplamsay=0;
int toplamx=0;
int toplamy=0;
float enbuyuk=700;

int ann=0;
int anm=0;

//Ana fonksiyonumuzu başlatıyoruz.

void setup()
{
  
size(640,480);

printArray(Capture.list());

//kameram=new Capture(this,width,height,30);

kameram=new Capture(this,Capture.list()[1]);
kameram.start();
//RGB olarak takip edilecek renk değerimizi belirledik
yakin=color(75,75,75);
}

void elipsciz()
{
if(enbuyuk<20)
{
fill(yakin);
strokeWeight(10.0);
stroke(0);
ellipse(toplamx,toplamy,16,16);
}
 //print(toplamx);print("      ");println(toplamy);


}





void draw()
{
if(kameram.available()) {
kameram.read();
}

//açacağımız kamera penceresinde her pixeli aktif ettik.

kameram.loadPixels();

//Tek bir ekran olmasını istedik.bunu image(kameram,random.width,random.height) olarak değiştirirseniz ne demek istediğimi anlarsınız.

image(kameram,0,0);

//Karşılaştırma fonksiyonumuz için değer atadık.

 enbuyuk=700;

//takibe başlangıç değerlerinı set ettik.

 int yakinx=0;
 int yakiny=0;
 
//satır ve sütun taramasını gerçekleşitiyoruz.

for(int i=0; i<kameram.width; i++)
{
for(int j=0; j<kameram.height; j++)
{

//yer atadık.taramayı genişlikten aldım arkadaşlar.

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
print(kirmizi);print("    ");print(yesil);print("    ");println(mavi);
}}}

//Sağlaması durumunda bulunduğu bölgede bir elipse şekli oluşturması ve içinin o renk ile dolu olmasını sağladık.

toplamsay=toplamsay+1;
if (toplamsay==1){   // 30 kez koordinat toplayıp 1 kez işaretleme yapıyor ortalama değere göre
  
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
 
 
 

// 10 kez alacak 1 kez ortalama yer belirleyip orada kalacak. elips te dahil. titreşmesin diye koordinatların ortalaması
// x kendi ortalaması y kendi ortalaması


}
