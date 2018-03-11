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
	exec("/home/pi/PSB/UdpSenderTest 1 2 127.0.0.1");
}

exec( "/home/pi/PSB/UdpSenderTest -2 -2 127.0.0.1 " );

#system( "/home/pi/PSB/OutputState -1" );

if( exec( "/home/pi/PSB/OutputState 1" ) == "1" )
{
	#echo "lampka wlaczona";
	$lampka = '1';
}
else
{
	#echo "lampka wylaczona";
	$lampka = '0';
}

?>

<form action="index.php?toglelampka" method="get">

<input type="hidden" name="toglelampka" value="1">
<input type="submit" value="<?php echo $lampka=='1' ? "Wylacz lampke" : "Wlacz lampke"; ?>" style="font-size : 30px; height:150px; width:400px" />

</form>
