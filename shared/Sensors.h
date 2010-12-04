
#ifndef _Sensors_
#define _Sensors_




#include "../HT RobotC Drivers/drivers/LEGOLS-driver.h"
#include "../HT RobotC Drivers/drivers/LEGOTS-driver.h"
#include "../HT RobotC Drivers/drivers/HTAC-driver.h"
#include "../HT RobotC Drivers/drivers/HTMAG-driver.h"
#include "../HT RobotC Drivers/drivers/HTIRS2-driver.h"
#include "../HT RobotC Drivers/drivers/LEGOUS-driver.h"








#define LEFT_LIGHT_SENSOR() LSvalNorm(LeftLightSensor)
#define RIGHT_LIGHT_SENSOR() (LSvalNorm(RightLightSensor) -2)



#define IRSensorValue() (HTIRS2readACDir(IR))

#define SonarSensorDistance() (USreadDist(Sonar) / 2.54)  //  distance in inches



#define kMagnetSensorNormal -4
#define kMagnetThreshold 20
#define MagnetBatonPresent() (abs(HTMAGreadVal(Magnet) - kMagnetSensorNormal) > kMagnetThreshold)



bool EnemyRobotDetected();



#define AbortIfNoSMUX() if ( !SMUXiInitialized() ) { wait1Msec(200); StopAllTasks(); }

bool SMUXiInitialized();  //  plays sound "Exception" if they're not inited
void SensorsInit();



#endif
