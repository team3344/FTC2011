

#ifndef _RobotControl_
#define _RobotControl_




#include "Vector.h"



typedef struct {
	Vector location;
	float orientation;
} RobotPosition;










void RobotFollowWhiteLine();


void RobotFollowIR();




void RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right

void RobotMove(float distance);	//	distance in inches???.  Can be negative.











#endif
