
#ifndef _Tracker_
#include "Tracker.h"
#endif


static RobotPosition currentRobotPosition;


void TrackerGetCurrentPosition(RobotPosition& positionOut)
{
	memcpy(positionOut, currentRobotPosition, sizeof(RobotPosition));
}


void TrackerSetCurrentPosition(RobotPosition& position)
{
  memcpy(currentRobotPosition, position, sizeof(RobotPosition));
}


/*

This was for a non-omni robot

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
		float dx = posChange.displacement.x;
		posChange.angleChange = atan( -dx / sqrt(powf(robotRadius, 2.0) - powf(dx, 2.0)) );
	}
}


*/