# Wanduhr

In this repository you can find all the code needed to built a "smart" wall clock using an esp8266 and led ring segments. 
The esp8266 gets the time via NTP. The appearance of the clock can be adjusted using a PWA or via the browser.   
If you need the schematics or build the housing I've designed, the necessarry files can be found in [this repo](https://github.com/FrankenApps/Wanduhr_support_files).

## Setup
1. The code needs to be uploaded using PlatformIO, make sure to install all librarys first
2. Once powered up, the esp8266 will create a WIFI access point named "Wanduhr"
3. Connect to the AP, enter the credentials for your home WIFI and the correct time should be displayed

## Customizing
Once connected to the local network, you can access the web page for controlling the clock by entering the IP-adress of the esp8266. The page is optimized for using it as a PWA, so make sure to add it to your homescreen. From there you can control the clock and adjust its appearance.

## Appearance
The "Wanduhr" is intended to look (a bit) like this:

![Wanduhr (render)](https://raw.githubusercontent.com/FrankenApps/Wanduhr_support_files/master/images/Wanduhr.gif)