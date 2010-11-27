
#ifndef _Sensors_
#include "Sensors.h"
#endif



bool EnemyRobotDetected()
{
	return false; //SonarSensorGetDistance() > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}





// Status
//#define HTSMUX_STAT_NORMAL      0x00  /*!< Nothing going on, everything's fine */
//#define HTSMUX_STAT_BATT        0x01  /*!< No battery voltage detected status */
//#define HTSMUX_STAT_BUSY        0x02  /*!< Auto-dected in progress status */
//#define HTSMUX_STAT_HALT        0x04  /*!< Multiplexer is halted status */
//#define HTSMUX_STAT_ERROR       0x08  /*!< Command error detected status */
//#define HTSMUX_STAT_NOTHING     0xFF  /*!< Status hasn't really been set yet */


bool SMUXiInitialized()
{
  short status = smuxData[SMUX1].status | smuxData[SMUX2].status;
  short badFlags = HTSMUX_STAT_BATT | HTSMUX_STAT_HALT | HTSMUX_STAT_ERROR | HTSMUX_STAT_NOTHING;

  bool initialised = ( status & badFlags > 0 );

  if ( initialized ) PlaySound(soundException);

  return initialised;
}
