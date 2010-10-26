

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
bool RobotFindWhiteLine(float expectedAngle);	//	returns true if it finds it and is aligned to it

void RobotFollowIR();
bool RobotIRIsVisible();




void RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right
void RobotMove(float distance);	//	distance in inches???.  Can be negative.




//	Position Tracking
void RobotSetCurrentPosition(RobotPosition& pos);
void RobotGetCurrentPosition(RobotPosition& posOut);



//	motor control by power
void MotorRotateToEncoderValueAtPower(int m, int encoderValue, int power);
void MotorRotateTurnsAtPower(int m, float turns, int power);

//	motor control by speed
//	NOTE: speed is in radians/sec
void MotorRotateEncoderPointsAtSpeed(int m, int encoderPoints, int speed);
void MotorRotateTurnsAtSpeed(int m, float turns, int speed);




void RobotGoToKeyPoint(KeyPointID target);

void RobotMoveWithVector(Vector& displacement);	// go in the direction of 'displacement' and travel its magnitude





#endif
