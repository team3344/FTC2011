

#ifndef _RobotControl_
#include "RobotControl.h"
#endif


#ifndef _Field_
#include "Field.h"
#endif


#ifndef _Defines_
#include "../shared/Defines.h"
#endif




void abort(string errStr)
{
  hogCPU();

  nxtDisplayCenteredTextLine(0, errStr);
  PlaySound(soundException);
  while ( true ) {} //  loop forever
}



void RobotStop()
{
  motor[Left] = 0;
  motor[Right] = 0;
}

void _RobotZeroDriveEncoders()
{
  nMotorEncoder[Left] = 0;
  nMotorEncoder[Right] = 0;

  wait1Msec(55);
}


#define MotorCloseThreshold 1000
#define MotorClose(m, e) ( (abs(nMotorEncoder[m] - e) < MotorCloseThreshold) || abs(nMotorEncoder[m]) < MotorCloseThreshold)



//	Line Following
//===========================================================================================================

#define kLineFollowerMotorPower 20
#define kLineFollowerTurnRange (kLineFollowerMotorPower)  //  FIXME: does this work??



bool RobotFollowWhiteLineForDistance(float distance, bool avoidEnemies)
{
  nxtDisplayCenteredTextLine(0, "folw line fo dist");
  nxtDisplayCenteredTextLine(1, (string)distance);
  PlaySound(soundUpwardTones);


  MechanismElevatorTarget(kElevatorTargetLineFollowing);


	_RobotZeroDriveEncoders();


	bool success = true;

  float brightnessRange = CurrentLineFollowingContext.lineBrightness - CurrentLineFollowingContext.surroundingBrightness;
  float gain = kLineFollowerTurnRange / brightnessRange;

  int targetEncoder = DriveMotorConvertDistanceToEncoder(distance);
  nxtDisplayCenteredTextLine(4, (string)targetEncoder);

  //  go until we reach the distance
  while ( ((nMotorEncoder[Left] + nMotorEncoder[Right]) / 2) < targetEncoder )
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


  RobotStop();


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
  nxtDisplayCenteredTextLine(0, "following line");

  MechanismElevatorTarget(kElevatorTargetLineFollowing);

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


#define kWhiteLineScanAngle PI / 4.0
#define kRobotLineScanPower 20
#define kMinLineSurroundingDifference 7

void _RecordLineBrightness(int b)
{
  if ( CurrentLineFollowingContext.lineBrightness < b )
    CurrentLineFollowingContext.lineBrightness = b;
  else if ( CurrentLineFollowingContext.surroundingBrightness > b )
    CurrentLineFollowingContext.surroundingBrightness = b;
}



bool RobotFindWhiteLine()	//	returns true if it finds it
{
  _RobotZeroDriveEncoders();

  nxtDisplayCenteredTextLine(0, "finding line");

  MechanismElevatorTarget(kElevatorTargetLineFollowing);

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




#define kRobotRotateSpeed 30


void RobotRotateToOrientation(float orientation)
{
	float currentOrientation = CurrentRobotPosition.orientation;
	float angle = orientation - currentOrientation;

	//	reduce angle
	if ( abs(angle) > 2.0 * PI )  //  FIXME: what if it's < -2PI ????????????
	{
		if ( angle < 0 ) angle += 2.0 * PI;
		else angle -= 2.0 * PI;
	}


	//	encoder
	_RobotZeroDriveEncoders();
	float wheelDistance = angle * (kRobotWidth / 2);
	int encoderPoints = DriveMotorConvertDistanceToEncoder(wheelDistance);


	//	set encoder targets
	int rightEncoder = encoderPoints * SIGN(wheelDistance);


	//	start rotating
	motor[Right] = kRobotRotateSpeed * SIGN(wheelDistance);
	motor[Left] = -motor[Right];


	//	wait
	while( true )
	{
	  bool right = false, left = false;

	  if ( abs(nMotorEncoder[Left]) > abs(rightEncoder) )
	  {
	    left = true;
	    motor[Left] = 0;
	  }
	  if ( abs(nMotorEncoder[Right]) > abs(rightEncoder) )
	  {
	    right = true;
	    motor[Right] = 0;
	  }

	  if ( left && right ) break;
	}

  //  we're already stopped


	//	update bot orientation
	CurrentRobotPosition.orientation = orientation;
}



bool RobotMoveDistance(float distance, bool avoidEnemies)
{
  nxtDisplayCenteredTextLine(0, "moving distance");

	_RobotZeroDriveEncoders();

	int encoderPoints = DriveMotorConvertDistanceToEncoder(distance);


	//	start moving
	motor[Left] = RobotMoveSpeed * SIGN(encoderPoints);
	motor[Right] = motor[Left];


	bool success;

	while ( true )
	{
	  bool left = false, right = false;

	  if ( MotorClose(Left, encoderPoints) )
	    motor[Left] = RobotMoveSpeed / 2 * SIGN(encoderPoints);
	  else
	    motor[Left] = RobotMoveSpeed * SIGN(encoderPoints);

	  if ( MotorClose(Right, encoderPoints) )
	    motor[Right] = RobotMoveSpeed / 2 * SIGN(encoderPoints);
	  else
	    motor[Right] = RobotMoveSpeed * SIGN(encoderPoints);


	  if ( abs(nMotorEncoder[Left]) > abs(encoderPoints) )
	  {
	    left = true;
	    motor[Left] = 0;
	  }
	  if ( abs(nMotorEncoder[Right]) > abs(encoderPoints) )
	  {
	    right = true;
	    motor[Right] = 0;
	  }

	  if ( left && right )
	  {
	    success = true;
	    break;
	  }


	  if ( avoidEnemies && EnemyRobotDetected() ) //  if we see an enemy, stop
	  {
	    PlaySound(soundLowBuzz);
	    success = false;
	    RobotStop();
	    break;
	  }
	}

  //  we're already stopped


	//	update position
	float orientation = CurrentRobotPosition.orientation;
	float travelled = DriveMotorConvertEncoderToDistance((nMotorEncoder[Left] + nMotorEncoder[Right]) / 2);
	CurrentRobotPosition.location.x += travelled * cos(orientation);
	CurrentRobotPosition.location.y += travelled * sin(orientation);

	return success;
}





bool RobotMoveUntilPerpendicularLine(float maxDistance, bool avoidEnemies)
{
  nxtDisplayCenteredTextLine(0, "move until line");

   _RobotZeroDriveEncoders();

  int targetEncoder = DriveMotorConvertDistanceToEncoder(maxDistance);


  //  start moving
  motor[Left] = RobotMoveSpeed;
  motor[Right] = RobotMoveSpeed;

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







void RobotMountBridge()
{
	MechanismElevatorTarget(kElevatorTargetBridgeCrossing);

	RobotMoveDistance(9, false);  //  get flush against the bridge  //  FIXME: is our angle bad when we're here???????

	float distanceFromCenter = (kBridgeLength / 2) + kRotationPointDistanceFromFront;
	float center = kFieldSize / 2;
	CurrentRobotPosition.location.y = center + ( (CurrentRobotPosition.location.y < center) ? -distanceFromCenter : distanceFromCenter );
  CurrentRobotPosition.orientation = ( CurrentRobotPosition.location.y < center ) ? PI / 2.0 : -PI / 2.0;

	RobotMoveDistance(-kRobotBridgeApproachDistance, false);	//	back up a bit



	//  push it down
	servo[LeftStomper] = kLeftStomperDown;
  servo[RightStomper] = kRightStomperDown;

  wait1Msec(300);

  //  drive up on it a little
  RobotMoveDistance(3, false);


  //  retract the stompers
  servo[LeftStomper] = kLeftStomperUp;
  servo[RightStomper] = kRightStomperUp;
}


bool RobotMountCenterDispenser()
{
  bool success = true;

  //  bring elevator to top
  motor[Elevator] = kElevatorSpeed;
  while ( !ElevatorIsAtTop() ) {}
  motor[Elevator] = 0;




  _RobotZeroDriveEncoders();


  int distance = kDispenserPerpendicularDistance - 8;
  int encoder = DriveMotorConvertDistanceToEncoder(distance);


  while ( ( (nMotorEncoder[Left] + nMotorEncoder[Right]) / 2 ) < encoder )
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

    float speed = RobotMoveSpeed * .7;
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

  MechanismElevatorTarget(kElevatorTargetMidDispenser);


  RobotMoveDistance(14, false); //  get pressed up against the dispenser

  float approachDistance = 2;

  RobotMoveDistance(-approachDistance, false);


  //  update position
  CurrentRobotPosition.location.y = kFieldSize - approachDistance;
  CurrentRobotPosition.location.x = kFieldSize / 2;
  CurrentRobotPosition.orientation = PI / 2.0;


  return success;
}



#define kRobotAccReadingBalanced -24
#define kRobotAccThreshold 5
#define kRobotAccBalancedThreshold 20
#define kSampleInterval 750

void RobotBalance()
{
  RobotMoveSpeed = 35;  //  go a little slower than usual


  long lastSampleTime = nPgmTime;

  int minError = 0;
  int maxError = 0;

  while ( true )
  {
    int reading;
    HTACreadX(Accelerometer, reading);

    int error = reading - kRobotAccReadingBalanced;

    if ( error > maxError )
    {
      maxError = error;
    }

    if ( error < minError )
    {
      minError = error;
    }


    if ( nPgmTime > lastSampleTime + kSampleInterval )
    {
      if ( MAX(abs(minError), abs(maxError)) > kRobotAccThreshold ) //  we're not balanced
      {
        if ( abs(minError) > kRobotAccThreshold && maxError > kRobotAccThreshold )
        {
          //  we're still oscillating, wait another interval
        }
        else if ( abs(maxError) > kRobotAccBalancedThreshold )
        {
          RobotMoveDistance(1, false);  //  forwards an inch
        }
        else if ( abs(minError) > kRobotAccBalancedThreshold )
        {
          RobotMoveDistance(-1, false); //  backwards an inch
        }
      }

      //  clear and prepare for next stuff
      minError = 0;
      maxError = 0;
      lastSampleTime = nPgmTime;
    }

  }
}
