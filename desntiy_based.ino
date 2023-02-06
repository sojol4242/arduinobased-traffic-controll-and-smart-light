#include <TimerOne.h>
#define RST_PIN 5    // Configurable, see typical pin layout above
// Red,yellow,green
int signal1[] = { 10, 9, 11 };   // connect signal lights
int signal2[] = { 37, 39, 41 };  // connect signal lights
int signal3[] = { 47, 49, 51 };  // connect signal lights
int signal4[] = { 17, 18, 19 };  // connect signal lights
int i;
// delay
int redDelay = 8000; 
int yellowDelay = 3500;
// trigger and echo pins
volatile int triggerpin1 = 24;  // ultrasonic signal out pin
volatile int triggerpin2 = 34;
volatile int triggerpin3 = 44; 
volatile int triggerpin4 = 50;
volatile int echopin1 = 26;  // ultrasonic signal receiving pin
volatile int echopin2 = 31;
volatile int echopin3 = 46;
volatile int echopin4 = 52;
volatile long time;           // Variable for storing the time traveled
volatile int S1, S2, S3, S4;  // Variables for storing the distance covered

int t = 5;  // distance under which it will look for vehicles.

void setup() {
  Serial.begin(9600);
  Timer1.initialize(700000);           //Begin using the timer. This function must be called first. "microseconds" is the period of time the timer takes.
  Timer1.attachInterrupt(softInterr);  //Run a function each time the timer period finishes.

  // Declaring LED pins as output
  for (int i = 0; i < 4; i++) {
    pinMode(signal1[i], OUTPUT);
    pinMode(signal2[i], OUTPUT);
    pinMode(signal3[i], OUTPUT);
    pinMode(signal4[i], OUTPUT);
  }
  // Declaring ultrasonic sensor pins as output
  pinMode(triggerpin1, OUTPUT);
  pinMode(echopin1, INPUT);
  pinMode(triggerpin2, OUTPUT);
  pinMode(echopin2, INPUT);
  pinMode(triggerpin3, OUTPUT);
  pinMode(echopin3, INPUT);
  pinMode(triggerpin4, OUTPUT);
  pinMode(echopin4, INPUT);
}
//  driver code 
void loop() {
  // If there are vehicles at signal 1
  if (S1 < t) {
    signal1Function();
  }
  // If there are vehicles at signal 2
  if (S2 < t) {
    signal2Function();
  }
  // If there are vehicles at signal 3
  if (S3 < t) {
    signal3Function();
  }
  // If there are vehicles at signal 4
  if (S4 < t) {
    signal4Function();
  }
}
// This is interrupt function and it will run each time the timer period finishes. The timer period is set at 100 milli seconds.
void softInterr() {
  // Reading from first ultrasonic sensor
  digitalWrite(triggerpin1, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin1, LOW);
  time = pulseIn(echopin1, HIGH);
  S1 = time * 0.034 / 2;
  // Reading from second ultrasonic sensor
  digitalWrite(triggerpin2, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin2, LOW);
  time = pulseIn(echopin2, HIGH);
  S2 = time * 0.034 / 2;
  // Reading from third ultrasonic sensor
  digitalWrite(triggerpin3, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin3, LOW);
  time = pulseIn(echopin3, HIGH);
  S3 = time * 0.034 / 2;
  // Reading from fourth ultrasonic sensor
  digitalWrite(triggerpin4, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin4, LOW);
  time = pulseIn(echopin4, HIGH);
  S4 = time * 0.034 / 2;
}

void signal1Function() {
  Serial.println("signal 1");
  low();
  // Make RED LED LOW and make Green HIGH for 5 seconds
  digitalWrite(signal1[0], LOW);
  digitalWrite(signal1[2], HIGH);
  digitalWrite(signal3[0], LOW);
  digitalWrite(signal3[2], HIGH);
  delay(redDelay);
  // if there are vehicels at other signals
  if (S2 < t || S3 < t || S4 < t) {
    // Make Green LED LOW and make yellow LED HIGH for 2 seconds
    digitalWrite(signal1[2], LOW);
    digitalWrite(signal1[1], HIGH);
    digitalWrite(signal3[2], LOW);
    digitalWrite(signal3[1], HIGH);
    delay(yellowDelay);
  }
}

void signal2Function() {
  Serial.println("signal 2");
  low();
  digitalWrite(signal2[0], LOW);
  digitalWrite(signal2[2], HIGH);
  digitalWrite(signal4[0], LOW);
  digitalWrite(signal4[2], HIGH);
  delay(redDelay);
  if (S1 < t || S3 < t || S4 < t) {
    digitalWrite(signal2[2], LOW);
    digitalWrite(signal2[1], HIGH);
    digitalWrite(signal4[2], LOW);
    digitalWrite(signal4[1], HIGH);
    delay(yellowDelay);
  }
}

void signal3Function() {
  Serial.println("signal 3");
  low();
  digitalWrite(signal3[0], LOW);
  digitalWrite(signal3[2], HIGH);
  digitalWrite(signal1[0], LOW);
  digitalWrite(signal1[2], HIGH);
  delay(redDelay);
  if (S1 < t || S2 < t || S4 < t) {
    digitalWrite(signal3[2], LOW);
    digitalWrite(signal3[1], HIGH);
    digitalWrite(signal1[2], LOW);
    digitalWrite(signal1[1], HIGH);
    delay(yellowDelay);
  }
}

void signal4Function() {
  Serial.println("signal 4");
  low();
  digitalWrite(signal4[0], LOW);
  digitalWrite(signal4[2], HIGH);
  digitalWrite(signal2[0], LOW);
  digitalWrite(signal2[2], HIGH);
  delay(redDelay);
  if (S1 < t || S2 < t || S3 < t) {
    digitalWrite(signal4[2], LOW);
    digitalWrite(signal4[1], HIGH);
    digitalWrite(signal2[2], LOW);
    digitalWrite(signal2[1], HIGH);
    delay(yellowDelay);
  }
}

// Function to make all LED's LOW except RED one's.
void low() {
  for (int i = 1; i < 3; i++) {
    digitalWrite(signal1[i], LOW);
    digitalWrite(signal2[i], LOW);
    digitalWrite(signal3[i], LOW);
    digitalWrite(signal4[i], LOW);
  }
  for (int i = 0; i < 1; i++) {
    digitalWrite(signal1[i], HIGH);
    digitalWrite(signal2[i], HIGH);
    digitalWrite(signal3[i], HIGH);
    digitalWrite(signal4[i], HIGH);
  }
}
 