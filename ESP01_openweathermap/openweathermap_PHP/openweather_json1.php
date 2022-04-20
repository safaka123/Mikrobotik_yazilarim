<?php


function WeatherUrl($url){
		$cn = curl_init();
		curl_setopt($cn, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($cn, CURLOPT_URL, $url);    // get the contents using url
		$weatherdata = curl_exec($cn); // execute the curl request
		curl_close($cn); //close the cURL
		return $weatherdata;
}


//$url="http://api.openweathermap.org/data/2.5/weather?q=Delhi,IN,IN&units=metric&appid=d62ca415a6b61d8927e6d87b8c420c9f";
$url="https://api.openweathermap.org/data/2.5/weather?q=izmir,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric&lang=tr";

$response=WeatherUrl($url);
//echo $response;

//echo "<br>";
//echo "<br>";

$data = json_decode($response);

	
$temp = $data->main->temp ;// Celsius
$minimum_temp = $data->main->temp_min; // Celsius
$maximum_temp = $data->main->temp_max ; // Celsius 
$feels_like = $data->main->feels_like ;// Celsius
$pressure = $data->main->pressure ;//hPa
$humidity = $data->main->humidity ;// %
$coordlon=$data->coord->lon;
$clouds=$data->clouds->all;
$speed=$data->wind->speed ;// m/s
$w_deg=$data->wind->deg  ;// degree
$winddt=$data->dt;
date_default_timezone_set("Europe/istanbul");

$updatedate=date("d-m-Y ",$winddt). "<br>";
$updatetime=date("H:i:s O",$winddt). "<br>";
$updatebir=date("d-m-Y H:i:s O",$winddt);
//echo 'update : '. $updatebir;echo "<br>";
$sunrise = $data->sys->sunrise;
$sunrisebir=date("d-m-Y H:i:s O",$sunrise);
//echo 'sunrise : '. $sunrisebir;echo "<br>";
$sunrisedate=date("d-m-Y ",$sunrise). "<br>";
$sunrisetime=date("H:i:s O",$sunrise). "<br>";

$sunset = $data->sys->sunset;
$sunsetbir=date("d-m-Y H:i:s O",$sunset);
//echo 'Sunset : '. $sunsetbir;echo "<br>";
$sunsetdate=date("d-m-Y ",$sunset). "<br>";
$sunsettime=date("H:i:s O",$sunset). "<br>";

$country = $data->sys->country;
$city = $data->name;


// alt satırlarda İ harfini i harfine çeviriyorum.
$searchchar   = 'İ';
$konum = strpos($city, $searchchar);
if ($konum === false) {
  //  echo "'$city' dizgesi içinde '$searchchar' dizgesi yok";
    $bak=$city;
} else {
   // echo "'$city' dizgesi içinde '$searchchar' dizgesi var";
  //  echo " ve $konum. karakterden başlıyor";
    $bak=str_replace("İ","I",$city);// burada İ harfi i harfine çevriliyor.
}
$city=$bak;
/*echo "<br>";
echo "<br>";


echo 'winddt : '.$updatedate." ".$updatetime;
echo "<br>";
echo 'Sunrise : '.$sunrisedate." ".$sunrisetime;
echo "<br>";
echo 'Sunset : '.$sunsetdate." ".$sunsettime;
echo "<br>";


echo 'Temperature : '. $temp;echo "<br>";
echo 'Minimum Temperature : '. $minimum_temp;echo "<br>";
echo 'Maximum Temperature : '. $maximum_temp;echo "<br>";
echo 'Feels Like : '. $feels_like;echo "<br>";
echo 'Pressure : '. $pressure;echo "<br>";
echo 'Humidity : '. $humidity;echo "<br>";
echo 'coordlon : '. $coordlon;echo "<br>";
//echo 'winddt : '. $winddt;echo "<br>";

echo "<br>";
echo "<br>";
*/

$t=time();
//echo(date("d-m-Y",$t));echo "<br>";
//echo(date("H:i:s O",$t));echo "<br>";
$date=date("d-m-Y  H:i:s O",$t);
$date1=date("d-m-Y",$t);
$hour1=date("H:i",$t);
$CMno=date("d",$t);

//$time=date("H:i:s O",$t);
//echo "<br>";
$cweekday=(date("w",$t));
//echo "<br>";
$cdayname=(date("D",$t));
//echo "<br>";
$cweekno=(date("W",$t));
//echo "<br>";
$cmonthname=(date("M",$t)); // apr may sep gibi kısa isim verir.

$cmonthday= (date("t",$t)); 

//echo(date("F",$t));// april semtember gibi tam isim verir.


$response1["Temperature"] = trim($minimum_temp);
$response1["Min_Temp"] = trim($minimum_temp);
$response1["Max_Temp"] = trim($maximum_temp);
$response1["Feels_Like"] =trim($feels_like);
$response1["Pressure"] =trim($pressure);
$response1["Humidity"] =trim($humidity);
$response1["Country"] =trim($country);
$response1["City"] =trim($city);
$response1["Clouds"] =trim($clouds);
$response1["Speed"] =trim($speed);
$response1["W_deg"] =trim($w_deg);
$response1["update"] =trim($updatebir);
$response1["sunrise"] =trim($sunrisebir);
$response1["sunset"] =trim($sunsetbir);
$response1["Cdate"] =trim($date);
$response1["CMname"] =trim($cmonthname);
$response1["CWno"] =trim($cweekno);
$response1["CDno"] =trim($cweekday);
$response1["CDname"] =trim($cdayname);
$response1["CMday"] =trim($cmonthday);
$response1["datesh"] =trim($date1);
$response1["hoursh"] =trim($hour1);
$response1["CMno"] =trim($CMno);


//echo "<br>";
/*
// timezone ile birlikte unixtime çözümü. ================
$timezone  = 3;
$unitime=$winddt;
$unitime=$unitime+3600*($timezone);

echo 'zaman : '.gmdate("l d F Y h:i:s T +$timezone",$unitime). "<br>";echo "<br>";
//=============================================================


echo "<br>";
echo $response;			 
echo "<br>";
echo "<br>";








date_default_timezone_set("Asia/Bangkok");
echo date_default_timezone_get() . "<br>";
echo date("l jS \of F Y h:i:s A") . "<br>";
date_default_timezone_set("Europe/istanbul");
echo date_default_timezone_get() . "<br>";
echo date("l jS \of F Y h:i:s A") . "<br>";


// Show JSON response
    echo json_encode($response1);
 */   


//echo "<br>";
//echo "<br>";
//echo "<br>";
    
//    date_default_timezone_set("Europe/istanbul");
//$t=$winddt;// unix kodunu normal tarihe cevirmek.
//echo ("denenem"). "<br>";
//echo(date("d-m-Y ",$t)). "<br>";
//echo(date("H:i:s O",$t)). "<br>";

//echo "<br>";
//echo "<br>";
//echo "<br>";

$connect_web = simplexml_load_file('http://www.tcmb.gov.tr/kurlar/today.xml');

$usd_isim=  $connect_web->Currency[0]->Isim;   
$usd_buying = $connect_web->Currency[0]->BanknoteBuying;
$usd_selling = $connect_web->Currency[0]->BanknoteSelling;
$usd_cross = $connect_web->Currency[0]->CrossRateOther;
$usd_cr1="USD";
$usd_cr2="USD";

$euro_isim=  $connect_web->Currency[3]->Isim;    
$euro_buying = $connect_web->Currency[3]->BanknoteBuying;
$euro_selling = $connect_web->Currency[3]->BanknoteSelling;
$euro_cross = $connect_web->Currency[3]->CrossRateOther;
$euro_cr1="EURO";
$euro_cr2="USD";

//print_r($connect_web);

$array = array(
"USD" => (array('buying'=>floatval($usd_buying),'selling'=>floatval($usd_selling),'cross'=>floatval($usd_cross),'CR1'=>$usd_cr1,'CR2'=>$usd_cr2)),
 "EURO" =>  (array('buying'=>floatval($euro_buying),'selling'=>floatval($euro_selling),'cross'=>floatval($euro_cross),'CR1'=>$euro_cr1,'CR2'=>$euro_cr2)),
 "openweathermap"=>($response1)
 
  );
  


echo json_encode($array);





?>