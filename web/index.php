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
<script type="text/javascript" src="jquery.min.js"></script>

<script type="text/javascript">




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
    var save = prompt("Bitte beschreibung eingeben","");   
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
* { font-size:10pt; }
</style>
</head>
<?php
 //$test=render_processors();
//define("UPLOAD_DIR", "/var/www/tmp/");
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
<body onload="set_options();SendCommand('pro')" style="font: 9pt Arial,'Helvetica Neue',Helvetica,sans-serif; margin-top:0px;">

<form name="myForm" id="myForm"  method="post" enctype="multipart/form-data">

<table width="1000" border="0" cellpadding="5" style="border-right: 1px solid #BBB; border-left: 1px solid #BBB;border-bottom: 1px solid #BBB; background-color:#f5f5f5;" cellspacing="0"  align="center">
<tr><td colspan="5" style="padding:10px; background: url('bg_header.jpg') repeat-y scroll left top rgb(67, 187, 209);"><img src="ep_logo_web.png"></td></tr>

<tr style="background:black; color:white;">
<td colspan="5" align="center"><table style="background:black; color:white;"><tr>
	<td></td>
	<td>

	


	<td>Processor:</td>
	<td><select name="processors" id="processors" style="font:10pt  Monaco,ProFont,Andale Mono,Anonymous,Courier New,Courier,Angelus III,Bitstream Vera,Doire,Everson Mono,Excalibur Monospace" onchange="SendCommand('pro')">
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
 id="avr2"><td colspan="3">Commands: <a style="color:white"  href="javascript:show_popup('helpcommands') ">?</a></td><td colspan="3"></td></tr>
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

<input type="button" value="Read Signature" onclick="SendCommand('readsignature')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="Erase Flash" onclick="SendCommand('erase')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="Download Flash" onclick="SendCommand('read-flash')">
&nbsp;&nbsp;&nbsp;
<b>Read Fuses:</b>
&nbsp;&nbsp;&nbsp;
<input type="button" value="low" onclick="SendCommand('read-fuse','1')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="high" onclick="SendCommand('read-fuse','2')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="extended" onclick="SendCommand('read-fuse','3')">
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

<input type="button" value="Read Signature" onclick="SendCommand('readsignature')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="Dump Memory" onclick="SendCommand('dump')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="Start openocd" onclick="SendCommand('start-gdb')">
&nbsp;&nbsp;&nbsp;
<input type="button" value="Stop openocd"  onclick="SendCommand('stop-gdb' )">
&nbsp;&nbsp;&nbsp;
GDB-Port:&nbsp;<b onclick="SendCommand('port','1' )"> <?php echo render_gdb() ?> </b>&nbsp;
<input type="button" value="change"  onclick="SendCommand('port','1' )">
&nbsp;&nbsp;&nbsp;
Telnet-Port:&nbsp;<b onclick="SendCommand('port','-1' )">  <?php echo render_tel() ?> </b>&nbsp;
<input type="button" value="change"  onclick="SendCommand('port','-1' )">

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
Please insert the command in following form: <br> mdw [phys] addr [count] <br><br>   mdw = 32-bit word<br>   mdh = 16-bit halfword<br>   mdb = 8-bit byte<br><br>When the current target has an MMU which is present and<br>active, addr is interpreted as a virtual address. Otherwise,<br>or if the optional phys flag is specified, addr is interpreted<br>as a physical address. If count is specified, displays that<br>many units

<h2>Start/Stop openocd:</h2>
starts/tops openocd with current settings.<br>
after start it will remain open for gdb/telnet connections

<h2>Change Ports:</h2>
change gdb/telnet port<br>
ports can only be changed via browser
</div>
</div>



    <div align="right">
<div id="helptemp" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helptemp') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>


<div align="left">
The "Temp Firmware"-field shows the last uploaded file.<br>
This file will be overriten once a new file is uploaded.

