
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
#endif
}
