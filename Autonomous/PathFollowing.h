

#ifndef _PathFollowing_
#define _PathFollowing_



#ifndef _Field_
#include "Field.h"
#endif


#ifndef _RobotControl_
#include "RobotControl.h"
#endif



static bool AbortPathFollowing;	//	set this to yes to have the path follower stop at the next iteration

bool RobotTravelFromNodeToNode(Node src, Node dest);
bool RobotTravelPathSegment(PathSegment& segment);



#endif
