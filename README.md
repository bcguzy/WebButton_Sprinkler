# WebButton_Sprinkler  
A sprinkler that runs at the push of a WiFi button

## Documentation for hardware
The hardware configuration is the exact same as my [Weather_Sprinkler project](https://github.com/bcguzy/Weather_Sprinkler), just without the deep sleep wire. The same modifications could be made to improve the hardware.  
  
## Programming Libraries and techniques used  
The arduino IDE was used to develop the software for the sprinkler because of its robust support for the NodeMCU and for ease of use.
[The standard ESP8266 libraries](https://github.com/esp8266/Arduino) for arduino were used and the libraries for Wifi, web server, and mDNS were used.
The Web server library is used to show the button page on the local network and the mDNS library was used to redirect a simple address (water.local) to the correct IP.
Note that the placeholder ssid, password, and API key need to be replaced before this github code can be used. Serial outputs were used for debugging and to ensure that data was being recieved.
