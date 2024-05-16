#ifndef PAGE_DISPLAYSETTINGS_H_
#define PAGE_DISPLAYSETTINGS_H_

const char PAGE_DisplaySettings[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Display Settings</strong>
<hr>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr><td align="right">Second Color</td><td><input id="second-color" name="second-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right">Unit Minute Color</td><td><input id="unit-minute-color" name="unit-minute-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right">Tenth Minute Color</td><td><input id="tenth-minute-color" name="tenth-minute-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right">Unit Hour Color</td><td><input id="unit-hour-color" name="unit-hour-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right">Tenth Hour Color</td><td><input id="tenth-hour-color" name="tenth-hour-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right">Blink Color</td><td><input id="blink-color" name="blink-color" type="color" value="#ffffff" style="width:150px"></td></tr>
<tr><td align="right"></td><td> </td></tr>
<tr><td align="right">Blinking Effect:</td><td><input type="checkbox" id="blinking-effect" name="blinking-effect"></td></tr>
<tr><td align="right">Show Seconds:</td><td><input type="checkbox" id="show-seconds" name="show-seconds"></td></tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--grey" value="Save"></td></tr>
</table>
</form>
<script>
  
window.onload = function ()
{
  load("style.css","css", function() 
  {
    load("microajax.js","js", function() 
    {
        setValues("/admin/displayvalues");
    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>
)=====";

void send_display_settings_html()
{
	Serial.println("************************************");
	Serial.println(server.args());

	  if (server.args() > 0 )  // Save Settings
	  {
		    config.ShowSeconds = 0;
		    config.BlinkingEffect = 0;
	    for ( uint8_t i = 0; i < server.args(); i++ ) {
	      if (server.argName(i) == "second-color") config.SecondColor = server.arg(i);
	      if (server.argName(i) == "unit-minute-color") config.UnitMinuteColor = server.arg(i);
	      if (server.argName(i) == "tenth-minute-color") config.TenthMinuteColor = server.arg(i);
	      if (server.argName(i) == "unit-hour-color") config.UnitHourColor = server.arg(i);
	      if (server.argName(i) == "tenth-hour-color") config.TenthHourColor = server.arg(i);
	      if (server.argName(i) == "blink-color") config.BlinkColor = server.arg(i);
	      if (server.argName(i) == "show-seconds") config.ShowSeconds =  1;
	      if (server.argName(i) == "blinking-effect") config.BlinkingEffect =  1;
	    }
	    //Serial.println(config.Blinkingeffect);
	    //Serial.println(config.SecondColor);
	    WriteConfig();
	  }
	  server.send_P ( 200, "text/html", PAGE_DisplaySettings );
	  Serial.println(__FUNCTION__);
}

void send_display_settings_values_html()
{

  String values ="";
  values += "second-color|" + (String) config.SecondColor + "|input\n";
  values += "unit-minute-color|" + (String) config.UnitMinuteColor + "|input\n";
  values += "tenth-minute-color|" + (String) config.TenthMinuteColor + "|input\n";
  values += "unit-hour-color|" + (String) config.UnitHourColor + "|input\n";
  values += "tenth-hour-color|" + (String) config.TenthHourColor + "|input\n";
  values += "blink-color|" + (String) config.BlinkColor + "|input\n";
  values += "show-seconds|" +  (String) (config.ShowSeconds ? "checked" : "") + "|chk\n";
  values += "blinking-effect|" +  (String) (config.BlinkingEffect ? "checked" : "") + "|chk\n";
  Serial.println(values);
  server.send ( 200, "text/plain", values);
  Serial.println(__FUNCTION__);
  //AdminTimeOutCounter=0;
  temp_minute = 60;
}

#endif /* PAGE_DISPLAYSETTINGS_H_ */
