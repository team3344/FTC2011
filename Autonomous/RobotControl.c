

#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Field_
#include "Field.h"
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

  wait1Msec(70);
}






//	Line Following
//===========================================================================================================

#define kLineFollowerMotorPower 30
#define kLineFollowerTurnRange (kLineFollowerMotorPower * .85)


/*
task FollowLine()
{
  FollowingLine = true;

  _RobotZeroDriveEncoders();

  float brightnessRange = CurrentLineFollowingContext.lineBrightness - CurrentLineFollowingContext.surroundingBrightness;
  float gain = kLineFollowerTurnRange / brightnessRange;

  while ( true )
  {
    float left = LEFT_LIGHT_SENSOR();
    float right = RIGHT_LIGHT_SENSOR();
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
  RobotStop();
  //PlaySound(soundDownwardTones);

  //  update the position of the robot
  int encoder = (nMotorEncoder[Left] + nMotorEncoder[Right]) / 2;
  int distance = DriveMotorConvertEncoderToDistance(encoder);

  float orientation = CurrentRobotPosition.orientation;
  CurrentRobotPosition.location.x += distance * cos(orientation);
  CurrentRobotPosition.location.y += distance * sin(orientation);

  FollowingLine = false;
}
*/



bool RobotFollowWhiteLineForDistance(float distance, bool avoidEnemies)
{
  MechanismElevatorSetHeight(kElevatorHeightLineFollowing);

	_RobotZeroDriveEncoders();


	bool success = true;

  float brightnessRange = CurrentLineFollowingContext.lineBrightness - CurrentLineFollowingContext.surroundingBrightness;
  float gain = kLineFollowerTurnRange / brightnessRange;

  int targetEncoder = DriveMotorConvertDistanceToEncoder(distance);
  nxtDisplayCenteredTextLine(4, (string)targetEncoder);

  //  go until we reach the distance
  while ( (abs(nMotorEncoder[Left] + nMotorEncoder[Right]) / 2) < targetEncoder )
  {
    float left = LEFT_LIGHT_SENSOR();
    float right = RIGHT_LIGHT_SENSOR();
    float error = left - right;

    nxtDisplayCenteredTextLine(0, (string)left);
    nxtDisplayCenteredTextLine(1, (string)right);

    float turn = error * gain;

    motor[Left] = kLineFollowerMotorPower - turn;
    motor[Right] = kLineFollowerMotorPower + turn;


    if ( EnemyRobotDetected() && avoidEnemies )
    {
      success = false;
      break;
    }
  }


  //  update the position of the robot
  int encoder = (nMotorEncoder[Left] + nMotorEncoder[Right]) / 2;
  int distTravelled = DriveMotorConvertEncoderToDistance(encoder);

  float orientation = CurrentRobotPosition.orientation;
  CurrentRobotPosition.location.x += distTravelled * cos(orientation);
  CurrentRobotPosition.location.y += distTravelled * sin(orientation);


	return success;
}

#define kBrightnessEqualityThreshold 3 //  if brightnesses are less than this much different, they're the same

bool RobotFollowWhiteLineToEnd(bool avoidEnemies) //  FIXME: error in this method!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
  MechanismElevatorSetHeight(kElevatorHeightLineFollowing);

  _RobotZeroDriveEncoders();


  float brightnessRange = CurrentLineFollowingContext.lineBrightness - CurrentLineFollowingContext.surroundingBrightness;
  float gain = kLineFollowerTurnRange / brightnessRange;


  bool success = true;

  while ( true )
  {
    float left = LEFT_LIGHT_SENSOR();
    float right = RIGHT_LIGHT_SENSOR();
    float error = left - right;


    bool same = abs(error) < kBrightnessEqualityThreshold;
    bool notLine = ( ((left + right) / 2) - CurrentLineFollowingContext.surroundingBrightness) < kBrightnessEqualityThreshold;

    if ( same && notLine )
    {
      break;
    }




    //  abort if a robot is in the way
    if ( EnemyRobotDetected() && avoidEnemies )
    {
      success = false;
      break;
    }


    float turn = error * gain;

    motor[Left] = kLineFollowerMotorPower - turn;
    motor[Right] = kLineFollowerMotorPower + turn;
  }



  //  stop
  RobotStop();

  //  update the position of the robot
  int encoder = (nMotorEncoder[Left] + nMotorEncoder[Right]) / 2;
  int distance = DriveMotorConvertEncoderToDistance(encoder);

  float orientation = CurrentRobotPosition.orientation;
  CurrentRobotPosition.location.x += distance * cos(orientation);
  CurrentRobotPosition.location.y += distance * sin(orientation);


  return success;
}


