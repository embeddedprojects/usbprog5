<?php

function read_sig($processor,$speed,$voltage,$swd)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "web": true, "voltage": '.$voltage.', "swd": "'.$swd.'"}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}


function read_flash($processor,$speed,$save,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "flash-read": "/var/www/tmp/'.$save.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.'}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}

function eeprom_read($processor,$speed,$save,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;

$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "eeprom-read": "/var/www/tmp/'.$save.'", "web": true,"voltage": '.$voltage.' }';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}



function load($i,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"load": '.$i.', "processor": null, "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.'}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}


function save($processor,$speed,$save,$voltage,$eeprom,$i,$swd)
{

$fuses=explode(",",$i);
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}
if(($fuses[0]=='')||($fuses[0]=='-')||($fuses[0]==' ')||($fuses[0]=='no')||($fuses[0]=='none')||($fuses[0]=='null' )) {
$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "safe": "'.$save.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "eeprom": ' . $eeprom . ', "swd": "'.$swd.'"}';
}else{
if(($fuses[1]=='')||($fuses[1]=='-')||($fuses[1]==' ')||($fuses[1]=='no')||($fuses[1]=='none')||($fuses[1]=='null' )) {
$in ='{"fuse-write-low": "'.$fuses[0].'", "speed": '.$speed.', "processor": "'.$processor.'", "safe": "'.$save.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "eeprom": ' . $eeprom . '}';
}else{
if(($fuses[2]=='')||($fuses[2]=='-')||($fuses[2]==' ')||($fuses[2]=='no')||($fuses[2]=='none')||($fuses[2]=='null' )) {
$in ='{"fuse-write-low": "'.$fuses[0].'", "speed": '.$speed.', "processor": "'.$processor.'", "safe": "'.$save.'", "eeprog-port": 8888, "fuse-write-high": "'.$fuses[1].'", "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "eeprom": ' . $eeprom . '}';
}else{
$in ='{"fuse-write-low": "'.$fuses[0].'", "fuse-write-extended": "'.$fuses[2].'", "speed": '.$speed.', "processor": "'.$processor.'", "safe": "'.$save.'", "eeprog-port": 8888, "fuse-write-high": "'.$fuses[1].'", "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "eeprom": ' . $eeprom . '}';
}}}

$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
system("sync");
return $retur;
}



function gdb_start($processor,$speed,$voltage,$swd)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    echo "OK.\n";
}
 
echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    echo "OK.\n";
}

$in ='{"gdb": "start", "speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "swd": "'.$swd.'"}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
$retur='';

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
system("touch /tmp/gdb_runs");
return $retur;
}


function gdb_stop($processor,$speed,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"gdb": "stop", "speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.'}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
system("rm /tmp/gdb_runs");
return $retur;
}




function del($i,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"processor": null, "del-conf": '.$i.', "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.'}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}


function upload($processor,$speed,$datei,$voltage,$eeprom,$swd)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$parts=pathinfo($datei);


$i=file('/var/www/tmp/processor');

$volta=$i[1];

if ($i[4]==2){
$SWD='on';

}else{
$SWD='no';
} 

$in ='{"flash-write": "'. $datei .'", "speed": ' . $speed . ', "processor": "'.$processor.'", "safe": "/var/www/tmp/tmp.' . $parts['extension'] . '", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$volta.', "eeprom": ' . $eeprom . ', "swd": "'.$SWD.'"}';



$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}



function erase($processor,$speed,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "delete": true, "web": true,"voltage": '.$voltage.'}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}



function read_fuse($processor,$i,$speed,$voltage)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}
switch($i)
{
	case '0': 
		$in ='{"fuse-read-extended": true, "speed": '.$speed.', "processor": "'.$processor.'", "fuse-read-high": true, "eeprog-port": 8888, "fuse-read-low": true, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;

	case '1': 
		$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "fuse-read-low": true, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	case '2': 
		$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "fuse-read-high": true, "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	case '3': 
		$in ='{"fuse-read-extended": true, "speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	default:
	}


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}



function write_fuse($processor,$i,$speed,$voltage,$save)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}
switch($i)
{


	case '1': 
		$in ='{"fuse-write-low": "'.$save.'", "speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	case '2': 
		$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "fuse-write-high": "'.$save.'", "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	case '3': 
		$in ='{"fuse-write-extended": "'.$save.'", "speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0,  "web": true,"voltage": '.$voltage.'}';
	break;
	default:
	}


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}


function desc($processor,$save,$i,$voltage,$swd)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}

$in ='{"load": '.$i.', "processor": "'.$processor.'", "rename": "'.$save.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 0, "web": true,"voltage": '.$voltage.', "swd": "'.$swd.'"}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}



function dump($processor,$save,$speed,$voltage,$swd)
{
$address =	"127.0.0.1";
$service_port =	8888;
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    #echo "socket_create() fehlgeschlagen: Grund: " . socket_strerror(socket_last_error()) . "\n";
} else {
    #echo "OK.\n";
}
 
#echo "Versuche, zu '$address' auf Port '$service_port' zu verbinden ...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    #echo "socket_connect() fehlgeschlagen.\nGrund: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    #echo "OK.\n";
}
echo $speed;
echo $processor;
echo $save;
$in ='{"speed": '.$speed.', "processor": "'.$processor.'", "eeprog-port": 8888, "eeprog-ip": "127.0.0.1", "v": 3,  "web": true,"dump": "'.$save.'","voltage": '.$voltage.', "swd": "'.$swd.'"}';


$retur="";
#echo "HTTP HEAD request senden ...";
socket_write($socket, $in, strlen($in));
#echo "OK.\n";

#echo "Serverantwort lesen:\n\n";
while ($out = socket_read($socket, 2048)) {
  $retur=$retur . $out;
}

#echo "\n\r--Socket schliesen ...";
socket_close($socket);
#echo "OK.\n\n";
#echo $retur;
return $retur;
}

?>


