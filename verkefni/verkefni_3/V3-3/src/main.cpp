#include "vex.h"
#include <string>

using namespace vex;

// Skilgreiningar
const int CENTER_FOV = 158;  
const int OFFSET_X = 25;      
const int DISTANCE_MAX = 30; 
const int DISTANCE_MIN = 20; 

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

    if (Vision5.largestObject.exists) {
      //int objX = Vision5.largestObject.centerX;
      int objWidth = Vision5.largestObject.width;

      // Einföld nálgun: stærra width => nær
      if (objWidth > DISTANCE_MAX) {
        LeftMotor.spin(reverse);
        RightMotor.spin(reverse);
        state = "Bakkar (hlutur of nálægt)";
      }
      else if (objWidth > DISTANCE_MIN && objWidth < DISTANCE_MAX){
        LeftMotor.stop(brakeType::brake);
        RightMotor.stop(brakeType::brake);
        state = "Stoppar - enginn hlutur";
      }
      /*else if (objX > CENTER_FOV + OFFSET_X) {
        LeftMotor.spin(forward);
        RightMotor.spin(reverse);
        task::sleep(10);
        state = "Beygir til hægri";
      }
      else if (objX < CENTER_FOV - OFFSET_X) {
        LeftMotor.spin(reverse);
        RightMotor.spin(forward);
        task::sleep(10);
        state = "Beygir til vinstri";
      }*/
      else if (objWidth > DISTANCE_MAX) {
       
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        
        state = "Fer áfram";
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
