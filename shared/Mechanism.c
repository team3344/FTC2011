
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





/*
bool MechanismHasMagnetBaton()
{
	return MagneticSensorMagnetIsPresent();
}
*/


#define kIndicatorLightPower 70	//	FIXME: IS THIS GOOD ENOUGH????????????????????????????

void MechanismSetIndicatorLightState(bool turnedOn)
{
	motor[IndicatorLight] = ( turnedOn ) ? kIndicatorLightPower : 0;
}





#define kMechanismConveyorFullCycleEncoderCount 2500	//	FIXME: this is garbage	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define kMechanismConveyorMotorSpeed 50

bool _conveyorRunning;

bool MechanismConveyorIsRunning()
{
  return _conveyorRunning;
}

task MechanismCycleConveyor()
{
  _conveyorRunning = true;

  nMotorEncoder[Conveyor] = 0;
  motor[Conveyor] = kMechanismConveyorMotorSpeed;
  while ( nMotorEncoder[Conveyor] < kMechanismConveyorFullCycleEncoderCount ) {}
  motor[Conveyor] = 0;

  _conveyorRunning = false;
}









#define kSlideMaxPosition 255
#define kSlideMinPosition 1

#define kSlideDownPosition 100
#define kSlideMagnetPosition 86
#define kSlideRegularPosition 70
#define kSlideLongPosition 95

short MechanismSlideGetPosition()
{
    return servo[Slide];
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
bool _movingSlide;

bool MechanismSlideIsMoving()
{
  return _movingSlide;
}

task MechanismSlideIncrementPosition()
{
  _movingSlide = true;

  short pos = MechanismSlideGetPosition();
  MechanismSlideSetPosition(pos + kSlidePositionIncrement);
  wait1Msec(kSlideAdjustmentWait);

  _movingSlide = false;
}

task MechanismSlideDecrementPosition()
{
  _movingSlide = true;

  short pos = MechanismSlideGetPosition();
  MechanismSlideSetPosition(pos - kSlidePositionIncrement);
  wait1Msec(kSlideAdjustmentWait);

  _movingSlide = false;
}

void MechanismSlideSetRegularPosition()
{
  MechanismSlideSetPosition(kSlideRegularPosition);
}

void MechanismSlideSetMagnetPosition()
{
  MechanismSlideSetPosition(kSlideMagnetPosition);
}



void MechanismSlideSetDownPosition()
{
    MechanismSlideSetPosition(kSlideDownPosition);
}

void MechanismSlideSetLongPosition()
{
  MechanismSlideSetPosition(kSlideLongPosition);
}








void MechanismInit()
{
  servo[Kicker] = kKickerServoDownPosition; //  put the kicker down

  MechanismSlideSetDownPosition();


  _movingSlide = false;

}
