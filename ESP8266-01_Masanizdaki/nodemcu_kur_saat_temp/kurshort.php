<?php
 header('Content-Type: text/html; charset=utf-8');

$connect_web = simplexml_load_file('http://www.tcmb.gov.tr/kurlar/today.xml');
$usdgos=1;
$eurogos=1;
$gbpgos=1;
$irrgos=1;
$cnygos=1;
$jpygos=1;
$rubgos=1;
$bgngos=1;


$usd_isim=  $connect_web->Currency[0]->Isim;   
$usd_buying = $connect_web->Currency[0]->BanknoteBuying;
$usd_buy=strlen($usd_buying);
if ($usd_buy>=5):
    $usd_buy=substr($usd_buying,0,5);
endif;    
$usd_selling = $connect_web->Currency[0]->BanknoteSelling;
$usd_sell=strlen($usd_selling);
if ($usd_sell>=5):
    $usd_sell=substr($usd_selling,0,5);
endif;  
$usd_cross = $connect_web->Currency[0]->CrossRateOther;
$usd_cr1="TL";
$usd_cr2="USD";

$euro_isim=  $connect_web->Currency[3]->Isim;    
$euro_buying = $connect_web->Currency[3]->BanknoteBuying;
$euro_buy=strlen($euro_buying);
if ($euro_buy>=5):
    $euro_buy=substr($euro_buying,0,5);
endif;    
$euro_selling = $connect_web->Currency[3]->BanknoteSelling;
$euro_sell=strlen($euro_selling);
if ($euro_sell>=5):
    $euro_sell=substr($euro_selling,0,5);
endif;  
$euro_cross = $connect_web->Currency[3]->CrossRateOther;
$euro_cr1="USD";
$euro_cr2="EURO";

$gbp_isim=  $connect_web->Currency[4]->Isim;  
if ($gbp_isim=="İNGİLİZ STERLİNİ"):
    $gbp_isim="iNGiLiZ STERLiNi";
endif;


$gbp_buying = $connect_web->Currency[4]->BanknoteBuying;
$gbp_buy=strlen($gbp_buying);
if ($gbp_buy>=5):
    $gbp_buy=substr($gbp_buying,0,5);
endif;  
$gbp_selling = $connect_web->Currency[4]->BanknoteSelling;
$gbp_sell=strlen($gbp_selling);
if ($gbp_sell>=5):
    $gbp_sell=substr($gbp_selling,0,5);
endif; 
$gbp_cross = $connect_web->Currency[4]->CrossRateOther;
$gbp_cr1="USD";
$gbp_cr2="GBP";

$irr_isim=  $connect_web->Currency[15]->Isim;  
if ($irr_isim=="İRAN RİYALİ"):
    $irr_isim="iRAN RiYALi";
endif;
$irr_buying = $connect_web->Currency[15]->ForexBuying;
$irr_buy=strlen($irr_buying);
if ($irr_buy>=5):
    $irr_buy=substr($irr_buying,0,5);
endif; 
$irr_selling = $connect_web->Currency[15]->ForexSelling;
$irr_sell=strlen($irr_selling);
if ($irr_sell>=5):
    $irr_sell=substr($irr_selling,0,5);
endif; 
$irr_cross = $connect_web->Currency[15]->CrossRateUSD;
$irr_cr1="IRR";
$irr_cr2="USD";

$cny_isim=  $connect_web->Currency[16]->Isim; 
if ($cny_isim=="ÇİN YUANI"):
    $cny_isim="CiN YUANI";
endif;

$cny_buying = $connect_web->Currency[16]->ForexBuying;
$cny_buy=strlen($cny_buying);
if ($cny_buy>=5):
    $cny_buy=substr($cny_buying,0,5);
endif; 
$cny_selling = $connect_web->Currency[16]->ForexSelling;
$cny_sell=strlen($cny_selling);
if ($cny_sell>=5):
    $cny_sell=substr($cny_selling,0,5);
