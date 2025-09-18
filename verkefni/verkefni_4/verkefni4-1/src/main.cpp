#include "vex.h"

using namespace vex;

int main() {
    vexcodeInit();

    while (true) {
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
