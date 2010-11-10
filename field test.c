#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTSMUX,              sensorNone)
#pragma config(Sensor, S3,     Accelerometer,       sensorI2CHiTechnicAccel)
#pragma config(Sensor, S4,     Sonar,               sensorSONAR)
#pragma config(Motor,  motorA,          Conveyor,      tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          IndicatorLight, tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     Front,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C1_2,     Back,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Left,          tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Right,         tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Kicker,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Door,                 tServoStandard)
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



#include "shared/include.c"
#include "Autonomous/include.c"



task main()
{
	FieldInit();	//  initialize the map of the field
	MechanismInit();

	//long startTime = nPgmTime;



	RobotPosition startPos;
  FieldGetNodeLocation(NodeRedStartSquareLeft, startPos.location);
  startPos.orientation = PI / 2;

  memcpy(currentRobotPosition, startPos, sizeof(RobotPosition));


  //RobotRotateToOrientation(PI);


	RobotTravelFromNodeToNode(NodeRedStartSquareLeft, NodeBlueStartSquareLeft);


	/*
  FieldSetCurrentNode(NodeRedStartSquareLeft);
  FieldSetGoalNode(NodeBlueStartSquareLeft);
  FieldRecalculatePath();





  for ( int i = 0; i < 10; i++ )
  {
    nxtDisplayCenteredTextLine(i, (string)FieldGetCurrentNode());
    FieldAdvance();
    if ( FieldGetNextNode() == NodeZero) break;
  }
  */

  wait10Msec(1000);
}
