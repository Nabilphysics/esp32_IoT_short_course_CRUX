//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Edited for LED Control by Syed Razwanul Haque Nabil
// Founder & CEO, www.cruxbd.com , nabilcrux@gmail.com
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
uint8_t ledPin = 2; //GPIO 2
char state;
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test by CRUX"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(ledPin, OUTPUT);
}

void loop() {
 if (SerialBT.available() > 0) {
   state = SerialBT.read();
   if (state == 'H' || state == 'h') {
     digitalWrite(ledPin, HIGH);
   }
   if (state == 'L' || state == 'l') {
     digitalWrite(ledPin, LOW);
   }
 }
 Serial.println(state);
 delay(50);
}
