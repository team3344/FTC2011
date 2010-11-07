
#ifndef _Sensors_
#include "Sensors.h"
#endif








//	Accelerometer
int AccelerometerSensorGetValue()
{
  return SensorValue[Accelerometer];
}


int IRSensorGetValue()
{
  HTIRSreadDir(msensor_S2_4);
}



//	Ultrasonic
float SonarSensorGetDistance()	//	distance is in inches
{
	float cm = SensorValue[Sonar];	//	sensor output is in cm
	return cm / 2.54;			//	convert it to inches
}




//	IR
/*
bool IRSensorBeaconIsVisible()
{
	return SensorValue[IR] != 0;	//	0 means it's not visible
}

float IRSensorGetAngleToBeacon(tSensors s)
{
  return
}

float IRSensorGetIRStrength(tSensors s)
{

}
*/

#define kMagnetSensorNothingPresent 663
#define kMagnetSensorThreshold 50     //  FIXME: this value is crap!!!!!!!!!!!!!!

//	Magnet
bool MagneticSensorMagnetIsPresent()
{
  return abs(SensorValue[Magnetic] - kMagnetSensorNothingPresent) > kMagnetSensorThreshold;
}





//  Light
int LightSensorLeftGetBrightness()
{
  return LSvalNorm(msensor_S2_1);
}

int LightSensorRightGetBrightness()
{
  return LSvalNorm(msensor_S2_2);
}








bool EnemyRobotDetected()
{
	return SonarSensorGetDistance() > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}
