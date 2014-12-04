<?php
include("embeddedprog.php");
include("client.php");
//ajax server

error_reporting(E_ALL ^ E_NOTICE ^ E_DEPRECATED ^ E_STRICT);

$cmd = $_GET['cmd'];
$processor = $_GET['processor'];
$vendor = $_GET['vendor'];
$speed = $_GET['speed'];
$voltage = $_GET['voltage'];
$i=$_GET['i'];
$save=$_GET['save'];
$pointer=$_GET['pointer'];
$eeprom=$_GET['eeprom'];


switch($cmd)
{

  case "read-eeprom":
    #echo embeddedprog_read($vendor,$processor,$voltage,$speed,$save);
	echo eeprom_read($processor,$speed,$save,$voltage);
	#echo "done";
  break; 
  case "dump":
    #echo embeddedprog_read($vendor,$processor,$voltage,$speed,$save);
	echo dump($processor,$save,$speed,$voltage);
  break;
  case "desc":
    #echo embeddedprog_read($vendor,$processor,$voltage,$speed,$save);
    echo desc($processor,$save,$i,$voltage);
  break;   

  case "read-fuse":
    #echo embeddedprog_signature($vendor,$processor,$voltage,$speed);
    echo read_fuse($processor,$i,$speed,$voltage);
  break;    
  case "write-fuse":
    #echo embeddedprog_signature($vendor,$processor,$voltage,$speed);
    echo write_fuse($processor,$i,$speed,$voltage,$save);
  break; 
  case "pro":
    #echo embeddedprog_signature($vendor,$processor,$voltage,$speed);
    echo pro($processor,$i,$voltage,$speed);
  break;  
  case "readsignature":
    #echo embeddedprog_signature($vendor,$processor,$voltage,$speed);
    echo read_sig($processor,$speed,$voltage);
  break;
  case "erase":
    #echo embeddedprog_erase($vendor,$processor,$voltage,$speed);
    echo erase($processor,$speed,$voltage);
  break;
  case "write-flash":
    #echo embeddedprog_write($vendor,$processor,$voltage,$speed);
  break;
  case "start-gdb":
    #echo embeddedprog_startgdb($vendor,$processor,$voltage,$speed);
    echo gdb_start($processor,$speed,$voltage);
  break;
  case "stop-gdb":
    #echo embeddedprog_stopgdb($vendor,$processor,$voltage,$speed);
    echo gdb_stop($processor,$speed,$voltage);
  break;
  case "read-flash":
    #echo embeddedprog_read($vendor,$processor,$voltage,$speed,$save);
	echo read_flash($processor,$speed,$save,$voltage);
  break;
  case "del-conf":
    #echo embeddedprog_delete($vendor,$processor,$voltage,$speed,$i);
    echo del($i,$voltage);
  break;
  case "programm":
    #echo embeddedprog_programm($vendor,$processor,$voltage,$speed,$i);
    echo load($i,$voltage);
  break;
  case "save-conf":
    #echo embeddedprog_save($vendor,$processor,$voltage,$speed,$save);
    echo save($processor,$speed,$save,$voltage,$eeprom);
  break;
  case "upload":
    #echo exec_upload($vendor,$processor,$voltage,$speed,$i);
    echo upload($processor,$speed,$i,$voltage,$eeprom);
  break;
  case "port":
    #echo embeddedprog_read($vendor,$processor,$voltage,$speed,$save);
    echo port($processor,$save,$i,$voltage);
  break; 

  default:
    echo "unkown command";

}




?>
