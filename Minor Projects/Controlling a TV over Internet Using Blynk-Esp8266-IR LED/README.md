# Controlling IR Devices Using ESP8266 and Blynk App in Android

A simple device used to control any IR Device* using ESP8266 and Blynk App from any where in the world.

> Requirement
An IR LED 940nm (i used a 5mm 940nm)
Red LED 
Resistors
ESP8266

> Library Used
ESP8266wIfI : https://github.com/esp8266/Arduino
Blynk : https://github.com/blynkkk/blynk-library/releases/tag/v0.6.1
IRremoteESP8266 : https://github.com/crankyoldgit/IRremoteESP8266

Complete code is in the source code/main

First Do a Reciever Dump for the IR codes by the device remote, then enter the IR codes into the irsend.sendNEC(), function.

