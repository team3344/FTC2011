
#ifndef _Sensors_
#define _Sensors_








//	Accelerometer
float AccelerometerGetTiltAngle(short s);



//	Ultrasonic
float UltrasonicSensorGetDistance(short s);	//	distance is in inches



//	IR
bool IRSensorBeaconIsVisible(short s);
float IRSensorGetAngleToBeacon(short s);
float IRSensorGetIRStrength(short s);



//	Magnet
bool MagneticSensorMagnetIsPresent(short s);



//	Light
float LightSensorGetBrightness(short s);










bool EnemyRobotDetected();






#endif
