<?php
//	$conn = mysql_connect("localhost","root", "scott");

	$conn = mysqli_connect("localhost","root", "scott");

	if (!$conn)
		echo "Connection failed";
	else
		echo "Successfully established connection";
?>
