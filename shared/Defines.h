
#ifndef _Defines_
#define _Defines_


/*	All measurements are in inches	*/





//#define kLightSensorDistanceFromCenter 5





#define kTetrixMotorEncoderPointsPerRotation 4 * 360
#define kNXTMotorEncoderPointsPerRotation 360

//#define kRobotWidth 10

//	FIXME: this is wrong too!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kRobotWheelRadius 2
#define kRobotWheelCircumference (kRobotWheelRadius * 2 * PI)


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)



//#define kRobotRadius 13	//	FIXME: this is wrong for our bot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



#endif
