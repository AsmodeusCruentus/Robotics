#include "vex.h"

using namespace vex;

int threshold = 1500; 

int displayStatus() {
    while (true) {
        int leftVal   = LineLeft.value(analogUnits::mV);
        int centerVal = LineCenter.value(analogUnits::mV);
        int rightVal  = LineRight.value(analogUnits::mV);

        bool leftOn   = (leftVal   < threshold);
        bool centerOn = (centerVal < threshold);
        bool rightOn  = (rightVal  < threshold);

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1,1);

        if(centerOn) {
            Brain.Screen.print("Middle");
        }
        else if(leftOn) {
            Brain.Screen.print("Left");
        }
        else if(rightOn) {
            Brain.Screen.print("Right");
        }
        else {
            Brain.Screen.print("Looking for line");
        }
        this_thread::sleep_for(200); 
    }
    return 0;
}



int main() {
    vexcodeInit();
    
    thread t1 = thread(displayStatus);
    
    while (true) {
        if (Controller1.ButtonB.pressing() || Takki.value() == 0) {
            LeftMotor.stop();
            RightMotor.stop();
            //break;   
        }
        int leftVal   = LineLeft.value(analogUnits::mV);
        int centerVal = LineCenter.value(analogUnits::mV);
        int rightVal  = LineRight.value(analogUnits::mV);

        int threshold = 1500; 

        bool leftOnLine   = (leftVal   > threshold);
        bool centerOnLine = (centerVal > threshold);
        bool rightOnLine  = (rightVal  > threshold);

        if(centerOnLine) {
            LeftMotor.spin(forward, 10, pct);
            RightMotor.spin(forward, 10, pct);
        }
        else if(leftOnLine) {
            LeftMotor.spin(forward, 1, pct);
            RightMotor.spin(forward, 5, pct);
        }
        else if(rightOnLine) {
            LeftMotor.spin(forward, 5, pct);
            RightMotor.spin(forward, 1, pct);
        }
        else {
            if(leftOnLine) {
            LeftMotor.spin(forward, 1, pct);
            RightMotor.spin(forward, 5, pct);
            } 
            else if(rightOnLine) {
                LeftMotor.spin(forward, 5, pct);
                RightMotor.spin(forward, 1, pct);
            }
    }}}
