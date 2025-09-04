#include "vex.h"
using namespace vex;


int main() {
    vexcodeInit();

    double wheelbase = 30.0;
    double baseOuterSpeed = 40.0; 
    double radius = 50.0; 
    int laps = 3;
    double radiusIncrement = 5.0; 

    for(int lap = 0; lap < laps; lap++) {
        double innerRadius = radius - wheelbase / 2.0;
        double outerRadius = radius + wheelbase / 2.0;

        double innerSpeed = baseOuterSpeed * (innerRadius / outerRadius);

        double circumference = 2.0 * 3.14159 * outerRadius;

        double wheelDiameter = 10.0; // cm
        double wheelCircumference = 3.14159 * wheelDiameter;
        double rotationDegrees = (circumference / wheelCircumference) * 360.0;

        LeftMotor.resetPosition();
        RightMotor.resetPosition();

        while(fabs(LeftMotor.position(rotationUnits::deg)) < rotationDegrees) {
            // --- CHECK FOR BUTTON B ---
            if(Controller1.ButtonB.pressing() || !takki.value()) {
                LeftMotor.stop();
                RightMotor.stop();
                wait(20, msec);
            }

            LeftMotor.spin(directionType::fwd, baseOuterSpeed, velocityUnits::pct);
            RightMotor.spin(directionType::fwd, innerSpeed, velocityUnits::pct);
            wait(20, msec);
        }

        radius += radiusIncrement;
    }
    
    LeftMotor.stop();
    RightMotor.stop();
    wait(1, seconds);
}
