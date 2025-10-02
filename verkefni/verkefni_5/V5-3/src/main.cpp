#include "vex.h"

using namespace vex;

int referenceAngle;

void pickupCube() {
  ArmMotor.spinToPosition(-70, degrees, false); 
  wait(1, seconds);

  ClawMotor.spinToPosition(180, degrees, false);
  wait(1, seconds);

  ArmMotor.spinToPosition(70, degrees, false);
  wait(1, seconds);
}

void dropoffCube() {
  // Drivetrain.turnToHeading(90, degrees);

  ArmMotor.spinToPosition(-70, degrees, false);
  wait(1, seconds);

  ClawMotor.spinToPosition(-180, degrees, false);
  wait(1, seconds);
}

void driveToPositionX(double x) {
  if (GPS8.xPosition(mm) < x) { referenceAngle = 90; }
  else { referenceAngle = 270; }

  Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()), degrees, true);
  Drivetrain.drive(forward);
  while (fabs(GPS8.xPosition(mm) - x) > 20) {
    wait(0.1, seconds);
  }
  Drivetrain.stop();
}

void driveToPositionY(double y) {
  if (GPS8.yPosition(mm) < y) { referenceAngle = 0; }
  else { referenceAngle = 180; }

  Drivetrain.turnFor(right, (referenceAngle - GPS8.heading()), degrees, true);
  Drivetrain.drive(forward);
  while (fabs(GPS8.yPosition(mm) - y) > 20) {
    wait(0.1, seconds);
  }
  Drivetrain.stop();
}

void driveTo(double x, double y) {
  driveToPositionX(x);
  driveToPositionY(y);
}
void driveToD(double x) {
  driveToPositionX(x);
}

color detectCubeColor() {
  Vision5.takeSnapshot(RED_SIG);
  if (Vision5.objectCount > 0) return color::red;

  Vision5.takeSnapshot(BLUE_SIG);
  if (Vision5.objectCount > 0) return color::blue;

  Vision5.takeSnapshot(GREEN_SIG);
  if (Vision5.objectCount > 0) return color::green;

  return color::transparent;
}

void handleCubeAt(double x, double y) {
  driveTo(x, y);

  pickupCube();  

  color c = detectCubeColor();

  if (c == color::red) {
    driveTo(600, 0);
    driveToD(400);
    dropoffCube();
  } else if (c == color::blue) {
    driveTo(650, -500);
    driveToD(400);
    dropoffCube();
  } else if (c == color::green) {
    driveTo(600, -1000);
    driveToD(400);
    dropoffCube();
  } else {
    Drivetrain.stop();
  }
}

int main() {
  GPS8.calibrate();
  while (GPS8.isCalibrating()) { task::sleep(50); }
  GPS8.setOrigin(0, 0, mm);
  Drivetrain.setTurnVelocity(30, percent);

  handleCubeAt(-1400, 1350);
  driveTo(600, 600);
  handleCubeAt(0, 1350);
  handleCubeAt(1400, 1350);

  Drivetrain.stop();
  
}
