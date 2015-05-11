/*
This is a test program for use with Robs camera track system.
 
V1.1 - 11th May 2015
 
This program moves the 3A stepper motor on the camera track 325 * 5 steps in each direction.
The pad must be placed at the stepper motor end when the program is started
 
For use with the Adafruit Motor Shield v2
---->   http://www.adafruit.com/products/1438

Added to GitHub

*/
 
 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
 
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
 
// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);
 
 
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");
 
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
 
  myMotor->setSpeed(10);  // 10 rpm  
}
 
int directionCounter = 0;
int type = DOUBLE; //DOUBLE Required for additional torque otherwise it does not move smoothly
int steps = 5; //Equivalent to 5 * 1.8 degrees of motion for each step
int reversalSteps = 650; //This is (325 * 5) steps in each direction which is equivalent to just short of the full travel length
 
void loop() {
  
<<<<<<< HEAD
  //Print to serial to state we are moving, Tom is a big ginger bear
=======
  //Print to serial to state we are moving the track 5 steps
>>>>>>> bd56e0224b2170bee1dc5e2747c1c56f5453865a
  Serial.println("Moving main track stepper motor 5 steps.");
  
  //Make a movement selecting the correct direction using a reversing counter
  if(directionCounter < reversalSteps / 2)myMotor->step(steps, BACKWARD, type);
  else myMotor->step(steps, FORWARD, type);
  
  //Give the instruction to release the motor this removes all electrical power from the motor as it is not required to hold the load stationary
  myMotor->release();
  
  //Increment and reset the direction counter
  directionCounter++;
  if(directionCounter >= reversalSteps)directionCounter = 0;
  
  //Delay 500ms  
  delay(500);
}
