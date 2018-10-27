<style type="text/css">
body {
  width: 120px;
  height: 700px;
	font-size: 18pt; 
}
</style>

<?php

#echo $_GET['my_checkbox'];
#echo $_GET['isLampkaSet'];


if(isset($_GET['toglelampka']))
{
	#echo "toglam lampke";
	exec("/home/pi/PSB/UdpSenderTest 3 2 127.0.0.1");
}
if(isset($_GET['toglesub']))
{
	exec("/home/pi/PSB/UdpSenderTest 2 2 127.0.0.1");
}

exec( "/home/pi/PSB/UdpSenderTest -2 -2 127.0.0.1 " );

#system( "/home/pi/PSB/OutputState -1" );

if( exec( "/home/pi/PSB/OutputState 3" ) == "1" )
{
	#echo "lampka wlaczona";
	$lampka = '1';
}
else
{
	#echo "lampka wylaczona";
	$lampka = '0';
}

if( exec("/home/pi/PSB/OutputState 2" ) == "1" )
{
 	$sub = '1';
}
else
{
	$sub = '0';
}

?>

<form action="index.php?toglelampka" method="get">

<input type="hidden" name="toglelampka" value="1">
<input type="submit" value="<?php echo $lampka=='1' ? "Wylacz lampke" : "Wlacz lampke"; ?>" style="font-size : 30px; height:150px; width:400px" />

</form>

<form action="index.php?toglesub" method="get">

<input type="hidden" name="toglesub" value="1">
<input type="submit" value="<?php echo $sub=='1' ? "Wylacz wzmacniacz" :"Wlacz wzmacniacz"; ?>" style="font-size:30px; height:150px; width:400px" />

</form>
