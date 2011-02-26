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
#define Accelerometer msensor_S3_3


#include "JoystickDriver.c"
#include "shared/include.c"
#include "Autonomous/include.c"




void initializeRobot()
{
	FieldInit();	//  initialize the map of the field
	SensorsInit();
  MechanismInit();

	PlaySound(soundUpwardTones);
}


void DispenseBatons(int count)
{
  PlaySound(soundFastUpwardTones);

  //  put the elevator up to the top
  motor[Elevator] = kElevatorSpeed;
  while ( !ElevatorIsAtTop() ) {}
  motor[Elevator] = 0;

  //  position slide
  servo[Slide] = kSlideRegularPosition;

  //  kick batons out - go 1 more time than necessary
  for ( int i = 0; i <= count; i++ )
  {
    StartTask(MechanismKickerKick);       //  start kicking
    while ( MechanismKickerIsKicking ) {} //  wait 'til we're done
  }

  //  put the slide out all the way to make sure batons slid off
  servo[Slide] = kSlideMaxPosition;
  wait10Msec(20);
}






#define DEBUG 1




task main()
{
	initializeRobot();

	//  different things to do in autonomous
	bool score_preloads;
	bool balance;
	int preload_count;
	bool get_doubler;
	bool block_center;



	/*
	hogCPU();
	while ( true )
	{
	  int x, y, z;
	  HTACreadX(Accelerometer, y);
	  nxtDisplayCenteredTextLine(1, (string)y);
	}
	releaseCPU();

	//  x = -24 is normal


	positive error means go forward
	//  8 is unbalanced - need to move forward
	*/


	//  FIXME: remove this - prints out line sensor info
	/*
	MechanismElevatorTarget(kElevatorTargetLineFollowing);
	while ( true )
	{
	  nxtDisplayCenteredTextLine(0, (string)LEFT_LIGHT_SENSOR());
	  nxtDisplayCenteredTextLine(1, (string)RIGHT_LIGHT_SENSOR());
	}
	*/


	hogCPU(); //  do this so the waitForStart task doesn't display its trash on the screen while we're trying to get input








	NXTMenu sideMenu;
	sideMenu.title = "Select Side";
	sideMenu.items[0] = "Left";
	sideMenu.items[1] = "Right";
	sideMenu.itemCount = 2;

	int side = NXTShowSelectionMenu(sideMenu);


	//  set the start node
	Node startNode = ( side == 0 ) ? NodeFriendStartSquareLeft : NodeFriendStartSquareRight;
	FieldSetCurrentNode(startNode);

	//	set the start position
	FieldGetNodeLocation(startNode, CurrentRobotPosition.location);
	CurrentRobotPosition.orientation = PI / 2.0;


	//  get doubler?
	NXTMenu autonomousMenu;
	autonomousMenu.title = "Get Doubler?";
	autonomousMenu.items[0] = "No";
	autonomousMenu.items[1] = "Yes";
	autonomousMenu.itemCount = 2;

	get_doubler = NXTShowSelectionMenu(autonomousMenu);



	if ( !get_doubler )
	{
	  autonomousMenu.title = "Score Preloads?";
	  autonomousMenu.items[0] = "No";
	  autonomousMenu.items[1] = "Yes";
	  autonomousMenu.itemCount = 2;

	  score_preloads = NXTShowSelectionMenu(autonomousMenu);


	  if ( score_preloads )
	  {
	    autonomousMenu.title = "How Many?";
	    autonomousMenu.items[0] = "1";
	    autonomousMenu.items[1] = "2";
	    autonomousMenu.items[2] = "3";
	    autonomousMenu.items[3] = "4";
	    autonomousMenu.items[4] = "5";
	    autonomousMenu.itemCount = 5;

	    preload_count = NXTShowSelectionMenu(autonomousMenu) + 1;
	  }

	  autonomousMenu.title = "What Next?";
	  autonomousMenu.items[0] = "Balance";
	  autonomousMenu.items[1] = "Block Center";
	  autonomousMenu.itemCount = 2;

	  if ( NXTShowSelectionMenu(autonomousMenu) == 0 )
	  {
	    balance = true;
	    block_center = false;
	  }
	  else
	  {
	    balance = false;
	    block_center = true;
	  }
	}


	eraseDisplay();
	releaseCPU();	//	'unhog' the CPU so other tasks can run

	/********************   Menu Above  ********************/








	Node targetBridge = (FieldGetCurrentNode() == NodeFriendStartSquareLeft) ? NodeFoeBridgeCenter : NodeFriendBridgeCenter;


//#if DEBUG == 0
	waitForStart(); //  FIXME: uncomment this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#endif

	long startTime = nPgmTime;


  //  get out of the corner, so we don't hit the wall when we move
	bool left = FieldGetCurrentNode() == NodeFriendStartSquareLeft;
	RobotRotateToOrientation(PI / 2.0 + ((left) ? -PI / 6 : PI / 6) );
	RobotMoveDistance(4, false);




	/**********   Preloads   **********/
  if ( score_preloads )
  {
    //  asynchronously raise the elevator to the top  //  FIXME: why don't this work. wtf???
    //MechanismElevatorTargetEncoder = kElevatorMaxEncoder;
    //StartTask(MechanismElevatorTarget, kHighPriority);


	  if ( FieldGetCurrentNode() == NodeFriendStartSquareLeft ) //  left start position;
	  {
      servo[Slide] = kSlideLongPosition;  //  extend the slide out

	    RobotRotateToOrientation(0.13);
	    RobotMoveDistance(17.4, false);
	    RobotRotateToOrientation(-1.5 + (PI / 3.9));


	    //  FIXME: can i remove this????
	    while ( MechanismElevatorIsTargeting ) {} //  wait 'til the elevator reaches the top
	    DispenseBatons(preload_count);



	    //  push the goal out of the way
	    RobotRotateToOrientation(PI / 6.3);
	    RobotMoveDistance(13, false);
	    RobotMoveDistance(-14, false);



	    //  go back to the node
	    Vector location;
	    FieldGetNodeLocation(NodeLine1BottomEnd, location);
	    RobotMoveToLocation(location, false, false);
	    FieldSetCurrentNode(NodeLine1BottomEnd);
	  }
	  else  //  right side
	  {
	    //  go to mobile goal & line up next to it
	    RobotRotateToOrientation(3.0159423);
	    RobotMoveDistance(19, false);


      servo[Slide] = kSlideLongPosition;  //  extend the slide out

	    RobotRotateToOrientation(PI / 3.1);


      //  FIXME: can i remove this???
      while ( MechanismElevatorIsTargeting ) {} //  wait 'til the elevator reaches the top
	    DispenseBatons(preload_count);


	    //  push mobile goal out of the way!!
	    RobotRotateToOrientation(4.6 /6.0 * PI);
	    RobotMoveDistance(13, false);
	    RobotMoveDistance(-14, false);



	    //  go back to the node
	    Vector location;
	    FieldGetNodeLocation(NodeLine3BottomEnd, location);
	    RobotMoveToLocation(location, false, false);
	    FieldSetCurrentNode(NodeLine3BottomEnd);
    }

	  servo[Slide] = kSlideDownPosition;  //  retract the slide to keep it protected

  }/********** End Preloads  **********/






	/**********  Mission   **********/
  if ( get_doubler )
  {

  	//  where we are and where we're going
	  Node src = FieldGetCurrentNode(); //  FIXME: make sure we're actually on the node????
	  Node dest = NodeFriendDispenserCenter;


	  RobotTravelFromNodeToNode(src, NodeLine2Bottom, false);
	  //RobotMoveDistance(-1, false); //  FIXME:
    PlaySound(soundUpwardTones);
    //RobotTravelFromNodeToNode(NodeLine2Bottom, NodeLine2Top, false);
	  //RobotTravelFromNodeToNode(NodeLine2Top, dest, false);
	  //PlaySound(soundUpwardTones);

    RobotRotateToOrientation(PI / 1.9);
    RobotFindWhiteLine();
    RobotFollowWhiteLineForDistance(18, false);

    MechanismElevatorTarget(kElevatorTargetBridgeCrossing);

    RobotMoveDistance(30, false);

    RobotFindWhiteLine();
    RobotFollowWhiteLineToEnd(true);

    while ( true )
    {
      PlaySound(soundBeepBeep);
    }



	  if ( false ) //RobotTravelFromNodeToNode(src, dest, true) )	// go to the dispenser.  avoid enemies
    {
      RobotRotateToOrientation(PI / 2.0); //  turn towards dispenser

      //servo[Gate] = kGateUpPosition;

      //  FIXME: can this be asynchronous???????????????????????????????????????????????
      MechanismElevatorTarget(kElevatorTargetMidDispenser);


      if ( RobotMountCenterDispenser() )	//	get aligned with the dispenser
      {



        //  FIXME: DO WORK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      }


      //servo[Gate] = kGateDownPosition;
    }

    Vector location;
    FieldGetNodeLocation(NodeFriendDispenserCenter, location);
    RobotMoveToLocation(location, true, false);   //  backup to the node


  }
  /**********   End Mission   **********/




  //  FIXME: what is this for??????????????????????????????//
  //  put elevator at bottom
  /*
  motor[Elevator] = -kElevatorSpeed;
  while ( !ElevatorIsAtBottom() ) {}
  motor[Elevator] = 0;
*/




  /**********   Balance   **********/
  if ( balance )
  {
    Node currentID = FieldGetCurrentNode();
    RobotTravelFromNodeToNode(currentID, targetBridge, true);	//	go to the bridge

	  RobotMoveDistance(2 , false);

	  RobotBalance();	//	FIXME: use the accelerometor to balance the bot

  }/**********   End Balance **********/






  /**********   Blocking   **********/
  if ( block_center )
  {
    Node currentID = FieldGetCurrentNode();
    RobotTravelFromNodeToNode(currentID, NodeFoeDispenserCenter, true);
    RobotRotateToOrientation(PI / 2); //  look straight ahead to prep for TeleOp
  }
  /**********   Blocking   **********/

}
