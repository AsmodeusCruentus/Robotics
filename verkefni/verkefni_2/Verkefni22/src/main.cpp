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
    vexcodeInit();

    Inertial20.calibrate();
    while (Inertial20.isCalibrating()) {
        wait(100, msec);
    }

    LeftMotor.setVelocity(10, percent);
    RightMotor.setVelocity(10, percent);

    enum turnType {left, right};

turnType turns[] = {right, left, left, right, right, left, right, right, left, right, right, left, left, right};

for (auto turn : turns) {
    double Distance = 500;
    Drivetrain.setDriveVelocity(15, percent); 
    Drivetrain.drive(forward);

    double start = (LeftMotor.position(rotationUnits::deg) + RightMotor.position(rotationUnits::deg)) / 2.0;
    while (((LeftMotor.position(rotationUnits::deg) + RightMotor.position(rotationUnits::deg)) / 2.0 - start) < Distance) {
        if (Controller1.ButtonB.pressing()) {
            Drivetrain.stop();
            while (Controller1.ButtonB.pressing()) {
                wait(20, msec);
            }
            Drivetrain.drive(forward); 
        }
        wait(20, msec);
    }
    Drivetrain.stop();

    Inertial20.setRotation(0, degrees);

    if (turn == right) {
        LeftMotor.spin(forward, 10, percent);
        RightMotor.spin(reverse, 10, percent);
        while (Inertial20.rotation(degrees) < 90.0) {
            if (Controller1.ButtonB.pressing()) {
                LeftMotor.stop();
                RightMotor.stop();
                while (Controller1.ButtonB.pressing()) {
                    wait(20, msec);
                }
                LeftMotor.spin(forward, 10, percent);
                RightMotor.spin(reverse, 10, percent);
            }
            wait(20, msec);
        }
    } else { 
        LeftMotor.spin(reverse, 10, percent);
        RightMotor.spin(forward, 10, percent);
        while (Inertial20.rotation(degrees) > -90.0) {
            if (Controller1.ButtonB.pressing()) {
                LeftMotor.stop();
                RightMotor.stop();
                while (Controller1.ButtonB.pressing()) {
                    wait(20, msec);
                }
                LeftMotor.spin(reverse, 10, percent);
                RightMotor.spin(forward, 10, percent);
            }
            wait(20, msec);
        }
    }

    LeftMotor.stop();
    RightMotor.stop();

    wait(1, seconds);
}}
