#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT1, ratio18_1, false);
motor RightDriveSmart = motor(PORT3, ratio18_1, true);
inertial DrivetrainInertial = inertial(PORT20);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);
motor ClawMotor = motor(PORT4, ratio18_1, false);
motor ArmMotor = motor(PORT5, ratio18_1, false);
// rotation Rotation4 = rotation(PORT4, false);
gps GPS8 = gps(PORT10, -40, 300.00, mm, 180);
signature BLUE_SIG =
    signature(1, -329, 683, 177, 6063, 9467, 7765, 2.5, 0);
signature GREEN_SIG =
    signature(2, -7975, -6177, -7076, -3687, -2091, -2889, 2.5, 0);
signature RED_SIG =
    signature(3, 6177, 7765, 6971, -1713, -1063, -1388, 2.5, 0);
signature Vision5__SIG_4 = signature(4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision5__SIG_5 = signature(5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision5__SIG_6 = signature(6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision5__SIG_7 = signature(7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision5 =
    vision(PORT7, 50, BLUE_SIG, GREEN_SIG, RED_SIG,
           Vision5__SIG_4, Vision5__SIG_5, Vision5__SIG_6, Vision5__SIG_7);
controller Controller1;
digital_in Takki(Brain.ThreeWirePort.A);

// distance DistanceLeft = distance(PORT12);
// distance DistanceRight = distance(PORT20);
// optical Optical19 = optical(PORT19);
// bumper BumperA = bumper(Brain.ThreeWirePort.A);
// motor ForkMotorGroupMotorA = motor(PORT2, ratio18_1, false);
// motor ForkMotorGroupMotorB = motor(PORT9, ratio18_1, true);
// motor_group ForkMotorGroup = motor_group(ForkMotorGroupMotorA, ForkMotorGroupMotorB);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}