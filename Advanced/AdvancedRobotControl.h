

#ifndef _AdvancedRobotControl_
#define _AdvancedRobotControl_

#include "../Common/RobotControl.h"
#include "Tracker.h"
#include "Map.h"



void RobotGoToNode(NodeID target);


void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude




#endif
