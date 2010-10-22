

#ifndef _AdvancedRobotControl_
#define _AdvancedRobotControl_


#ifndef _RobotControl_
#include "../Common/RobotControl.h"
#endif

#ifndef _Tracker_
#include "Tracker.h"
#endif

#ifndef _Map_
#include "Map.h"
#endif


void RobotGoToNode(NodeID target);


void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude




#endif
