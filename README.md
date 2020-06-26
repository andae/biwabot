## Biwabot
### Telegram Bot learning project Builds a Flood Early Warning System with ESP8266.
___
### Introduction
It relies on [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library so, in order to use a Biwabot object, you need to install the ArduinoJson library first (you can use library manager).
You also need to install the [ESP8266 Arduino Core and Library](https://github.com/esp8266/Arduino).
Don't you know Telegram bots and how to setup one? Check [this](https://core.telegram.org/bots#6-botfather).

+ **_Please pay attention to the installed version of ArduinoJson library: it MUST be 5.13.5 or lesser._**

### Feature
+ Manage WiFi connection (methods for connecting to an access point, set a static IP)
+ Send and receive messages
+ Inline keyboards
+ Receive localization messages
+ Reply keyboards 
+ Receive contacts messages 

### Supported boards
The library works with the ESP8266 chipset: all the ESP8266 boards are supported.

### Simple usage 
Build a flood early warning system with ESP8266 example provided in the [examples folder](https://github.com/andae/biwabot/tree/master/examples/biwabot).

### Special thanks
A special thanks go to these people who helped me making this project library.
+ Gianmaria Mancosu
+ Marco Madlena
+ Stefano Ledda


### Changelog

+ 1.0.0 Initial version

