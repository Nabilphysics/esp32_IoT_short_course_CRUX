/***************************************************
  Adafruit MQTT Library ESP32 Example
  Edited by Syed Razwanul Haque (Nabil)
  CEO and Founder, www.cruxbd.com
  www.youtube.com/Nabilphysics
  This is a very basic code. I upload it just for an IDEA
  Three or more LED can be controlled by this code using adafruit IoT
  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include "WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// the on off button feed turns this LED on/off
#define LED1 1  //GPIO 1
#define LED2 2  //GPIO 2
#define LED3 3  //GPIO 3

/************************* WiFi Access Point *********************************/
#define WLAN_SSID   	"yourSSID"
#define WLAN_PASS   	"yourPassword"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER  	"io.adafruit.com"
#define AIO_SERVERPORT  1883               	// use 8883 for SSL
// You have to replace it with your own User name and AIO key
#define AIO_USERNAME	"crux"
#define AIO_KEY     	"2dacfc5913343434b3ac09718cafe124"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe onoffbutton1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff1");
Adafruit_MQTT_Subscribe onoffbutton2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff2");
Adafruit_MQTT_Subscribe onoffbutton3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff3");

/*************************** Sketch Code ************************************/

void MQTT_connect();

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
 
  Serial.begin(115200);
  Serial.println("\n Starting");
  delay(10);
  Serial.println(F("MQTT Switch demo"));
  Serial.println(WiFi.SSID());
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff & slider feed.
  mqtt.subscribe(&onoffbutton1);
  mqtt.subscribe(&onoffbutton2);
  mqtt.subscribe(&onoffbutton3);
}

uint32_t x=0;

void loop() {
 
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
 
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000))) {
	// Check if its the onoff button feed
	if (subscription == &onoffbutton1) {
  	Serial.print(F("On-Off button: "));
  	Serial.println((char *)onoffbutton1.lastread);
 	 
  	if (strcmp((char *)onoffbutton1.lastread, "ON") == 0) {
    	digitalWrite(LED1, HIGH);
  	}
  	if (strcmp((char *)onoffbutton1.lastread, "OFF") == 0) {
    	digitalWrite(LED1, LOW);
  	}
	}

	if (subscription == &onoffbutton2) {
  	Serial.print(F("On-Off button 2: "));
  	Serial.println((char *)onoffbutton2.lastread);
 	 
  	if (strcmp((char *)onoffbutton2.lastread, "ON") == 0) {
    	digitalWrite(LED2, HIGH);
  	}
  	if (strcmp((char *)onoffbutton2.lastread, "OFF") == 0) {
    	digitalWrite(LED2, LOW);
  	}
	}
 	if (subscription == &onoffbutton3) {
  	Serial.print(F("On-Off button 3: "));
  	Serial.println((char *)onoffbutton3.lastread);
 	 
  	if (strcmp((char *)onoffbutton3.lastread, "ON") == 0) {
    	digitalWrite(LED3, HIGH);
  	}
  	if (strcmp((char *)onoffbutton3.lastread, "OFF") == 0) {
    	digitalWrite(LED3, LOW);
  	}
	}
    
//	// check if its the slider feed
//	if (subscription == &slider) {
//  	Serial.print(F("Slider: "));
//  	Serial.println((char *)slider.lastread);
//  	uint16_t sliderval = atoi((char *)slider.lastread);  // convert to a number
//  	analogWrite(PWMOUT, sliderval);
//	}
  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
	mqtt.disconnect();
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
   	Serial.println(mqtt.connectErrorString(ret));
   	Serial.println("Retrying MQTT connection in 5 seconds...");
	 
   	mqtt.disconnect();
   	delay(5000);  // wait 5 seconds
   	retries--;
   	if (retries == 0) {
     	// basically die and wait for WDT to reset me
     	while (1);
   	}
  }
  Serial.println("MQTT Connected!");
  }
