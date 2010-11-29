
#ifndef _Sensors_
#include "Sensors.h"
#endif



bool EnemyRobotDetected()
{
	return false; //SonarSensorGetDistance() > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}


bool SMUXiInitialized()
{
  short status = smuxData[SMUX1].status | smuxData[SMUX2].status;
  short badFlags = HTSMUX_STAT_BATT | HTSMUX_STAT_HALT | HTSMUX_STAT_ERROR | HTSMUX_STAT_NOTHING;

  bool initialized = ( status & badFlags > 0 );

  if ( initialized ) PlaySound(soundException);

  return initialized;
}

void SensorsInit()
{
  HTSMUXinit();             //  init the sensor multiplexor driver
	HTSMUXscanPorts(SMUX1);   //  tell smuxi to detect connected sensors
  HTSMUXscanPorts(SMUX2);   //

  LSsetActive(LeftLightSensor);
  LSsetActive(RightLightSensor);
}
