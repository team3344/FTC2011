
#ifndef _Mechanism_
#include "Mechanism.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif



#define kSlidePositionIncrement 1
#define kSlideAdjustmentWait 70


task MechanismSlideIncrementPosition()
{
  MechanismSlideIsMoving = true;

  short pos = servo[Slide];


  pos += kSlidePositionIncrement;
  if ( pos > kSlideMaxPosition ) pos = kSlideMaxPosition; //  limit position
  servo[Slide] = pos;
  wait1Msec(kSlideAdjustmentWait);

  MechanismSlideIsMoving = false;
}

task MechanismSlideDecrementPosition()
{
  MechanismSlideIsMoving = true;

  short pos = servo[Slide];
  pos -= kSlidePositionIncrement;
  if ( pos < kSlideMinPosition ) pos = kSlideMinPosition;
  servo[Slide] = kSlideMinPosition;
  wait1Msec(kSlideAdjustmentWait);

  MechanismSlideIsMoving = false;
}






void MechanismInit()
{
  AbortIfNoSMUX();


  servo[Slide] = kSlideDownPosition;
  servo[Gate] = kGateDownPosition;

  //  put stompers in up position
  servo[RightStomper] = kRightStomperUp;
  servo[LeftStomper] = kLeftStomperUp;



  //  calibrate elevator
#if 1
  motor[Elevator] = -kElevatorSpeed;
  while ( !ElevatorIsAtBottom() ) {}	//	lower the elevator until it hits the bottom
  motor[Elevator] = 0;
  nMotorEncoder[Elevator] = 0;	//	reset the encoder
#endif
}



//  FIXME: these values are garbage!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kElevatorInitialAngle asin( (kElevatorInitialHeight - kElevatorArmHeight) / kElevatorArmRadius )
#define kElevatorArmHeight 8.25	      //	height above the ground of the rotation point of the arm
#define kElevatorInitialHeight 1.5   //	distance from ground to end or arm radius
#define kToothHeightAboveElevator 1	//	height of the getter's teeth above the end of the arm
#define kElevatorArmRadius 8.75

float MechanismElevatorCurrentHeight()
{
  int encoder = nMotorEncoder[Elevator];
  float angle = kElevatorInitialAngle + ((encoder / (9 * kTetrixMotorEncoderPointsPerRotation)) * 2 * PI );
  float height = ( kElevatorArmRadius * sin(angle) ) + kElevatorArmHeight + kToothHeightAboveElevator;


  nxtDisplayCenteredTextLine(0, (string)encoder);
  nxtDisplayCenteredTextLine(1, (string)angle);
  nxtDisplayCenteredTextLine(2, (string)height);
  nxtDisplayCenteredTextLine(3, (string)kElevatorInitialAngle);
  //wait10Msec(1000);


  return height;
}


#define ElevatorIsSafe() (!ElevatorIsAtTop() && !ElevatorIsAtBottom())
void MechanismElevatorSetHeight(float height)	//	FIXME: recheck this method???
{
	//float angle = asin((kElevatorArmHeight - height - kToothHeightAboveElevator) / -kElevatorArmRadius);

  float angle = asin( (height - kElevatorArmHeight - kToothHeightAboveElevator) / kElevatorArmRadius);

	int targetEncoder = ( (angle - kElevatorInitialAngle) / ( 2 * PI ) ) * kTetrixMotorEncoderPointsPerRotation * 9;


	nMotorEncoderTarget[Elevator] = targetEncoder;

	motor[Elevator] = kElevatorSpeed * SIGN(targetEncoder - nMotorEncoder[Elevator]);

  if ( abs(height - MechanismElevatorCurrentHeight()) < .25 )
  {
    //  don't do anything.  we're basically there
  }
	else if ( height < MechanismElevatorCurrentHeight() )
	{
		while ( nMotorRunState[Elevator] != runStateIdle && !ElevatorIsAtBottom() ) {} //  go until we're there or we hit the bottom
	}
	else
	{
		while ( nMotorRunState[Elevator] != runStateIdle && !ElevatorIsAtTop() ) {}  //  go until we're there of we hit the top
	}


	motor[Elevator] = 0;  //  stop
}
