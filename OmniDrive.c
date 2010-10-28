

#ifndef _OmniDrive_
#include "OmniDrive.h"
#endif




#define kRobotHalfLength 10
#define kRobotHalfWidth 8





static bool boost;

#define kPowerNormal .4
#define kPowerBoost 1.0


void SetBoostState(bool state)
{
	boost = state;
}

bool BoostToggle()
{
	boost = !boost;
	return boost;
}


bool BoostIsOn()
{
	return boost;
}


//	motor names: Left, Right, Front, Back
void SetMotorPower(short m, float power)	//	power is from 0 to 1
{
	motor[m] = power * 100. * (( BoostIsOn() ) ? kPowerBoost : kPowerNormal);
}





/*	drive - controls bot arcade style
*	omni - x component controls sidewinding
*/
void OmniArcadeDrive(Vector& drive, Vector& omni)
{
	float power = drive.y;
	float turn = drive.x;
	float side = omni.x;

	SetMotorPower(Left, power + turn);
	SetMotorPower(Right, power - turn);
	SetMotorPower(Front, side);
	SetMotorPower(Back, side);
}


/*	strafe - controls forward, backward, & side to side
*	rotate - x component controls the rotation of the bot around the center
*/
void OmniStrafeDrive(Vector& strafe, Vector& rotate)
{
	SetMotorPower(Left, strafe.y);
	SetMotorPower(Right, strafe.y);
	SetMotorPower(Front, strafe.x + rotate.x);	//	FIXME: should rotate.x be scaled down????????????????
	SetMotorPower(Front, strafe.x - rotate.x);
}







void SetMotorSpeedsForVelocities(float dx_dt, float dy_dt, float dtheta_dt, float angle)
{
	float Fr, Br;	//	velocities of the front and back wheels for rotation
	Fr = kRobotHalfLength * dtheta_dt;
	Br = -Fr;

	float Ft, Bt;	//	velocities of the front and back wheels for translation
	Ft = dx_dt / cos(angle);
	Bt = Ft;

	float F, B;
	F = Fr + Ft;
	B = Br + Bt;

	float L, R;
	L = dy_dt / cos(angle);
	R = L;


	motor[Left] = L;
	motor[Right] = R;
	motor[Front] = F;
	motor[Back] = B;
}


/*



#define kMaxTranslationalAcceleration 2	//	acceleration is in inches per second^2
#define kMaxRotationalAcceleration 2	//	radians per second^2

#define kMaxWheelVelocity 20			//	inches per second





typedef struct {
	float initialVelocity;	//	FIXME: necessario???
	float acceleration;
	float acceleration_duration;
	float constant_velocity_duration;
} VelocityCurve;



float VelocityCurveGetVelocityAtTime(float time, VelocityCurve& vCurve)
{
	return 2;	//	FIXME: implement
}



float VelocityCurveGetDistanceAtTime(float time, VelocityCurve& vCurve)
{
	//	FIXME: implement







	return 3;	//	FIXME: remove
}



float OmniTimeRequiredForTranslation(Vector& translation)
{
	/*
	 *		|	constant acceleration until max velocity, then
	 *		|	constant velocity until it's time to slow down
	 *		|
	 *	  v	|	--------------------
	 *		|  /					\
	 *		| /						 \
	 *		|/________________________\____
	 *				      t
	 */
/*
	float distance = VectorGetMagnitude(translation);

	float timeIfPeak = kMaxWheelVelocity / kMaxTranslationalAcceleration * 2;	//	time to accelerate to max velocity, then decelerate to zero
	float distanceIfPeak = .5 * kMaxWheelVelocity * timeIfPeak;					//	distance we go if we just peak then go back down

	if ( distance > distanceIfPeak )
	{
		float timeAtMaxVelocity = kMaxWheelVelocity / (distance - distanceIfPeak );
		return timeAtMaxVelocity + timeIfPeak;
	}
	else
	{
		//	dist = peak * time * .5
		//	time * .5 * acc = peak

		//	dist = (time * .5 * acc) * time * .5
		//	dist = time^2 * .25 * acc
		//	time^2 = dist / (.25 * acc)
		return sqrt(distance / (.25 * kMaxTranslationalAcceleration));
	}
}


float OmniTimeRequiredForRotation(float rotationAngle)
{
	//	FIXME: implement















}


/*

//	FIXME: is it necessary to include an initial & final velocity here???????????????????????????????
void OmniCreateVelocityCurve(float minDuration, float maxAcceleration, float maxVelocity, float initialVelocity, float finalVelocity, VelocityCurve& vCurve)
{
	float timeIfPeak = (maxVelocity / acceleration) * 2;
	float distanceIfPeak


	//	FIXME: implement
	///

	//////////
	//////////////
	////////////////
	//////////////////
	////////////////////

	///////////////////////
	/////////////////////////











}

*/


/*
void OmniTranslate(Vector& translation)
{
	VelocityCurve xCurve, yCurve;

	//	FIXME:	get both curves & get them correctly
	OmniCreateVelocityCurve(0, kMaxTranslationalAcceleration, kMaxWheelVelocity, 0, xCurve);	//	get the velocity curve



	float endTime = 3;	//	FIXME: fix this
	float time;

	//	FIXME: set time here!!!!!!!!!!
	while ( (time = 3) <= endTime )
	{
		float dx_dt = VelocityCurveGetVelocityAtTime(time, xCurve);
		float dy_dt = VelocityCurveGetVelocityAtTime(time, yCurve);
		SetMotorSpeedsForVelocities(VelocityCurveGetVelocityAtTime(dx_dt, dy_dt, 0, 0);
	}
}





void OmniRotate(float angle)
{
	//	FIXME: implement
}





void OmniTranslateAndRotate(Vector& translation, float angle)
{
	float time = MAX( OmniTimeRequiredForTranslation(translation), OmniTimeRequiredForRotation(rotationAngle) );


	//	FIXME: implement






}
*/
