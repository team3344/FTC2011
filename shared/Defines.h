
#ifndef _Defines_
#define _Defines_




#define kLightSensorDistanceFromCenter 5



//	All measurements are in inches

#define kTetrixMotorEncoderPointsPerRotation 4. * 360.
#define kNXTMotorEncoderPointsPerRotation 360.

#define kRobotWidth 16.25


#define kRobotWheelRadius 2			//	multiply this by a wheel's rotation in radians to get the distance travelled in inches
#define kRobotWheelCircumference (2 * PI * kRobotWheelRadius)


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)



#define kRobotRadius 13	//	FIXME: this is wrong for our bot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



#endif
