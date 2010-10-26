



#ifndef _RobotControl_
#include "RobotControl.h"
#endif

#ifndef _Sensors_
#include "Sensors.h"
#endif


#ifndef _Defines_
#include "../Defines.h"
#endif





#define kLineEdgeLightSensorValue 20	//	FIXME: can this value be calibrated during run????????????????

#define kLineFollowerFastMotorSpeed 60
#define kLineFollowerSlowMotorSpeed 0

task RobotFollowWhiteLine()
{
	while ( true )
	{
		if ( SensorValue[FloorLightSensor] )
		{
			motor[RightMotor] = kLineFollowerFastMotorSpeed;
			motor[LeftMotor] = kLineFollowerSlowMotorSpeed;
		}
		else
		{
			motor[RightMotor] = kLineFollowerSlowMotorSpeed;
			motor[LeftMotor] = kLineFollowerFastMotorSpeed;
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







//==========================================================================

void MotorRotateToEncoderValue(int m, int encoderValue, int speed)
{
  int s = (encoderValue > nMotorEncoder[m]) ? speed : -speed;
  motor[m] = s;

  if ( s > 0 )
    while ( nMotorEncoder[m] < encoderValue ) {}
  else
    while ( nMotorEncoder[m] > encoderValue ) {}

   motor[m] = 0;  //  stop
}

void MotorRotateTurns(int m, int turns, int speed)
{
    int encoderValue = kMotorEncoderPointsPerRotation * turns;
   MotorRotateToEncoderValue(m, encoderValue, speed);
}




















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


