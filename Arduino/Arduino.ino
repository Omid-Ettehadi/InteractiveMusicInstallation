/*
  Interactive Music Installation

  created 6 Nov 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
#include <FastLED.h>
#include <ArduinoJson.h>

// Pin Defnition
// Ultrasonic Sensors
#define us1TrigPin 12
#define us1EchoPin 11

#define us2TrigPin 10
#define us2EchoPin 9

#define us3TrigPin 8
#define us3EchoPin 7

// Instruments
#define instrument1_Note1 A0
#define instrument1_Note2 A1
#define instrument1_Note3 A2

#define instrument2_Note1 A3
#define instrument2_Note2 A4
#define instrument2_Note3 A5

#define instrument3_Note1 2
#define instrument3_Note2 3
#define instrument3_Note3 4

// LED Strip
#define LEDPin 5
#define NUM_LEDS 60

// Objects
Ultrasonic us1(us1TrigPin, us1EchoPin);
Ultrasonic us2(us2TrigPin, us2EchoPin);
Ultrasonic us3(us3TrigPin, us3EchoPin);

CRGB leds[NUM_LEDS];

// Variables
int distance1,distance2,distance3;
int instrument1[3];
int instrument2[3];
int instrument3[3];

// Sampling
unsigned long lastRead;
const int sampleRate = 200;
unsigned long lastLEDRead;
const int sampleRateLED = 500;

void setup() {
  // Initialize serial communications
  Serial.begin(9600);

  // Assign Pins
  pinMode(instrument1_Note1, INPUT_PULLUP);
  pinMode(instrument1_Note2, INPUT_PULLUP);
  pinMode(instrument1_Note3, INPUT_PULLUP);
  pinMode(instrument2_Note1, INPUT_PULLUP);
  pinMode(instrument2_Note2, INPUT_PULLUP);
  pinMode(instrument2_Note3, INPUT_PULLUP);
  pinMode(instrument3_Note1, INPUT_PULLUP);
  pinMode(instrument3_Note2, INPUT_PULLUP);
  pinMode(instrument3_Note3, INPUT_PULLUP);

  // Initialize all variables
  distance1 = 1000;
  distance2 = 1000;
  distance3 = 1000;
  
  FastLED.addLeds<WS2812, LEDPin, GRB>(leds, NUM_LEDS);
}
 
void loop() {
  if (millis() - lastRead >= sampleRate) {

    // Read distances
    distance1 = us1.distanceRead(); 
    distance2 = us2.distanceRead(); 
    distance3 = us3.distanceRead();

    // Filter distances and get rid of anything under 5
    if ( distance1 <= 5 ){distance1 = 1000;}
    if ( distance2 <= 5 ){distance2 = 1000;}
    if ( distance3 <= 5 ){distance3 = 1000;}

    // Read instrument's keys
    // Zero is Off, 1 is On
    //---------------- instrument 1 ----------------//
    instrument1[0] = digitalRead(instrument1_Note1);
    instrument1[1] = digitalRead(instrument1_Note2);
    instrument1[2] = digitalRead(instrument1_Note3);
    for ( int i = 0; i<3; i++){
      if (instrument1[i] == 0) {
        instrument1[i] = 1;
      } else {
        instrument1[i] = 0;
      }
    }
    //---------------- instrument 2 ----------------//
    instrument2[0] = digitalRead(instrument2_Note1);
    instrument2[1] = digitalRead(instrument2_Note2);
    instrument2[2] = digitalRead(instrument2_Note3);
    for ( int i = 0; i<3; i++){
      if (instrument2[i] == 0) {
        instrument2[i] = 1;
      } else {
        instrument2[i] = 0;
      }
    }
    //---------------- instrument 3 ----------------//
    instrument3[0] = digitalRead(instrument3_Note1);
    instrument3[1] = digitalRead(instrument3_Note2);
    instrument3[2] = digitalRead(instrument3_Note3);
    for ( int i = 0; i<3; i++){
      if (instrument3[i] == 0) {
        instrument3[i] = 1;
      } else {
        instrument3[i] = 0;
      }
    }

    // Send data to P5
    DynamicJsonBuffer messageBuffer(1000);                  // Create the Buffer for the JSON object        
    JsonObject& p5Send = messageBuffer.createObject();      // Create a JsonObject variable in that buffer       
  
    p5Send["us1"] = distance1;                              // Assign distance1 to the key "us1" in the json object
    p5Send["us2"] = distance2;                              // Assign distance2 to the key "us2" in the json object 
    p5Send["us3"] = distance3;                              // Assign distance3 to the key "us3" in the json object 

    p5Send["instrument1_Note1"] = instrument1[0];           // Assign instrument1[0] to the key "instrument1_Note1" in the json object 
    p5Send["instrument1_Note2"] = instrument1[1];           // Assign instrument1[1] to the key "instrument1_Note2" in the json object 
    p5Send["instrument1_Note3"] = instrument1[2];           // Assign instrument1[2] to the key "instrument1_Note3" in the json object 

    p5Send["instrument2_Note1"] = instrument2[0];           // Assign instrument2[0] to the key "instrument2_Note1" in the json object 
    p5Send["instrument2_Note2"] = instrument2[1];           // Assign instrument2[1] to the key "instrument2_Note2" in the json object 
    p5Send["instrument2_Note3"] = instrument2[2];           // Assign instrument2[2] to the key "instrument2_Note3" in the json object 

    p5Send["instrument3_Note1"] = instrument3[0];           // Assign instrument3[0] to the key "instrument3_Note1" in the json object 
    p5Send["instrument3_Note2"] = instrument3[1];           // Assign instrument3[1] to the key "instrument3_Note2" in the json object 
    p5Send["instrument3_Note3"] = instrument3[2];           // Assign instrument3[2] to the key "instrument3_Note3" in the json object 

    p5Send.printTo(Serial);                                 // Print JSON object as a string
    Serial.println();                                       // Print a \n character to the serial port to distinguish between objects
    
    lastRead = millis();
  }


  if (millis() - lastLEDRead >= sampleRateLED){
    
    // LEDs
    //-------------------------------- instrument 1 --------------------------------//
    if ( instrument1[0] == 1 || instrument1[1] == 1 || instrument1[2] == 1 ) {
      for (int i = 0; i <= 60; i++) {
        leds[i] = CRGB ( 255, 0, 0);
        FastLED.show();
      }
      for (int i = 60; i >= 0; i--) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    } 
    //-------------------------------- instrument 2 --------------------------------//
    else if ( instrument2[0] == 1 || instrument2[1] == 1 || instrument2[2] == 1 ) {
      for (int i = 0; i <= 60; i++) {
        leds[i] = CRGB ( 0, 0, 255);
        FastLED.show();
      }
      for (int i = 60; i >= 0; i--) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    } 
    //-------------------------------- instrument 3 --------------------------------//
    else if ( instrument3[0] == 1 || instrument3[1] == 1 || instrument3[2] == 1 ){
      for (int i = 0; i <= 60; i++) {
        leds[i] = CRGB ( 0, 255, 0);
        FastLED.show();
      }
      for (int i = 60; i >= 0; i--) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    } 
    //--------------------- distance under 150, engage audience ---------------------//
    else if ( distance1 <= 150 || distance2 <= 150 || distance3 <= 150 ) {
      for (int i = 0; i <= 20; i++) {
        leds[i] = CRGB ( 255, 255, 255);
        FastLED.show();
      }
      for (int i = 20; i >= 0; i--) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    } 
    //----------------------------- Turn everything off -----------------------------//
    else{ 
      for (int i = 60; i >= 0; i--) {
        leds[i] = CRGB ( 0, 0, 0);
        FastLED.show();
      }
    }
    lastLEDRead = millis();
  }
}
