

#ifndef _PathFollowing_
#define _PathFollowing_



#ifndef _FTCField_
#include "FTCField.h"
#endif


#ifndef _RobotControl_
#include "RobotControl.h"
#endif










void RobotGetCurrentPathSegment(PathSegment& psOut);

void RobotTravelFromKeyPointToKeyPoint(KeyPointID src, KeyPointID dest);
void RobotTravelPathSegment(PathSegment& ps);
void RobotInvalidateCurrentPathSegmentForTime(float time);	//	time in seconds
void RobotAbortCurrentTravel();
void RobotRetraceMovementToPreviousKeyPoint();









#endif
