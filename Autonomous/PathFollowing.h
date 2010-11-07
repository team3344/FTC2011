

#ifndef _PathFollowing_
#define _PathFollowing_



#ifndef _Field_
#include "Field.h"
#endif


#ifndef _RobotControl_
#include "RobotControl.h"
#endif



void AbortPathFollowing();

bool RobotTravelFromKeyPointToKeyPoint(Node src, Node dest);
bool RobotTravelPathSegment(PathSegment& segment);




#endif
