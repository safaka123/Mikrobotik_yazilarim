<?php

// Check if we got the field from the user
//   buraya alarm bölümü aç ve oradan alexa butonuna bilgi gitsin. 
if (isset($_GET['deger']) ) {
 
    $deger = $_GET['deger'];



$curl = curl_init();

curl_setopt_array($curl, array(
  CURLOPT_URL => 'https://esp8266-4140a.firebaseio.com/LED1.json?auth=2NaRXXwRefCCxTx9KBarrDm957KKDJsN4nJj1Dqq',
  CURLOPT_RETURNTRANSFER => true,
  CURLOPT_ENCODING => '',
  CURLOPT_MAXREDIRS => 10,
  CURLOPT_TIMEOUT => 0,
  CURLOPT_FOLLOWLOCATION => true,
  CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
  CURLOPT_CUSTOMREQUEST => 'PUT',
  CURLOPT_POSTFIELDS =>$deger,
  CURLOPT_HTTPHEADER => array(
    'Content-Type: text/plain'
  ),
));
$response = curl_exec($curl);

curl_close($curl);
echo $response;
//echo json_encode($response);

}



?>