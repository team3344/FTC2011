
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
  servo[Slide] = kSlideDownPosition;
  servo[Gate] = kGateDownPosition;

  //  put stompers in up position
  servo[RightStomper] = kRightStomperUp;
  servo[LeftStomper] = kLeftStomperUp;



  //  calibrate elevator
#if 1
  if ( SMUXiInitialized() ) //  only calibrate elevator if SMUXi are initialized
  {
    motor[Elevator] = -kElevatorSpeed;
    while ( !ElevatorIsAtBottom() ) {}	//	lower the elevator until it hits the bottom
    motor[Elevator] = 0;
    nMotorEncoder[Elevator] = 0;	//	reset the encoder
  }
  else
  {
    while ( true )
    {
      if ( SMUXiInitialized ) break;  //  check once per second
      wait1Msec(1000);
    }
  }
#endif
}



//  FIXME: these values are garbage!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kElevatorInitialAngle asin( (kElevatorArmHeight - kElevatorInitialHeight) / kElevatorArmRadius )
#define kElevatorArmHeight 15	//	height above the ground of the rotation point of the arm
#define kElevatorInitialHeight	//	distance from ground to end or arm radius
#define kToothHeightAboveElevator 1	//	height of the getter's teeth above the end of the arm
#define kElevatorArmRadius 10

float MechanismElevatorCurrentHeight()
{
  int encoder = nMotorEncoder[Elevator];
  float angle = kElevatorInitialAngle + ((encoder / (9 * kTetrixMotorEncoderPointsPerRotation)) * 2 * PI );
  float height = ( kElevatorArmRadius * sin(angle) ) + kElevatorInitialHeight + kToothHeightAboveElevator;
  
  return height;
}



void MechanismSetElevatorHeight(float height)	//	FIXME: recheck this method???
{
	float angle = asin((kElevatorArmHeight - kElevatorInitialHeight - kToothHeightAboveElevator) / kElevatorArmRadius);
	
	int targetEncoder = ( (angle - kElevatorInitialAngle) / ( 2 * PI ) ) * kTetrixMotorEncoderPointsPerRotation * 9;

	if ( height < MechanismElevatorCurrentHeight() )
	{
		while ( nMotorEncoder[Elevator] > targetEncoder && !ElevatorIsAtBottom() ) {} //  go until we're there or we hit the bottom
	}
	else
	{
		while ( nMotorEncoder[Elevator] < targetEncoder && !ElevatorIsAtTop() ) {}  //  go until we're there of we hit the top
	}
	
	
	motor[Elevator] = 0;  //  stop
}
