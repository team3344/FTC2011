

#ifndef _OmniDrive_
#define _OmniDrive_




#ifndef _Vector_
#include "../shared/Vector.h"
#endif

#ifndef _Defines_
#include "../shared/Defines.h"
#endif



#define kDrivePowerLow		.2
#define kDrivePowerNormal	.4
#define kDrivePowerHigh		1.0

static float DrivePowerMultiplier = kDrivePowerNormal;	//	set this to slow down or speed up the bot

void SetMotorPower(short m, float power);	//	power is from 0 to 1





#endif
