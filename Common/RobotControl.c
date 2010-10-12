
//#include "RobotControl.h"
//#include "Sensors.h"






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






task RobotRotate(float angle)
{
	//printf("rotating angle: %f\n", angle);
	
	
	
}


task RobotMove(float distance)
{
	
	//printf("moving distance: %f\n", distance);
	
	
}





