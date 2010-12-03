
#ifndef _Defines_
#define _Defines_




/*	All measurements are in inches	*/



#define kMotorDoneThreshold 20
#define MotorDone(m, target) ((nMotorRunState[m] == runStateIdle) || (abs(target - nMotorEncoder[m]) < kMotorDoneThreshold))




#define kTetrixMotorEncoderPointsPerRotation 4. * 360.
#define kNXTMotorEncoderPointsPerRotation 360.
#define kDriveMotorGearRatio 2

#define DriveMotorConvertEncoderToDistance(encoder) ( (encoder / (kDriveMotorGearRatio * kTetrixMotorEncoderPointsPerRotation)) * kRobotWheelCircumference )
#define DriveMotorConvertDistanceToEncoder(dist) ( (dist / kRobotWheelCircumference) * kTetrixMotorEncoderPointsPerRotation * kDriveMotorGearRatio )





#define kRobotWheelRadius 2	//
#define kRobotWheelCircumference (2 * PI * kRobotWheelRadius)


#define ln(x) log(x)
#define powf(a, x) exp(x * ln(a))
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)
#define SIGN(x) ((x < 0) ? -1 : 1)



#define kLightSensorDistanceFromCenter 9.5
#define kRobotRadius 13
#define kRobotWidth 16.25
#define kRobotLength 17.25
#define kRotationPointDistanceFromFront kLightSensorDistanceFromCenter - 2


#endif
