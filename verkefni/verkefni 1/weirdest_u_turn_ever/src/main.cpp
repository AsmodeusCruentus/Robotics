#include "vex.h"
using namespace vex;

int main() {
  vexcodeInit();

  Drivetrain.setDriveVelocity(50, percent);
  Drivetrain.setTurnVelocity(40, percent);
  Drivetrain.setStopping(hold);

  const double L = 500; // each straight = 50 cm

  // 12 relative 90° turns that trace your diagram.
  // R, L, L, R, R, L, R, R, R, L, R, R
  turnType turns[] = {
    right, left, left, right, right, left,
    right, right, right, left, right, right
  };
  int n = sizeof(turns)/sizeof(turns[0]);

  for (int i = 0; i < n; i++) {
    Drivetrain.driveFor(forward, L, mm);
    Drivetrain.turnFor(turns[i], 90, degrees, true);
    wait(100, msec);
  }
  // Final straight to the “End”
  Drivetrain.driveFor(forward, L, mm);
}
