

#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Defines_
#include "../shared/Defines.h"
#endif




//	Line Following
//===========================================================================================================

#define kLineFollowerMotorPower 30

bool RobotFollowWhiteLineForDistance(LineFollowingContext& ctxt, float distance, bool avoidEnemies)
{
	return true;
}

bool RobotFollowWhiteLineToEnd(LineFollowingContext& ctxt, bool avoidEnemies)
{
	return true;
}





task _RobotScanWhiteLine()
{
  //  look at brightnesses and save them in CurrentLineFollowingContext
}



#define kRobotScanAngle PI / 4

bool RobotFindWhiteLine()	//	returns true if it finds it
{
  StartTask(_RobotScanWhiteLine); //  start scanning

  float orientation = CurrentRobotPosition.orientation;
  RobotRotateToOrientation(orientation + kRobotScanAngle);
  RobotRotateToOrientation(orientation - kRobotScanAngle);

  StopTask(_RobotScanWhiteLine);  //  stop scanning


  //  FIXME: align with the line now!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	return true;  //  FIXME: only return true if it finds it!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}







#define kRobotMoveSpeed 20	//	FIXME: change this
#define kRobotRotateSpeed kRobotMoveSpeed


void RobotRotateToOrientation(float orientation)
{
	float currentOrientation = CurrentRobotPosition.orientation;
	float angle = orientation - currentOrientation;

	//	reduce angle
	if ( abs(angle) > 2 * PI )
	{
		if ( angle < 0 ) angle += 2 * PI;
		else angle -= 2 * PI;
	}

	float wheelDistance = angle * (kRobotWidth / 2);


	//	start rotating
	motor[Left] = ( wheelDistance > 0 ) ? -kRobotRotateSpeed : kRobotRotateSpeed;
	motor[Right] = -motor[Left];

	int encoderPoints = TetrixConvertDistanceToEncoder(wheelDistance);
	nMotorEncoder[Left] = 0;

	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done

	//	stop
	motor[Left] = 0;
	motor[Right] = 0;


	CurrentRobotPosition.orientation = orientation;
}



bool RobotMoveDistance(float distance)
{
  nMotorEncoder[Left] = 0;
  nMotorEncoder[Right] = 0;

	int encoderPoints = TetrixConvertDistanceToEncoder(distance);


	//nxtDisplayCenteredTextLine(3, (string)encoderPoints);


	motor[Left] = ( distance > 0 ) ? kRobotMoveSpeed : -kRobotMoveSpeed;
	motor[Right] = motor[Left];

	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done


	//  stop
	motor[Left] = 0;
	motor[Right] = 0;


	return true;	//	FIXME: this value should mean something	///////////////////////////////////////////////////////////////////////////////////////////////////////
}


void RobotApproachBridge()
{
  //  FIXME: implement
}

void RobotLowerBridge()
{
  //  FIXME: implement
}

void RobotMountCenterDispenser()
{
  //  FIXME: implement
}

void RobotBalance()
{
  //  FIXME: implement
}
