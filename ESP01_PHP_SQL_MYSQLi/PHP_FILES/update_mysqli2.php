<?php

    // komut satırı bu şekilde olacak. parametreleri ile birlikte yazılacak. 
    // http://mikrobotikradyo.unaux.com/api2/led/update_mysqli.php?id=1&status=OFF

    // database bağlantı verileri password dahil config_mysqli den alıyor. 
	// Include data base connect class
	$filepath = realpath (dirname(__FILE__));
	require_once($filepath."/config_mysqli.php");
//__________________________________________________________________________________
	// aşağıdaki satırda en sonda database ismi yer almaktadır. config dosyasında verilmedi. 
    // config dosyasından gelen verilerle databese bağlantısı yapılıyor. 
	$conn = mysqli_connect($servername, $username, $password,"sql7734385");
	
	
	if ($conn->connect_error) {
	die("Connection failed: " . $conn->connect_error);
	}
	echo "Connected successfully \n";
     echo "<br>";

 //_______________________________________________________________    

//=================================================================================
//Aşağıdaki if cümlesi parametre olarak verilenleri burada okur ve değişkene aktarır. 
// şayet parametre geldiyse bunu çalıştırır gelmediyse if cümlesini uygulamadan sonlanır. 

if (isset($_GET['id']) && isset($_GET['status'])) {
 
 // burada parametre olarak verdiğimiz değişken değerlerini değişkenlere yükler. 
    $id = $_GET['id'];
    $status= $_GET['status'];

	$sql = "UPDATE led SET status='$status' WHERE id='$id'";
	if ($conn->query($sql) === TRUE) {
	echo "<br>";
    echo "Record updated successfully\n";
    echo "<br>";
	} else {
    echo "<br>";    
	echo "Error updating record: " . $conn->error;
    echo "<br>";
	}
//=============================================================	

	
//tek kayıt oku *************************************
	$sql = "SELECT id, status FROM led WHERE id='$id'";
	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {
        echo "<br>";
        echo "tek kayıt okunuyor";
        echo "<br>";
		echo "id: " . $row["id"]. " - Status: " . $row["status"]. "\n";
        echo "<br>";
	}
	} else {
	echo "0 results";
	}

}
//*************************************
	
	

//  tümünü oku ====================================
    echo "<br>";
    echo "Tüm veriler okunuyor \n";
    echo "<br>";
    $merged_results[]= "";
	$sonuc=mysqli_query($conn,"select * from led");
	while($satir=mysqli_fetch_array($sonuc))
	{
		echo $satir['status'],"\n";
        $merged_results[] = $satir['status'];
        //echo "<br>";
		
	}
//=======================================================

echo "<br>";
echo "ARRAY olarak yaz ===>   ";
var_dump ($merged_results);

echo "<br>";
echo " JSON ENCODE olarak yaz ===>   ";
echo json_encode($merged_results);


?>