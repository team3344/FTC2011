
#ifndef _Defines_
#define _Defines_


//	All measurements are in inches



#define kRobotWidth 10

#define kRobotTravelConstant .01	//	multiply this # by an encoder value to get distance travelled


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)



//#define PrintVector(v) printf("<%f, %f, %f>", v.x, v.y, v.z)



#endif
