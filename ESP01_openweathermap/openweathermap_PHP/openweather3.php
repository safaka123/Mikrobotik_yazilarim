<?php





$url = "https://api.openweathermap.org/data/2.5/weather?q=izmir,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric&lang=tr&mode=xml";
$xml = simplexml_load_file($url);
print_r($xml);

echo "<br>";
echo "<br>";


echo "<br>";
$country = $xml->city->country;
$city = $xml->city['name'];

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
//$bak=str_replace("İ","I",$city);// burada İ harfi i harfine çevriliyor.
echo "<br>";
echo "<br>";

//echo $bak;
echo "<br>";
echo "<br>";

$coord = $xml->city->coord['lon'];
echo "Country: $country<br/>City: $bak <br/>LON: $coord";

echo "<br>";
echo "<br>";


date_default_timezone_set("Europe/istanbul");
$t=time();
//echo($t . "<br>");
//echo(date("Y-m-d",$t). "<br>");
//echo(date("H-i-s O",$t). "<br>");
//printf("Tarih: %u million bicycles in %s.",$number,$str);
echo(date("d-m-Y",$t));
echo(date("H:i:s O",$t));
$date=date("d-m-Y",$t);
$time=date("H:i:s O",$t);

//$response=array("Country"=>$country,"City"=>$city);,
$response["success"] = 1;
$response["Country"] = trim($country);
$response["City"] =trim(strtolower($bak));
$response["Lon"] =trim($coord);
$response["Date"] =trim($date);
$response["Time"] =trim($time);

//'name' => $this->name


echo "<br>";
echo "<br>";
echo "<br>";

// Show JSON response
    echo json_encode($response);
    
echo "<br>";
echo "<br>";
echo "<br>";
    

$connect_web = simplexml_load_file('http://www.tcmb.gov.tr/kurlar/today.xml');

print_r($connect_web);

echo "<br>";
echo "<br>";
echo "<br>";
echo "<br>";



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
 "openweathermap"=>($response)
 
  );
  


echo json_encode($array);


?>