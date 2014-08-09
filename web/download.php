	
<?php
	$name=$_GET['name'];
	$pfad = "/var/www/tmp/".$name;

	header("Content-Type: application/force-download");
	header("Content-Disposition: attachment; filename=\"". urlencode($name) ."\"");
	header("Content-Length: ". filesize($pfad));
	header("Content-Transfer-Encoding: binary");
	readfile($pfad);
?>
