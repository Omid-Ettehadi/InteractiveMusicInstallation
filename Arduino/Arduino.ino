/*
  Interactive Music Installation

  created 6 Nov 2018
  by Omid Ettehadi
*/

// Libraries
#include <Ultrasonic.h>
#include <ArduinoJson.h>

#define us1TrigPin 12
#define us1EchoPin 11
#define us2TrigPin 10
#define us2EchoPin 9
#define us3TrigPin 8
#define us3EchoPin 7

int distance1,distance2,distance3;

// Sampling
unsigned long lastRead;
const int sampleRate = 250;
unsigned long dataLastRead;
const int dataSampleRate = 250;

// Objects
Ultrasonic us1(us1TrigPin, us1EchoPin);
Ultrasonic us2(us2TrigPin, us2EchoPin);
Ultrasonic us3(us3TrigPin, us3EchoPin);

void setup() {
  // Initialize serial communications
  Serial.begin(9600);

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

    /*
    Serial.print(distance1);
    Serial.print("\n");
    Serial.print(distance2);
    Serial.print("\n");
    Serial.print(distance3);
    Serial.print("\n");
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
  
    p5Send.prettyPrintTo(Serial);                           // Print JSON object as a string
    Serial.println();                                       // Print a \n character to the serial port to distinguish between objects
    
    dataLastRead = millis();
  }
}
