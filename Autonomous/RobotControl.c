

#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Defines_
#include "../shared/Defines.h"
#endif





void RobotStop()
{
  motor[Left] = 0;
  motor[Right] = 0;
}

void _RobotZeroDriveEncoders()
{
  nMotorEncoder[Left] = 0;
  nMotorEncoder[Right] = 0;
}






//	Line Following
//===========================================================================================================

#define kLineFollowerMotorPower 30
#define kLineFollowerTurnRange (kLineFollowerMotorPower * (2.0 / 3.0))


static bool FollowingLine;
static bool AbortLineFollowing;

task FollowLine()
{
  FollowingLine = true;

  _RobotZeroDriveEncoders();

  float brightnessRange = CurrentLineFollowingContext.lineBrightness - CurrentLineFollowingContext.surroundingBrightness;
  float gain = kLineFollowerTurnRange / brightnessRange;

  while ( true )
  {
    float left = LEFT_LIGHT_SENSOR;
    float right = RIGHT_LIGHT_SENSOR;
    float error = left - right;

    nxtDisplayCenteredTextLine(0, (string)left);
    nxtDisplayCenteredTextLine(1, (string)right);

    float turn = error * gain;

    motor[Left] = kLineFollowerMotorPower - turn;
    motor[Right] = kLineFollowerMotorPower + turn;

    if ( AbortLineFollowing )
    {
      PlaySound(soundBeepBeep);
      AbortLineFollowing = false;
      break;  //  abort
    }
  }

  //  stop
  motor[Left] = 0;
  motor[Right] = 0;
  PlaySound(soundDownwardTones);
  wait10Msec(100);

  //  update the position of the robot
  int encoder = (nMotorEncoder[Left] + nMotorEncoder[Right]) / 2;
  int distance = DriveMotorConvertEncoderToDistance(encoder);

  float orientation = CurrentRobotPosition.orientation;
  CurrentRobotPosition.location.x += distance * cos(orientation);
  CurrentRobotPosition.location.y += distance * sin(orientation);

  FollowingLine = false;
}




bool RobotFollowWhiteLineForDistance(LineFollowingContext& ctxt, float distance, bool avoidEnemies)
{
  memcpy(CurrentLineFollowingContext, ctxt, sizeof(LineFollowingContext));
  StartTask(FollowLine);

  int targetEncoder = DriveMotorConvertDistanceToEncoder(distance);
  nxtDisplayCenteredTextLine(4, (string)targetEncoder);

  //  go until we reach the distance
  while ( abs(nMotorEncoder[Left] + nMotorEncoder[Right]) < targetEncoder )
  {
    int encoder = nMotorEncoder[Left];
    nxtDisplayCenteredTextLine(5, (string)encoder);

    if ( EnemyRobotDetected() && avoidEnemies )
    {
      AbortLineFollowing = true;  //  abort
      while ( FollowingLine ) {}  //  wait until it's stopped

      return false;
    }
  }

  AbortLineFollowing = true;
  while ( FollowingLine ) {}

	return true;
}

#define kBrightnessEqualityThreshold 3 //  if brightnesses are less than this much different, they're the same

bool RobotFollowWhiteLineToEnd(LineFollowingContext& ctxt, bool avoidEnemies) //  FIXME: what if it sees an enemy
{
  memcpy(CurrentLineFollowingContext, ctxt, sizeof(LineFollowingContext));

  StartTask(FollowLine);


  while ( true )
  {
    float left = LEFT_LIGHT_SENSOR;
    float right = RIGHT_LIGHT_SENSOR;

    float diff = left - right;
    bool same = abs(diff) < kBrightnessEqualityThreshold;
    bool notLine = ( ((left + right) / 2) - ctxt.surroundingBrightness) < kBrightnessEqualityThreshold;


    if ( same && notLine )
    {
      AbortLineFollowing = true;    //  abort line following
      while ( FollowingLine ) {}    //  wait until it stops

      return true;
    }


    //  abort if a robot is in the way
    if ( EnemyRobotDetected() && avoidEnemies )
    {
      AbortLineFollowing = true;   //  abort line following
      while ( FollowingLine ) {}  //  wait until it stops

      return false;
    }
  }

}


#define kWhiteLineScanAngle PI / 4
#define kRobotLineScanPower 20
#define kMinLineSurroundingDifference 15

void _RecordLineBrightness(int b)
{
  if ( CurrentLineFollowingContext.lineBrightness < b )
    CurrentLineFollowingContext.lineBrightness = b;
  else if ( CurrentLineFollowingContext.surroundingBrightness > b )
    CurrentLineFollowingContext.surroundingBrightness = b;
}



