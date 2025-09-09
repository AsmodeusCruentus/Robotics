#include "vex.h"

using namespace vex;

const double wheelDiameter = 100.0;
const double wheelCircumference = wheelDiameter * M_PI; 

double rotationsToMeters(double rotations) {
    return (rotations * wheelCircumference) / 1000.0;
}

double getDistanceMeters() {
    double leftRot = LeftMotor.position(rev);
    double rightRot = RightMotor.position(rev);
    return (rotationsToMeters(leftRot) + rotationsToMeters(rightRot)) / 2.0;
}

int trackingTask() {
    LeftMotor.resetPosition();
    RightMotor.resetPosition();
    timer t;
    t.clear();

    while (true) {
        double timeSec = t.time(sec); 
        double dist = getDistanceMeters();
        double avgSpeed = (timeSec > 0) ? dist / timeSec : 0.0;

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print("Distance: %.2f m", dist);
        Brain.Screen.newLine();
        Brain.Screen.print("Avg speed: %.2f m/s", avgSpeed);

        this_thread::sleep_for(200);
    }
    return 0;
}

void driveAvoidObstacles() {
    while (Light.brightness() >= 70) {
        int dist = DistSensor.objectDistance(mm);
        if (dist > 0 && dist < 400) { 
            LeftMotor.stop();
            RightMotor.stop();
            task::sleep(300);

            LeftMotor.spin(reverse, 25, percent);
            RightMotor.spin(forward, 25, percent);
            task::sleep(700);

            LeftMotor.stop();
            RightMotor.stop();
        } else {
            LeftMotor.spin(forward, 25, percent);
            RightMotor.spin(forward, 25, percent);
        }

        task::sleep(20);
    }

    LeftMotor.stop();
    RightMotor.stop();
}

int main() {
    while (true){

    driveAvoidObstacles();
    task tracker(trackingTask);

}}
