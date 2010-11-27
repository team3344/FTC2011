
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
  servo[Flap] = kFlapFlatPosition;

  //  put stompers in up position
  servo[RightStomper] = kRightStomperUp;
  servo[LeftStomper] = kLeftStomperUp;




  //  calibrate elevator
#if 0
  if ( SMUXiInitialized() ) //  only calibrate elevator if SMUXi are initialized
  {
    motor[Elevator] = -kElevatorSpeed;
    while ( ElevatorIsAtTop ) {}
    motor[Elevator] = 0;
    nMotorEncoder[Elevator] = 0;
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
#define kElevatorInitialAngle (-PI / 4)
#define kElevatorInitialHeight 2.5
#define kElevatorArmRadius 10

float MechanismElevatorCurrentHeight()
{
  //  FIXME: implement

  int encoder = nMotorEncoder[Elevator];


  //float angle = kElevatorInitialAngle + !!!!!!!!!!!!!!!!!!!
}




void MechanismSetElevatorHeight(float height)
{
  float angle = asin(height - kElevatorInitialHeight);
  int targetEncoder = ( (angle - kElevatorInitialAngle) / ( 2 * PI ) ) * kTetrixMotorEncoderPointsPerRotation * 9;

  if ( height < MechanismElevatorCurrentHeight )
  {
    while ( nMotorEncoder[Elevator] > targetEncoder && !ElevatorIsAtBottom ) {} //  go until we're there or we hit the bottom
  }
  else
  {
    while ( nMotorEncoder[Elevator] < targetEncoder && !ElevatorIsAtTop ) {}  //  go until we're there of we hit the top
  }


  motor[Elevator] = 0;  //  stop

  //  FIXME: try this method!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
