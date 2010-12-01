
#ifndef _Defines_
#define _Defines_







//	All measurements are in inches

#define kTetrixMotorEncoderPointsPerRotation 4. * 360.
#define kNXTMotorEncoderPointsPerRotation 360.
#define kDriveMotorGearRatio 2



#define DriveMotorConvertEncoderToDistance(encoder) ( (encoder / (kDriveMotorGearRatio * kTetrixMotorEncoderPointsPerRotation)) * kRobotWheelCircumference )
#define DriveMotorConvertDistanceToEncoder(dist) ( (dist / kRobotWheelCircumference) * kTetrixMotorEncoderPointsPerRotation * kDriveMotorGearRatio )





#define kRobotWheelRadius 2			//	multiply this by a wheel's rotation in radians to get the distance travelled in inches
#define kRobotWheelCircumference (2 * PI * kRobotWheelRadius)


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)



#define kLightSensorDistanceFromCenter 5
#define kRobotRadius 13	//	FIXME: this is wrong for our bot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kRobotWidth 16.25
#define kRotationPointDistanceFromFront 10	//	FIXME: this is wrong!!!!!!!!!!!!!!!!!!!!!!!!!


#endif
