<?php
$servername = "localhost";
$username = "root";
$password = "scott";

try {
    $conn = new PDO("mysql:host=$servername;dbname=Test", $username, $password);
    // set the PDO error mode to exception
	if ($conn)
		echo "Connected successfully...";
	else 
		echo $conn;
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	$sql = "select uname, password from user;";

	echo "<br />\nDisplaying the data returned from database...\n";
	$data = $conn->query($sql)->fetchAll();

	foreach ($data as $row) {
    	echo $row['name']."<br />\n";
	}
	
	echo "<br />\nDone... \n";

} catch(PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}

?>

