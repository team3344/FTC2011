
#ifndef _Sensors_
#include "Sensors.h"
#endif



bool EnemyRobotDetected()
{
	return false; //SonarSensorGetDistance() > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}
