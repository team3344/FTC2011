#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ElevatorBottomStop,     sensorTouch)
#pragma config(Sensor, S3,     SMUX2,               sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX1,               sensorI2CCustom)
#pragma config(Motor,  motorA,          IndicatorLight, tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  motorC,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Elevator,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Intake,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Kicker,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    LeftStomper,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    Flap,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_6,    RightStomper,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//  SMUX1
#define Magnet msensor_S4_3
#define LeftLightSensor msensor_S4_2
#define RightLightSensor msensor_S4_1
#define IR msensor_S4_4


//  SMUX2
#define ElevatorTopStop msensor_S3_1
#define Accelerometer msensor_S3_4


#define DEBUG //  FIXME: remove this!!!




#include "shared/include.c"
#include "TeleOp/include.c"





void initializeRobot()
{
  SensorsInit();
	AbortIfNoSMUX();
	MechanismInit();

	DrivePowerMultiplier = 1;

	return;
}





void DriveControl(Controller& controller)
{
    //  power - hold L1 to go fast, hold L2 to go slow
    if ( ControllerButtonIsPressed(controller, ControllerButtonR1) )
    {
		  DrivePowerMultiplier = kDrivePowerHigh;
    }
    else if ( ControllerButtonIsPressed(controller, ControllerButtonL1) )
    {
		  DrivePowerMultiplier = kDrivePowerLow;
    }
    else
    {
		  DrivePowerMultiplier = kDrivePowerNormal;
    }


    //  hold L2 or R2 to stomp - let go and they go back up
    if ( ControllerButtonIsPressed(controller, ControllerButtonR2) ||
          ControllerButtonIsPressed(controller, ControllerButtonL2) )
    {
      servo[RightStomper] = kRightStomperDown;
      servo[LeftStomper] = kLeftStomperDown;
    }
    else
    {
      servo[RightStomper] = kRightStomperUp;
      servo[LeftStomper] = kLeftStomperUp;
    }


    //  tank drive
    SetMotorPower(Left, controller.leftJoystick.y);
    SetMotorPower(Right, controller.rightJoystick.y);
}



#define kSlideIncrement -1

void MechanismControl(Controller& controller)
{
    //  slide adjustment w/horizontal of DPad
    if ( controller.isFresh )
    {
      if ( controller.dPad.x == -1 ) servo[Slide] += kSlideIncrement;
      else if ( controller.dPad.x == 1 ) servo[Slide] -= kSlideIncrement;
    }



    //  intake
    if ( controller.leftJoystick.y > .25 )
    {
      servo[Intake] = kIntakeReverse;
    }
    else if ( controller.leftJoystick.y < -.25 )
    {
      servo[Intake] = kIntakeOn;
    }
    else
    {
      servo[Intake] = kIntakeOff;
    }





    if ( ControllerButtonIsPressed(controller, ControllerButtonR1) )
    {
      if ( !MechanismKickerIsKicking )
      {
        StartTask(MechanismKickerKick);
        PlaySoundFile("ChaChing.rso");
      }
    }


    //  FIXME: slide positions


#define ABORT_ELEVATOR_TARGET() StopTask(MechanismElevatorTargetTask)


    if ( MechanismElevatorIsTargeting == false )
    {
      if ( ControllerButtonIsPressed(controller, ControllerButton2) )
      {
        ABORT_ELEVATOR_TARGET();
        MechanismElevatorTargetEncoder = kElevatorTargetMidDispenser;
        StartTask(MechanismElevatorTargetTask);
      }

      else if ( ControllerButtonIsPressed(controller, ControllerButton3) )
      {
        ABORT_ELEVATOR_TARGET();
        MechanismElevatorTargetEncoder = kElevatorTargetHighDispenser;
        StartTask(MechanismElevatorTargetTask);
      }
      else if ( ControllerButtonIsPressed(controller, ControllerButton4) )
      {
        ABORT_ELEVATOR_TARGET();
        MechanismElevatorTargetEncoder = kElevatorTargetLineFollowing;
        StartTask(MechanismElevatorTargetTask);
      }
    }



    //  elevator up/down control with L1 & L2
    if ( controller.dPad.y > .5 && !ElevatorIsAtTop() )
    {
      ABORT_ELEVATOR_TARGET();
      motor[Elevator] = kElevatorSpeed;
    }
    else if ( controller.dPad.y < -.5 && !ElevatorIsAtBottom() )
    {
      ABORT_ELEVATOR_TARGET();
      motor[Elevator] = -kElevatorSpeed;
    }
    else if ( !MechanismElevatorIsTargeting ) //  if we're not targeting, turn it off
    {
      motor[Elevator] = 0;
    }


    if ( ControllerButtonIsPressed(controller, ControllerButtonL1) )
    {
      servo[Slide] = kSlideRegularPosition;
    }
    else if ( ControllerButtonIsPressed(controller, ControllerButtonL2) )
    {
      servo[Slide] = kSlideDownPosition;
    }
}



task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase


	//  FIXME: this worked!!!
	//MechanismElevatorTargetEncoder = kElevatorTargetMidDispenser;
	//StartTask(MechanismElevatorTargetTask);
	//wait10Msec(1000);



	//  FIXME: remove below 2 trash lines!!!
	//MechanismElevatorTarget(kElevatorTargetMidDispenser);   //  THIS WORKS FINE
	//wait10Msec(1000);



	while (true)
	{
		Controller primary, secondary;
		UpdatePrimaryController(primary);
		UpdateSecondaryController(secondary);

		if ( primary.isFresh || secondary.isFresh )
		{
		  DriveControl(primary);
		  MechanismControl(secondary);
    }

#ifdef DEBUG
		nxtDisplayCenteredTextLine(0, (string)nMotorEncoder[Elevator]);
    nxtDisplayCenteredTextLine(1, (string)motor[Elevator]);
#endif


		if ( MagnetBatonPresent() )
		{
			motor[IndicatorLight] = 100;  //  turn the light on
		}
		else
		{
			motor[IndicatorLight] = 0;
		}
	}
}
