unsigned long timecode=1649642615;
unsigned long yearsn=31556926;
unsigned long  monthsn=2629743;
unsigned long weeksn=604800;
float daysn=86400;
const long hoursn=3600;
int FLAG=0; // leap year control
int GMT=3; // timezone 
int GMTHOUR;// HOUR + TIMEZONE
long temp1=0;
long temp2=0;
float temp3=0.00;
float temp4=0.00;
int YEAR=0;
float yearcount=0;
int MONTH=0;
int DAY=0;
int WEEK=0;
int weekday=0;
int monthday=0;
int leapyear=0;
int HOUR=0;
int MINUTE=0;
int minute1=0;
int SECOND=0;
String monthyaz;// monthname
String gunyaz;// day name

void setup() {
Serial.begin(9600);
}

void loop() {
YEAR=(timecode/yearsn)+1970;
DAY=(int(timecode/daysn)-(int(timecode/yearsn)*365.24))+1;// 0.0.1970 1 jan =1
MONTH=int(timecode/monthsn)%12;// gerçek hesaplama aygunhesap kısmında yapılıyor.Çıkan sonuç 3.5 olduğunda 4. ay oluyor 
Serial.print(" MONTH        :  ");Serial.println(MONTH);
WEEK=((timecode/weeksn)-int((timecode/yearsn)*52.177))+1;
if (YEAR%4==0){  // 2021 de leap year dan dolayı olabilir gün 1 fazla geliyor. *******************
  leapyear=0;
  
}else{
  leapyear=4-(YEAR%4);// 2021 1  gün fazla veriyor **************************
}

aygunhesap();
weekdayhesap();



// *********** saat hesabı ***************
  long hours  = timecode / hoursn; 
  long hours2  = hours % 24;
  long seconds  = timecode % hoursn; 
  long minute2  = seconds / 60;
  long minute1  = seconds % 60;
 HOUR=hours2;
 MINUTE=minute2;
 SECOND=minute1;
 if (HOUR+GMT>24){//GMT eklendikten sonra 24 saati geçiyorsa saati 24 saat çıktıktan sonraya göre ayarla.
  GMTHOUR=HOUR+GMT;
 GMTHOUR=GMTHOUR-24;
 DAY=DAY+1;weekdayhesap();
 if (monthday==0){monthday=1;}
 }else{
  GMTHOUR=HOUR+GMT;
 }
if (FLAG==1){   // Unixtime sadece GMT=0 saatini verir. GMT +3 dediğimizde gece yarısını geçip 1 sonraki güne girer. GMT +3 e göre yeniden gün düzenlemesi yapar. 
  weekdayhesap();
  
  Serial.print(" flag kontrol       :  ");Serial.println(FLAG);
  FLAG=0;
}

 //NEW MONTH CALCULATE
//temp1=timecode / monthsn;
//temp2=timecode % monthsn;
//temp2=temp2 / 86400;
Serial.print(" YEAR         :  ");Serial.println(YEAR);
Serial.print(" MONTH        :  ");Serial.println(MONTH);
Serial.print(" DAY          :  ");Serial.println(DAY);
if (WEEK==0){
  Serial.print(" WEEK         :  ");Serial.print("52nd week of ");Serial.println(YEAR-1);
}else{
Serial.print(" WEEK         :  ");Serial.println(WEEK);
}
Serial.print(" LEAP YEAR    :  ");Serial.println(leapyear);
Serial.print(" MONTH NAME   :  ");Serial.println(monthyaz);
Serial.print(" DAY OF MONTH :  ");Serial.println(monthday);
Serial.print(" DAY OF WEEK  :  ");Serial.println(weekday);
Serial.print(" DAY NAME     :  ");Serial.println(gunyaz);
Serial.print(" HOUR         :  ");Serial.println(HOUR);
Serial.print(" HOUR+GMT+3:00:  ");Serial.println(GMTHOUR);
Serial.print(" MINUTE       :  ");Serial.println(MINUTE);
Serial.print(" SECOND       :  ");Serial.println(SECOND);
Serial.println("==============================");
Serial.println("");
delay(1000);
}


void weekdayhesap(){// haftanın günü hesabı ve ismi==========
String gunler[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat","Sun"};

weekday=(DAY-((WEEK-1)*7))-leapyear;
if (weekday<1){
  
  WEEK=WEEK-1;
  weekday=(DAY-((WEEK-1)*7))-leapyear;
}else{
  temp1=0;
}
gunyaz=gunler[weekday-1];
}
//======================================


void aygunhesap(){// Ayın günü hesabı ve MONTH hesabı artık yıllara göre hesaplanır. 
  int monthcount=0;// Ay sayısı saydırılır. Gün sayısından kaç ay hesaplanarak çıkarıldığını tutar. 
//  String gunler[] = {"Sun", "Mon", 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'};

String aylar[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int aysay[] = {31,28,31,30,31,30,31,31,30,31,30,31};
temp1=DAY;Serial.print(" DAYCONTROL          :  ");Serial.println(temp1); 
if (DAY<=31){MONTH=1;
// bu bölüm sadece 31 den küçük gün sayısı içindir. 1-31 ocak arası. Diğerlerinde Ay hesabı while döngüsünde yapılır.
monthyaz=aylar[MONTH-1 ];
  monthday=temp1;
}else{


if (temp1>aysay[MONTH-1]){//Gün sayısı bulunduğu ayın sayısından büyükse hesap başlar. 
 
while (temp1>aysay[MONTH-1]){// Gün sayısı bulunduğu  ayın sayısından büyükse hesap başlar.

for (int i = 0; i <MONTH+1; i++) {// MONTH sayısında bir büyüğüne kadar kontrole devam. Özellikle Aysonu ve başı için.

if (i==1&leapyear==0){ // artık yıl kontrolü Artık yılda FLAG ayarlanır. 
  temp2=aysay[i]+1;
  FLAG=1;// artık yıl ise bayrak 1 oluyor. saatte değişikliğe gidiliyor. 
  
}else{
  temp2=aysay[i];
}
temp1=temp1-temp2;

Serial.print("temp2  ");Serial.println(temp2);
Serial.println(temp1);
Serial.println("day of the month is subtracted.");
monthcount=monthcount+1; // AY sayısı yeniden hesaplanıyor. Son çıkarılan tam aydan 1 fazlası. 
if (i<12){temp2=aysay[i+1];}//ay sayısı 12 den küçükse 1 sonraki ayın gün sayısını alır.
if (temp1<=temp2){// burada temp1 kalan gün sayısını temp2 aylık günsayısı ile kontrol eder. 28-29-30-31 gibi. 
                  // 12. ay olduğunda başka ay yok bundan dolayı kalan sayıyı kontrol eder. eski temp2 ye göre. 
                  // bunda şubat 28 ve 29 ile diğer ayların 30. günleri için ihtiyaç duyuldu. 
  temp2=i+1;
  MONTH=monthcount+1;// Ay sayısı burada yeniden hesaplanır ve +1 demek, bir sonraki aya geçildi demektir. 
  monthyaz=aylar[MONTH-1 ];
  monthday=temp1;
  break;
}
}}
}
}
// bu bölüm sadece 31 den küçük gün sayısı içindir. 1-31 ocak arası. Diğerlerinde Ay hesabı while döngüsünde yapılır.
monthyaz=aylar[MONTH-1 ];
  monthday=temp1;
}

