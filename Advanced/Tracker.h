

#ifndef _Tracker_
#define _Tracker_

#include "../Defines.h"
#include "Vector.h"
#include "../Common/RobotControl.h"






typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;




task TrackAllMotion();	//	FIXME: is this a necessary function???



void TrackerCalculateChange(int dl, int dr, PositionChange& posChange);




void TrackerGetCurrentPosition(RobotPosition& positionOut);
void TrackerSetCurrentPosition(RobotPosition& position);



#endif
