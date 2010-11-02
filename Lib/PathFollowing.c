


#ifndef _PathFollowing_
#include "PathFollowing.h"
#endif



PathSegment _currentPathSegment;







void RobotGetCurrentPathSegment(PathSegment& psOut)
{
	memcpy(psOut, _currentPathSegment, sizeof(PathSegment));
}



void RobotTravelPathSegment(PathSegment& ps)
{
	Vector startLocation, endLocation;
	
	
	
	
	
	
	float currentAngle;
	
	KeyPointInfo srcInfo, destInfo;
	
	//	FIXME: collect info on src & dest
	
	
	
	
	
	
	
	
	
	
	
	
}

void RobotInvalidateCurrentPathSegmentForTime(float time)	//	time in seconds
{
	
	
	
	
	
	
	
	
	
	
	
	
	
}

void RobotRetraceMovementToPreviousKeyPoint()
{
	
	
	
	
	
	
	
	
	
	
	
	
	
}

void RobotTravelFromKeyPointToKeyPoint(KeyPointID src, KeyPointID dest)
{
	
	
	
	
	
	
	
	
	
	
	
	
}

