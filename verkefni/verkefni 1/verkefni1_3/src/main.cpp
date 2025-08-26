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
  int main() {
  vexcodeInit();

  turnType turns[] = {right, left, left, right, right, left, right, right, left, right, left, right};
  int numTurns = sizeof(turns)/sizeof(turns[0]);

  for(int i = 0; i < numTurns; i++) {
    Drivetrain.driveFor(forward, 500, mm);
    wait(200, msec);
    Drivetrain.turnFor(turns[i], 90, degrees);
    wait(200, msec);
  }

  Drivetrain.driveFor(forward, 500, mm);
  wait(200, msec);
}}
 
 
 
 
 
 
  '''
  int i = 500;

while (true) {
  if (i >= 2500) {break;}

  Drivetrain.driveFor(forward, i, mm);
  wait(200, msec);

  Drivetrain.driveFor(reverse, i, mm);
  wait(200, msec); 

  i += 500;  
}


}
'''