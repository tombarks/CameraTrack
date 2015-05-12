/*
CameraTrack Arduino Project
 
V1.1 - 11th May 2015
 
This file contains code for moving the main track and camera body stepper motors.
 
For use with the Adafruit Motor Shield v2
---->   http://www.adafruit.com/products/1438

*/

#define FORWARDS 0
#define BACKWARDS 1
 
int travelCounter = 0;           //Stores the number of steps moved in the current travel direction since the last reversal (if any)
int type = DOUBLE;               //DOUBLE, a type of stepper motor step activating two coils simultaneously, Required for additional torque otherwise it does not move smoothly
int stepsPerDrive = 5;           //Equivalent to 5 * 1.8 degrees of motion for each step
int stepsInFullTravel = 1625;    //The number of motor steps that result in travel from one end of the track to the other (or slightly less than to ensure we don't hit the stops
int numberOfTravels = 1;         //The number of travels and subsequent reversals of direction per shoot
int travelDirection = BACKWARDS; //The current direction of motion

void Stepper_SetTravelParameters(int _stepsPerDrive, int _stepsInFullTravel, int _numberOfTravels)
{
  stepsPerDrive =  stepsPerDrive;
  stepsInFullTravel = _stepsInFullTravel;
  numberOfTravels = _numberOfTravels;
}

//Trigger the camera track stepper motor to move a fixed set of steps
int Stepper_DriveMainTrackMotor() {
  
  int moveSteps = 0;  //Stores the number of movement steps this drive
  
  //Check if we have completed our travels
  if(numberOfTravels == 0) return 0;
  
  //Print to serial to state we are moving the track 5 steps
  Serial.println("Driving main track stepper motor.");
  
  //Check if we have reached the end of travel
  if(travelCounter < stepsInFullTravel)
  {
    //Check how many move steps there are to the end of travel and 
    moveSteps = stepsInFullTravel - travelCounter;
    if(moveSteps > stepsPerDrive)moveSteps = stepsPerDrive;
  }
  else
  {
    //Print message to serial
    Serial.println("Main camera track travel completed.");
    
    //Reset travel counter
    travelCounter = 0;
    
    //Decrement the number of travels
    if(numberOfTravels != 0)numberOfTravels--;
    if(numberOfTravels == 0)return 1;
    
    //Reverse direction
    switch(travelDirection)
    {
      case FORWARDS:
          travelDirection = BACKWARDS;
        break;
      
      case BACKWARDS:
          travelDirection = FORWARD;
        break; 
    }
    
    //Set the moveSteps
    moveSteps = stepsPerDrive;
    if(moveSteps > stepsInFullTravel)moveSteps = stepsInFullTravel;
  }
  
  //Make a movement selecting the correct direction using a reversing counter
  if(moveSteps > 0)myMotor->step(moveSteps, travelDirection, type);
  
  //Increment the travel counter
  travelCounter += moveSteps;
  
  //Give the instruction to release the motor this removes all electrical power from the motor as it is not required to hold the load stationary
  myMotor->release();
  
  //Return
  return 1; 
}

//Trigger the camera body rotation stepper motor to move a fixed set of steps
void Stepper_DriveCameraBodyRotationMotor()
{
   //Do something
}

