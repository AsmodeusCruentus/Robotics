#include "vex.h"
#include <string>

using namespace vex;


const int CENTER_FOV = 158;  
const int DEAD_X = 40;       

std::string state = "Stoppar"; 

int displayTask() {
  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Staða: %s", state.c_str());
    this_thread::sleep_for(400); 
  }
  return 0;
}

int main() {
  vexcodeInit();

  thread t1 = thread(displayTask);

  while (true) {
    Vision5.takeSnapshot(Vision5__GREENBOX);
    

    if (Vision5.largestObject.exists) {
      int objX     = Vision5.largestObject.centerX;
      int objWidth = Vision5.largestObject.width;

      if (objX > CENTER_FOV + DEAD_X) {
        RightMotor.spin(reverse,10,percent);
        LeftMotor.spin(forward,10,percent);
        task::sleep(10);
        state = "Beygir til hægri";
      } 
      else if (objX < CENTER_FOV - DEAD_X) {
        RightMotor.spin(forward,10,percent);
        LeftMotor.spin(reverse,10,percent);
        task::sleep(10);
        state = "Beygir til vinstri";
      }
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
