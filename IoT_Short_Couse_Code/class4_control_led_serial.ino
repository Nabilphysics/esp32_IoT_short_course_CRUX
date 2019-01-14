uint8_t ledPin = 2; //GPIO 2
char state;
void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
}
void loop() {
 if (Serial.available() > 0) {
   state = Serial.read();
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
