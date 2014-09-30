<?php
	if (file_exists('/tmp/update_done')){
		header("location: index.php?".rand(1,10));
	}else{header( "refresh:3;url=update.php" );}

?>
<html>
<head>
<title>usbprog5 update in progress</title>
</head>
<body>
 <div align="left">
<div id="update" style="display:;border:0px solid gray;padding:.3em;background-color:white;position:absolute;width:80%;height:80%;left:10%;top:10%">



<a style="color:black;font-family:Ubuntu Mono,Terminus Font,GNU Unifont;size:5;" ><center>
<font size="7">
update in progress
</font>
</center>
</a>


<img id="update_loading" src="loading.gif" style="display:;position:absolute;width:40px;height:40px;left:48%;top:42%" / >
</tr></td>
</div></div>
</body>
</html>