<h2>save profile:</h2>
saves the current temp file + settings as an profile for later use.

<h2>program:</h2>
program the board with the current temp settings.

<h2>Upload:</h2>
please chose the needed settings BEFORE you upload the file.<br>
Here you can upload your files as temp files.<br>
check autoflash to upload and program at once.

</div>
</div>




    <div align="right">
<div id="helparch" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helparch') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>

<div align="left">
The "Flash Archive"-field shows your saved files+settings.<br>
the description can be changed by clicking on it

<h2>program:</h2>
to program just use the program button, it will use your saved file + settings.

<h2>delete:</h2>
with the delete button you can delete an old entry.


</div>
</div>




        

    <div align="right">
<div id="helpUp" style="display:none;border:1px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">
    <div align="right">
        <a style="color:blue"  href="javascript:hide_popup('helpUp') "><img src="icon_del_gr_20x20_004.png"></a>
    </div>

<div align="left">
<h2>Update:</h2>
<a>you can get the latest updates from :  <a style="color:blue"  href="javascript:hide_popup('helpUp') ">dlseite</a>.<br>
to update just upload the update.tar.gz .</a>


<h2>Change IP:</h2>
refers you to a new page where you can chose your preffered inet settings.(Only useable in Pro Version)

<h2>Download Client:</h2>
downloads the newest version of the client,<br>
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

<input type="file" value="" name="datei">
<input type="submit" value="Upload File">
<input type="checkbox" name="flashdirect" value="1" >
&nbsp;Autoflash after upload
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

<tr valign="top" style="background:#BBB"><td colspan="4">Update programmer:<a style="color:white"  href="javascript:show_popup('helpUp') ">?</a></td><td colspan="2">Settings:<a style="color:white"  href="javascript:show_popup('helpUp') ">?</a></td></tr>
<tr><td colspan="4" align="">
<br>

<input type="file" value="" name="date">
<input type="submit" value="Upload Update">
<br><br>
</td>
<td colspan="2" align="">

<!--<input type="button" value="Change IP">-->
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<input type="button" value="Download embeddedprog.py" onclick="window.open('download.php?name=embeddedprog.py&'+1*new Date(),'_top');">
</td>
</td></tr>

</form>



<tr valign="top" style="background:#BBB"><td colspan="5">Command Lines:</td></tr>
<tr><td>Read Signature</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --speed 2 </td></tr>
<tr><td>Flash</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --flash-write /tmp/yourprog.hex --speed 2</td></tr>
<tr><td>Read Flash</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --flash-read yourprog.hex  --speed 2</td></tr>
<tr><td>Erase</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --delete --speed 2</td></tr>
<tr><td>Start openocd</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --gdb "start" --speed 2</td></tr>
<tr><td>Stop openocd</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --gdb "stop" --speed 2</td></tr>
<tr><td>Dump Memory</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --dump "mdw addr count" --speed 2</td></tr>
<tr><td>Read Fuse High</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_high --speed 2</td></tr>
<tr><td>Read Fuse Low</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_low --speed 2</td></tr>
<tr><td>Read Fuse Extended</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_read_extended --speed 2</td></tr>
<tr><td>Write Fuse High</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_high "fusebits" --speed 2</td></tr>
<tr><td>Write Fuse Low</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_low "fusebits" --speed 2</td></tr>
<tr><td>Write Fuse Extended</td><td colspan="4">embeddedprog.py --processor "yourProcessor" --fuse_write_extended "fusebits" --speed 2</td></tr>

<tr valign="top" style="background:#BBB"><td colspan="5"></td></tr>

</table>
<br>
<center><i style="color:#BBB">embeddedprog 0.1 created by <a href="" style="color:#bbb;">embedded projects GmbH</a>. Based on GNU/Linux, OpenOCD, avrdude and many other Open Source projects. <a href="" style="color:#bbb;">Documentation</a></i></center>


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


</script>
</html>
