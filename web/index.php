<?php 

include "embeddedprog.php";
include "render.php";

if(isset($_GET['download'])) {

	$pfad = "/var/www/tmp/myprog.hex";

	header("Content-Type: application/force-download");
	header("Content-Disposition: attachment; filename=\"". urlencode("myprog.hex") ."\"");
	header("Content-Length: ". filesize($pfad));
	header("Content-Transfer-Encoding: binary");
	

	readfile($pfad);
	exit;
}

render_get_post();




?>

<!--echo '<script type="text/javascript">alert("' . $gruss . '")</script>'; -->
<html>
<head>
<title>embeddedprog GUI</title>
<?php
echo render_options()
?>

<style type="text/css">



</style>
<link rel="stylesheet" href="flexselect.css" type="text/css" media="screen" />
<script type="text/javascript" src="jquery.min.js"></script>
<script src="liquidmetal.js" type="text/javascript"></script>
<script src="jquery.flexselect.js" type="text/javascript"></script>

<script type="text/javascript">



//jQuery(document).ready(function() {
//$("select.flexselect").flexselect();
//});
function art(string){
 
  avr  = document.getElementById('avr');
  ocd  = document.getElementById('ocd');
  avr2 = document.getElementById('avr2');
  ocd2 = document.getElementById('ocd2');
    if (string==1) {

        ocd.style.display='none';
        avr.style.display='';
        ocd2.style.display='none';
        avr2.style.display='';
      }
    else{
	ocd.style.display='';
	avr.style.display='none';
	ocd2.style.display='';
	avr2.style.display='none';
	}



}


function show_popup(id) {
    if (document.getElementById){
        obj = document.getElementById(id);
        if (obj.style.display == "none") {
            obj.style.display = "";
        }
    }
}
function hide_popup(id){
    if (document.getElementById){
        obj = document.getElementById(id);
        if (obj.style.display == ""){
            obj.style.display = "none";
	    document.getElementById('textarea1').value="";
        }
    }
}


     $(document).ready(function() {
	  
/*
       var refreshId = setInterval(function() {

     $.ajax({

        'url' : 'refresh.php?' + 1*new Date(),
        'type' : 'GET',
        'data' : {
        },
        'success' : function(data) {              
           var values = data.split(":"); 
           $("#refresh").text(values[0]);
           $('#presetvalue1').val(values[2]);
           $('#presetvalue2').val(values[3]);
           $('#presetvalue3').val(values[4]);
           if(values[1]==1) jQuery("#radio-choice-1").attr('checked', 'checked');
           if(values[1]==2) jQuery("#radio-choice-2").attr('checked', 'checked');
           if(values[1]==3) jQuery("#radio-choice-3").attr('checked', 'checked');
           if(values[1]==4) jQuery("#radio-choice-4").attr('checked', 'checked');
        },
        'error' : function(request,error)
        {
            //alert("Request: "+JSON.stringify(request));
        }
      });
//      $("#refresh").load('refresh.php?' + 1*new Date());

       }, 1000);
 */               
    });


     function tryToDownload(name,data)
    {
 
        oIFrm = document.getElementById('myIFrm');
        oIFrm.src = 'download.php?name='+name;
        alert(data);
 
    }

function sleep(millis, callback) {
    setTimeout(function()
            { callback(); }
    , millis);
}



