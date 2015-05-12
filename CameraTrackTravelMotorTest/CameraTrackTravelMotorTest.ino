/*
CameraTrack Arduino Project
 
V1.1 - 12th May 2015

CameraTrackTravelMotorTest.ino
 
Arduino based camera tracking system. Developed as a collaborative effort between two Chepstonians. 
Final design goal is a dual motor camera track system allowing for stepped linear motion along the camera track over a fixed time period, 
rotatation of the camera body about the vertical axis and automatic triggering of camera.
 
For use with the Adafruit Motor Shield v2
---->   http://www.adafruit.com/products/1438

Added to GitHub at https://github.com/tombarks/CameraTrack

*/ 
 
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
 
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
 
// Connect a stepper motor with 200 steps per revolution (1.8 degree) to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

//Global variables
int loopDelay = 1;  //defines the number of seconds between each motion and camera trigger event
 
//Main setup routine
void setup() {
  
  // set up Serial library at 9600 bps
  Serial.begin(9600);
  
  //Say hello
  Serial.println("CameraTrack software loading....");
  
  // create with the default frequency 1.6KHz
  AFMS.begin();
  
  //Set the motor speed to 10 rpm 
  myMotor->setSpeed(10);

  //Add some code to load the parameters for the shoot
  Stepper_SetTravelParameters(5, 1625, 2) //stepsPerDrive, stepsPerTravel, numberOfTravels

  //Add some code to delay the start of the shoot until the user indicates that they are ready to start  
}

//The main process loop
void loop() {
  
  //local stack cars
  int mainTrackDriveOutcome;
  
  //try and drive the main track motor and store the outcome
  mainTrackDriveOutcome = Stepper_DriveMainTrackMotor();
  
  //Check the outcome of the main track drive
  if(mainTrackDriveOutcome != 0)
  {  
    //Move the camera body rotation stepper motor
    //**This may need to happen in some manner asncronous to the main track motor as the number of steps to achieve the desired camera rotation
    //**over the desired travel may not be aligned with the main track motor.
    Stepper_DriveCameraBodyRotationMotor();
    
    //Trigger camera autofocus
    Camera_TriggerAutoFocus();
    
    //Trigger the camera shutter
    Camera_TriggerShutter();
    
    //Do some other action if we have finished the drive
    if(mainTrackDriveOutcome == 2)
    {
       //doalittledance 
    }
  }
  
  //Delay for loopDelay seconds
  for(int i = 0; i < loopDelay; i++)delay(1000);
}
