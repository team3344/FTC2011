
#ifndef _Sensors_
#define _Sensors_




#include "../HT RobotC Drivers/drivers/LEGOLS-driver.h"
#include "../HT RobotC Drivers/drivers/LEGOTS-driver.h"
#include "../HT RobotC Drivers/drivers/HTAC-driver.h"
#include "../HT RobotC Drivers/drivers/HTMAG-driver.h"



#define LEFT_LIGHT_SENSOR SensorValue[LeftLightSensor]
#define RIGHT_LIGHT_SENSOR SensorValue[RightLightSensor] + 3




//	Accelerometer
//float AccelerometerSensorGetTiltAngle(tSensors s);
int AccelerometerSensorGetValue();


//	Ultrasonic
float SonarSensorGetDistance();	//	distance is in inches



//	IR
int IRSensorGetValue();
//float IRSensorGetAngleToBeacon(tSensors s);
//float IRSensorGetIRStrength(tSensors s);




#define kMagnetSensorNormal 300
#define kMagnetThreshold 50
#define MagnetBatonPresent (abs(HTMAGreadVal(Magnet) - kMagnetSensorNormal) > kMagnetThreshold)



bool EnemyRobotDetected();






#endif
