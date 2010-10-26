



#ifndef _RobotControl_
#include "RobotControl.h"
#endif

#ifndef _Sensors_
#include "Sensors.h"
#endif


#ifndef _Defines_
#include "../Defines.h"
#endif





#define kLineEdgeLightSensorValue 20	//	FIXME: can this value be calibrated during run????????????????

#define kLineFollowerFastMotorSpeed 60
#define kLineFollowerSlowMotorSpeed 0

task RobotFollowWhiteLine()
{
	while ( true )
	{
		if ( SensorValue[FloorLightSensor] )
		{
			motor[RightMotor] = kLineFollowerFastMotorSpeed;
			motor[LeftMotor] = kLineFollowerSlowMotorSpeed;
		}
		else
		{
			motor[RightMotor] = kLineFollowerSlowMotorSpeed;
			motor[LeftMotor] = kLineFollowerFastMotorSpeed;
		}

		//	FIXME: how do we know we're at the end of the line???????????????????????????????
		if ( true/* we're at the end of the line */ )	//	FIXME: ???
		{
			break;
		}
	}
}




task RobotFollowIR()
{
	//	FIXME: implement
}






void RobotRotate(float angle)
{
	//printf("rotating angle: %f\n", angle);



}


void RobotMove(float distance)
{

	//printf("moving distance: %f\n", distance);


}







//==========================================================================

void MotorRotateToEncoderValue(int m, int encoderValue, int speed)
{
  int s = (encoderValue > nMotorEncoder[m]) ? speed : -speed;
  motor[m] = s;

  if ( s > 0 )
    while ( nMotorEncoder[m] < encoderValue ) {}
  else
    while ( nMotorEncoder[m] > encoderValue ) {}

   motor[m] = 0;  //  stop
}

void MotorRotateTurns(int m, int turns, int speed)
{
    int encoderValue = kMotorEncoderPointsPerRotation * turns;
   MotorRotateToEncoderValue(m, encoderValue, speed);
}
