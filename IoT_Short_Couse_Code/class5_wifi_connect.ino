/*
 This example is written for a network using WPA(Wi-Fi Protected Access) encryption. For
 WEP(Wired Equivalent Privacy) or WPA, change the Wifi.begin() call accordingly.
 created for arduino 25 Nov 2012
 by Tom Igoe
 Edited by Syed Razwanul Haque (Nabil)
 */

#include <WiFi.h>

const char* ssid     = "yourssid";
const char* password = "yourpasswd";

void setup()
{
    Serial.begin(115200);
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
 }

 void loop(){
   }
