

#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Defines_
#include "../shared/Defines.h"
#endif


//	Position Tracking
//===========================================================================================================
static RobotPosition _currentRobotPosition;

void RobotSetCurrentPosition(RobotPosition& pos)
{
	memcpy(_currentRobotPosition, pos, sizeof(RobotPosition));
}

void RobotGetCurrentPosition(RobotPosition& posOut)
{
	memcpy(posOut, _currentRobotPosition, sizeof(RobotPosition));
}












//	Line Following
//===========================================================================================================

#define kLineFollowerMotorPower 30

bool RobotFollowWhiteLineForDistance(LineFollowingContext& ctxt, float distance)
{
	return true;
}

bool RobotFollowWhiteLineToEnd(LineFollowingContext& ctxt)
{
	return true;
}

bool RobotFindWhiteLine(LineFollowingContext& ctxtOut)	//	returns true if it finds it and gives the context
{
	return true;
}















#define kRobotMoveSpeed 20	//	FIXME: change this
#define kRobotRotateSpeed kRobotMoveSpeed


void RobotRotateToOrientation(float orientation)
{
	float currentOrientation = _currentRobotPosition.orientation;
	float angle = orientation - currentOrientation;
	
	//	reduce angle
	if ( abs(angle) > 2 * PI )
	{
		if ( angle < 0 ) angle += 2 * PI;
		else angle -= 2 * PI;
	}
	
	float wheelDistance = angle * (kRobotWidth / 2);
	
	//	start rotating
	motor[Left] = ( wheelDistance > 0 ) ? kRobotRotateSpeed : -kRobotRotateSpeed;
	motor[Right] = -motor[Left];
	
	int encoderPoints = TetrixConvertDistanceToEncoder(wheelDistance);
	nMotorEncoder[Left] = 0;
	
	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done
	
	//	stop
	motor[Left] = 0;
	motor[Right] = 0;
}



bool RobotMoveDistance(float distance)
{
	int encoderPoints = TetrixConvertDistanceToEncoder(distance);
	
	motor[Left] = ( distance > 0 ) ? kRobotMoveSpeed : -kRobotMoveSpeed;
	motor[Right] = motor[Left];
	
	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done
	
	
	return true;	//	FIXME: this value should mean asometihgn	///////////////////////////////////////////////////////////////////////////////////////////////////////
}


/*
bool RobotMoveWithVector(Vector& displacement)
{
	RobotPosition currentPosition;
	//TrackerGetCurrentPosition(&currentPosition);

	//printf("currentPosition.orientation = %f\n", currentPosition.orientation);

	//printf("displacement angle = %f\n", VectorGetAngle(displacement));

	RobotRotateAngle(VectorGetAngle(&displacement) - currentPosition.orientation);	//	turn towards the destination
	bool success = RobotMoveDistance(VectorGetMagnitude(&displacement));								//	move the required distance to the destination




	//FIXME: remove below line

	RobotPosition future;
	VectorAdd(&currentPosition.location, &displacement, &future.location);
	future.orientation = VectorGetAngle(&displacement);
	//	TrackerSetCurrentPosition(&future);
	//	FIXME: trash above

	return success;
}
*/

void RobotApproachBridge()
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
















