#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT1, ratio18_1, false);
motor RightMotor = motor(PORT3, ratio18_1, true);
inertial Inertial20 = inertial(PORT20);
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT3, ratio18_1, true);
gyro TurnGyroSmart = gyro(Brain.ThreeWirePort.D);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart,
                                   TurnGyroSmart, 319.19, 320, 130, mm, 1);
// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}