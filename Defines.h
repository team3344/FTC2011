
#ifndef _Defines_
#define _Defines_


//	All measurements are in inches

#define kMotorEncoderPointsPerRotation 4 * 360

#define kRobotWidth 10


#define kRobotWheelRadius 2			//	multiply this by a wheel's rotation in radians to get the distance travelled in inches


#define kRobotMotorCount 7


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)



//#define PrintVector(v) printf("<%f, %f, %f>", v.x, v.y, v.z)



#endif
