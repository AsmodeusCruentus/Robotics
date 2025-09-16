#include "vex.h"
#include <string>

using namespace vex;

// Skilgreiningar
const int CENTER_FOV = 158;  
// const int OFFSET_X = 25;     

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
      int objX = Vision5.largestObject.centerX;
      int objWidth = Vision5.largestObject.width;
      
      if(objWidth > 150){
        LeftMotor.spin(reverse);
        RightMotor.spin(reverse);}
      
      else if (objWidth < 100) {
        LeftMotor.spin(forward);
        RightMotor.spin(forward);
        state = "Bakkar (hlutur of nálægt)";
      } 
     
      
      else if(Vision5.largestObject.centerX > CENTER_FOV + 30 && objWidth < 100){
        RightMotor.spin(reverse);
        LeftMotor.spin(forward);
        task::sleep(10);
      }
      else if (Vision5.largestObject.centerX < CENTER_FOV - 30 && objWidth < 100) {
        RightMotor.spin(forward);
        LeftMotor.spin(reverse);
      }
      
      else{
        LeftMotor.stop(brakeType::brake);
        RightMotor.stop(brakeType::brake);}
    }
    else {
      LeftMotor.stop(brakeType::brake);
      RightMotor.stop(brakeType::brake);
      state = "Stoppar - enginn hlutur";
    }

    wait(50, msec);
  }
}
