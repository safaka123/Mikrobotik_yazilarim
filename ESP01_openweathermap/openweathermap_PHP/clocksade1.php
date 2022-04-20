<?php


// bu program kullanılırken    api/openweather/clocksade1.php?ut=1650371383 gibi satır yazılmalı. bu satıra yazılan 
// unixtime kodunu php dosyası çözer ve gönderir. 




// Check if we got the field from the user
if (isset($_GET['ut']) ) {
 
    $unitime = $_GET['ut'];
   // $status= $_GET['status'];



date_default_timezone_set("Europe/istanbul");
$t=$unitime;
//$t=time();
//echo($t . "<br>");
//echo(date("Y-m-d",$t). "<br>");
//echo(date("H-i-s O",$t). "<br>");
//printf("Tarih: %u million bicycles in %s.",$number,$str);
echo(date("d-m-Y ",$t));
echo(date("H:i:s O",$t));
}
?>