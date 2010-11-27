
#ifndef _RobotControl_
#define _RobotControl_



#ifndef _Vector_
#include "../shared/Vector.h"
#endif


#ifndef _Sensors_
#include "../shared/Sensors.h"
#endif







typedef struct {
  float orientation;
  Vector location;
} RobotPosition;



//  FIXME: figure out these distances!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//  distance in inches that the sonar sensor sensor should read when the bot is aligned correctly for dispensing
#define kLowDispenserMountDistance 3
#define kMidDispenserMountDistance 5
#define kHighDispenserMountDistance 7








//	Position Tracking
//===========================================================================================================
static RobotPosition CurrentRobotPosition;




#define TetrixConvertEncoderToDistance(encoder) ( (encoder / kTetrixMotorEncoderPointsPerRotation) * kRobotWheelCircumference )
#define TetrixConvertDistanceToEncoder(dist) ( (dist / kRobotWheelCircumference) * kTetrixMotorEncoderPointsPerRotation )




typedef struct {
	int lineBrightness, surroundingBrightness;
} LineFollowingContext;

LineFollowingContext CurrentLineFollowingContext;



bool RobotFollowWhiteLineForDistance(LineFollowingContext& ctxt, float distance, bool avoidEnemies);
bool RobotFollowWhiteLineToEnd(LineFollowingContext& ctxt, bool avoidEnemies);

bool RobotFindWhiteLine();	//	returns true if it finds it.  saves context to CurrentLineFollowingContext



void RobotRotateToOrientation(float orientation);
bool RobotMoveDistance(float distance, bool avoidEnemies);				//	distance in inches.  Can be negative.


void RobotApproachBridge();
void RobotLowerBridge();
void RobotMountCenterDispenser();	//	we're right in front of it.  drive up close to it and get in position to dispense




void RobotBalance();	//	call this when we're on the bridge and the robot will adjust its position until it's balanced





#endif
