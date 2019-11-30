#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>  
#include <WiFiUdp.h>
#include <NeoPixelBrightnessBus.h>
#include <NTPClient.h>
#include <FS.h>
#include "index.h"

#define colorSaturation 255 //is overriden by brightness

String currentTime = "00:00:00";
const uint16_t PixelCount = 60;

NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> strip(PixelCount, 2);  //pin is ignored on esp8266

//all the settings as global variables
RgbColor secondsRGB(0, colorSaturation, 0);
RgbColor minutesRGB(colorSaturation, 0, 0);
RgbColor hoursRGB(0, 0, colorSaturation);
RgbColor off(0);
RgbColor helperColorRGB(colorSaturation/8);
boolean showHelper = true;
boolean daylightSavings = true;
boolean clockMode = true;
boolean stopwatchMode = false;
String ntpProvider = "europe.pool.ntp.org";
float helperBrightness = 16.0;
int pointerBrightness = 128;

ESP8266WebServer server(80);

WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, ntpProvider.c_str(), 3600, 60000);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

unsigned char h2int(char c)
{
    if (c >= '0' && c <='9'){
        return((unsigned char)c - '0');
    }
    if (c >= 'a' && c <='f'){
        return((unsigned char)c - 'a' + 10);
    }
    if (c >= 'A' && c <='F'){
        return((unsigned char)c - 'A' + 10);
    }
    return(0);
}

String urldecode(String str){  
    String encodedString="";
    char c;
    char code0;
    char code1;
    for (unsigned int i = 0; i < str.length(); i++){
        c=str.charAt(i);
      if (c == '+'){
        encodedString+=' ';  
      }else if (c == '%') {
        i++;
        code0=str.charAt(i);
        i++;
        code1=str.charAt(i);
        c = (h2int(code0) << 4) | h2int(code1);
        encodedString+=c;
      } else{
        
        encodedString+=c;  
      }
      
      yield();
    }
    
   return encodedString;
}

String split(String s, char parser, int index) {
  String rs="";
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex,rToIndex);
    } else parserCnt++;
  }
  return rs;
}

void getSettingsFromStorage(){
  File f = SPIFFS.open("/config.txt", "r");
    String settingsData = "";
    for(unsigned int i=0; i < f.size(); i++){ //Read until end of file 
      settingsData += String((char)f.read());
    }
    String secondsColor = split(settingsData, ';', 0);
    String minutesColor = split(settingsData, ';', 1);
    String hoursColor = split(settingsData, ';', 2);
    String helperColor = split(settingsData, ';', 3);
    //actually update the rgb colors of the neopixel library (convert html to neoPixelRGB color)
    secondsColor = secondsColor.substring(4);
    secondsColor.replace(")", ",");
    secondsRGB = RgbColor(split(secondsColor, ',', 0).toInt(), split(secondsColor, ',', 1).toInt(), split(secondsColor, ',', 2).toInt());
    minutesColor = minutesColor.substring(4);
    minutesColor.replace(")", ",");
    minutesRGB = RgbColor(split(minutesColor, ',', 0).toInt(), split(minutesColor, ',', 1).toInt(), split(minutesColor, ',', 2).toInt());
    hoursColor = hoursColor.substring(4);
    hoursColor.replace(")", ",");
    hoursRGB = RgbColor(split(hoursColor, ',', 0).toInt(), split(hoursColor, ',', 1).toInt(), split(hoursColor, ',', 2).toInt());

    helperBrightness = split(settingsData, ';', 9).toFloat();
    helperBrightness = split(settingsData, ';', 10).toFloat()/helperBrightness;
    pointerBrightness = split(settingsData, ';', 10).toInt();

    helperColor = helperColor.substring(4);
    helperColor.replace(")", ",");
    helperColorRGB = RgbColor(round(split(helperColor, ',', 0).toFloat()/helperBrightness), round(split(helperColor, ',', 1).toFloat()/helperBrightness), round(split(helperColor, ',', 2).toFloat()/helperBrightness));

    if(split(settingsData, ';', 4) == "true"){
      showHelper = true;
    } else{
      showHelper = false;
    }
    if(split(settingsData, ';', 5) == "true"){
      daylightSavings = true;
    } else{
      daylightSavings = false;
    }
    if(split(settingsData, ';', 6) == "true"){
      clockMode = true;
    } else{
      clockMode = false;
    }
    if(split(settingsData, ';', 7) == "true"){
      stopwatchMode = true;
    } else{
      stopwatchMode = false;
    }
    ntpProvider = split(settingsData, ';', 8);
}

