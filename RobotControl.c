



#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif





#define kLineEdgeLightSensorValue 20	//	FIXME: can this value be calibrated during run????????????????

#define kLineFollowerFastMotorPower 60
#define kLineFollowerSlowMotorPower 0

task RobotFollowWhiteLine()
{
	while ( true )
	{
		if ( SensorValue[FloorLightSensor] )
		{
			motor[RightMotor] = kLineFollowerFastMotorPower;
			motor[LeftMotor] = kLineFollowerSlowMotorPower;
		}
		else
		{
			motor[RightMotor] = kLineFollowerSlowMotorPower;
			motor[LeftMotor] = kLineFollowerFastMotorPower;
		}

		//	FIXME: how do we know we're at the end of the line???????????????????????????????
		if ( true/* we're at the end of the line */ )	//	FIXME: ???
		{
			break;
		}
	}
}




task RobotFollowIR()
{
	//	FIXME: implement
	
	
	
	
	
	
	
	
}






void RobotRotate(float angle)
{
	//printf("rotating angle: %f\n", angle);



}


void RobotMove(float distance)
{

	//printf("moving distance: %f\n", distance);


}






//	motor control
//==========================================================================


//	motor control by power
void MotorRotateEncoderPointsAtPower(int m, int encoderValue, int power)
{
  int p = (encoderValue > nMotorEncoder[m]) ? power : -power;
  motor[m] = p;

  if ( p > 0 )
    while ( nMotorEncoder[m] < encoderValue ) {}
  else
    while ( nMotorEncoder[m] > encoderValue ) {}

   motor[m] = 0;  //  stop
}

void MotorRotateTurnsAtPower(int m, int turns, int power)
{
	int encoderValue = kMotorEncoderPointsPerRotation * turns;
	MotorRotateToEncoderValue(m, encoderValue, power);
}



typedef struct {
	float speed;
	int encoderValueStart;
	int encoderValueTarget;
	int m;
} MotorMotionInfo;

typedef struct {
	int timer;
	MotorMotionInfo motors[kRobotMotorCount];
} RobotMotionInfo;




void UpdateMotorPower()
{
	for ( int i = 0; i < kRobotMotorCount; i++ )
	{
		
	}
}





//	motor control by speed
void MotorRotateEncoderPointsAtSpeed(int m, int encoderPoints, float speed)
{
	int start = nMotorEncoder[m];
	
	int target = start + encoderPoints;
	
	float dist = (encoderPoints / kMotorEncoderPointsPerRotation) * 2 * PI;	//	number of radians to rotate for
	
	int time = dist / speed;	//	time in seconds
	
	
	time1[MotorTimer] = //	time in 1000ths of a second since the timer started
	ClearTimer(MotorTimer);
	//	time1 only works for 30 seconds
	//	time10 works for 5 min and gives time in 100ths of a second
	
	
}

void MotorRotateTurnsAtSpeed(int m, float turns, int speed)
{
	
}









//	Node Traveling
//===================================================================================================================


void _RobotGoFromCurrentNodeToNode(Node& current, Node& target)
{
	Vector displacement;
	VectorSubtract(&target.location, &current.location, &displacement);
	
	//printf("\ncurrentLocation = ");
	//PrintVector(current.location);
	
	//printf("\ntarget.location = ");
	//PrintVector(target.location);
	
	//printf("\nrobot move w/vector: ");
	//PrintVector(displacement);
	//printf("\n");
	
	
	RobotMoveWithVector(&displacement);	//	FIXME: only do this for things without landmarks or beacons???
	
	//	FIXME: look for landmarks???
	//	FIXME: if we hit a landmark, tell tracker we have an absolute position
	
	
	
	
	
}


void RobotGoToNode(NodeID target)
{
	MapSetGoalNodeID(target);
	
	Node previous;
	MapGetNode(MapGetCurrentNodeID(), &previous);	//	start position
	
	while ( true )
	{
		NodeID node = MapAdvance();			//	get the id of the next node along the path
		if ( node == NodeIDZero ) break;	//	if we're at the end of the path, we're done!
		
		Node segmentTarget;
		MapGetNode(node, &segmentTarget);	//	this is where we're heading
		
		_RobotGoFromCurrentNodeToNode(&previous, &segmentTarget);	//	go to the target
		
		previous = segmentTarget;	//	the node we're now heading to will be the previous node in the next iteration
	}
}







//	FIXME: below method is trash and may have been redone in OmniDrive.c

void RobotMoveWithVector(Vector& displacement)
{
	RobotPosition currentPosition;
	TrackerGetCurrentPosition(&currentPosition);
	
	//printf("currentPosition.orientation = %f\n", currentPosition.orientation);
	
	//printf("displacement angle = %f\n", VectorGetAngle(displacement));
	
	RobotRotate(VectorGetAngle(&displacement) - currentPosition.orientation);	//	turn towards the destination
	RobotMove(VectorGetMagnitude(&displacement));								//	move the required distance to the destination
	
	
	
	
	//FIXME: remove below line
	
	RobotPosition future;
	VectorAdd(&currentPosition.location, &displacement, &future.location);
	future.orientation = VectorGetAngle(&displacement);
	TrackerSetCurrentPosition(&future);
	//	FIXME: trash above
	
}


