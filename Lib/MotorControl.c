



#ifndef _MotorControl_
#include "MotorControl.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif






//	motor control by power
void MotorRotateEncoderPointsAtPower(int m, int encoderValue, int power)
{
  int p = (encoderValue > nMotorEncoder[m]) ? power : -power;
  motor[m] = p;

  if ( p > 0 )
    while ( nMotorEncoder[m] < encoderValue ) {}
  else
    while ( nMotorEncoder[m] > encoderValue ) {}

   motor[m] = 0;  //  stop
}

void MotorRotateTurnsAtPower(int m, int turns, int power)
{
	int encoderValue = kTetrixMotorEncoderPointsPerRotation * turns;
	//MotorRotateToEncoderValue(m, encoderValue, power);
}

//	FIXME: is all this stuff shenannigans???

typedef struct {
	float speed;
	int lastUpdateTime;
	int encoderValueStart;
	int encoderValueTarget;
	int m;
} MotorMotionInfo;

typedef struct {
	int timer;
	MotorMotionInfo motors[kRobotMotorCount];
} RobotMotionInfo;


task ContinuouslyUpdateMotorPower()
{
	while ( true )
	{
		//UpdateMotorPower();
		wait1Msec(kRobotMotorRefreshInterval);
	}
}


void UpdateMotorPower()
{
	for ( int i = 0; i < kRobotMotorCount; i++ )
	{
		//	FIXME: implement////////////////////////////
	}
}





//	motor control by speed
void MotorRotateEncoderPointsAtSpeed(int m, int encoderPoints, float speed)
{
	int start = nMotorEncoder[m];

	int target = start + encoderPoints;

	float dist = (encoderPoints / kTetrixMotorEncoderPointsPerRotation) * 2 * PI;	//	number of radians to rotate for

	int time = dist / speed;	//	time in seconds


//	time1[MotorTimer] = //	time in 1000ths of a second since the timer started
//	ClearTimer(MotorTimer);
	//	time1 only works for 30 seconds
	//	time10 works for 5 min and gives time in 100ths of a second
	//	int nPgmTime is the time in 1000ths of a second since the program started == use this!

}

void MotorRotateTurnsAtSpeed(int m, float turns, int speed)
{

}
