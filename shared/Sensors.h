
#ifndef _Sensors_
#define _Sensors_




#include "../HT RobotC Drivers/drivers/LEGOLS-driver.h"
#include "../HT RobotC Drivers/drivers/LEGOTS-driver.h"
#include "../HT RobotC Drivers/drivers/HTAC-driver.h"
#include "../HT RobotC Drivers/drivers/HTMAG-driver.h"
#include "../HT RobotC Drivers/drivers/HTIRS2-driver.h"
#include "../HT RobotC Drivers/drivers/LEGOUS-driver.h"



#define LEFT_LIGHT_SENSOR LSvalNorm(LeftLightSensor)
#define RIGHT_LIGHT_SENSOR (LSvalNorm(RightLightSensor) + 3)



#define IRSensorValue HTIRS2readACDir(IR)

#define SonamuxUpdateIntervalrSensorDistance (USreadDist(Sonar) / 2.54)  //  distance in inches



#define kMagnetSensorNormal 300
#define kMagnetThreshold 50
#define MagnetBatonPresent (abs(HTMAGreadVal(Magnet) - kMagnetSensorNormal) > kMagnetThreshold)



bool EnemyRobotDetected();



bool SMUXiInitialized();  //  plays sound "Exception" if they're not inited




#endif
