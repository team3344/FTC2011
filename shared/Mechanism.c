
#ifndef _Mechanism_
#include "Mechanism.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif



void MechanismInit()
{
  AbortIfNoSMUX();


  servo[Slide] = kSlideDownPosition;
  servo[Flap] = kFlapFlatPosition;

  //  put stompers in up position
  servo[RightStomper] = kRightStomperUp;
  servo[LeftStomper] = kLeftStomperUp;


  servo[Kicker] = kKickerDown;



  //  calibrate elevator
#if 1
  motor[Elevator] = -kElevatorSpeed;
  long time = nPgmTime;
  while ( !ElevatorIsAtBottom() )	//	lower the elevator until it hits the bottom
  {
    if ( nPgmTime > time + 4000 ) //  if it takes longer than 4 seconds, stop so we don't kill it
    {
      PlaySound(soundException);
      PlaySound(soundException);
      PlaySound(soundException);

      break;
    }
  }

  motor[Elevator] = 0;
  nMotorEncoder[Elevator] = 0;	//	reset the encoder
#endif
}

#define kElevatorEncoderTargetTolerance 100


void MechanismElevatorTarget(int targetEncoder)
{
  long endTime = nPgmTime + 3500;  //  3.5 seconds from now

  if ( abs(targetEncoder - nMotorEncoder[Elevator]) < kElevatorEncoderTargetTolerance )
  {
    //  we're basically there, so return
    PlaySound(soundLowBuzz);
    return;
  }


  //  restrict encoder
  if ( targetEncoder > kElevatorMaxEncoder ) targetEncoder = kElevatorMaxEncoder;

	motor[Elevator] = kElevatorSpeed * SIGN(targetEncoder - nMotorEncoder[Elevator]);

  if ( targetEncoder < nMotorEncoder[Elevator] )
	{
		while ( nMotorEncoder[Elevator] > targetEncoder && !ElevatorIsAtBottom() )  //  go until we're there or we hit the bottom
		{
		  if ( nPgmTime > endTime )
	    {
	      PlaySound(soundException);
	      PlaySound(soundException);
	      break;
	    }
		}

		if ( abs(targetEncoder - nMotorEncoder[Elevator]) < 300 )
		{
		  motor[Elevator] = SIGN(motor[Elevator]) * kElevatorSpeed / 2;
		}
	}
	else
	{
		while ( nMotorEncoder[Elevator] < targetEncoder )  //  go until we're there of we hit the top
	  {
	    if ( nPgmTime > endTime )
	    {
	      PlaySound(soundException);
	      PlaySound(soundException);
	      break;
	    }

	    if ( abs(targetEncoder - nMotorEncoder[Elevator]) < 300 )
		  {
		    motor[Elevator] = SIGN(motor[Elevator]) * kElevatorSpeed / 2;
		  }
	  }
  }

	motor[Elevator] = 0;  //  stop
}


#define ElevatorIsSafe() (!ElevatorIsAtTop() && !ElevatorIsAtBottom())

/*
void MechanismElevatorSetHeight(float height)	//	FIXME: recheck this method???
{
	float angle = asin( (height - kElevatorArmHeight - kToothHeightAboveElevator) / kElevatorArmRadius);

	int targetEncoder = ( (angle - kElevatorInitialAngle) / ( 2 * PI ) ) * kTetrixMotorEncoderPointsPerRotation * 9;

	MechanismElevatorTarget(targetEncoder);
}
*/



task MechanismElevatorTargetTask()
{
#ifdef DEBUG
  ++elevatorTaskCount;
#endif

  MechanismElevatorIsTargeting = true;

  MechanismElevatorTarget(MechanismElevatorTargetEncoder);
  motor[Elevator] = 0;  //  turn it off

  MechanismElevatorIsTargeting = false;
}




task MechanismKickerKick()
{
  if ( MechanismKickerIsKicking ) return;
  MechanismKickerIsKicking = true;

  servo[Kicker] = kKickerUp;
  wait1Msec(800);
  servo[Kicker] = kKickerDown;
  wait1Msec(300);

  MechanismKickerIsKicking = false;
}
