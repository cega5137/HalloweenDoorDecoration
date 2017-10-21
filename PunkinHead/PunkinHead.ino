#include "FastLED.h"
//#include time

//Number of LEDs
#define NUM_LEDS 8
#define MAXBrigness 50

//Define our clock and data lines
#define DATA_PIN 11
#define CLOCK_PIN 13

//Pins for ultrasonic sensor
const int trigPin = 14;
const int echoPin = 12;

// LED for testing
const int led = 11;
const int led2 = 10; 

// Tolerance
float tol = 80;

// time Delay
float timeDelay = 10;
float lightDelay = 0.1;

//Create the LED array
CRGB leds[NUM_LEDS];

// Function Definitions
void setUltrasonic(int trigPin, int echoPin);
int getDistance();
void peopleAproaching(CRGB *LED);
void standBy(CRGB *LED);


void setup() { 

      //Tell FastLED what we're using. Note "BGR" where you might normally find "RGB".
      //This is just to rearrange the order to make all the colors work right.
      FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

      //Set global brightness
      FastLED.setBrightness(50);

      // Set Ultrasonic sensor
      setUltrasonic(trigPin, echoPin);
      pinMode(led, OUTPUT);
      pinMode(led2, OUTPUT);
}



void loop() { 

  uint8_t x;
  uint16_t wait = 100;
  float distance;
  distance = getDistance();

  if (distance < tol) {
    peopleAproaching(leds);
  }

  else {
    standBy(leds);
  }
}



void setUltrasonic(int trigPin, int echoPin){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  }

int getDistance(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  return distance;
  }

void peopleAproaching(CRGB *LED) {
  for (int x = 0; x < NUM_LEDS; x++)
  {
    LED[x] = CRGB::OrangeRed;
  }

  float t0 = millis();
  float T  = millis();
  while ((t0 + timeDelay) > T) {
      FastLED.setBrightness(MAXBrigness);
      delayMicroseconds(lightDelay);
      FastLED.setBrightness(0);
      delayMicroseconds(lightDelay);
      T = millis();
    } 
 }


void standBy(CRGB *LED) {
  //FastLED.setBrightness(50);
  for (int x = 0; x < NUM_LEDS; x++)
  {
    leds[x] = CRGB::OrangeRed;
  }

  for (int L = 0;L < MAXBrigness; L++ ){
    FastLED.setBrightness(L);
  }

  for (int L = MAXBrigness; L > 0; L-- ){
    FastLED.setBrightness(L);
  }
  
}
