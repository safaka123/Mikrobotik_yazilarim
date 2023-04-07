<?php
 header('Content-Type: text/html; charset=utf-8');
 
 date_default_timezone_set("Europe/Istanbul") ; // timezone işaretlenir.


$gos1=1;
$gos2=1;
$gos3=1;
$gos4=1;
$gos5=1;
$gos6=1;

  $turkey= "TU/IS"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos1."ff"."bosgg";
  

       
 date_default_timezone_set("America/Los_Angeles") ; // timezone işaretlenir.
 $america= "US/LA"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos2."ff"."bosgg";
 
  date_default_timezone_set("Europe/London"); // timezone işaretlenir.
 $london= "GB/LO"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos3."ff"."bosgg";
 
  date_default_timezone_set("Europe/Madrid") ; // timezone işaretlenir.
 $madrid="SP/MA"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos4."ff"."bosgg";
 
   date_default_timezone_set("Asia/Tokyo") ; // timezone işaretlenir.
 $tokyo="JA/TO"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos5."ff"."bosgg";
 
    date_default_timezone_set("Asia/Hong_Kong"); // timezone işaretlenir.
 $hongkong= "HK/HK"."aa".date("H:i")."bb".date("d/m")."cc".date("D")."dd".date("P")."ee".$gos6."ff"."bosggaa";
 
 date_default_timezone_set("Europe/Istanbul") ; // timezone işaretlenir.
 
  
    echo $turkey;

    echo $america;

    echo $london;

    echo $madrid;

    echo $tokyo;

    echo $hongkong;
    
 
 ?>