
#ifndef _Sensors_
#define _Sensors_



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



//	Magnet
bool MagneticSensorMagnetIsPresent();



//	Light
int LightSensorLeftGetBrightness();
int LightSensorRightGetBrightness();










bool EnemyRobotDetected();






#endif
