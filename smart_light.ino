/*
  A simple program designed to setup and demonstrate the Keyes LDR Sensor Module - BDAA100008.
 
  The program monitors a connected analog pin and outputs the value to the
  serial monitor.
  
  modified 29th August 2019
  by Sebastian Karam - Flux Workshop
*/
int digitalPIN = 2;  // define OUT signal pin
int sense;         // define variable to store value read from pin
int led = 3;

void setup() {
  pinMode(digitalPIN, INPUT);  // set the OUT signal pin as an input
  pinMode(led, OUTPUT);        // set the OUT signal pin as an input

  Serial.begin(9600);  // launch the serial monitor
  Serial.println("Flux Workshop Example");
}

void loop() {
  sense = digitalRead(digitalPIN);                   // read the voltage level on the A0
  Serial.println((String) "Light level: " + sense);  // send the result to the serial monitor
  if (sense == 0) {
    digitalWrite(led, HIGH);
    delay(500);
  } else {
    digitalWrite(led, LOW);
    delay(500);

  }
 
}