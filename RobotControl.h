

#ifndef _RobotControl_
#define _RobotControl_



#ifndef _Vector_
#include "Vector.h"
#endif


typedef struct {
	Vector location;
	float orientation;
} RobotPosition;




void RobotFollowWhiteLine();

void RobotFollowIR();
void RobotIRVisible();




void RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right
void RobotMove(float distance);	//	distance in inches???.  Can be negative.




//	Position Tracking
void RobotSetCurrentPosition(RobotPosition& pos);
void RobotGetCurrentPosition(RobotPosition& posOut);




void MotorRotateToEncoderValueAtPower(int m, int encoderValue, int power);
void MotorRotateTurnsAtPower(int m, int turns, int power);




void RobotGoToNode(NodeID target);

void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude





#endif
