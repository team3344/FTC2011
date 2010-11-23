
#ifndef _Mechanism_
#include "Mechanism.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif






void MechanismSlideSetPosition(short position)
{
  nxtDisplayCenteredTextLine(1, (string)position);


  short value = MIN(position, kSlideMaxPosition);
  value = MAX(value * 1, kSlideMinPosition);



  servo[Slide] = value;
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







void MechanismDoorSetPosition(short position)
{
  servo[DoorRight] = position;
}






void MechanismInit()
{

  MechanismSlideSetPosition(kSlideDownPosition);
}
