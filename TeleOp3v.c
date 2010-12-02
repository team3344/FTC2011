#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ElevatorTopStop,     sensorTouch)
#pragma config(Sensor, S3,     SMUX2,               sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX1,               sensorI2CCustom)
#pragma config(Motor,  motorA,          IndicatorLight, tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  motorC,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Elevator,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Kicker,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Gate,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    RightStomper,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    LeftStomper,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//  SMUX1
#define Magnet msensor_S4_4
#define Sonar msensor_S4_3
#define Accelerometer msensor_S4_2


//  SMUX2
#define ElevatorBottomStop msensor_S3_1
#define IR msensor_S3_2
#define LeftLightSensor msensor_S3_3
#define RightLightSensor msensor_S3_4



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////



#include "shared/include.c"
#include "TeleOp/include.c"


void initializeRobot()
{
  //  init smuxi
  HTSMUXinit();
  HTSMUXscanPorts(SMUX1);
  HTSMUXscanPorts(SMUX2);


	AbortIfNoSMUX();

	MechanismInit();

	DrivePowerMultiplier = 1;

	return;
}





void DriveControl(Controller& controller)
{
    //  power
    if ( ControllerButtonIsPressed(controller, ControllerButton1) )
    {
		  DrivePowerMultiplier = kDrivePowerLow;
    }
    else if ( ControllerButtonIsPressed(controller, ControllerButton2) )
    {
		  DrivePowerMultiplier = kDrivePowerNormal;
    }
    else if ( ControllerButtonIsPressed(controller, ControllerButton3) )
    {
		  DrivePowerMultiplier = kDrivePowerHigh;
    }


    if ( ControllerButtonIsPressed(controller, ControllerButtonR1) )
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


bool vibrating = false;
task vibrate()
{
  vibrating = true;

  motor[Elevator] = -20;
  wait10Msec(1);
  motor[Elevator] = 20;
  while ( !ElevatorIsAtTop() ) {}
  motor[Elevator] = 0;

  vibrating = false;
}




void MechanismControl(Controller& controller)
{
    //  slide adjustment
    if ( controller.dPad.x == -1 && !MechanismSlideIsMoving)
    {
		  StartTask(MechanismSlideIncrementPosition);
    }
    else if ( controller.dPad.x == 1 && !MechanismSlideIsMoving )
    {
		  StartTask(MechanismSlideDecrementPosition);
    }



    if ( ControllerButtonIsPressed(controller, ControllerButtonR1) )
    {
      //if ( !vibrating ) StartTask(vibrate);

      servo[Kicker] = kKickerSpeed;

      PlaySoundFile("ChaChing.rso");
    }
    else if ( ControllerButtonIsPressed(controller, ControllerButtonR2) )
    {
      servo[Kicker] = kKickerStopped - kKickerSpeed;
    }
    else
    {
      servo[Kicker] = kKickerStopped;
    }


    if ( !vibrating )
    {
      if ( ControllerButtonIsPressed(controller, ControllerButtonL1) && !ElevatorIsAtTop() )
      {
        motor[Elevator] = kElevatorSpeed;
      }
      else if ( ControllerButtonIsPressed(controller, ControllerButtonL2) && !ElevatorIsAtBottom() )
      {
        motor[Elevator] = -kElevatorSpeed;
      }
      else
      {
        motor[Elevator] = 0;
      }
    }

	//  magnet slide position
	if ( ControllerButtonIsPressed(controller, ControllerButton4) )
	{
		servo[Slide] = kSlideMagnetPosition;
	}

	//  regular slide position
	if ( ControllerButtonIsPressed(controller, ControllerButton2) )
	{
		servo[Slide] = kSlideRegularPosition;
	}

	//  down position
	if ( ControllerButtonIsPressed(controller, ControllerButton3) )
	{
	  servo[Slide] = kSlideDownPosition;
	}

	//  long position
	if ( ControllerButtonIsPressed(controller, ControllerButton1) )
	{
		servo[Slide] = kSlideLongPosition;
	}



	if ( controller.dPad.y == 1 )
	{
	  servo[Gate] = kGateUpPosition;
	}
	else if ( controller.dPad.y == -1 )
	{
	  servo[Gate] = kGateDownPosition;
	}



  /*
  //  trap door on magazine
	if ( controller.dPad.y == -1 )
	{
	  servo[Flap] = kFlapDownPosition;
  }
  else if ( controller.dPad.y == 1 )
  {
    servo[Flap] = kFlapUpPosition;
  }
  else
  {
    servo[Flap] = kFlapFlatPosition;
  }*/


}



task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase


	while (true)
	{
		Controller primary, secondary;
		UpdatePrimaryController(primary);
		UpdateSecondaryController(secondary);

		DriveControl(primary);
		MechanismControl(secondary);


		if ( MagnetBatonPresent )
		{
			motor[IndicatorLight] = 100;  //  turn the light on
		}
		else
		{
			motor[IndicatorLight] = 0;
		}
	}
}
