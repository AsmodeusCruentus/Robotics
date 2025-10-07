#include "vex.h"

using namespace vex;

int referenceAngle;

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

int main() {
  GPS8.calibrate();
  while (GPS8.isCalibrating()) { task::sleep(50); }
  GPS8.setOrigin(0, 0, mm);
  Drivetrain.setTurnVelocity(30, percent);
  Drivetrain.setDriveVelocity(80, percent);

  double positions[8][2] = {
    {900, 900},
    {-900, 900},
    {900, 600},
    {-900, 300},
    {900, 0},
    {-900, -300},
    {900,   -600},
    {-900,   -900},

  };

  for (int i = 0; i < 7; i++) {
    double x = positions[i][0];
    double y = positions[i][1];
    driveTo(x, y);
    wait(0.5, seconds);
  }

  Drivetrain.stop();
}