bool RobotFindWhiteLine()	//	returns true if it finds it
{
  //  initial values
  CurrentLineFollowingContext.lineBrightness = 0;
  CurrentLineFollowingContext.surroundingBrightness = 100;


  float maxScanArc = kWhiteLineScanAngle * (kRobotWidth / 2);
  int scanEncoder = DriveMotorConvertDistanceToEncoder(maxScanArc);


  motor[Left] = kRobotLineScanPower;
  motor[Right] = -kRobotLineScanPower;

  while ( abs(nMotorEncoder[Left]) < abs(scanEncoder) )
  {
    _RecordLineBrightness(LEFT_LIGHT_SENSOR);
    _RecordLineBrightness(RIGHT_LIGHT_SENSOR);

    int contrast = CurrentLineFollowingContext.surroundingBrightness - CurrentLineFollowingContext.lineBrightness;

    int edge = (CurrentLineFollowingContext.lineBrightness + CurrentLineFollowingContext.surroundingBrightness) / 2;
    bool leftOnEdge = abs(LEFT_LIGHT_SENSOR - edge) < kBrightnessEqualityThreshold;

    if ( abs(contrast) > kMinLineSurroundingDifference && leftOnEdge )
    {
      RobotStop();
      return true;
    }
  }

  _RobotZeroDriveEncoders();

  motor[Left] = -kRobotLineScanPower;
  motor[Right] = kRobotLineScanPower;

  while ( abs(nMotorEncoder[Right]) < abs(scanEncoder * 2) )
  {
    _RecordLineBrightness(LEFT_LIGHT_SENSOR);
    _RecordLineBrightness(RIGHT_LIGHT_SENSOR);

    int contrast = CurrentLineFollowingContext.surroundingBrightness - CurrentLineFollowingContext.lineBrightness;

    int edge = (CurrentLineFollowingContext.lineBrightness + CurrentLineFollowingContext.surroundingBrightness) / 2;
    bool rightOnEdge = abs(RIGHT_LIGHT_SENSOR - edge) < kBrightnessEqualityThreshold;

    if ( abs(contrast) > kMinLineSurroundingDifference && rightOnEdge )
    {
      RobotStop();
      return true;
    }
  }


  motor[Left] = kRobotLineScanPower;
  motor[Right] = -kRobotLineScanPower;

  _RobotZeroDriveEncoders();
  while ( abs(nMotorEncoder[Left]) < scanEncoder ) {}

	return false;
}







#define kRobotMoveSpeed 30	//	FIXME: change this
#define kRobotRotateSpeed kRobotMoveSpeed


void RobotRotateToOrientation(float orientation)
{
	float currentOrientation = CurrentRobotPosition.orientation;
	float angle = orientation - currentOrientation;

	//	reduce angle
	if ( abs(angle) > 2 * PI )
	{
		if ( angle < 0 ) angle += 2 * PI;
		else angle -= 2 * PI;
	}

	float wheelDistance = angle * (kRobotWidth / 2);


	//	start rotating
	motor[Left] = ( wheelDistance > 0 ) ? -kRobotRotateSpeed : kRobotRotateSpeed;
	motor[Right] = -motor[Left];

	int encoderPoints = DriveMotorConvertDistanceToEncoder(wheelDistance);
	nMotorEncoder[Left] = 0;

	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done

	//	stop
	motor[Left] = 0;
	motor[Right] = 0;


	CurrentRobotPosition.orientation = orientation;
}



bool RobotMoveDistance(float distance, bool avoidEnemies)
{
  nMotorEncoder[Left] = 0;
  nMotorEncoder[Right] = 0;

	int encoderPoints = DriveMotorConvertDistanceToEncoder(distance);


	//nxtDisplayCenteredTextLine(3, (string)encoderPoints);


	motor[Left] = ( distance > 0 ) ? kRobotMoveSpeed : -kRobotMoveSpeed;
	motor[Right] = motor[Left];

	while ( abs(nMotorEncoder[Left]) < abs(encoderPoints) ) {}	//	wait until we're done


	//  stop
	motor[Left] = 0;
	motor[Right] = 0;


	return true;	//	FIXME: this value should mean something	///////////////////////////////////////////////////////////////////////////////////////////////////////
}


void RobotApproachBridge()
{
  //  FIXME: implement
}

void RobotLowerBridge()
{
  servo[LeftStomper] = kLeftStomperDown;
  servo[RightStomper] = kRightStomperDown;

  wait1Msec(300);

  RobotMoveDistance(3, false);

  servo[LeftStomper] = kLeftStomperUp;
  servo[RightStomper] = kRightStomperUp;
  //  FIXME: tryme
}

bool RobotMountCenterDispenser()
{
  bool success = true;

  while ( SonarSensorDistance  > kMidDispenserMountDistance )
  {
    if ( IRSensorValue == 0 )
    {
      wait1Msec(250); //  wait 1/4 second
      if ( IRSensorValue == 0 ) //  if we still can't see anything, abort
      {
        success = false;
        break;
      }
    }


    float speed = ( SonarSensorDistance > 12 ) ? 30 : 15; //  FIXME: test out this speed
    float errorRange = 4;
    float turnRange = speed;
    float gain = turnRange / errorRange;

    float error = 5 - IRSensorValue;
    float turn = error * gain;

    motor[Left] = speed - turn;
    motor[Right] = speed + turn;
  }

  //  stop
  motor[Left] = 0;
  motor[Right] = 0;

  return success;
}

void RobotBalance()
{






  //  FIXME: implement
}