endif;
$cny_cross = $connect_web->Currency[16]->CrossRateUSD;
$cny_cr1="CNY";
$cny_cr2="USD";


$jpy_isim=  $connect_web->Currency[11]->Isim;  
if ($jpy_isim=="JAPON YENİ"):
    $jpy_isim="JAPON YENi";
endif;
$jpy_buying = $connect_web->Currency[11]->BanknoteBuying;
$jpy_buy=strlen($jpy_buying);
if ($jpy_buy>=5):
    $jpy_buy=substr($jpy_buying,0,5);
endif;
$jpy_selling = $connect_web->Currency[11]->BanknoteSelling;
$jpy_sell=strlen($jpy_selling);
if ($jpy_sell>=5):
    $jpy_sell=substr($jpy_selling,0,5);
endif;
$jpy_cross = $connect_web->Currency[11]->CrossRateUSD;
$jpy_cr1="JPY";
$jpy_cr2="USD";

$rub_isim=  $connect_web->Currency[14]->Isim;  
if ($rub_isim=="RUS RUBLESİ"):
    $rub_isim="RUS RUBLESi";
endif;
$rub_buying = $connect_web->Currency[14]->ForexBuying;
$rub_buy=strlen($rub_buying);
if ($rub_buy>=5):
    $rub_buy=substr($rub_buying,0,5);
endif;
$rub_selling = $connect_web->Currency[14]->ForexSelling;
$rub_sell=strlen($rub_selling);
if ($rub_sell>=5):
    $rub_sell=substr($rub_selling,0,5);
endif;
$rub_cross = $connect_web->Currency[14]->CrossRateUSD;
$rub_cr1="RUB";
$rub_cr2="USD";

$bgn_isim=  $connect_web->Currency[12]->Isim;   
$bgn_buying = $connect_web->Currency[12]->ForexBuying;
$bgn_buy=strlen($bgn_buying);
if ($bgn_buy>=5):
    $bgn_buy=substr($bgn_buying,0,5);
endif;
$bgn_selling = $connect_web->Currency[12]->ForexSelling;
$bgn_sell=strlen($bgn_selling);
if ($bgn_sell>=5):
    $bgn_sell=substr($bgn_selling,0,5);
endif;
$bgn_cross = $connect_web->Currency[12]->CrossRateUSD;
$bgn_cr1="BGN";
$bgn_cr2="USD";

$usd_cross="  ";
$euro_cross="  ";
$gbp_cross="  ";
$irr_cross="  ";
$cny_cross="  ";
$jpy_cross="  ";
$rub_cross="  ";
$bgn_cross="  ";


echo 'USD   aa'.$usd_buy.'bb'.$usd_sell."cc".$usd_cross."dd".$usd_cr1."ee".$usd_cr2."ff".$usdgos."gg";
echo 'EURO  aa'.$euro_buy.'bb'.$euro_sell."cc".$euro_cross."dd".$euro_cr1."ee".$euro_cr2."ff".$eurogos."gg";
echo 'GBP   aa'.$gbp_buy.'bb'.$gbp_sell."cc".$gbp_cross."dd".$gbp_cr1."ee".$gbp_cr2."ff".$gbpgos."gg";
echo 'IR_RiYaa'.$irr_buy.'bb'.$irr_sell."cc".$irr_cross."dd".$irr_cr1."ee".$irr_cr2."ff".$irrgos."gg";
echo 'CHN_YUaa'.$cny_buy.'bb'.$cny_sell."cc".$cny_cross."dd".$cny_cr1."ee".$cny_cr2."ff".$cnygos."gg";
echo 'JP_YENaa'.$jpy_buy.'bb'.$jpy_sell."cc".$jpy_cross."dd".$jpy_cr1."ee".$jpy_cr2."ff".$jpygos."gg";
echo 'RUS_RUaa'.$rub_buy.'bb'.$rub_sell."cc".$rub_cross."dd".$rub_cr1."ee".$rub_cr2."ff".$rubgos."gg";
echo 'BU_LEVaa'.$bgn_buy.'bb'.$bgn_sell."cc".$bgn_cross."dd".$bgn_cr1."ee".$bgn_cr2."ff".$bgngos."ggaa";
//echo "<br>".'usd buy  '.$usd_buy;
//echo "<br>".'usd sell  '.$usd_sell;

