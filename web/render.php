<?php


function render_get_post()
{
  // change ip / change gdb port


}

function render_tel()
{
if (is_file('/var/www/tmp/port')){
	$temp=file('/var/www/tmp/port');	
	$save=$temp[1];
	}
	else{	
	$save=4444;
}
  return $save;


}

function render_gdb()
{
if (file_exists('/var/www/tmp/port')){
	$temp=file('/var/www/tmp/port');	
	$save=$temp[0];
	}
	else{	
	$save=3333;
}
  return $save;
}

function render_processors()
{     
	include("processor.php");
	$help=file('/var/www/tmp/processor');
	$x=0;
	$returni="";	
        //for($i=0;$i<10;$i++)
	foreach($processors as $i=>$value)
        {
		if (file_exists('/var/www/tmp/processor')){
			if(($x+1)==$help[0]){ 
          			$sel=' selected="selected"';}
    			else{$sel='';}
			$x=$x+1;
		}
		else{
		$sel='';
		}
             // return "<option>".$vendor[$i]."</option>";
  	echo "<option value=\"" . $processors[$i] . "\"".$sel.">" . $i . "</option>\n";

 	}




	return $returni;
}
function render_vendors()
{
include("processor.php");
  $return="";
        foreach($vendor as $i=>$value)
  {
		if(isset($_POST['vendors']) && $_POST['vendors'] == ($i+1)){ 
          		$sel=' selected="selected"';}
    		else{$sel='';}
	
  		$return= $return . "<option value=\"" . $i . "\"".$sel.">" . $vendor[$i] . "</option>";
  }
  return $return;
}


function render_firmware_table()
{
  $eeprom="";
  $line=" ";
  $lines=file('/var/www/save/eeprog.rc');
  
  unset($lines[0]);
  $row=0; 
  foreach($lines as $i=>$value)
  {
	$code=json_decode($lines[$i],true);
	if($code['desc']=='')
	{
		if($code['eeprom']==0)
		{
		$code['desc']=="write flash";
		}
		else
		{
		$code['desc']=="write EEPROM";
		}
	}

	if($code['eeprom']==1)
		{
		$code['flash-write']=$code['eeprom-write'];
		$eeprom="EEPROM: ";
		}	
	else 	{
		$eeprom="";	
		}
	if($code['flash-write']=='')
		{
		$code['mode']='read-flash';
		$code['flash-write']=$code['flash-read'];
		}
	
	$part=pathinfo($code['flash-write']);
    if($row%2)$style="even"; else $style="odd";
	$datei=$part['basename'];
	echo '<tr class="'.$style.'"><td onclick="SendCommand(\'desc\',\'' . $i . '\')">' . $code['desc'] . '</td><td>' . $eeprom . $datei . '</td><td>' . $code['processor'] . '</td><td>' . (filesize($code['flash-write'])/1000) . 'kb</td><td style="padding-top: 5px"><img src="icon_del_gr_20x20_004.png" onclick="SendCommand(\'del-conf\', ' . $i . ')"/>&nbsp;<img src="download_icon.png" onclick="window.open(\'download.php?name='. urlencode($datei) .'&path=safe&\'+1*new Date(),\'_top\');"></td><td><img src="button_002.png"  onclick="SendCommand(\'programm\', ' . $i . ')"/></td></tr>';
    $row++;
  }
#  <img src="icon_del_gr_20x20_004.png" />
  return $line;


} 

function render_temp()
{
  $line=" ";
  $eeprom="";
  $lines=file('/var/www/save/eeprog.rc');
  $code=json_decode($lines[0],true);

	if($code['eeprom']==1)
		{
		$code['flash-write']=$code['eeprom-write'];
		$eeprom="EEPROM: ";
		}
	if($code['flash-write']=='')
		{
		$code['mode']='read-flash';
		$code['flash-write']=$code['flash-read'];
		}

	$part=pathinfo($code['flash-write']);
	$datei=$part['basename'];
	if (($part['extension']== null) ||($part['extension'] == '')){
		$part['extension'] = 'diesefile sollte nicht existieren';
	}

$line= $line . '<tr><td><b>Temp File</b></td><td><b>'. $eeprom . $datei . '</b></td><td><b>' . $code['processor'] .' </b></td><td><b>' . (filesize('/var/www/tmp/tmp.'. $part['extension'])/1000) . 'kb</b></td><td><img src="icon_del_gr_20x20_004.png" onclick="SendCommand(\'del-conf\', 0)"/>&nbsp;<img src="download_icon.png" onclick="window.open(\'download.php?name=tmp.'. $part['extension'] .'&path=tmp&\'+1*new Date(),\'_top\');"></td><td><img src="button_002.png" value="program" onclick="SendCommand(\'programm\', ' . '0' . ')"></td></tr>';
return $line;
} 

function render_options()
{
  $line=" ";
if(file_exists('/var/www/tmp/processor')){

  $i=file('/var/www/tmp/processor');
  
  $line="<script type=\"text/javascript\">
	function set_options() {
	var dd = document.getElementById('processors');
        dd.selectedIndex = " . ($i[0]) . " ;

"."var dd = document.getElementById('speed');
	try{
	if(1==".$i[2]."){dd.selectedIndex = 2};
	if(2==".$i[2]."){dd.selectedIndex = 1};
	if(3==".$i[2]."){dd.selectedIndex = 0};
      }
	catch(e){dd.selectedIndex = 2;}

"."var ddd = document.getElementById('speed');
for (var i = 1 ; i < 6 ; i=i+2){
  if (  i == " . $i[1] . ") {
        radiobtn = document.getElementById((i.toString()+'v'));
	radiobtn.checked = true;
        break;
    }
}
}

</script>";
  
}
else{
$line="<script type=\"text/javascript\">
	function set_options() {};
	</script>";
}
return $line;
}






?>
