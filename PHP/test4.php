<? php
	class Test{
		function __construct() {
			echo "Executing default constructor"
		}
		function __construct($var) {
			echo "Executing single argument constructor"
			echo "var : ", $var;
		}

	}

	echo "Creating instance of class <br />\n";
	$instance1 = new Test();
	$instance2 = new Test("ABC");
	$instance3 = new Test(12);
?>
