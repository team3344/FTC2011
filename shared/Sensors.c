
#ifndef _Sensors_
#include "Sensors.h"
#endif






bool EnemyRobotDetected()
{
	return false; //SonarSensorGetDistance() > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}


bool SMUXiInitialized()
{
  bool bad = (HTSMUXreadStatus(SMUX1) & HTSMUX_STAT_BATT) || (HTSMUXreadStatus(SMUX2) & HTSMUX_STAT_BATT);
  if ( bad ) PlaySound(soundException);
  return !bad;
}

void SensorsInit()
{
  HTSMUXinit();             //  init the sensor multiplexor driver
	HTSMUXscanPorts(SMUX1);   //  tell smuxi to detect connected sensors
  HTSMUXscanPorts(SMUX2);   //

  LSsetActive(LeftLightSensor);
  LSsetActive(RightLightSensor);
}
