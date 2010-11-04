



#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Defines_
#include "Defines.h"
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


#define kLineEdgeLightSensorValue 20	//	FIXME: can this value be calibrated during run????????????????

#define kLineFollowerFastMotorPower 60
#define kLineFollowerSlowMotorPower 0

task RobotFollowWhiteLine()
{
	while ( true )
	{


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



void RobotMoveWithVector(Vector& displacement)
{
	RobotPosition currentPosition;
	//TrackerGetCurrentPosition(&currentPosition);
	
	//printf("currentPosition.orientation = %f\n", currentPosition.orientation);
	
	//printf("displacement angle = %f\n", VectorGetAngle(displacement));
	
	RobotRotate(VectorGetAngle(&displacement) - currentPosition.orientation);	//	turn towards the destination
	RobotMove(VectorGetMagnitude(&displacement));								//	move the required distance to the destination
	
	
	
	
	//FIXME: remove below line
	
	RobotPosition future;
	VectorAdd(&currentPosition.location, &displacement, &future.location);
	future.orientation = VectorGetAngle(&displacement);
	//	TrackerSetCurrentPosition(&future);
	//	FIXME: trash above
	
}





