<!DOCTYPE html>
<html>
<body>




<?php
$homepage = file_get_contents('https://esp8266-4140a.firebaseio.com/bool.json?auth=2NaRXXwRefCCxTx9KBarrDm957KKDJsN4nJj1Dqq');
echo "bool= $homepage <br>";
echo("");
echo json_encode($homepage);
?>

</body>
</html>