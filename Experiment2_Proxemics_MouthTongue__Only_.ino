#include <animationTools.h>
#include <Servo.h>

//JIGNESH - SERVO MOUTH 
int servoMouthPin = 6;   // attached to
int moveRate = 40;       //the time between updates in milliseconds
int minAngle = 70;       //open mouth
int maxAngle = 110;      //closing mouth
int moveIncrement = 1;   
int servoAngle;

long lastMouthOpen;
Servo servoMouth;  

//NEO - LED TONGUE
int ledPin1 = 13;         // attached to   
int fadeRate = 5;         //the time between updates in milliseconds
int minBrightVal = 0;     
int maxBrightVal = 255;   
int fadeIncrement = 1;   
int ledBrightness;
long lastTimeYouChanged;  

//SENSOR
int sensorPin = 10;
int threshold = 3200; //1m
int distanceMM;


////////////////////////////

void setup() {
  
servoMouth.attach(servoMouthPin); 
servoAngle = minAngle;

pinMode(ledPin1, OUTPUT);                  
ledBrightness = minBrightVal;

}

////////////////////////////

void loop() {

//SENSOR STUFF
distanceMM = pulseIn (sensorPin, HIGH);

if (distanceMM <= threshold) {
 servoAngle = maxAngle;
} else { 
 servoAngle = minAngle;
}
 

//LED MOVEMENT 

if(millis()-lastTimeYouChanged>=fadeRate) 
{                                          
analogWrite(ledPin1,ledBrightness);

ledBrightness += fadeIncrement;

if (servoAngle <= 90) {
  ledBrightness = maxBrightVal; 
  } else {
      ledBrightness = minBrightVal;
    }


//SERVO MOVEMENT

if (millis()-lastMouthOpen >=moveRate) {
  servoMouth.write (servoAngle);
  servoAngle += moveIncrement;
  
  if (servoAngle <= minAngle || servoAngle >= maxAngle) 
  {
    moveIncrement = -moveIncrement;
    }

lastMouthOpen = millis(); 
}

Serial.print("Distance in MM:"); //check sensor working
Serial.println (distanceMM); //print the distance

}

}
