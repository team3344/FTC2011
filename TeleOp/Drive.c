

#ifndef _Drive_
#include "Drive.h"
#endif


//	motor names: Left, Right, Front, Back
void SetMotorPower(short m, float power)	//	power is from 0 to 1
{
	motor[m] = power * 100. * DrivePowerMultiplier;
}
