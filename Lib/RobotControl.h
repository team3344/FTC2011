

#ifndef _RobotControl_
#define _RobotControl_



#ifndef _Vector_
#include "Vector.h"
#endif

#ifndef _FTCField_
#include "FTCField.h"
#endif




//	NOTE: robot always follows RIGHT side of line
void RobotFollowWhiteLine();
bool RobotFindWhiteLine(float expectedAngle);	//	returns true if it finds it and is aligned to it


void RobotFollowIR();
bool RobotIRIsVisible();





void RobotRotate(float angle);			//	0 = straight ahead, pi/2 = left, -pi/2 = right
void RobotRotateToAngle(float angle);
void RobotMove(float distance);			//	distance in inches???.  Can be negative.




void RobotLowerBridge();
void RobotMountCenterDispenser();	//	we're right in front of it.  drive up close to it and get in position to dispense






//	Position Tracking
void RobotSetCurrentPosition(RobotPosition& pos);
void RobotGetCurrentPosition(RobotPosition& posOut);



void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude




void RobotBalance();	//	call this when we're on the bridge and the robot will adjust its position until it's balanced





#endif
