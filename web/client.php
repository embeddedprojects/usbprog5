<?php

function read_sig($processor,$speed,$voltage)
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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.' }';


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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": "/var/www/tmp/'.$save.'", "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": "/var/www/tmp/'.$save.'", "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.' }';


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

$in ='{"load": '.$i.', "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": null, "processor": null, "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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


function save($processor,$speed,$save,$voltage,$eeprom)
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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": "'.$save.'", "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.', "eeprom": ' . $eeprom . '}';


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



function gdb_start($processor,$speed,$voltage)
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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": "start", "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": "stop", "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": null, "processor": null, "del-conf": '.$i.', "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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


function upload($processor,$speed,$datei,$voltage,$eeprom)
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



$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": "'. $datei .'", "speed": ' . $speed . ', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": "/var/www/tmp/tmp.' . $parts['extension'] . '", "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.', "eeprom": ' . $eeprom . '}';



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

$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": true, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';


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
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": true, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": true, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": true, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
	break;

	case '1': 
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": true, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
	break;
	case '2': 
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": true, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
	break;
	case '3': 
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": true, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
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
		$in ='{"load": null, "fuse-write-low": "'.$save.'", "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
	break;
	case '2': 
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": "'.$save.'", "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
	break;
	case '3': 
		$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": "'.$save.'", "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": null,"voltage": '.$voltage.'}';
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


function desc($processor,$save,$i,$voltage)
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

$in ='{"load": '.$i.', "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": null, "processor": "'.$processor.'", "del-conf": null, "rename": "'.$save.'", "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 0, "eeprom-read": null, "delete": false,"web": true,"dump": null,"voltage": '.$voltage.'}';


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



function dump($processor,$save,$speed,$voltage)
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
$in ='{"load": null, "fuse-write-low": null, "fuse-read-extended": false, "fuse-write-extended": null, "signature": false, "raw": null, "gdb": null, "eeprog_port": null, "flash-write": null, "speed": '.$speed.', "processor": "'.$processor.'", "del-conf": null, "flash-read": null, "safe": null, "show-all": false, "fuse-read-high": false, "eeprog-port": 8888, "desc": null, "fuse-write-high": null, "eeprom-write": null, "fuse-read-low": false, "eeprog_ip": null, "eeprog-ip": "127.0.0.1", "mode": null, "v": 3, "eeprom-read": null, "delete": false, "web": true,"rename": null,"dump": "'.$save.'","voltage": '.$voltage.'}';


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