void handleRoot() {
  String html = MAIN_page;
  server.send(200, "text/html", html);
}

void handleUpdateSettings() {
  String rawData = server.arg("plain");
  server.send(200, "text/plain", "success");
  String decodedData = urldecode(rawData).substring(9);
  Serial.println("New Settings: " + decodedData);
  //SPIFFS.format();
  File f = SPIFFS.open("/config.txt", "w");
  if (!f) {
    Serial.println("Error: Configuration file could not be updated.");
  }
  else{
    f.print(decodedData); //Write new user configuration into config file
    f.close();  
  }
  getSettingsFromStorage();
  
}

void handleGetSettings() {
  File f = SPIFFS.open("/config.txt", "r");
  String currentSettings = "";
  for(unsigned int i=0; i < f.size(); i++){ //Read until end of file 
    currentSettings += String((char)f.read());
  }
  server.send(200, "text/plain", currentSettings);
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  //get configuration file from memory if it exists
  if(SPIFFS.begin()){
      Serial.println("SPIFFS initializing ... OK");
  } else{
      Serial.println("SPIFFS initializing ... error!");
  }
  //SPIFFS.format(); //remove for production
  if(SPIFFS.exists("/config.txt") == false){
    File f = SPIFFS.open("/config.txt", "w");

    if (!f) {
      Serial.println("File creation failed.");
    }
    else{
        String defaultSettings = "rgb(0,255,0);rgb(255,0,0);rgb(0,0,255);rgb(238,238,238);true;true;true;false;europe.pool.ntp.org;16;128;";
        f.print(defaultSettings); //Write default configuration into file
        f.close();  
    }
  } else{
    getSettingsFromStorage();
  }

  //start up wifi and http server
  WiFiManager wifiManager;
  wifiManager.autoConnect("Wanduhr");
  Serial.println("Connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/updateSettings", handleUpdateSettings);
  server.on("/currentSettings", handleGetSettings);

  server.begin();
  Serial.println("HTTP server started");

  strip.Begin(); // this resets all the neopixels to an off state
  strip.Show();
  strip.SetBrightness(pointerBrightness); //set strip maximum brightness
  Serial.println("NeoPixels initialized");
  timeClient.begin();
  Serial.println("Connected to NTP-Provider");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  timeClient.update();
    if(currentTime != timeClient.getFormattedTime() && clockMode == true){
      currentTime = timeClient.getFormattedTime();

      int time_offset = 0;
      if(daylightSavings){
        time_offset = 1;
      } else{
        time_offset = 0;
      }     
      
      //Serial.println(currentTime);
      int seconds = currentTime.substring(6,8).toInt();
      int minutes = currentTime.substring(3,5).toInt();
      int hours   = currentTime.substring(0,2).toInt()+time_offset; //because this is UTC

      if(hours > 12){
        hours -= 12;
      }
      if(hours==12){
        hours = 0;
      }
      for(int i = 0; i<PixelCount; i++){
       strip.SetPixelColor(i, off); //save the if-statement and will eventually be overriden nevertheless 
      }

      //markers
      if (showHelper) {
        strip.SetPixelColor(0, helperColorRGB);
        strip.SetPixelColor(15, helperColorRGB);
        strip.SetPixelColor(30, helperColorRGB);
        strip.SetPixelColor(45, helperColorRGB);
      }
      
      strip.SetBrightness(pointerBrightness);
      strip.SetPixelColor(seconds, secondsRGB);
      strip.SetPixelColor(minutes, minutesRGB);
      strip.SetPixelColor(hours*5, hoursRGB);
      strip.Show();
      delay(600);
    }
}