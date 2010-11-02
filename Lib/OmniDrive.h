

#ifndef _OmniDrive_
#define _OmniDrive_




#ifndef _Vector_
#include "Vector.h"
#endif

#ifndef _Defines_
#include "Defines.h"
#endif




void SetBoostState(bool state);
bool BoostToggle();	//	toggles boost and returns the new value
bool BoostIsOn();







/*	drive - controls bot arcade style
 *	omni - x component controls sidewinding
 */
void OmniArcadeDrive(Vector& drive, Vector& omni);


/*	strafe - controls forward, backward, & side to side
 *	rotate - x component controls the rotation of the bot around the center
 */
void OmniStrafeDrive(Vector& strafe, Vector& rotate);


void OmniDrivePro(Controller& ctrlr);




void OmniTranslate(Vector translation);
void OmniRotate(float angle);
void OmniTranslateAndRotate(Vector translation, float angle);








#endif
