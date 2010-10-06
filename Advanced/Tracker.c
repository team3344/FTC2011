
#import "Tracker.h"



static int previousRightEncoder;
static int previousLeftEncoder;

static RobotPosition currentRobotPosition;


RobotPosition TrackerGetCurrentPosition()
{
	return currentRobotPosition;
}


void TrackerSetCurrentPosition(RobotPosition position)
{
	currentRobotPosition = position;
}



PositionChange TrackerCalculateChange(int dl, int dr)
{
	PositionChange delta;
	
	if ( dl * dr < 0 )	//	one of the values is negative
	{
		
	}
	else	//	both wheels are moving in the same direction
	{
		//	FIXME: branch if dl > dr, dr > dl?????????????
		
		float leftRadius = (dl * kRobotWidth) / (dr - dl);	//	radius from rotation point to center of left wheel
		float arcAngle = dl / leftRadius;
		float robotRadius = leftRadius + (kRobotWidth / 2);
		
		delta.displacement.x = robotRadius * cos(arcAngle);
		delta.displacement.y = robotRadius * sin(arcAngle);
		float dx = delta.displacement.x;
		delta.angleChange = atanf( -dx / sqrt(powf(robotRadius, 2.0) - powf(dx, 2.0)) );
	}
	
	
	return delta;
}