function SendCommand(command, i, help)
{
	if(command!='start-gdb'&&command!='pro'){	
	document.getElementById('loading').style.display="";
	}
	
    var processor = $("select#processors option").filter(":selected").val();
    var speed = $("select#speed option").filter(":selected").val();
    var pointer = '';
    var voltage = $('input[name=voltage]:checked', '#myForm').val();
    var safe = '';
    if(command=='save-conf'){ 
    var save = prompt("Please add a description","");   
    }

    if(command=='read-flash'){ 
    var save = prompt("Please insert filename","myprog.hex");   
    }
    if ((command=='read-flash')&&((save ==null)||(save==""))){document.getElementById('loading').style.display="none";return;}

    if(command=='pro'){
	
	i=document.getElementById('processors').selectedIndex;
	}
    if((command=='save-conf')&&((save==null)||(save==""))){document.getElementById('loading').style.display="none";return;}
	
    if(command=='port'){
	if (i=='1'){
	var save = prompt("Please insert new GDB port","");	
	}
	else{
	var save = prompt("Please insert new Telnet port","");
	}
	}
     if(command=='desc'){
		var save = prompt("Please insert new description","");
		if ((save==null)||(save=="")){document.getElementById('loading').style.display="none";return;}
	}
     if(command=='dump'){
		var save = prompt("Please insert the command in following form: \n mdw [phys] addr [count] \n\n   mdw = 32-bit word\n   mdh = 16-bit halfword\n   mdb = 8-bit byte\n\nWhen the current target has an MMU which is present and active, addr is interpreted as a virtual address. Otherwise, or if the optional phys flag is specified, addr is interpreted as a physical address. If count is specified, displays that many units","mdw ");
	if ((save==null)||(save=="")){document.getElementById('loading').style.display="none";return;}
	}       


	if(command=='del-conf'){
		var box=window.confirm("Do you want to delete this line?");
		if(box==true){
		}
		else{
			document.getElementById('loading').style.display="none";return;
		}
		
}

     $.ajax({
        'url' : 'server.php?cmd=' + command + '&processor=' + processor + '&voltage='+ voltage + '&speed=' + speed + '&i=' + i + '&save=' + save + '&pointer=' + pointer + '&' + 1*new Date(),
        'type' : 'GET',
        'data' : {
        },
        'success' : function(data) { 
		if (command!='upload'){
		document.getElementById('loading').style.display="none";
		}
		if(command=='pro'){
		art(data);
		return;
		}
		if(command=='read-flash'){
			
			if (data.indexOf("unexpected error")<1){
				save=save+'&'+1*new Date();
		//tryToDownload(save,data)
          			window.open('download.php?name='+save+'&'+1*new Date(),"_top");
			}




		


		   //parent.location.href= '/tmp/myprog.hex';
			//'download.php?download=true&'+ 1*new Date();
		   //location.href =  '/tmp/myprog.hex';
		
		}
		if ((command=='upload')&&(help==1)){
			location.replace(location.pathname);
		}
		else{ 
		if ((command=='save-conf')||(command=='del-conf')||(command=='start-gdb')||(command=='stop-gdb')||(command=='port')||(command=='desc')){
			//location.reload();
			//location.reload(true)
			//RefreshForm.submit();
			//history.go(0);
			//location.href = location.href;
			//location.href = location.pathname;
			location.replace(location.pathname);
		}
		else{         
			//this.form.textarea1.value=data;
			if (command!='upload'){
			document.getElementById('textarea1').value=data;
			show_popup('my_popup');
			}
              //alert('Antwort: ' + data);
		}
		}
	      //location.reload();
        },
        'error' : function(request,error)
        {
		document.getElementById('loading').style.display="none";
            	//alert("Kommunikation mit Board fehlgeschlagen");
        }
      });
  




               




   

}


function UpdateValues(index)
{
        if(index==1)
          document.getElementById("presetvalue1org").value=document.getElementById("presetvalue1").value;
        if(index==2)
          document.getElementById("presetvalue2org").value=document.getElementById("presetvalue2").value;
        if(index==3)
          document.getElementById("presetvalue3org").value=document.getElementById("presetvalue3").value;

}

</script>

<style type="text/css">
* { font-size:9pt; }
.even { background-color:white;}
.odd{ background-color:lightgrey;}

