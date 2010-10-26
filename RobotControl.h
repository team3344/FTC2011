

#ifndef _RobotControl_
#define _RobotControl_



#ifndef _Vector_
#include "../Advanced/Vector.h"
#endif


typedef struct {
	Vector location;
	float orientation;
} RobotPosition;




void RobotFollowWhiteLine();

void RobotFollowIR();




void RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right
void RobotMove(float distance);	//	distance in inches???.  Can be negative.




//	Position Tracking
void RobotSetCurrentPosition(RobotPosition& pos);
void RobotGetCurrentPosition(RobotPosition& posOut);




void MotorRotateToEncoderValue(int m, int encoderValue, int speed);
void MotorRotateTurns(int m, int turns, int speed);




void RobotGoToNode(NodeID target);

void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude





#endif
