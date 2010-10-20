

#ifndef _Vector_
#include "Vector.h"
#endif




#define kRobotHalfLength 10
#define kRobotHalfWidth 8





bool boost;


bool BoostOn()
{
	return boost;
}


//	motor names: Left, Right, Front, Back
void SetMotorSpeed(short motor, float speed)
{
	//	FIXME: adjust for boost
	motors[motor] = speed;
}




/*	drive - controls bot arcade style
*	omni - x component controls sidewinding
*/
void Drive1(Vector& drive, Vector& omni)
{
	
}



/*	strafe - controls forward, backward, & side to side
*	rotate - x component controls the rotation of the bot around the center
*/
void Drive2(Vector& strafe, Vector& rotate)
{
	
}







SetMotorSpeedsForVelocities(float dxdt, float dydt, float dthetadt, float angle)
{
	float fr, br;	//	velocities of the front and back wheels for rotation
	fr = kRobotHalfLength * dthetadt;
	br = -fr;
	
	//////////////////////////
	
	
	
	
	
}













