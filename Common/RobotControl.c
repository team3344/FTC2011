
#include "RobotControl.h"
#include "Sensors.h"






#define kLineEdgeLightSensorValue 20

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
	}
	
	//	FIXME: what happens when it gets to the end of the line???????????????????????????????
}


