#include "vex.h"
#include <string>
using namespace vex;

//------------------- Stillingar -------------------
const int IMG_WIDTH     = 316;
const int CENTER_FOV    = IMG_WIDTH / 2;   // 158
const int DEAD_BAND_PX  = 10;

const int DISTANCE_MIN  = 20;  // of lítil -> of langt í burtu
const int DISTANCE_MAX  = 30;  // of stór -> of nálægt
const int TARGET_WIDTH  = (DISTANCE_MIN + DISTANCE_MAX) / 2;

// P/PD stillingar
const double KP_TURN = 0.6;    // % per px fyrir beygju
const double KD_TURN = 0.25;   // D-hluti til að róa
const double KP_FWD  = 1.0;    // % per px fyrir hraða fram/aftur

const int SEARCH_SPEED = 20;   // % þegar hlutur finnst ekki

std::string state = "Stoppar";

// hjálparfall til að klemma í -100..100%
double clampPct(double x) {
  if (x > 100) return 100;
  if (x < -100) return -100;
  return x;
}

// Sýna stöðu á skjá
int displayTask() {
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Staða: %s", state.c_str());
    wait(200, msec);
  }
  return 0;
}

int main() {
  vexcodeInit();

  thread t1 = thread(displayTask);

  double lastErr = 0.0;

  while (true) {
    Vision5.takeSnapshot(Vision5__GREENBOX);

    if (Vision5.largestObject.exists) {
      // --- Mæla frávik/offset ---
      int objX     = Vision5.largestObject.centerX; // 0..316
      int objWidth = Vision5.largestObject.width;

      int errX     = objX - CENTER_FOV;             // <0 vinstri, >0 hægri
      int wErr     = TARGET_WIDTH - objWidth;       // >0 = keyra áfram (of langt)
      double dErr  = errX - lastErr;

      // --- Stjórnun ---
      // beygja út frá láréttu skekkju
      double turnCmd = KP_TURN * errX + KD_TURN * dErr;
      if (std::abs(errX) < DEAD_BAND_PX) turnCmd = 0;

      // hraði fram/aftur út frá stærð (fjarlægð)
      double fwdCmd  = KP_FWD * wErr;

      // blanda í vinstri/hægri mótorprósentur
      double leftPct  = clampPct(fwdCmd - turnCmd);
      double rightPct = clampPct(fwdCmd + turnCmd);

      LeftMotor.setVelocity(leftPct, percent);
      RightMotor.setVelocity(rightPct, percent);
      LeftMotor.spin(forward);
      RightMotor.spin(forward);

      // Stöðustrengur
      if (turnCmd == 0 && std::abs(wErr) <= 2)      state = "Miðjar og í réttri fjarlægð";
      else if (fwdCmd > 0)                          state = "Fer áfram";
      else if (fwdCmd < 0)                          state = "Bakkar";
      else if (turnCmd > 0)                         state = "Beygir til hægri";
      else if (turnCmd < 0)                         state = "Beygir til vinstri";
      else                                          state = "Stillir sig";

      lastErr = errX;

    } else {
      // --- Hlutur týndur: hæg leitarsnúningur ---
      LeftMotor.setVelocity(-SEARCH_SPEED, percent);
      RightMotor.setVelocity( SEARCH_SPEED, percent);
      LeftMotor.spin(forward);
      RightMotor.spin(forward);
      state = "Leitar að kassa";
      lastErr = 0;
    }

    wait(20, msec);
  }
}
