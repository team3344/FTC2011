#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     LeftLightSensor,     sensorLightActive)
#pragma config(Sensor, S2,     RightLightSensor,    sensorLightActive)
#pragma config(Sensor, S4,     Sonar,               sensorSONAR)
#pragma config(Motor,  motorA,          Left,          tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          Right,         tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Servo,  srvo_S3_C1_1,    Kicker,               tServoStandard)
#pragma config(Servo,  srvo_S3_C1_2,    Door,                 tServoStandard)
#pragma config(Servo,  srvo_S3_C1_3,    Slide,                tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an TETRIX robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


#define IndicatorLight 3
#define Conveyor 2
#define Magnetic 3

#include "shared/include.c"
#include "Autonomous/include.c"




task main()
{
  RobotFindWhiteLine();
  PlaySound(soundBeepBeep);
  wait10Msec(20);
  RobotFollowWhiteLineToEnd(CurrentLineFollowingContext, true);

  nxtDisplayCenteredTextLine(0, "ctxt");
  nxtDisplayCenteredTextLine(1, (string)CurrentLineFollowingContext.surroundingBrightness);
  nxtDisplayCenteredTextLine(2, (string)CurrentLineFollowingContext.lineBrightness);

  while ( true ) {}
}
