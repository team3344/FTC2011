
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



typedef struct {
	int lineBrightness, surroundingBrightness;
} LineFollowingContext;

LineFollowingContext CurrentLineFollowingContext;



bool RobotFollowWhiteLineForDistance(float distance, bool avoidEnemies);
bool RobotFollowWhiteLineToEnd(bool avoidEnemies);

bool RobotFindWhiteLine();	//	returns true if it finds it.  saves context to CurrentLineFollowingContext



void RobotRotateToOrientation(float orientation);
bool RobotMoveDistance(float distance, bool avoidEnemies);				//	distance in inches.  Can be negative.

bool RobotMoveUntilPerpendicularLine(float maxDistance, bool avoidEnemies);


#define kRobotBridgeApproachDistance 1.5 //	distance away from the bridge that the bot is once it approaches the bridge
void RobotApproachBridge();
void RobotLowerBridge();
bool RobotMountCenterDispenser();	//	we're right in front of it.  drive up close to it and get in position to dispense




bool RobotMoveToLocation(Vector& location, bool backwards, bool avoidEnemies);





void RobotBalance();	//	call this when we're on the bridge and the robot will adjust its position until it's balanced





#endif
