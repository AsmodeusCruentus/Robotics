using namespace vex;
using signature = vision::signature;

extern brain Brain;
extern smartdrive Drivetrain;
extern motor_group ForkMotorGroup;
extern rotation Rotation4;
extern gps GPS8;
extern distance DistanceLeft;
extern distance DistanceRight;
extern optical Optical19;
extern bumper BumperA;
extern signature BLUE_SIG;
extern signature GREEN_SIG;
extern signature RED_SIG;
extern signature Vision5__SIG_4;
extern signature Vision5__SIG_5;
extern signature Vision5__SIG_6;
extern signature Vision5__SIG_7;
extern vision Vision5;
extern motor ClawMotor;
extern motor ArmMotor;
extern controller Controller1;
extern digital_in Takki;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );