<?php
//global $vendor;
	//global $atmel;
	//include 'processor.php';


	// In dieser Datei darf kein HTML generiert werden!!!!
	// und kein echo!!!!!!!!!!!!!!!!!!!!!!



	function port($processor,$save,$i)
	{

	if (file_exists('/var/www/tmp/port')){
	$avr=file('/var/www/tmp/port');
	$gdb=$avr[0];
	$tel=$avr[1];
	}
	else{
	$gdb=3333;
	$tel=4444;
	}
	$handle = fopen('/var/www/tmp/port', "w");
	
	if ($i==1){
	fwrite($handle, $save . "\n" . $tel );
 	#$lol=shell_exec('echo "' . $save . '" > /var/www/tmp/port');	
	#$lol=shell_exec('echo "' . $tel . '" >> /var/www/tmp/port');
	}else{
	fwrite($handle, $gdb .  $save );
 	#$lol=shell_exec('echo "' . $gdb . '" > /var/www/tmp/port');	
	#$lol=shell_exec('echo "' . $save . '" >> /var/www/tmp/port');	
	}		
	fclose($handle);


		return $lol;

	}

	function embeddedprog_test($pointer)
	{

	if (feof($pointer)){return '/done';}
	
	$write=fread($pointer,16);	


		return $write;

	}


	function embeddedprog_write($vendor,$processor,$voltage,$speed)
	{

		
		$write=shell_exec('python /var/www/client.py --processor '.$processor.' --flash-write test.hex --speed '.$speed );

		return $write;

	}

	function embeddedprog_read($vendor,$processor,$voltage,$speed,$save)
	{


                $read=shell_exec('python /var/www/client.py --processor '.$processor.' --speed '.$speed.' --flash-read /var/www/tmp/'.$save );


	return $read;
}

function embeddedprog_erase($vendor,$processor,$voltage,$speed)
{
                $erase=shell_exec('python /var/www/client.py --processor '.$processor.' --delete --speed '.$speed );
	return $erase;
}

function embeddedprog_signature($vendor,$processor,$voltage,$speed)
{
                $signature=shell_exec('python /var/www/client.py --processor '.$processor.'  --speed '.$speed );
	return $signature;
}


function embeddedprog_save($vendor,$processor,$voltage,$speed,$save)
{
                $safe=shell_exec('python /var/www/client.py --processor '.$processor.'  --speed '.$speed.' --safe "'.$save.'"');
        return $safe;
}

function embeddedprog_delete($vendor,$processor,$voltage,$speed,$i)
{
                $del=shell_exec('python /var/www/client.py --del-conf '. $i );
		
        return $del.$i.'python client.py --del-conf '. $i ;
}

function embeddedprog_programm($vendor,$processor,$voltage,$speed,$i)
{
                $programm=shell_exec('python /var/www/client.py --load '.$i );
        return $programm;
}

function embeddedprog_startgdb($vendor,$processor,$voltage,$speed,$i)
{
                $programm=shell_exec('python /var/www/client.py --processor '.$processor.'  --speed '.$speed.' --gdb start ' ) ;
        return $programm;
}


function embeddedprog_stopgdb($vendor,$processor,$voltage,$speed,$i)
{
                $programm=shell_exec('python /var/www/client.py --processor '.$processor.'  --speed '.$speed.' --gdb stop ' );
        return $programm;
}


function pro($processor,$i,$voltage,$speed)
{
	
	$avr=file('/var/www/avrdude.rc');        
	$ocd=file('/var/www/openocd.rc');

 	$lol=shell_exec('echo ' . $i . ' > /var/www/tmp/processor');
 	$lol=shell_exec('echo ' . $voltage . ' >> /var/www/tmp/processor');
 	$lol=shell_exec('echo ' . $speed . ' >> /var/www/tmp/processor');
	$lol=shell_exec('echo ' . $processor . ' >> /var/www/tmp/processor');
	
	if (in_array ($processor."\n",$avr)){
	return 1;
	} 
	
	
 	if (in_array ($processor."\n",$ocd,true)){
	return 2;
	}
	return 0;
        #return 'avr';
}




function embeddedprog_upload($datei){
define("UPLOAD_DIR", "/var/www/tmp/");
if ($datei['name']==((null)||("")))
{
        return ;
}
else
{
$name = preg_replace("/[^A-Z0-9._-]/i", "_", $datei["name"]);
$parts=pathinfo($name);
if($parts['extension']=='gz'){
$success = move_uploaded_file($datei["tmp_name"],UPLOAD_DIR . "update.tar.gz" );
system("sync");
if (!$success) {
        return "upload hat nicht funktioniert\r";
	exit;
    }
else
{
exec("sudo /var/www/update.sh > /dev/null &");
//system("sudo /var/www/update.sh");
return ;
exit;
}
}
else{
$success = move_uploaded_file($datei["tmp_name"],UPLOAD_DIR . "tmp." . $parts['extension']);
system("sync");
if (!$success) {
        return "upload hat nicht funktioniert\r";
    }
else
{
if($_POST["flashdirect"]!="1")
{
$return='<script type="text/javascript"> SendCommand("upload","'.$datei['name'].'","1"); </script>';
} else {
$return='<script type="text/javascript"> SendCommand("upload","'.$datei['name'].'"); SendCommand("programm","0"); </script>';
}
return $return;
}
}
}
}


function exec_upload($vendor,$processor,$voltage,$speed,$datei)
{
$parts=pathinfo($datei);
$programm=shell_exec('python /var/www/client.py --processor ' . $processor . '  --speed ' . $speed . ' --safe "/var/www/tmp/tmp.' . $parts['extension'] . '" --flash-write "' .$datei. '"' );
return $programm;
}


function exec_update($datei)
{
$parts=pathinfo($datei);
$programm=shell_exec( );



return $programm;
}


function embeddedprog_version()
{

$f = fopen('/root/version', 'r');
$line = fgets($f);
fclose($f);
return $line;
}
?>
