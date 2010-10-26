#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     Test,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define EncoderPointsPerRotation 4 * 360

#include "../Common/include.c"
#include "../Advanced/include.c"


task main()
{
  MotorRotateToEncoderValue(Test, 1440, 20);
  wait10Msec(50);
  MotorRotateTurns(Test, 2, 25);
}