
#ifndef _Mechanism_
#include "Mechanism.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif







#define kKickerServoDownPosition 250
#define kKickerServoUpPosition 255 - 90
#define kKickerPostDelay 550            //  delay after mechanism kicks

bool _kickingBaton;

bool MechanismIsKicking()
{
  return _kickingBaton;
}

task MechanismKickBaton()
{
  _kickingBaton = true;

  servo[Kicker] = kKickerServoUpPosition;
  wait1Msec(kKickerPostDelay);
  servo[Kicker] = kKickerServoDownPosition;
  wait1Msec(250);								//	FIXME: is this delay alright

  _kickingBaton = false;
}




/*

bool MechanismHasMagnetBaton()
{
	return MagneticSensorMagnetIsPresent();	//	FIXME: fix this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}




#define kIndicatorLightPower 70	//	FIXME: IS THIS GOOD ENOUGH????????????????????????????

void MechanismSetIndicatorLightState(bool turnedOn)
{
	motor[IndicatorLight] = ( turnedOn ) ? kIndicatorLightPower : 0;
}

*/



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









#define kSlideMaxPosition 110
#define kSlideMinPosition 1

#define kSlideDownPosition 0
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


  short value = MIN(position, kSlideMaxPosition);
  value = MAX(value * 1, kSlideMinPosition);



  servo[Slide] = value;
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
