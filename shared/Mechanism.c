
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

#define kElevatorEncoderTargetTolerance 60


void MechanismElevatorTarget(int targetEncoder)
{
  long endTime = nPgmTime + 3500;  //  3.5 seconds from now

  if ( abs(targetEncoder - nMotorEncoder[Elevator]) < kElevatorEncoderTargetTolerance )
  {
    //  we're basically there, so return
    //PlaySound(soundLowBuzz);
    return;
  }





  //  restrict encoder
  if ( targetEncoder > kElevatorMaxEncoder ) targetEncoder = kElevatorMaxEncoder;



	motor[Elevator] = kElevatorSpeed * SIGN(targetEncoder - nMotorEncoder[Elevator]);



	long error;
	while ( abs( (error = (targetEncoder - nMotorEncoder[Elevator])) ) > kElevatorEncoderTargetTolerance &&
	        nPgmTime < endTime )
	{
	  //  wait

	  if ( abs(error) < 400 ) //  go half speed when we're 400 or less away
	  {
	    motor[Elevator] = SIGN(error) * kElevatorSpeed * .5;
	  }
	}


	if ( nPgmTime > endTime )
	{
	  PlaySound(soundException);  //  it timed out!!
	  PlaySound(soundException);  //
	}


	motor[Elevator] = 0;  //  stop
}


#define ElevatorIsSafe() (!ElevatorIsAtTop() && !ElevatorIsAtBottom())



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
  wait1Msec(650); //  was 850
  servo[Kicker] = kKickerDown;
  wait1Msec(520);

  MechanismKickerIsKicking = false;
}
