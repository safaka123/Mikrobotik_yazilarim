<?php
$gun_dizi = array(
        'Monday'    => 'Pazartesi',
        'Tuesday'   => 'Salı',
        'Wednesday' => 'Çarşamba',
        'Thursday'  => 'Perşembe',
        'Friday'    => 'Cuma',
        'Saturday'  => 'Cumartesi',
        'Sunday'    => 'Pazar',
        'January'   => 'Ocak',
        'February'  => 'Şubat',
        'March'     => 'Mart',
        'April'     => 'Nisan',
        'May'       => 'Mayıs',
        'June'      => 'Haziran',
        'July'      => 'Temmuz',
        'August'    => 'Ağustos',
        'September' => 'Eylül',
        'October'   => 'Ekim',
        'November'  => 'Kasım',
        'December'  => 'Aralık',
        'Mon'       => 'Pts',
        'Tue'       => 'Sal',
        'Wed'       => 'Çar',
        'Thu'       => 'Per',
        'Fri'       => 'Cum',
        'Sat'       => 'Cts',
        'Sun'       => 'Paz',
        'Jan'       => 'Oca',
        'Feb'       => 'Şub',
        'Mar'       => 'Mar',
        'Apr'       => 'Nis',
        'Jun'       => 'Haz',
        'Jul'       => 'Tem',
        'Aug'       => 'Ağu',
        'Sep'       => 'Eyl',
        'Oct'       => 'Eki',
        'Nov'       => 'Kas',
        'Dec'       => 'Ara',
        'Monday'    => 'Pazartesi',
        'Tuesday'   => 'Salı',
        'Wednesday' => 'Çarşamba',
        'Thursday'  => 'Perşembe',
        'Friday'    => 'Cuma',
        'Saturday'  => 'Cumartesi',
        'Sunday'    => 'Pazar',
    );


date_default_timezone_set("Europe/istanbul");
$t=time();
//echo($t . "<br>");
//echo(date("Y-m-d",$t). "<br>");
//echo(date("H-i-s O",$t). "<br>");
//printf("Tarih: %u million bicycles in %s.",$number,$str);
echo(date("d-m-Y",$t));
echo(date("H:i:s O",$t));
echo "<br>";

echo(date("w",$t)." =haftanın günü ");
echo "<br>";
echo "<br>";
$gunismi=(date("l",$t));
echo ($gun_dizi[$gunismi])."  ==>  türkçe gün ismi";
echo "<br>";
echo "<br>";
echo(date("l",$t)." =haftanın günü ");
echo "<br>";
echo "<br>";
echo(date("W",$t))." = kaçıncı hafta ";
echo "<br>";
echo "<br>";
$ayismi=(date("F",$t));
echo ($gun_dizi[$ayismi])."  ==>  türkçe ay ismi";
echo "<br>";
echo "<br>";
echo(date("F",$t))."   ==> Ay ismi ";
echo "<br>";
echo "<br>";
echo(date("d-m-Y",$t))." =kısa tarih ";
echo "<br>";
echo(date("H:i",$t))." =saniyesiz saat ";
//$dayofweek = date('w', strtotime($t));
//$result    = date('Y-m-d', strtotime(($day - $dayofweek).' day', strtotime($t)));
//echo ($dayofweek);
echo "<br>";





?>