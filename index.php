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


if(isset($_GET['my_checkbox']) && $_GET['isLampkaSet']=='0')
{
	#echo "wlaczam lampke";
    // user checked the box
	exec( "/home/pi/PSB/UdpSenderTest 1 1 127.0.0.1" );
}
else if(!isset($_GET['my_checkbox']) && $_GET['isLampkaSet']=='1')
{
	#echo "wylaczam lampke";
	// user did not check the box
	exec( "/home/pi/PSB/UdpSenderTest 1 0 127.0.0.1" );
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




<form action="" method="get">

<input type="submit" value="Update" style="height:100px; width:200px" />

<p></p>

<input  id='cmn-toggle-1' 
        class='cmn-toggle cmn-toggle-round'
        type='checkbox' 
        value='1'
        name='my_checkbox'
        <?php echo $lampka== '1' ? 'checked' : '0'; ?> 
/>
<label for='cmn-toggle-1'>Lampka</label>
<input type="hidden" name='isLampkaSet' value="<?php echo $lampka ?>" />

</form>