#define kWhiteLineScanAngle PI / 4
#define kRobotLineScanPower 20
#define kMinLineSurroundingDifference 10

void _RecordLineBrightness(int b)
{
  nxtDisplayCenteredTextLine(0, (string)CurrentLineFollowingContext.surroundingBrightness);
  nxtDisplayCenteredTextLine(1, (string)CurrentLineFollowingContext.lineBrightness);


  if ( CurrentLineFollowingContext.lineBrightness < b )
    CurrentLineFollowingContext.lineBrightness = b;
  else if ( CurrentLineFollowingContext.surroundingBrightness > b )
    CurrentLineFollowingContext.surroundingBrightness = b;
}



bool RobotFindWhiteLine()	//	returns true if it finds it
{
  MechanismElevatorSetHeight(kElevatorHeightLineFollowing);

  //  initial values
  CurrentLineFollowingContext.lineBrightness = 0;
  CurrentLineFollowingContext.surroundingBrightness = 100;


  float maxScanArc = kWhiteLineScanAngle * (kRobotWidth / 2);
  int scanEncoder = DriveMotorConvertDistanceToEncoder(maxScanArc);


  motor[Left] = kRobotLineScanPower;
  motor[Right] = -kRobotLineScanPower;

  while ( abs(nMotorEncoder[Left]) < abs(scanEncoder) )
  {
    _RecordLineBrightness(LEFT_LIGHT_SENSOR());
    _RecordLineBrightness(RIGHT_LIGHT_SENSOR());

    int contrast = CurrentLineFollowingContext.surroundingBrightness - CurrentLineFollowingContext.lineBrightness;

    int edge = (CurrentLineFollowingContext.lineBrightness + CurrentLineFollowingContext.surroundingBrightness) / 2;
    bool leftOnEdge = abs(LEFT_LIGHT_SENSOR() - edge) < kBrightnessEqualityThreshold;

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
    _RecordLineBrightness(LEFT_LIGHT_SENSOR());
    _RecordLineBrightness(RIGHT_LIGHT_SENSOR());

    int contrast = CurrentLineFollowingContext.surroundingBrightness - CurrentLineFollowingContext.lineBrightness;

    int edge = (CurrentLineFollowingContext.lineBrightness + CurrentLineFollowingContext.surroundingBrightness) / 2;
    bool rightOnEdge = abs(RIGHT_LIGHT_SENSOR() - edge) < kBrightnessEqualityThreshold;

    if ( abs(contrast) > kMinLineSurroundingDifference && rightOnEdge )
    {
      RobotStop();
      return true;
    }
  }


  motor[Left] = kRobotLineScanPower;
  motor[Right] = -kRobotLineScanPower;

  //  go back to the initial orientation
  _RobotZeroDriveEncoders();
  while ( abs(nMotorEncoder[Left]) < scanEncoder ) {}
  RobotStop();


	return false;
}







#define kRobotMoveSpeed 25
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


	//	encoder
	_RobotZeroDriveEncoders();
	float wheelDistance = angle * (kRobotWidth / 2);
	int encoderPoints = DriveMotorConvertDistanceToEncoder(wheelDistance);


	//	set encoder targets
	int rightEncoder = encoderPoints * SIGN(wheelDistance);
	nMotorEncoderTarget[Right] = rightEncoder;
	nMotorEncoderTarget[Left] = -rightEncoder;


	//	start rotating
	motor[Right] = kRobotRotateSpeed * SIGN(wheelDistance);
	motor[Left] = -motor[Right];


	//	wait
	while( !MotorDone(Left, -rightEncoder) || !MotorDone(Right, rightEncoder) ) {}	//	wait until we reach our target


	//	stop
	RobotStop();


	//	update bot orientation
	CurrentRobotPosition.orientation = orientation;
}



bool RobotMoveDistance(float distance, bool avoidEnemies)
{
	_RobotZeroDriveEncoders();

	int encoderPoints = DriveMotorConvertDistanceToEncoder(distance);


	//	set encoder targets
	nMotorEncoderTarget[Left] = encoderPoints;
	nMotorEncoderTarget[Right] = encoderPoints;
  //wait1Msec(70);

	//nxtDisplayCenteredTextLine(0, (string)encoderPoints);
	//wait10Msec(100);



	//	start moving
	motor[Left] = kRobotMoveSpeed * SIGN(distance);
	motor[Right] = motor[Left];


	bool success;

	while ( true )
	{
	  if ( MotorDone(Left, encoderPoints) && MotorDone(Right, encoderPoints) ) //  if we're there
	  {
	    success = true;
	    break;
	  }

	  if ( avoidEnemies && EnemyRobotDetected() ) //  if we see an enemy, stop
	  {
	    PlaySound(soundLowBuzz);
	    success = false;
	    break;
	  }
	}


	//  stop
	RobotStop();



	//	update position
	float orientation = CurrentRobotPosition.orientation;
	float travelled = DriveMotorConvertEncoderToDistance((nMotorEncoder[Left] + nMotorEncoder[Right]) / 2);
	CurrentRobotPosition.location.x += travelled * cos(orientation);
	CurrentRobotPosition.location.y += travelled * sin(orientation);


	return success;
}





