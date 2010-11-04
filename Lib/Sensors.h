
#ifndef _Sensors_
#define _Sensors_








//	Accelerometer
float AccelerometerSensorGetTiltAngle(tSensors s);



//	Ultrasonic
float SonarSensorGetDistance(tSensors s);	//	distance is in inches



//	IR
bool IRSensorBeaconIsVisible(tSensors s);
float IRSensorGetAngleToBeacon(tSensors s);
float IRSensorGetIRStrength(tSensors s);



//	Magnet
bool MagneticSensorMagnetIsPresent(tSensors s);



//	Light
float LightSensorGetBrightness(tSensors s);










bool EnemyRobotDetected();






#endif
