<?php
	class MyDB {
		
		public function getInstance() {
			
			
				/*1. To connect provide server namer, user and password*/
				$conn = mysqli_connect("localhost", "root", "scott");
				if (!$conn)
					echo "Connection failed";
				else
					echo "Successfully established connection";
				
				mysql_select_db("Test");
				
				
				$sql = "select * from user";
				
				$rows = mysql_query($sql);
				if ($rows > 0) {
					echo ("rows selected : ". $rows);
				} else {
					echo ("No rows selected");
				}
			
		}
	}
	
	echo ("*********Class to connect return the database instance**********");
	$ref = new MyDB();
	$ref->getInstance();
	
?>