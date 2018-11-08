/*
  Interactive Music Installation

  created 6 Nov 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
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

// Objects
Ultrasonic us1(us1TrigPin, us1EchoPin);
Ultrasonic us2(us2TrigPin, us2EchoPin);
Ultrasonic us3(us3TrigPin, us3EchoPin);

// Variables
int distance1,distance2,distance3;
int instrument1[3];
int instrument2[3];
int instrument3[3];

// Sampling
unsigned long lastRead;
const int sampleRate = 250;
unsigned long dataLastRead;
const int dataSampleRate = 250;


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
  distance1 = 0;
  distance2 = 0;
  distance3 = 0;
}
 
void loop() {
  if(millis() - lastRead >= sampleRate){
    
    distance1 = us1.distanceRead(); 
    distance2 = us2.distanceRead(); 
    distance3 = us3.distanceRead();

    /*for (int i = 0; i<3; i++){
      instrument1[i] = digitalRead("instrument1_Note"+i);
      instrument2[i] = digitalRead("instrument2_Note"+i);
      instrument3[i] = digitalRead("instrument3_Note"+i);
    }*/
    instrument1[0] = digitalRead(instrument1_Note1);
    instrument1[1] = digitalRead(instrument1_Note2);
    instrument1[2] = digitalRead(instrument1_Note3);

    instrument2[0] = digitalRead(instrument2_Note1);
    instrument2[1] = digitalRead(instrument2_Note2);
    instrument2[2] = digitalRead(instrument2_Note3);

    instrument3[0] = digitalRead(instrument3_Note1);
    instrument3[1] = digitalRead(instrument3_Note2);
    instrument3[2] = digitalRead(instrument3_Note3);

    /*
    Serial.print(distance1);
    Serial.print("\n");
    Serial.print(distance2);
    Serial.print("\n");
    Serial.print(distance3);
    Serial.print("\n");
    Serial.print("\n");

    Serial.print(instrument1[0]);
    Serial.print(",");
    Serial.print(instrument1[1]);
    Serial.print(",");
    Serial.print(instrument1[2]);
    Serial.print("\n");
    Serial.print(instrument2[0]);
    Serial.print(",");
    Serial.print(instrument2[1]);
    Serial.print(",");
    Serial.print(instrument2[2]);
    Serial.print("\n");
    Serial.print(instrument3[0]);
    Serial.print(",");
    Serial.print(instrument3[1]);
    Serial.print(",");
    Serial.print(instrument3[2]);
    Serial.print("\n");
    */
    
    lastRead = millis();
  }

  
  if(millis() - dataLastRead >= dataSampleRate){
    DynamicJsonBuffer messageBuffer(200);                   // Create the Buffer for the JSON object        
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

    p5Send.prettyPrintTo(Serial);                           // Print JSON object as a string
    Serial.println();                                       // Print a \n character to the serial port to distinguish between objects
    
    dataLastRead = millis();
  }
}
