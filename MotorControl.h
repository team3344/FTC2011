

#ifndef _MotorControl_
#define _MotorControl_



#ifndef _Vector_
#include "Vector.h"
#endif





//	motor control by power
void MotorRotateToEncoderValueAtPower(int m, int encoderValue, int power);
void MotorRotateTurnsAtPower(int m, float turns, int power);

//	motor control by speed
//	NOTE: speed is in radians/sec
void MotorRotateEncoderPointsAtSpeed(int m, int encoderPoints, int speed);
void MotorRotateTurnsAtSpeed(int m, float turns, int speed);



#endif
