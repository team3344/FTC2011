

#ifndef _Tracker_
#define _Tracker_

#include "Constants.h"
#include "Vector.h"
#include "../Common/RobotControl.h"






typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;




task TrackAllMotion();	//	FIXME: is this a necessary function???



PositionChange TrackerCalculateChange(int dl, int dr);




RobotPosition TrackerGetCurrentPosition();
void TrackerSetCurrentPosition(RobotPosition position);



#endif
