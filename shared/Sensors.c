
#ifndef _Sensors_
#include "Sensors.h"
#endif

#ifndef _RobotControl_
#include "../Autonomous/RobotControl.h"
#endif





bool EnemyRobotDetected()
{
  return false;

  //float distance = SonarSensorDistance();
	//return (distance < 20.0) && (distance > 8.0);	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
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

  //  set default values
  CurrentLineFollowingContext.surroundingBrightness = 29;
  CurrentLineFollowingContext.lineBrightness = 49;
}
