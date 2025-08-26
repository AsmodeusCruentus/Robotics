/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Moving Forward (mm)                                       */
/*                                                                            */
/*    This Program drives the robot forward for 150 millimeters.              */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 10, D
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  
  vexcodeInit();

  #turnType turns[] = {right, left, left, right, right, left, right, right, left, right, left, right};

  turnType turns[] = {right, left, right, left, right, left, right, left, right};

  for (auto turn : turns) {
    Drivetrain.driveFor(forward, 500, mm); 
    Drivetrain.turnFor(turn, 90, degrees);  
  }

  Drivetrain.driveFor(forward, 500, mm);    
}
 
 
