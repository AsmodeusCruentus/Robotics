#include "vex.h"
#include <string>

using namespace vex;

// Skilgreiningar
const int CENTER_FOV = 158;  
const int DEAD_X = 30;       // lítill dauðsvæði fyrir beygju

std::string state = "Stoppar"; 

// Thread sem sér um skjáinn
int displayTask() {
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Staða: %s", state.c_str());
    this_thread::sleep_for(200); 
  }
  return 0;
}

int main() {
  vexcodeInit();

  thread t1 = thread(displayTask);

  while (true) {
    Vision5.takeSnapshot(Vision5__GREENBOX);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(Vision5.largestObject.centerX);

    if (Vision5.largestObject.exists) {
      int objX     = Vision5.largestObject.centerX;
      int objWidth = Vision5.largestObject.width;

      // --- 1) Fyrst: stilla sjón (beygja að kassanum) ---
      if (objX > CENTER_FOV + DEAD_X) {
        // kassinn er til hægri -> beygja til hægri
        RightMotor.spin(reverse);
        LeftMotor.spin(forward);
        task::sleep(10);
        state = "Beygir til hægri";
      } 
      else if (objX < CENTER_FOV - DEAD_X) {
        // kassinn er til vinstri -> beygja til vinstri
        RightMotor.spin(forward);
        LeftMotor.spin(reverse);
        task::sleep(10);
        state = "Beygir til vinstri";
      }
      // --- 2) Svo: fjarlægð (fram/bak) þegar miðjuð ---
      else if (objWidth > 150) {
        LeftMotor.spin(reverse);
        RightMotor.spin(reverse);
        state = "Bakkar (hlutur of nálægt)";
      } 
      else if (objWidth < 100) {
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        state = "Fer áfram (hlutur of langt)";
      } 
      else {
        LeftMotor.stop(brakeType::brake);
        RightMotor.stop(brakeType::brake);
        state = "Miðjað og í lagi";
      }
    }
    else {
      LeftMotor.stop(brakeType::brake);
      RightMotor.stop(brakeType::brake);
      state = "Stoppar - enginn hlutur";
    }

    wait(50, msec);
  }
}
