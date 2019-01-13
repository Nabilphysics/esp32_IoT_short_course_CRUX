/*
Push Button 1 is attached with GPIO 4 and GND.
Input Pullup is activated that means Input pin is connected with HIGH internally.
When we press push button ESP32 will detect press as LOW
One Led is connected with GPIO 2 or If your ESP32 module contains Builtn in LED   
*/

int pushButton1 = 4;
int ledPin1 = 2;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton1, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  
}
void loop() {
  // read the input pin:
  int buttonState1 = digitalRead(pushButton1);
  // print out the state of the button:
  Serial.println(buttonState1);
  delay(100);        // delay in between reads for stability
  if(buttonState1 == 0)
  {
    digitalWrite(ledPin1, HIGH);
  }
  else{
    digitalWrite(ledPin1, LOW);
  }
  
}