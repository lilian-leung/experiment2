#include <animationTools.h>
#include <Servo.h>

//LILIAN - SERVO EYES
//TIME

long eventInterval = 10000; //10000 = 10 seconds
unsigned long previousMillis;

//SERVO
int servoPinLeft = 10;          
int servoPinRight = 11;
int servoAngle;
float servoSpeed = 0.2;

int sensorPin = 5;
int threshold1 = 1200; //1m
int threshold2 = 3500; //3m
int distanceMM;

Servo servoLeft;  // left eye
Servo servoRight;  // right eye

///////////////////////////////////

void setup() 
  {

  servoLeft.attach(servoPinLeft);  
  servoRight.attach(servoPinRight); 
 
  pinMode(sensorPin, INPUT);
  
  Serial.begin(9600);
  }

///////////////////////////////////


void loop()  {

    
distanceMM = pulseIn(sensorPin, HIGH);

servoLeft.write(servoAngle);
servoRight.write(servoAngle);


//DISTANCE IF

if (distanceMM <= threshold1) {  ///if you're close by
  servoSpeed = 0.8 ;             
  } 
 
if (distanceMM >= threshold2) {
  if (millis () >= eventInterval) {  //do this after after 10 sec
  servoSpeed = 0.1; }
  else
  {
  servoSpeed = 0.2;
}
}

previousMillis = millis ();

Serial.print("Distance in MM:"); //check sensor working
Serial.println(distanceMM); //print the distance

servoAngle = oscillate (0,180,0,servoSpeed,millis());

}
