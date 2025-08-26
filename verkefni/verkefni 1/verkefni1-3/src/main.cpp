/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  This program will turn right 90 degrees using the         */
/*                  Inertial Sensor.                                          */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1               
// RightMotor           motor         10              
// Inertial20           inertial      20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    Inertial20.calibrate();
    while (Inertial20.isCalibrating()) {
        wait(100, msec);
    }

    LeftMotor.setVelocity(10, percent);
    RightMotor.setVelocity(10, percent);

    enum turnType {left, right};

turnType turns[] = {right, left, left, right, right, left, right, right, left, right, left, left, right};

for (auto turn : turns) {
    Drivetrain.driveFor(forward, 500, mm);

    Inertial20.setRotation(0, degrees);

    if (turn == right) {
        LeftMotor.spin(forward, 10, percent);
        RightMotor.spin(reverse, 10, percent);
        waitUntil(Inertial20.rotation(degrees) >= 90.0);
    } else { 
        LeftMotor.spin(reverse, 10, percent);
        RightMotor.spin(forward, 10, percent);
        waitUntil(Inertial20.rotation(degrees) <= -90.0);
    }

    LeftMotor.stop();
    RightMotor.stop();

    wait(1, seconds);
}}
