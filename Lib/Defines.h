
#ifndef _Defines_
#define _Defines_




#define kLightSensorDistanceFromCenter 5



//	All measurements are in inches

#define kTetrixMotorEncoderPointsPerRotation 4 * 360
#define kNXTMotorEncoderPointsPerRotation 360

#define kRobotWidth 10

//	FIXME: this is wrong too!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kRobotWheelRadius 2			//	multiply this by a wheel's rotation in radians to get the distance travelled in inches


//#define kRobotMotorCount 7
//#define kRobotMotorRefreshInterval 20	//	number of milliseconds to wait between motor refreshes


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)




#define kRobotRadius 13	//	FIXME: this is wrong for our bot!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



//#define PrintVector(v) printf("<%f, %f, %f>", v.x, v.y, v.z)



#endif
