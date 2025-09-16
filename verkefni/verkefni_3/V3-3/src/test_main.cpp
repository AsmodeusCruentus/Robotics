#include "vex.h"
using namespace vex;

const int CENTER = 158;      // 0..316
const int DEAD   = 8;        // deadband px
const double K   = 0.45;     // turn strength
const int SEARCH_SPEED = 18; // %

// Distance targets (tune to your setup)
const int TOO_CLOSE_MM = 250;  // back up if nearer than this
const int TOO_FAR_MM   = 550;  // drive forward if farther than this

// Pick the biggest visible target across GREEN/BLUE/RED
bool getTarget(vision::object &out) {
  int bestArea = 0;
  vision::object best;

  Vision5.takeSnapshot(Vision5__GREENBOX);
  if (Vision5.largestObject.exists) {
    int a = Vision5.largestObject.width * Vision5.largestObject.height;
    if (a > bestArea) { bestArea = a; best = Vision5.largestObject; }
  }

  Vision5.takeSnapshot(Vision5__BLUEBOX);
  if (Vision5.largestObject.exists) {
    int a = Vision5.largestObject.width * Vision5.largestObject.height;
    if (a > bestArea) { bestArea = a; best = Vision5.largestObject; }
  }

  Vision5.takeSnapshot(Vision5__REDBOX);
  if (Vision5.largestObject.exists) {
    int a = Vision5.largestObject.width * Vision5.largestObject.height;
    if (a > bestArea) { bestArea = a; best = Vision5.largestObject; }
  }

  // ignore tiny noise blobs
  if (bestArea >= 200) { out = best; return true; }
  return false;
}

int main() {
  vexcodeInit();

  // stabilize vision: turn on your 3-wire light; optional tweak brightness
  Light.on();
  // Vision5.setBrightness(45);   // optional: uncomment if needed

  while (true) {
    vision::object obj;
    bool seen = getTarget(obj);

    if (seen) {
      int x   = obj.centerX;
      int err = x - CENTER;

      // TURN: tiny P with deadband
      double turn = (std::abs(err) > DEAD) ? K * err : 0;

      // FWD/BACK: prefer distance sensor
      double fwd = 0;
      int dmm = DistSensor.objectDistance(mm);  // returns -1 if nothing
      if (dmm > 0) {
        if (dmm > TOO_FAR_MM)      fwd = 25;   // go forward
        else if (dmm < TOO_CLOSE_MM) fwd = -25; // back up
      } else {
        // fallback if distance has no reading: use vision width
        if (obj.width > 140)       fwd = -20;
        else if (obj.width < 80)   fwd = 20;
      }

      // mix and clamp
      double L = std::max(-60.0, std::min(60.0, fwd - turn));
      double R = std::max(-60.0, std::min(60.0, fwd + turn));

      LeftMotor.setVelocity(L, percent);
      RightMotor.setVelocity(R, percent);
      LeftMotor.spin(forward);
      RightMotor.spin(forward);

      // tiny debug
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("x:%d w:%d d:%d L:%d R:%d",
        x, obj.width, dmm, (int)L, (int)R);

    } else {
      // search gently if nothing seen
      LeftMotor.setVelocity(-SEARCH_SPEED, percent);
      RightMotor.setVelocity( SEARCH_SPEED, percent);
      LeftMotor.spin(forward);
      RightMotor.spin(forward);

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Searching...");
    }

    wait(20, msec);
  }
}
