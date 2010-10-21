

#ifndef _Tracker_
#define _Tracker_

#ifndef _Defines_
#include "../Defines.h"
#endif


#ifndef _Vector_
#include "Vector.h"
#endif

#ifndef _RobotControl_
#include "../Common/RobotControl.h"
#endif





typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;



void TrackerGetCurrentPosition(RobotPosition& positionOut);
void TrackerSetCurrentPosition(RobotPosition& position);



#endif
