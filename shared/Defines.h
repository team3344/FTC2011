
#ifndef _Defines_
#define _Defines_




/*	All measurements are in inches	*/



#define kTetrixMotorEncoderPointsPerRotation 4. * 360.
#define kNXTMotorEncoderPointsPerRotation 360.
#define kDriveMotorGearRatio 2



#define DriveMotorConvertEncoderToDistance(encoder) ( (encoder / (kDriveMotorGearRatio * kTetrixMotorEncoderPointsPerRotation)) * kRobotWheelCircumference )
#define DriveMotorConvertDistanceToEncoder(dist) ( (dist / kRobotWheelCircumference) * kTetrixMotorEncoderPointsPerRotation * kDriveMotorGearRatio )





#define kRobotWheelRadius 2	//
#define kRobotWheelCircumference (2 * PI * kRobotWheelRadius)


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)
#define SIGN(x) ((x < 0) ? -1 : 1)



#define kLightSensorDistanceFromCenter 5	//
#define kRobotRadius 13						//	FIXME: this is wrong for our bot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kRobotWidth 16.25					//
#define kRobotLength 18						//
#define kRotationPointDistanceFromFront 10	//	FIXME: this is wrong!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
