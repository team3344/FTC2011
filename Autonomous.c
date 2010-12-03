#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ElevatorTopStop,     sensorTouch)
#pragma config(Sensor, S3,     SMUX2,               sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX1,               sensorI2CCustom)
#pragma config(Motor,  motorA,          IndicatorLight, tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  motorC,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right,         tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Elevator,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Kicker,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Gate,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    RightStomper,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    LeftStomper,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//  SMUX1
#define Magnet msensor_S4_2
#define LeftLightSensor msensor_S4_3
#define RightLightSensor msensor_S4_4


//  SMUX2 //  FIXME: set port numbers !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define ElevatorBottomStop msensor_S3_1
#define IR msensor_S3_2
#define Sonar msensor_S3_4
#define Accelerometer msensor_S3_2



//#include "JoystickDriver.c"
#include "shared/include.c"
#include "Autonomous/include.c"


void ff2() {}
void ff3() {}




void initializeRobot()
{
	FieldInit();	//  initialize the map of the field
	SensorsInit();
  MechanismInit();

	FTCGetStartPosition();	//	ask the user where the robot is starting

	PlaySound(soundUpwardTones);
}



static bool gettingDoubler;	//	global variable that tells whether or not the GetDoublerBaton task is running

task GetDoublerBaton()
{
	gettingDoubler = true;

	//  where we are and where we're going
	Node dest = NodeFriendDispenserCenter;
	Node src = FieldGetCurrentNode();

	if ( RobotTravelFromNodeToNode(src, dest, true) )	// go to the dispenser.  avoid enemies
  {
    RobotRotateToOrientation(PI); //  turn towards dispenser
    MechanismSetElevatorHeight(kElevatorHeightMidDispenser);  //  get the elevator to the right height

    if ( RobotMountCenterDispenser() )	//	get aligned with the dispenser
    {
	    //  FIXME: get 5 batons
	    //  FIXME: make a mess with the rest
    }





  }

	//	FIXME: backup to node
  //  FIXME: set elevator to reasonable height

	gettingDoubler = false;
}



void GetToBridgeAndBalance()
{
	Node bridgeID = NodeFriendBridgeCenter;	//	FIXME:  id of closest bridge???
	Node currentID = FieldGetCurrentNode();
	RobotTravelFromNodeToNode(currentID, bridgeID, true);	//	go to the bridge

	RobotBalance();	//	use the accelerometor to balance the bot
}




task main()
{
	initializeRobot();

	//waitForStart();	//  FIXME: add this back in!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	long startTime = nPgmTime;


  //
  //
	//	FIXME: score preloads
  //
  //




	StartTask(GetDoublerBaton); //  get doubler & make a mess

	while ( true )
	{
	  int elapsedTime = nPgmTime - startTime;

	  if ( elapsedTime > 25000 )    //  if 25 seconds have passed, abort getting doubler
	  {
	    AbortPathFollowing = true;  //  abort
	    while ( gettingDoubler ) {} //  wait until the task aborts
	    break;                      //  quit looping
	  }

	  if ( !gettingDoubler ) break; //  quit looping if we got the doubler & accomplished the task
	}

	if ( (nPgmTime - startTime ) > 10000 )  //  balance on the bridge if there's more than 10 seconds left
	{
	  GetToBridgeAndBalance();
	}


  ff2();
  ff3();
}