.myButton {
    -moz-box-shadow:inset 0px 1px 0px 0px #ffffff;
    -webkit-box-shadow:inset 0px 1px 0px 0px #ffffff;
    box-shadow:inset 0px 1px 0px 0px #ffffff;
    background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #ffffff), color-stop(1, #f6f6f6));
    background:-moz-linear-gradient(top, #ffffff 5%, #f6f6f6 100%);
    background:-webkit-linear-gradient(top, #ffffff 5%, #f6f6f6 100%);
    background:-o-linear-gradient(top, #ffffff 5%, #f6f6f6 100%);
    background:-ms-linear-gradient(top, #ffffff 5%, #f6f6f6 100%);
    background:linear-gradient(to bottom, #ffffff 5%, #f6f6f6 100%);
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ffffff', endColorstr='#f6f6f6',GradientType=0);
    background-color:#ffffff;
    -moz-border-radius:6px;
    -webkit-border-radius:6px;
    border-radius:6px;
    border:1px solid #dcdcdc;
    display:inline-block;
    cursor:pointer;
    color:#666666;
    font-family:arial;
    font-size:12px;
    font-weight:bold;
    padding:6px 18px;
    text-decoration:none;
    text-shadow:0px 1px 0px #ffffff;
}
.myButton:hover {
    background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #f6f6f6), color-stop(1, #ffffff));
    background:-moz-linear-gradient(top, #f6f6f6 5%, #ffffff 100%);
    background:-webkit-linear-gradient(top, #f6f6f6 5%, #ffffff 100%);
    background:-o-linear-gradient(top, #f6f6f6 5%, #ffffff 100%);
    background:-ms-linear-gradient(top, #f6f6f6 5%, #ffffff 100%);
    background:linear-gradient(to bottom, #f6f6f6 5%, #ffffff 100%);
    filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#f6f6f6', endColorstr='#ffffff',GradientType=0);
    background-color:#f6f6f6;
}
.myButton:active {
    position:relative;
    top:1px;
}

</style>
</head>
<?php
 //$test=render_processors();
//define("UPLOAD_DIR", "/var/www/tmp/");<script src="liquidmetal.js" type="text/javascript"></script>
//echo $_FILES['datei']['name'];
//if ($_FILES['datei']['name']==((null)||("")))
//{
//	echo leer;
//}
//else
//{
//$name = preg_replace("/[^A-Z0-9._-]/i", "_", $_FILES["datei"]["name"]);
//$parts=pathinfo($name);         
//$success = move_uploaded_file($_FILES["datei"]["tmp_name"],UPLOAD_DIR . "tmp" . "." . $parts['extension']);
//if (!$success) {
//        echo "<p>Unable to save file.</p>";
//        exit;
//    }
//else 
//{#
//$myfile=$_FILES['datei'];
//echo embeddedprog_upload($myfile);
//}	

//}	


//print_r($test); 
?>
<body onload="set_options();SendCommand('pro')" style="font: 9pt Arial,sans-serif; margin-top:0px;">

<form name="myForm" id="myForm"  method="post" enctype="multipart/form-data">

<table width="1000" border="0" cellpadding="5" style="border-right: 1px solid #BBB; border-left: 1px solid #BBB;border-bottom: 1px solid #BBB; background-color:#f5f5f5;" cellspacing="0"  align="center">
<tr><td colspan="5" style="padding:10px; background: url('bg_header.jpg') repeat-y scroll left top rgb(67, 187, 209);"><img src="ep_logo_web.png" height="50"></td></tr>

<tr style="background:black; color:white;">
<td colspan="5" align="center"><table style="background:black; color:white;"><tr>
	<td></td>
	<td>

	


	<td>Processor:</td>
	<td><select name="processors" id="processors" style="width: 300px;font:9pt  Arial, sans-serif" class="flexselect" onchange="SendCommand('pro')" >
	<!--<option>ARM7</option>-->
	<?php
	echo render_processors()
	?>
	</select></td>
	
	<?php

	?>

	

	<td>Programmer Speed:</td>
	<td><select name="speed" id="speed" onchange="SendCommand('pro')">
<option value=3
<?php
                if(isset($_POST['speed']) && $_POST['speed'] == 3){
                        echo 'selected="selected"';}
                
?>
>Slow</option>
<option value=2
<?php
                if(isset($_POST['speed']) && $_POST['speed'] == 2){
                        echo 'selected="selected"';}

?>
>Normal</option>
<option value=1
<?php
                if(isset($_POST['speed']) && $_POST['speed'] == 1){
                        echo 'selected="selected"';}

?>
>Fast</option></select></td>

	<td>Voltage:&nbsp;
		<input type="radio" name="voltage" id=1v value=1 onchange="SendCommand('pro')"

<?php
                if($_POST['voltage'] == 1){
                        echo 'checked="checked"';}

?>

>&nbsp;1.8V
		<input type="radio" name="voltage" id=3v value=3 onchange="SendCommand('pro')"

<?php
                if($_POST['voltage'] == 3){
                        echo 'checked="checked"';}

?>

>&nbsp;3.3V
		<input type="radio" name="voltage" id=5v value=5 onchange="SendCommand('pro')"

<?php
                if($_POST['voltage'] == 5){
                        echo 'checked="checked"';}

?>

>&nbsp;5.0V
	</td>

	</tr></table>
</td>	
</tr>






<tr valign="top" 
<?php 
$avr=file('/var/www/avrdude.rc');        
$i=file('/var/www/tmp/processor');
if(in_array ($i[3],$avr)){
echo  "style=\"background:#BBB;\"";
}
else{
echo "style=\"background:#BBB;display:none\"";
}
 ?>
 id="avr2"><td colspan="5">Commands: <a style="color:white"  href="javascript:show_popup('helpcommands') ">?</a></td></tr>
<tr id="avr" 
<?php 
$avr=file('/var/www/avrdude.rc');        
$i=file('/var/www/tmp/processor');
if(in_array ($i[3],$avr)){
echo  "style=\"\"";
}
else{
echo "style=\"display:none\"";
}
 ?>
><td colspan="5" align="center">
<br>

<input type="button" class="myButton" value="Read Signature" onclick="SendCommand('readsignature')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="Erase Flash" onclick="SendCommand('erase')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="Download Flash" onclick="SendCommand('read-flash')">
&nbsp;&nbsp;&nbsp;
<b>Read Fuses:</b>
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="low" onclick="SendCommand('read-fuse','1')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="high" onclick="SendCommand('read-fuse','2')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="extended" onclick="SendCommand('read-fuse','3')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="all" onclick="SendCommand('read-fuse','0')">
<br>
<br>
</td>

</tr>



<tr valign="top" 
<?php 
$ocd=file('/var/www/openocd.rc');        
$i=file('/var/www/tmp/processor');
if(in_array ($i[3],$ocd)){
echo  "style=\"background:#BBB;\"";
}
else{
echo "style=\"background:#BBB;display:none\"";
}
 ?>

 id="ocd2"><td colspan="3">Commands: <a style="color:white"  href="javascript:show_popup('helpocd') ">?</a></td><td colspan="3"></td></tr>
<tr id="ocd" 

<?php 
$ocd=file('/var/www/openocd.rc');        
$i=file('/var/www/tmp/processor');
if(in_array ($i[3],$ocd)){
echo  "style=\"\"";
}
else{
echo "style=\"display:none\"";
}
 ?>

><td colspan="5" align="center">
<br>

<input type="button" class="myButton"  value="Read Signature" onclick="SendCommand('readsignature')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="Dump Memory" onclick="SendCommand('dump')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="Start openocd" onclick="SendCommand('start-gdb')">
&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton" value="Stop openocd"  onclick="SendCommand('stop-gdb' )">
&nbsp;&nbsp;&nbsp;
GDB-Port:&nbsp;<b onclick="SendCommand('port','1' )"> <?php echo render_gdb() ?> </b>&nbsp;
<input type="button" class="myButton" value="change"  onclick="SendCommand('port','1' )">
&nbsp;&nbsp;&nbsp;
Telnet-Port:&nbsp;<b onclick="SendCommand('port','-1' )">  <?php echo render_tel() ?> </b>&nbsp;
<input type="button" class="myButton" value="change"  onclick="SendCommand('port','-1' )">

<br>
<br>
</td>

</tr>



<img src="loading.gif" id="loading"  style="display:none;position:absolute;width:40px;height:40px;left:44%;top:42%" />

    <div align="right">
<div id="my_popup" style="display:none;border:1px solid gray;padding:.3em;background-color:black;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:white"  href="javascript:hide_popup('my_popup') "onclick="location.replace(location.pathname);"><img src="icon_del_gr_20x20_004.png"></a>
    </div>

<textarea readonly name="textarea1" id="textarea1" style="color:white;font-family:Ubuntu Mono,Terminus Font,GNU Unifont;resize:none;border:0px;background-color:transparent;width:100%;height:97%;top:10% "data-role="none">
</textarea>
</div>




    <div align="right">
<div id="helpcommands" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helpcommands') "><img src="icon_del_gr_20x20_004.png"></a>
   </div>
<div align="left">

<h2>Signature:</h2>
Shows signature/standart output of the programmer

<h2>Erase Flash:</h2>
Erases the flash memory of the target board

<h2>Download Flash:</h2>
Reads the flash of the target board and offers it as an file, <br>
dependig of the chosen name the type changes, test.hex = hex ...

<h2>Read Fuses:</h2>
Read Fuses low/high/extended<br>
to write fuses please use the embeddedprog.py
</div>
</div>



    <div align="right">
<div id="helpocd" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helpocd') "><img src="icon_del_gr_20x20_004.png"></a>
   </div>
<div align="left">

<h2>Signature:</h2>
Shows signature/standart output of the programmer

<h2>Dump Memory:</h2>
Insert the command in following form: <br> mdw [phys] addr [count] <br><br>   mdw = 32-bit word<br>   mdh = 16-bit halfword<br>   mdb = 8-bit byte<br><br>When the current target has an MMU which is present and<br>active, addr is interpreted as a virtual address. Otherwise,<br>or if the optional phys flag is specified, addr is interpreted<br>as a physical address. If count is specified, displays that<br>many units

<h2>Start/Stop openocd:</h2>
Starts and stop openocd with current settings.<br>
After start it will remain open for gdb/telnet connections.

<h2>Change Ports:</h2>
Change gdb/telnet port.<br>
Ports can only be changed via browser
</div>
</div>



    <div align="right">
<div id="helptemp" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helptemp') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>


<div align="left">
The "Upload Firmware" field shows the last uploaded file.<br>
This file will be overwritten once a new file is uploaded.

<h2>Save profile:</h2>
Saves the current temp file + settings as an profile for later use.

<h2>Program:</h2>
Program the board with the current temp settings.

<h2>Upload:</h2>
Please choose the needed settings BEFORE you upload the file.<br>
Here you can upload your files.<br>
Check autoflash to upload and program at once. After your first upload
you can save the firmware with the current settings as profile in firmware archive.

</div>
</div>


    <div align="right">
<div id="helparch" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helparch') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>

<div align="left">
The "Flash Archive" field shows your saved files with the settings.<br>
Rhe description can be changed by clicking on it.

<h2>Program:</h2>
To program just use the program button, it will use your saved file + settings.

<h2>delete:</h2>
With the delete button you can delete an old entry.


</div>
</div>




        

    <div align="right">
<div id="helpUp" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helpUp') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>

<div align="left">
<h2>Update:</h2>
<a>You can get the latest updates from :  <a style="color:blue"  href="https://github.com/embeddedprojects/usbprog5/raw/master/update/update.tar.gz">Download</a>.<br>
to update just upload the update.tar.gz .</a>


<h2>Change IP:</h2>
Refers you to a new page where you can chose your preffered inet settings. (Only useable in pro version)

<h2>Download Client:</h2>
Downloads the newest version of the client,<br>
the client is used to communicate --via shell(command line)-- with the embeddedprog server.


</div>
</div>




<tr valign="top" style="background:#BBB"><td colspan="5">Upload Firmware: <a style="color:white"  href="javascript:show_popup('helptemp') ">?</a></td></tr>
<tr valign="top"><td colspan="5" align="">
<table width="100%" border="0" style="border: 0px solid black">
<tr><td style="width:15%">Description</td><td style="width:25%">Firmware</td><td style="width:15%">Processor</td><td style="width:10%">Size</td><td style="width:10%">Action</td><td style="width:10%">Flash</td></tr>
<?php
echo render_temp();
?>

</table>


<br>
</td>
<tr valign="top"><td colspan="5" align="center">

<input type="file" value="" name="datei" class="myButton" >
<input type="submit" value="Upload File" class="myButton" >
<input type="checkbox" name="flashdirect" value="1" >
&nbsp;Autoflash after upload
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="button" class="myButton"  value="safe profile" onclick="SendCommand('save-conf')">

<br>
<br>

</td>
</tr>
</td>
</td></tr>


<tr valign="top" style="background:#BBB"><td colspan="5">Flash Archive: <a style="color:white"  href="javascript:show_popup('helparch') ">?</a></td></tr>
<tr valign="top"><td colspan="5" align="">
<table width="100%" border="0" style="border: 0px solid black">
<tr><td style="width:15%">Description</td><td style="width:25%">Firmware</td><td style="width:15%">Processor</td><td style="width:10%">Size</td><td style="width:10%">Action</td><td style="width:10%">Flash</td></tr>
<?php


echo render_firmware_table();

?>

</table>





</td></tr>

<tr valign="top" style="background:#BBB"><td colspan="4">Update programmer:&nbsp;<a style="color:white"  href="javascript:show_popup('helpUp') ">?</a></td><td colspan="2">Settings:&nbsp;<a style="color:white"  href="javascript:show_popup('helpUp') ">?</a></td></tr>
<tr><td colspan="4" align="">
<br>

<input type="file" value="" name="date" class="myButton" >
<input type="submit" value="Upload Update" class="myButton" >
<br><br>
</td>
<td colspan="2" align="">

<!--<input type="button" value="Change IP">-->
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="button" class="myButton"  value="Download embeddedprog.py" onclick="window.open('download.php?name=embeddedprog.py&path=tmp&'+1*new Date(),'_top');">
</td>
</td></tr>

</form>



<tr valign="top" style="background:#43BBD1;"><td colspan="5">Command Lines:</td></tr>
<tr><td>Read Signature</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --speed 2 </td></tr>
<tr><td>Flash</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --flash-write /tmp/yourprog.hex</td></tr>
<tr><td>Read Flash</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --flash-read yourprog.hex</td></tr>
<tr><td>Erase</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --delete</td></tr>
<tr><td>Start openocd</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --gdb "start"</td></tr>
<tr><td>Stop openocd</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --gdb "stop"</td></tr>
<tr><td>Dump Memory</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --dump "mdw addr count"</td></tr>
<tr><td>Read Fuse High</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_high</td></tr>
<tr><td>Read Fuse Low</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_low</td></tr>
<tr><td>Read Fuse Extended</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_extended</td></tr>
<tr><td>Write Fuse High</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_high "fusebits"</td></tr>
<tr><td>Write Fuse Low</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_low "fusebits"</td></tr>
<tr><td>Write Fuse Extended</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_extended "fusebits"</td></tr>

<tr valign="top" style="background:#BBB"><td colspan="5"></td></tr>

</table>
<br>
<center><i style="color:#BBB">embeddedprog created by <a href="http://shop.embedded-projects.net" target="_blank" style="color:#bbb;">embedded projects GmbH</a>. Based on GNU/Linux, OpenOCD, avrdude and many other Open Source projects. <a href="http://www.usbprog.org" style="color:#bbb;" target="_blank">Homepage</a></i></center>


 <iframe id="myIFrm" src="" style="visibility:hidden">
</iframe>


</body>
<?php
$myfile=$_FILES['datei'];

echo embeddedprog_upload($myfile);
$myfile=$_FILES['date'];
echo embeddedprog_upload($myfile);


?>
<script type="text/javascript">


jQuery(document).ready(function() {
$("select.flexselect").flexselect();
});
</script>
</html>
