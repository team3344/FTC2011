
#ifndef _Sensors_
#define _Sensors_








//	Accelerometer
//float AccelerometerSensorGetTiltAngle(tSensors s);
int AccelerometerSensorGetValue();


//	Ultrasonic
float SonarSensorGetDistance();	//	distance is in inches



//	IR
int IRSensorGetValue();
//float IRSensorGetAngleToBeacon(tSensors s);
//float IRSensorGetIRStrength(tSensors s);



//	Magnet
bool MagneticSensorMagnetIsPresent();



//	Light
int LightSensorLeftGetBrightness();
int LightSensorRightGetBrightness();










bool EnemyRobotDetected();






#endif
