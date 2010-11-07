
#ifndef _RobotControl_
#define _RobotControl_



#ifndef _Vector_
#include "../shared/Vector.h"
#endif







typedef struct {
  float orientation;
  Vector location;
} RobotPosition;






//	Position Tracking
//===========================================================================================================
static RobotPosition currentRobotPosition;




#define TetrixConvertEncoderToDistance(encoder) ( (encoder / kTetrixMotorEncoderPointsPerRotation) * kRobotWheelCircumference )
#define TetrixConvertDistanceToEncoder(dist) ( (dist / kRobotWheelCircumference) * kTetrixMotorEncoderPointsPerRotation )




typedef struct {
	int lineBrightness, surroundingBrightness;
} LineFollowingContext;



bool RobotFollowWhiteLineForDistance(LineFollowingContext& ctxt, float distance);
bool RobotFollowWhiteLineToEnd(LineFollowingContext& ctxt);

bool RobotFindWhiteLine(LineFollowingContext& ctxtOut);	//	returns true if it finds it and gives the context



void RobotRotateToOrientation(float orientation);
bool RobotMoveDistance(float distance);				//	distance in inches.  Can be negative.


void RobotApproachBridge();
void RobotLowerBridge();
void RobotMountCenterDispenser();	//	we're right in front of it.  drive up close to it and get in position to dispense




//	Position Tracking
void RobotSetCurrentPosition(RobotPosition& pos);
void RobotGetCurrentPosition(RobotPosition& posOut);


void RobotBalance();	//	call this when we're on the bridge and the robot will adjust its position until it's balanced





#endif
