
#ifndef _Mechanism_
#include "Mechanism.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif







#define kKickerServoDownPosition 30
#define kKickerServoUpPosition 170
#define kKickerPostDelay 550            //  delay after mechanism kicks

task MechanismKickBaton()
{
  MechanismIsKicking = true;

  servo[Kicker] = kKickerServoUpPosition;
  wait1Msec(kKickerPostDelay);
  servo[Kicker] = kKickerServoDownPosition;
  wait1Msec(320);								//	FIXME: is this delay alright

  MechanismIsKicking = false;
}




void MechanismSlideSetPosition(short position)
{
  nxtDisplayCenteredTextLine(1, (string)position);

  //  door
  if ( position == kSlideDownPosition )
  {
    MechanismDoorClose();
  }
  else
  {
    MechanismDoorOpen();
  }


  short value = MIN(position, kSlideMaxPosition);
  value = MAX(value * 1, kSlideMinPosition);



  servo[Slide] = value;
}




#define kDoorClosedPosition 255
#define kDoorOpenPosition 0


void MechanismDoorClose()
{
    servo[Door] = kDoorClosedPosition;
}

void MechanismDoorOpen()
{
    servo[Door] = kDoorOpenPosition;
}






#define kSlidePositionIncrement 1
#define kSlideAdjustmentWait 70


task MechanismSlideIncrementPosition()
{
  MechanismSlideIsMoving = true;

  short pos = servo[Slide];
  MechanismSlideSetPosition(pos + kSlidePositionIncrement);
  wait1Msec(kSlideAdjustmentWait);

  MechanismSlideIsMoving = false;
}

task MechanismSlideDecrementPosition()
{
  MechanismSlideIsMoving = true;

  short pos = servo[Slide];
  MechanismSlideSetPosition(pos - kSlidePositionIncrement);
  wait1Msec(kSlideAdjustmentWait);

  MechanismSlideIsMoving = false;
}




void MechanismInit()
{
  servo[Kicker] = kKickerServoDownPosition; //  put the kicker down

  MechanismSlideSetPosition(kSlideDownPosition);
}
