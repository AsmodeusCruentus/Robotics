#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

brain  Brain;
motor LeftMotor(PORT1, ratio18_1, false);
motor RightMotor(PORT3, ratio18_1, true);
line LineLeft(Brain.ThreeWirePort.E);
line LineCenter(Brain.ThreeWirePort.F);
line LineRight(Brain.ThreeWirePort.G);
controller Controller1;
digital_in Takki(Brain.ThreeWirePort.A);

void vexcodeInit(void) {
}