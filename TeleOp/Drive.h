

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

static float DrivePowerMultiplier = kPowerNormal;	//	set this to slow down or speed up the bot



void SetMotorPower(short m, float power);	//	power is from 0 to 1





/*	drive - controls bot arcade style
 *	omni - x component controls sidewinding
 */
//void OmniArcadeDrive(Vector& drive, Vector& omni);


/*	strafe - controls forward, backward, & side to side
 *	rotate - x component controls the rotation of the bot around the center
 */
//void OmniStrafeDrive(Vector& strafe, Vector& rotate);
//

//void OmniDrivePro(Controller& ctrlr);


//void OmniSetStrafePower(float power);

//void OmniTranslate(Vector translation);
//void OmniRotate(float angle);
//void OmniTranslateAndRotate(Vector translation, float angle);








#endif
