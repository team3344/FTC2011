
#include "Tracker.h"



static int previousRightEncoder;
static int previousLeftEncoder;

static RobotPosition currentRobotPosition;


RobotPosition TrackerGetCurrentPosition(RobotPosition& positionOut)
{
	//	FIXME: implement
	
	
	return currentRobotPosition;
}


void TrackerSetCurrentPosition(RobotPosition position)
{
	currentRobotPosition = position;
}



void TrackerCalculateChange(int dl, int dr, PositionChange& posChange)
{
	if ( dl * dr < 0 )	//	one of the values is negative
	{
		
	}
	else	//	both wheels are moving in the same direction
	{
		//	FIXME: branch if dl > dr, dr > dl?????????????
		
		float leftRadius = (dl * kRobotWidth) / (dr - dl);	//	radius from rotation point to center of left wheel
		float arcAngle = dl / leftRadius;
		float robotRadius = leftRadius + (kRobotWidth / 2);
		
		posChange.displacement.x = robotRadius * cos(arcAngle);
		posChange.displacement.y = robotRadius * sin(arcAngle);
		float dx = delta.displacement.x;
		posChange.angleChange = atanf( -dx / sqrt(powf(robotRadius, 2.0) - powf(dx, 2.0)) );
	}
	
	
	return delta;
}


