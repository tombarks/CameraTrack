/*
This is a test program for use with Robs camera track system.
 
V1.0 - 10th May 2015
 
This program moves the 3A stepper motor on the camera track 325 * 5 steps in each direction.
The pad must be placed at the stepper motor end when the program is started
 
For use with the Adafruit Motor Shield v2
---->   http://www.adafruit.com/products/1438
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
  Serial.println("Single coil steps");
  if(directionCounter < reversalSteps / 2)myMotor->step(steps, BACKWARD, type);
  else myMotor->step(steps, FORWARD, type);
  directionCounter++;
  if(directionCounter >= reversalSteps)directionCounter = 0;
 myMotor->release();
 delay(500);
//  myMotor->step(100, BACKWARD, SINGLE);
 
//  Serial.println("Double coil steps");
//  myMotor->step(100, FORWARD, DOUBLE);
//  myMotor->step(100, BACKWARD, DOUBLE);
//  
//  Serial.println("Interleave coil steps");
//  myMotor->step(100, FORWARD, INTERLEAVE);
//  myMotor->step(100, BACKWARD, INTERLEAVE);
//  
//  Serial.println("Microstep steps");
//  myMotor->step(50, FORWARD, MICROSTEP);
//  myMotor->step(50, BACKWARD, MICROSTEP);
}
