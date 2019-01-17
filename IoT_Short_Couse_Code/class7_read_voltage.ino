/*
  
  ReadAnalogVoltage with ESP32
  Edited by Syed Razwanul Haque Nabil, www.github.com/Nabilphysics
  Original Code from Arduino Example
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +3.3V and ground.
  This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(13); //GPIO 13
  // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  float voltage = sensorValue * (3.3 / 4095.0);
  // print out the value you read:
  Serial.println(voltage);
}