/*
echo $usd_isim.'aa'.$usd_buying.'bb'.$usd_selling."cc".$usd_cross."dd".$usd_cr1."ee".$usd_cr2."ff".$usdgos."gg";
echo $euro_isim.'aa'.$euro_buying.'bb'.$euro_selling."cc".$euro_cross."dd".$euro_cr1."ee".$euro_cr2."ff".$eurogos."gg";
echo $gbp_isim.'aa'.$gbp_buying.'bb'.$gbp_selling."cc".$gbp_cross."dd".$gbp_cr1."ee".$gbp_cr2."ff".$gbpgos."gg";
echo $irr_isim.'aa'.$irr_buying.'bb'.$irr_selling."cc".$irr_cross."dd".$irr_cr1."ee".$irr_cr2."ff".$irrgos."gg";
echo $cny_isim.'aa'.$cny_buying.'bb'.$cny_selling."cc".$cny_cross."dd".$cny_cr1."ee".$cny_cr2."ff".$cnygos."gg";
echo $jpy_isim.'aa'.$jpy_buying.'bb'.$jpy_selling."cc".$jpy_cross."dd".$jpy_cr1."ee".$jpy_cr2."ff".$jpygos."gg";
echo $rub_isim.'aa'.$rub_buying.'bb'.$rub_selling."cc".$rub_cross."dd".$rub_cr1."ee".$rub_cr2."ff".$rubgos."gg";
echo $bgn_isim.'aa'.$bgn_buying.'bb'.$bgn_selling."cc".$bgn_cross."dd".$bgn_cr1."ee".$bgn_cr2."ff".$bgngos."gg";

*/



/*
$array = array(
"USD" => (array("USD",floatval($usd_buying),floatval($usd_selling),floatval($usd_cross),$usd_cr1,$usd_cr2)),
 "EURO" =>  (array("EURO",floatval($euro_buying),floatval($euro_selling),floatval($euro_cross),$euro_cr1,$euro_cr2)),
"GBP" =>  (array("GBP",floatval($gbp_buying),floatval($gbp_selling),floatval($gbp_cross),$gbp_cr1,$gbp_cr2)),
 "IRR" =>  (array("IRR",floatval($irr_buying),floatval($irr_selling),floatval($irr_cross),$irr_cr1,$irr_cr2)),
 "CNY" =>  (array("CNY",floatval($cny_buying),floatval($cny_selling),floatval($cny_cross),$cny_cr1,$cny_cr2)),
 "JPY" =>  (array("JPY",floatval($jpy_buying),floatval($jpy_selling),floatval($jpy_cross),$jpy_cr1,$jpy_cr2)),
 "RUB" =>  (array("RUB",floatval($rub_buying),floatval($rub_selling),floatval($rub_cross),$rub_cr1,$rub_cr2)),
 "BGN" =>  (array("BGN",floatval($bgn_buying),floatval($bgn_selling),floatval($bgn_cross),$bgn_cr1,$bgn_cr2))
  );
  
//$array = array ([0] =>$euro_buying, [1] =>$euro_selling, [2] =>$euro_cross);

echo json_encode($array);
//$float_value_of_var = floatval($euro_buying);
//$arr = array ('buying'=>floatval($gbp_buying),'selling'=>floatval($gbp_selling),'cross'=>floatval($gbp_cross));
//echo "<br>";
//echo json_encode($arr, JSON_FORCE_OBJECT);


// ["usd alis","7.8272","usd satis","7.8585","cross rate","1.1385"]
*/





 ?>