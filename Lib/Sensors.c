
#ifndef _Sensors_
#include "Sensors.h"
#endif








//	Accelerometer
float AccelerometerSensorGetTiltAngle(tSensors s)
{
	
}



//	Ultrasonic
float SonarSensorGetDistance(tSensors s)	//	distance is in inches
{
	float cm = SensorValue[s];	//	sensor output is in cm
	return cm / 2.54;			//	convert it to inches
}




//	IR
bool IRSensorBeaconIsVisible(tSensors s)
{
	
}

float IRSensorGetAngleToBeacon(tSensors s)
{
	
}

float IRSensorGetIRStrength(tSensors s)
{
	
}




//	Magnet
bool MagneticSensorMagnetIsPresent(tSensors s)
{
	
}




//	Light
float LightSensorGetBrightness(tSensors s)
{
	
}














bool EnemyRobotDetected()
{
	return SonarSensorGetDistance(Sonar) > 8;	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}



