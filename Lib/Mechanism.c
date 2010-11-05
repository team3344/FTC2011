
#ifndef _Mechanism_
#include "Mechanism.h"
#endif










#define kKickerServoDownPosition 250
#define kKickerServoUpPosition 255 - 80
#define kKickerPostDelay 400            //  delay after mechanism kicks

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
  wait1Msec(300);

  _kickingBaton = false;
}









#define kMechanismConveyorFullCycleEncoderCount 2000
#define kMechanismConveyorMotorSpeed 70

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











void MechanismInit()
{
  servo[Kicker] = kKickerServoDownPosition; //  put the kicker down



}