bool RobotMoveUntilPerpendicularLine(float maxDistance, bool avoidEnemies)
{
   _RobotZeroDriveEncoders();

  int targetEncoder = DriveMotorConvertDistanceToEncoder(maxDistance);


  //  start moving
  motor[Left] = kRobotMoveSpeed;
  motor[Right] = kRobotMoveSpeed;

  int brightnessThreshold = (.75 * CurrentLineFollowingContext.lineBrightness) + (.25 * CurrentLineFollowingContext.surroundingBrightness);

  bool success;

  while ( true )
  {
    if ( abs(nMotorEncoder[Left]) >= abs(targetEncoder) ) //  if we're at the max distance, ...	//	FIXME: update this to use nMotorEncoderTarget[] ??????????????????????????????????????????????????????????????????
    {
      success = false;
      break;
    }

    if ( avoidEnemies && EnemyRobotDetected() ) //  we detected an enemy!!!
    {
      success = false;
      break;
    }

    int brightness = ((LEFT_LIGHT_SENSOR() + RIGHT_LIGHT_SENSOR()) / 2);  //  average of the left & right light sensors
    if ( brightness > brightnessThreshold ) //  see if we detected a line
    {
      success = true;
      break;
    }
  }


  //  stop
  motor[Left] = 0;
  motor[Right] = 0;


  float distanceTravelled = DriveMotorConvertEncoderToDistance(nMotorEncoder[Left]);  //  find out how far we went
  float orientation = CurrentRobotPosition.orientation;

  //  update current position
  CurrentRobotPosition.location.x += distanceTravelled * cos(orientation);
  CurrentRobotPosition.location.y += distanceTravelled * sin(orientation);

  return success;
}




bool RobotMoveToLocation(Vector& location, bool backwards, bool avoidEnemies)
{
  Vector startLocation;
  memcpy(startLocation, CurrentRobotPosition.location, sizeof(Vector));

  Vector displacement;
  VectorSubtract(location, startLocation, displacement);

  float distance, angle;
  angle = VectorGetAngle(displacement);
  distance = VectorGetMagnitude(displacement);

  if ( backwards )
  {
    angle += PI;
    distance *= -1;
  }

  RobotRotateToOrientation(angle);

  return RobotMoveDistance(distance, avoidEnemies);
}







void RobotApproachBridge()
{
	MechanismElevatorSetHeight(kElevatorHeightBridgeCrossing);

	int speed = kRobotMoveSpeed;

	motor[Left] = speed;
	motor[Right] = speed;

	wait1Msec(1500);


	float distanceFromCenter = (kBridgeLength / 2) + kRotationPointDistanceFromFront;
	float center = kFieldSize / 2;
	CurrentRobotPosition.location.y = center + ( (CurrentRobotPosition.location.y < center) ? -distanceFromCenter : distanceFromCenter );


	RobotMoveDistance(-kRobotBridgeApproachDistance, false);	//	back up a bit


}

void RobotLowerBridge()
{
  servo[LeftStomper] = kLeftStomperDown;
  servo[RightStomper] = kRightStomperDown;

  wait1Msec(300);

  RobotMoveDistance(3, false);

  servo[LeftStomper] = kLeftStomperUp;
  servo[RightStomper] = kRightStomperUp;
}

bool RobotMountCenterDispenser()
{
  bool success = true;

  MechanismElevatorSetHeight(kElevatorHeightMidDispenser);

  while ( SonarSensorDistance() > kMidDispenserMountDistance )
  {
    if ( IRSensorValue() == 0 )
    {
      wait1Msec(250); //  wait 1/4 second
      if ( IRSensorValue() == 0 ) //  if we still can't see anything, abort
      {
        success = false;
        break;
      }
    }


    float speed = ( SonarSensorDistance() > 18 ) ? kRobotMoveSpeed : kRobotMoveSpeed / 2;
    float errorRange = 4;
    float turnRange = speed * .9;
    float gain = turnRange / errorRange;

    float error = 5 - IRSensorValue();
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
